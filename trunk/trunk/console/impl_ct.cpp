#include <iostream>

#include "../head/exception.h"
#include "../head/smart_ptr.h"

#include "impl_ct.h"
#include "console.h"




#include "../head/utility_new.h"



namespace ns_base
{
	h_impl_console_script_ct::~h_impl_console_script_ct()
	{	
		//if(m_current != m_internal)
		//{
		//	m_current->release();
		//}
		//if(m_internal) m_internal->release();

		if(m_thread_handle) WaitForSingleObject(m_thread_handle, INFINITE);
	}

	void h_impl_console_script_ct::init()
	{
		if(!m_bfirst) return;

		m_bfirst = false;
	}

	//线程1负责接受输入
	//线程2负责输入输出的处理
	//有输入时, 将它传入线程3等待处理, 这段时间不接受输入
	//有输出时, 显示出来并重新定位输入位置
	void h_impl_console_script_ct::wait_for_input()
	{
		init();
		if(m_str_cmd != "")//还未完成处理,TODO,线程安全?
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
				m_str_cmd = strSentence;
				break;
			}
		}
	}


	static DWORD WINAPI input_thread(PVOID pParam)
	{
		h_console_script_ct* hcs; 
		get(hcs);

		h_impl_console_script_ct* hics = (h_impl_console_script_ct*)hcs;

		while(1)
		{
			//等待输入
			hics->wait_for_input();
		}

		return 0;
	}


	//进入输出循环
	void h_impl_console_script_ct::entry_thread()
	{	
		init();
		m_thread_handle = CreateThread(0, 0, &input_thread, 0, 0, 0);
		format_output();
	}

	void h_impl_console_script_ct::run_once()
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
			
			bool ret = m_ct->load_string(m_str_cmd.c_str() );
			if(!ret)
			{
				output(m_ct->get_last_error(), light_red, black);
			}
			else
			{
				ret = m_ct->run();
				if(!ret)//运行时错误
				{
					output(m_ct->get_last_error(), light_red, black);
				}
			}

			h_console_script_ct* hcs;
			get(hcs);
			h_impl_console_script_ct* hics = (h_impl_console_script_ct*)hcs;
			hics->m_str_cmd = "";//输入重置
		}
	}

	//
	void h_impl_console_script_ct::dump(const char* path)
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
	void h_impl_console_script_ct::output(const char* content, int fc, int bc)
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
	void h_impl_console_script_ct::format_output()
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

	void h_impl_console_script_ct::clear()
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

	void h_impl_console_script_ct::release()
	{
		//if(m_current != m_internal)
		//{
		//	m_current->release();
		//}
		//if(m_internal) m_internal->release();
		//m_current = 0;
		//m_internal = 0;
	}
}

#include "../head/M_interface.h"

namespace{
	M_IMPL(ns_base::h_console_script_ct, ns_base::h_impl_console_script_ct);//2. 接口实现
}
//M_OPEN();//3. 模块建立


