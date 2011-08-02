#include <iostream>

#include "impl.h"
#include "console.h"

#include "../head/exception.h"

#include "../head/smart_ptr.h"

#include "../head/utility_new.h"



namespace ns_base
{
	static ns_base::Console::Color color_translate(int c)
	{
		switch (c)
		{
		case black:
			return Console::Black;
			break;
		case white:
			return Console::White;
			break;
		case grey:
			return Console::Grey;
			break;
		case light_grey:
			return Console::LightGrey;
			break;
		case blue:
			return Console::Blue;
			break;
		case green:
			return Console::Green;
			break;
		case cyan:
			return Console::Cyan;
			break;
		case red:
			return Console::Red;
			break;
		case purple:
			return Console::Purple;
			break;
		case light_blue:
			return Console::LightBlue;
			break;
		case light_green:
			return Console::LightGreen;
			break;
		case light_cyan:
			return Console::LightCyan;
			break;
		case light_red:
			return Console::LightRed;
			break;
		case light_purple:
			return Console::LightPurple;
			break;
		case orange:
			return Console::Orange;
			break;
		case yellow:
			return Console::Yellow;
			break;
		}
		return Console::Black;
	}

	bool impl_console::alloc()
	{
		return Console::Alloc();
	}

	bool impl_console::free()
	{
		return Console::Free();
	}

	bool impl_console::set_title (const char* title)
	{
		return Console::SetTitle(title);
	}

	bool impl_console::set_size (long columns, long lines)
	{
		return Console::SetSize(columns, lines);
	}

	bool impl_console::get_size (long * pcolumns, long * plines)
	{
		return Console::GetSize((int*)pcolumns, (int*)plines);
	}

	bool impl_console::set_cursor_pos (long x, long y)
	{
		return Console::SetCursorPos(x, y);
	}

	bool impl_console::get_cursor_pos (long * px, long * py)
	{
		return Console::GetCursorPos((int*)px, (int*)py);
	}

	bool impl_console::set_cursor_size (long dwPercentShown, bool bVisible)
	{
		return Console::SetCursorSize(dwPercentShown, bVisible);
	}

	bool impl_console::set_text_color (int fc, int bc)
	{
		return Console::SetTextColor(color_translate(fc), color_translate(bc) );
	}

	bool impl_console::clear()
	{
		return Console::Clear();
	}

	static int _lua_dump(lua_State* st)
	{
		h_console_script* hcs;
		get(hcs);

		if(!lua_isstring(st, -1) )
		{
			return 0;
		}
		const char* str_path = lua_tostring(st, -1);
		hcs->dump(str_path);
			
		char str_tmp[256];
		sprintf(str_tmp, "输出到%s", str_path);
		hcs->output(str_tmp, cyan, white);

		return 0;
	}

	static int _lua_print(lua_State* st)
	{
		h_console_script* hcs;
		get(hcs);

		if(!lua_isstring(st, -1) )
		{
			return 0;
		}
		const char* str_tmp = lua_tostring(st, -1);
		hcs->output(str_tmp, light_grey, black);
		return 0;
	}

	static int _lua_reserve(lua_State* st)
	{
		if(!lua_isnumber(st, -1) )
		{
			return 0;
		}

		h_console_script* hcs;
		get(hcs);

		int num = lua_tointeger(st, -1);

		hcs->set_show_reserve(num);
		return 0;
	}

	static int _lua_clear(lua_State* st)
	{
		if(lua_gettop(st) != 0)
		{
			return 0;
		}

		h_console_script* hcs;
		get(hcs);

		hcs->clear();
		return 0;
	}

	
	static int _lua_help(lua_State* st)
	{
		if(lua_gettop(st) != 0)
		{
			return 0;
		}
		
		h_console_script* hcs;
		get(hcs);

		hcs->output("\
					__dump(<fpath>)\t\n\
					__print(<content>)\t\n\
					__reserve(<line_number>)\t\n\
					__clear()\t\n\
					__help()\t\n", light_grey, black);
		
		return 0;
	}


	h_impl_console_script::~h_impl_console_script()
	{	
		//if(m_current != m_internal)
		//{
		//	m_current->release();
		//}
		//if(m_internal) m_internal->release();
		
		m_current = 0;
		m_internal = 0;

		if(m_thread_handle) WaitForSingleObject(m_thread_handle, INFINITE);
	}

	void h_impl_console_script::init()
	{
		if(!m_bfirst) return;

		m_bfirst = false;
		
		h_script* hs;
		get(hs);

		m_internal = hs->create_lua();
		m_current = m_internal;
		
		//注册
		set_lua(m_internal);
	}

	i_lua* h_impl_console_script::get_lua()
	{
		init();
		return m_current;
	}

	void h_impl_console_script::set_lua(i_lua* cur)
	{
		init();
		if(m_current != m_internal)
		{
			m_current->release();
		}
		if(cur != m_internal)
		{
			cur->add_ref();
		}
		m_current = cur;
		m_current->reg_func("__dump", &_lua_dump);
		m_current->reg_func("__print", &_lua_print);
		m_current->reg_func("__reserve", &_lua_reserve);
		m_current->reg_func("__clear", &_lua_clear);
		m_current->reg_func("__help", &_lua_help);
	}

	void h_impl_console_script::reset_lua()
	{
		init();
		set_lua(m_internal);
	}

	
	//线程1负责接受输入
	//线程2负责输入输出的处理
	//有输入时, 将它传入线程3等待处理, 这段时间不接受输入
	//有输出时, 显示出来并重新定位输入位置
	void h_impl_console_script::wait_for_input()
	{
		init();
		if(m_str_cmd != "")//还未完成处理
		{
			Sleep(100);
			return;
		}

		//wait for command input
		std::string strLine;
		std::string strSentence;

		while(1)
		{
			getline(std::cin, strLine) ;
			strSentence += strLine;
			//shift完成输入
			if(((GetKeyState(VK_SHIFT) & 0xff00) != 0) )
			{	
				h_console_script* hcs; 
				get(hcs);

				h_impl_console_script* hics = (h_impl_console_script*)hcs;
				hics->m_str_cmd = strSentence;
				break;
			}
		}
	}


	DWORD WINAPI input_thread(PVOID pParam)
	{
		h_console_script* hcs; 
		get(hcs);

		h_impl_console_script* hics = (h_impl_console_script*)hcs;

		while(1)
		{
			//等待输入
			hics->wait_for_input();
		}

		return 0;
	}


	//进入输出循环
	void h_impl_console_script::entry_thread()
	{	
		init();
		m_thread_handle = CreateThread(0, 0, &input_thread, 0, 0, 0);
		format_output();
	}

	void h_impl_console_script::run_once()
	{
		init();
		//处理m_str_cmd
		if(m_str_cmd != "")
		{
			//写入
			st_console_item item;
			item.m_fc = white;
			item.m_bc = black;
			item.m_input = true;
			item.m_item = m_str_cmd;

			m_items.push_back(item);
			int sz = m_items.size();
			if(sz > m_dump_sz)
			{	
				m_items.pop_front();
			}

			format_output();

			try
			{
				m_current->load_string(m_str_cmd.c_str() );
				m_current->do_script();

			}
			catch(ns_common::st_exception& e)
			{
				output(e.what(), light_red, black);
			}

			h_console_script* hcs;
			get(hcs);
			h_impl_console_script* hics = (h_impl_console_script*)hcs;
			hics->m_str_cmd = "";//输入重置
		}
	}

	//
	void h_impl_console_script::dump(const char* path)
	{
		init();
		h_filesystem* hf;
		get(hf);

		ns_common::smart_ptr<i_write_file> fout = hf->create_write_file(path);
		if(!fout) RAISE_EXCEPTION("");

		static std::string str_input = "<<< ";
		static std::string str_output = ">>> ";
		for(size_t i = 0; i<m_items.size(); ++i)
		{
			st_console_item& item = m_items[i];
			if(item.m_input)
				fout->write(str_input.c_str(), str_input.size() );
			else
				fout->write(str_output.c_str(), str_output.size() );
			fout->write(item.m_item.c_str(), item.m_item.size() );
			fout->write("\n", 1);
		}

	}
	//输出
	void h_impl_console_script::output(const char* content, int fc, int bc)
	{
		init();
		st_console_item item;
		item.m_fc = fc;
		item.m_bc = bc;
		item.m_input = false;
		item.m_item = content;

		m_items.push_back(item);
		int sz = m_items.size();
		if(sz > m_dump_sz)
		{	
			m_items.pop_front();
		}

		format_output();
		m_str_cmd = "";//输入重置
	}


	//格式化输出
	void h_impl_console_script::format_output()
	{
		init();
		h_console* hc;
		get(hc);

		//清屏
		system("cls");
		int sz = m_items.size();
		
		//最后要show的item
		int idx = sz-m_show_sz;
		if(idx<0) idx = 0;

		for(size_t i = idx; i<sz; ++i)
		{
			st_console_item& item = m_items[i];
			
			//输入
			if(item.m_input)
			{
				hc->set_text_color(light_green);
				printf("<<< ");
				hc->set_text_color(item.m_fc, item.m_bc);
				printf(item.m_item.c_str() );
				printf("\n" );
			}
			else//输出
			{
				hc->set_text_color(yellow);
				printf(">>> ");
				hc->set_text_color(item.m_fc, item.m_bc);
				printf(item.m_item.c_str() );
				printf("\n" );
			}
		}

		if(m_input_stat)
		{
			hc->set_text_color(light_green);
			printf("<<< ");
			hc->set_text_color(white);
		}
	}

	void h_impl_console_script::clear()
	{
		h_console* hc;
		get(hc);

		//清屏
		system("cls");
		this->m_items.clear();
		hc->set_text_color(light_green);
		printf("<<< ");
		hc->set_text_color(white);
	}

	void h_impl_console_script::release()
	{
		if(m_current != m_internal)
		{
			m_current->release();
		}
		if(m_internal) m_internal->release();
		m_current = 0;
		m_internal = 0;
	}
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}


#include "../head/M_interface.h"

M_IMPL(ns_base::h_console, ns_base::impl_console);//2. 接口实现

namespace{
	M_IMPL(ns_base::h_console_script, ns_base::h_impl_console_script);//2. 接口实现
}
M_OPEN();//3. 模块建立


