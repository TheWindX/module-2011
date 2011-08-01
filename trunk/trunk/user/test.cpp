// test1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../filesystem/interface.h"
#include "../data/interface.h"
#include "../compress/interface.h"
#include "../windows/interface.h"

#include "../head/smart_ptr.h"
#include "../head/exception.h"


int test1(int argc, char** argv)
{	
	using namespace ns_common;
	using namespace ns_base;
	
	h_filesystem* p_fs;//接口指针，不需要释放
	ns_base::get(p_fs);
	
	smart_ptr<i_path> p_path = p_fs->create_path();

	std::string str_path;
	str_path = p_fs->create_work_directory();
	str_path = p_path->system_complete(str_path.c_str() );

	
	const char* psz_path = p_path->first(str_path.c_str() );
	for(;psz_path;psz_path = p_path->next() )
	{
		if(p_path->is_directory(psz_path) )
			std::cout<<"dir:"<<std::string(psz_path)<<std::endl;
		else
		{

			smart_ptr<i_read_file> p_file = p_fs->create_read_file(psz_path );
			size_t sz = p_file->size();
			std::cout<<"file:"<<str_path<<"	sz:"<<sz<<std::endl;
		}
	}
	
	

	h_data* p_data;//接口指针，不需要释放
	ns_base::get(p_data);

	smart_ptr<i_hash> h = p_data->create_hasher();
	std::cout<<h->get_value()<<std::endl;
	h->process_long(1000);
	std::cout<<h->get_value()<<std::endl;



	smart_ptr<i_vector> p_vec = p_data->create_vector();

	struct st_cmp1
	{
		static bool cmp(void* l, void* r)
		{
			return *(std::string*)l<*(std::string*)r;
		}
	};

	p_vec->s_cmp += &st_cmp1::cmp;


	std::string a("32341234");
	std::string b("22341234");
	std::string c("3");
	std::string d("2341234");
	std::string e("02341234");
	std::string f("80");
	p_vec->push(&a);
	p_vec->push(&b);
	p_vec->push(&c);
	p_vec->push(&d);
	p_vec->push(&e);
	p_vec->push(&f);
	
	p_vec->sort();
	
	for(void* ret = p_vec->first(); ret; ret = p_vec->next() )
	{
		std::cout<<*(std::string*)ret<<std::endl;
	}
	std::string g("2341234");
	long idx = p_vec->lower_bound(&g);
	if(idx != -1)
	{
		std::cout<<*(std::string*)p_vec->get_at(idx)<<std::endl;
	}


	smart_ptr<i_map> m = p_data->create_map();

	struct st_cmp2
	{
		static bool cmp(void* l, void* r)
		{
			return *(int*)l>*(int*)r;
		}
	};
	m->s_cmp += &st_cmp2::cmp;

	int i1 = 1; int i2 = 2; int i3 = 333; int i4 = 44; int i5 = 5;

	m->insert(&i4, &i4);
	m->insert(&i2, &i4);
	m->insert(&i3, &i1);
	m->insert(&i1, &i3);

	void* k = m->first();
	for(; k; k = m->next() )
	{
		std::cout<<"key:"<<*(int*)k<<std::endl;
		std::cout<<"value:"<<*(int*)m->get_value()<<std::endl<<std::endl;
	}

	if(m->find_key(&i5) )
	{
		std::cout<<"get_value:"<<*(int*)m->get_value()<<std::endl;
	}
	return 0;
}


#include "../head/utility_new.h"


int test2(int argc, char** argv)
{	
	detect_memory_leaks(true);
	using namespace ns_common;
	using namespace ns_base;
	
	h_filesystem* p_fs;
	ns_base::get(p_fs);


	h_compress* p_comp;
	ns_base::get(p_comp);

	smart_ptr<i_read_file> p_file = p_fs->create_read_file("d:\\frame\\Package\\moduler\\user\\复件 user.vcproj");

	smart_ptr<ns_base::i_buffer> p_buff = p_file->read_all();
	
	ns_base::i_buffer* p_buff1 = p_comp->compress(ns_base::e_zlib, (const char*)p_buff->ptr(), p_buff->size(), p_buff->size() );

	smart_ptr<i_write_file> p_file1 = p_fs->create_write_file("d:\\frame\\Package\\moduler\\user\\user.vcproj.zlib");

	p_file1->write(p_buff1->ptr(), p_buff1->size() );
	return 0;
}

int test3(int argc, char** argv)
{	
	using namespace ns_common;
	using namespace ns_base;
	
	h_filesystem* fs;
	ns_base::get(fs);

	try
	{
		fs->create_work_directory();
	}
	catch(int err)
	{
		std::cout<<err<<std::endl;
	}
	

	return 0;
}

#include "../driver/interface.h"
struct runner1
{
	size_t m_counter;
	void run_once()
	{
		using namespace ns_base;
		h_driver* p_drv;
		ns_base::get(p_drv);
		std::cout<<"delta_time"<<p_drv->get_delta_ms()<<std::endl;
		if(m_counter>10)
		{
			p_drv->exit();
		}
		for(size_t i = 0; i<10000000; ++i)
		{
			float v = sinf(i)/1234.12341;
			float v1 = sinf(i)/i;
			v+=v/v1;
		}
		m_counter++;
		std::cout<<m_counter<<std::endl;
		

	}

	runner1():m_counter(0){};
};

#include "../console/interface.h"


int test4(int argc, char** argv)
{	
	using namespace ns_common;
	using namespace ns_base;
	
	h_driver* p_drv;
	ns_base::get(p_drv);
	

	h_console* p_console;
	ns_base::get(p_console);
	//p_console->alloc();
	p_console->set_size(2, 2);
	p_console->set_text_color(ns_base::light_blue, ns_base::light_red);

	runner1 r;
	p_drv->get_on_delegate(2) += std::make_pair(&r, &runner1::run_once);

	p_drv->run();
	

	return 0;
}

#include "../datetime/interface.h"
int test5(int argc, char** argv)
{	
	using namespace ns_common;
	using namespace ns_base;
	
	h_datetime* dt;
	ns_base::get(dt);
	std::cout<<dt->now_gregorian_format("%Y年_%h小时_%m分钟_%s秒")<<std::endl;
	std::cout<<dt->now_local_format("%Y年_%h小时_%m分钟_%s秒")<<std::endl;
	return 0;
}


int test6(int argc, char** argv)
{	
	using namespace ns_common;
	using namespace ns_base;
	
	h_data* id;
	ns_base::get(id );
	smart_ptr<i_heap> p_heap = id->create_heap();
	int i1 = 13;
	int i2 = 32;
	int i3 = 13;
	int i4 = 11;
	int i5 = 42;
	int i6 = 52;
	int i7 = 92;
	struct st_cmp
	{
		static bool cmp(void* l, void* r)
		{
			return *(int*)l<*(int*)r;
			if(*(int*)l<*(int*)r)
			{printf("%d cmp %d true\n", *(int*)l, *(int*)r);return true;}
			else
			{printf("%d cmp %d false\n", *(int*)l, *(int*)r);return false;}
		}
	};
	p_heap->s_cmp += &st_cmp::cmp;

	p_heap->push(&i1);
	p_heap->push(&i2);
	p_heap->push(&i3);
	p_heap->push(&i4);
	p_heap->push(&i5);
	p_heap->push(&i6);
	p_heap->push(&i7);
	std::cout<<*(int*)p_heap->top()<<std::endl;
	p_heap->pop();std::cout<<*(int*)p_heap->top()<<std::endl;
	p_heap->pop();std::cout<<*(int*)p_heap->top()<<std::endl;
	p_heap->pop();std::cout<<*(int*)p_heap->top()<<std::endl;
	p_heap->pop();std::cout<<*(int*)p_heap->top()<<std::endl;
	p_heap->pop();std::cout<<*(int*)p_heap->top()<<std::endl;
	p_heap->pop();std::cout<<*(int*)p_heap->top()<<std::endl;
	

	return 0;
}


int test7(int argc, char** argv)
{	
	using namespace ns_base;
	using ns_common::smart_ptr;

	h_driver* p_drv;
	ns_base::get(p_drv);


	struct st_evt
	{
		static void report(long now, long last)
		{
			std::cout<<"time is fire:"<<now<<"\t"<<last<<std::endl;
			h_driver* p_drv;
			ns_base::get(p_drv);
		}
	};
	smart_ptr<i_timer> t = p_drv->create_timer();
	handler<st_time_evt> evt = t->get_evt(1000);
	evt.get()->s_evt += &st_evt::report;

	evt = t->get_evt(1200);
	evt.get()->s_evt += &st_evt::report;

	evt = t->get_evt(80);
	evt.get()->s_evt += &st_evt::report;

	evt = t->get_evt(180);
	evt.get()->s_evt += &st_evt::report;

	evt = t->get_evt(2280);
	evt.get()->s_evt += &st_evt::report;


	p_drv->reset();
	while(1)
	{
		p_drv->run_once();
	}
	return 0;
}


#include "../log/interface.h"

int test8(int argc, char** argv)
{
	ns_base::h_logger* p_log;
	ns_base::get(p_log);
	
	p_log->set_console_lv("abcd", ns_base::e_error);
	p_log->set_console_format("abcd", "%level:%time,%name,%content");
	p_log->write("abcd", ns_base::e_fatal, "这是一条log");
	return 0;
}

void test_proxy()
{
	test8(0, 0);
}

int test9(int argc, char** argv)
{
	struct st_scope
	{
		static void pre_1()
		{
			ns_base::h_windows* p_handle = 0;
			ns_base::get(p_handle);
			ns_base::i_window* p_win = p_handle->create_window(0, 100, 100, 256, 256, "lala");
			ns_base::i_window* p_win2 = p_handle->create_window(p_win, 100, 100, 256, 256, "asdf");
			ns_base::i_window* p_win3 = p_handle->create_window(p_win2, 100, 100, 256, 256, "asdf1");
			
		}

		static void on_1()
		{
			ns_base::h_windows* p_handle = 0;
			ns_base::get(p_handle);
			if(!p_handle->run_once() )
			{
				ns_base::h_driver* p_drv;
				ns_base::get(p_drv);
				p_drv->exit();
			}
		}
	};
	ns_base::h_driver* g_drv;
	ns_base::get(g_drv);
	g_drv->get_pre_delegate(2) += &st_scope::pre_1;
	g_drv->get_on_delegate(2) += &st_scope::on_1;

	g_drv->run();
	
	return 0;
}


int test10(int argc, char** argv)
{
	struct st_scope
	{
		static void on_move(ns_base::i_window* win, long x, long y)
		{
			std::cout<<win<<std::endl;
			std::cout<<"x:"<<x<<std::endl;
			std::cout<<"y:"<<y<<std::endl<<std::endl;
		}
		static void on_erase(ns_base::i_window* win)
		{

		}
		static void on_key(ns_base::i_window* win, long key)
		{
			if(key == VK_F1)
			{
				std::cout<<win<<std::endl;
				std::cout<<key<<std::endl<<std::endl;
			}
		}
		static void on_char(ns_base::i_window* win, char key)
		{
			if(key == 'a')
			{
				std::cout<<win<<std::endl;
				std::cout<<'a'<<std::endl<<std::endl;
			}
		}
		static void on_enter(ns_base::i_window* win)
		{
			std::cout<<win<<"enter"<<std::endl;
		}
		static void on_leave(ns_base::i_window* win)
		{
			std::cout<<win<<"leave"<<std::endl;
		}
		static void pre_1()
		{
			ns_base::h_windows* p_handle = 0;
			ns_base::get(p_handle);
			ns_base::i_window* p_win = p_handle->create_window(0, 100, 100, 1024, 768, "lala");
			ns_base::i_window* p_win2 = p_handle->create_window(p_win, 100, 100, 256, 256, "asdf");
			ns_base::i_window* p_win3 = p_handle->create_window(p_win2, 100, 100, 256, 256, "asdf1");
			
			
			p_win->get_GDI()->draw_rect(true, 0xffff0000, 0, 0, 256, 256);
			p_win->get_GDI()->draw_text("lalaasdfasdf", "华文行楷", 24, 0xff000000, 0, 0);
			p_win2->get_GDI()->draw_rect(true, 0x3300ff00, 0, 0, 256, 256);
			p_win3->get_GDI()->draw_rect(true, 0xff0000ff, 0, 0, 256, 256);
			
			//p_win->s_on_mouse_move += &on_move;
			//p_win2->s_on_mouse_move += &on_move;
			//p_win3->s_on_mouse_move += &on_move;
			//p_win->s_on_erase += &on_erase;
			//p_win->s_on_key_down += &on_key;
			//p_win->s_on_char += &on_char;
			//p_win->s_on_enter += &on_enter;
			//p_win->s_on_leave += &on_leave;
		}

		static void on_1()
		{
			ns_base::h_windows* p_handle = 0;
			ns_base::get(p_handle);
			if(!p_handle->run_once() )
			{
				ns_base::h_driver* p_drv;
				ns_base::get(p_drv);
				p_drv->exit();
			}
		}
	};
	ns_base::h_driver* g_drv;
	ns_base::get(g_drv);
	g_drv->get_pre_delegate(2) += &st_scope::pre_1;
	g_drv->get_on_delegate(2) += &st_scope::on_1;

	g_drv->run();

	return 0;
}


struct st_scope
{
	ns_base::i_window* m_win;
	int m_x, m_y;
	i_image* m_img;
	st_scope():m_x(0),m_y(0),m_img(0){};
	~st_scope()
	{
		if(m_img)
		{
			m_img->release();
		}
	}
	void on_key(ns_base::i_window* win, long key)
	{
		if(key == VK_LEFT)
		{
			m_x -= 5;
		}
		else if(key == VK_RIGHT)
		{
			m_x += 5;
		}
		else if(key == VK_UP)
		{
			m_y -= 5;
		}
		else if(key == VK_DOWN)
		{
			m_y += 5;
		}
	}
	void erase(i_window*)
	{

	}
	void pre_1()
	{
		ns_base::h_windows* p_handle = 0;
		ns_base::get(p_handle);
		m_win = p_handle->create_window(0, 100, 100, 512, 512, "lala");
		m_win->s_on_key_down += std::make_pair(this, &st_scope::on_key);
		m_win->s_on_erase += std::make_pair(this, &st_scope::erase); 
		ns_base::h_image* p_img;
		ns_base::get(p_img);
		m_img = p_img->create_from_file("bmp1.bmp", ns_base::e_bmp);
		
	}
	void on_1()
	{
		ns_base::h_windows* p_handle = 0;
		ns_base::get(p_handle);
		m_win->get_GDI()->begin_draw(0xff000000);
		m_win->get_GDI()->draw_rect(true, 0xffff0000, m_x, m_y, 25, 25);
		m_win->get_GDI()->draw_image(m_img, m_x, m_y+100);
		
		ns_base::h_driver* p_driver = 0;
		ns_base::get(p_driver);
		long fps = p_driver->get_fps();
		char str_fps[256];
		sprintf(str_fps, "帧数:%6.2d", fps);
		m_win->get_GDI()->draw_text(str_fps, "微软雅黑", 24, 0xffff0000, 20, 20);

		m_win->get_GDI()->end_draw();
		if(!p_handle->run_once() )
		{	
			ns_base::h_driver* p_drv;
			ns_base::get(p_drv);
			p_drv->exit();
		}
	}
};

int test11(int argc, char** argv)
{
	st_scope scope;
	ns_base::h_driver* g_drv;
	ns_base::get(g_drv);
	g_drv->get_pre_delegate(2) += std::make_pair(&scope, &st_scope::pre_1);
	g_drv->get_on_delegate(2) += std::make_pair(&scope, &st_scope::on_1);

	g_drv->run();
	return 0;
}

#include "../system/interface.h"

int test12(int argc, char** argv)
{
	using namespace ns_base;

	h_system* hs;
	get(hs);
	
	i_font_info* p_font_info = hs->create_font_info(ANSI_CHARSET);
	
	bool valid = p_font_info->first();
	while(valid)
	{
		std::cout<<p_font_info->get_name()<<" "<<p_font_info->get_type()<<std::endl;
		valid = p_font_info->next();
	}

	p_font_info->release();
	return 0;		
}

int test13(int argc, char** argv)
{
	using namespace ns_base;

	h_system* hs;
	get(hs);

	try
	{
		i_os_info* os = hs->create_os_info();
		std::cout<<os->get_build_number();
		os->release();
		return 0;		
	}
	catch(ns_common::st_exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}


int test14(int argc, char** argv)
{
	using namespace ns_base;

	h_data* hd;
	get(hd);
	i_md5* md5 = hd->create_md5();
	std::cout<<md5->process_buff2str("asdf",4);
	md5->release();
	return 0;
}


struct st_test15
{
	i_window* w1;
	i_window* w2;
	i_window* w3;

	void on_drop_files(i_window* pw, i_drop_files* pd)
	{
		const char* fname = pd->first();
		while(fname)
		{
			std::cout<<"accept file:"<<fname<<std::endl;
			fname = pd->next();
		}
	}

	void on_erase(i_window*)
	{

	}
	void on_pre()
	{
		using namespace ns_base;
		h_windows* hw; get(hw);
		st_window_style style;
		//style.m_show = false;
		//style.m_layered = true;
		//style.m_bar = true;
		//style.m_as_tool = true;
		
		w1 = hw->create_window(0, 100, 100, 1024, 128, "test15_a", &style);
		
		//w1->set_bar(false);
		

		h_image* hi;
		get(hi);
		i_image* img = hi->create_from_file("bmp1.bmp", e_bmp);
		w1->init_GDI();
		//w1->get_GDI()->push_transform(0, 0, 2);
		w1->get_GDI()->draw_text("世界在头脑中", "微软雅黑", 24, 0xffff0000, 0, 0);
		//w1->get_GDI()->push_clip(1, 1, 15, 15);
		w1->get_GDI()->draw_image(img, 0, 0);
		w1->get_GDI()->end_draw();
		//w1->s_on_erase += std::make_pair(this, &st_test15::on_erase );
		//w1->update_layered();

		////w2 = hw->create_window(w1, 20, 20, 100, 100, "");
		//w3 = hw->create_window(0, 500, 20, 256, 256, "test15_b");
		//
		//h_logger* hl; get(hl);
		//hl->console_on("log", false);
		//hl->file_on("log", true);
		//hl->write("log", e_info, "on_pre done");
		//w2->draw_rect(true, 0xff330000, 0, 0, 100, 100);
		//w2->end_draw();
		//w2->s_drop_files += std::make_pair(this, &st_test15::on_drop_files);
	}

	void on_run()
	{	
		//using namespace ns_base;
		h_windows* hw; get(hw);
		
		h_driver* hd; get(hd);


		//if(hd->get_system_ms() >= 5000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w3->set_bar(false);
		//		w1->set_bar(false);
		//		w3->init_GDI();
		//		w3->get_GDI()->draw_rect(true, 0xff0000ff, 0, 0, 256, 256);
		//		w1->get_GDI()->draw_rect(true, 0xffff0000, 0, 0, 256, 256);
		//	}
		//}

		//if(hd->get_system_ms() >= 4000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w3->set_as_tool(true);
		//	}
		//}

		//if(hd->get_system_ms() >= 8000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w1->set_layered(false);
		//	}
		//}
		//h_logger* hl; get(hl);
		//hl->write("log", e_info, "on_run once");

		//if(hd->get_system_ms() == 3000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w1->set_size(100, 200);
		//	}
		//}

		//if(hd->get_system_ms() == 3000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w1->set_sizable(false);
		//	}
		//}

		//if(hd->get_system_ms() == 3000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w2->set_enable(false);
		//	}
		//}

		//if(hd->get_system_ms() == 2000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w2->set_as_child(w3);
		//	}
		//}

		//if(hd->get_system_ms() > 1000)
		//{
		//	static bool enter = false;
		//	if(!enter)
		//	{
		//		enter = true;
		//		w2->set_accept_file(true);
		//	}
		//}

		if(!hw->run_once() )
		{
			ns_base::h_driver* hd;
			ns_base::get(hd);
			hd->exit();
		}
	}
	void on_post()
	{
		//post 这里不应该用log, 有finalize之后
		//h_logger* hl; get(hl);
		//hl->write("log", e_info, "on_post done");
	}


};
int test15(int argc, char** argv)
{
	using namespace ns_base;
	
	h_driver* hd;
	get(hd);

	st_test15 ins;
	hd->get_pre_delegate(1)  += std::make_pair(&ins, &st_test15::on_pre );
	hd->get_on_delegate(1) += std::make_pair(&ins, &st_test15::on_run );
	hd->get_post_delegate(1) += std::make_pair(&ins, &st_test15::on_post );

	hd->run();
	return 0;
}

struct st_test16
{
	i_window* w1;
	i_static* w2;
	i_button* w3;

	void on_enter(i_window* w)
	{
		std::cout<<w->get_HWND()<<" enter"<<std::endl;
	}

	void on_leave(i_window* w)
	{
		std::cout<<w->get_HWND()<<" leave"<<std::endl;
	}
	void on_key(i_window* w, long k)
	{
		std::cout<<w->get_HWND()<<" on_key"<<k<<std::endl;
	}

	void on_lclick(i_window* w, long k, long d)
	{
		std::cout<<w->get_HWND()<<" on_lclick"<<k<<std::endl;
	}

	void on_push_button(i_button* b)
	{
		static int i = 100;
		char buff[256];
		itoa(i++, buff, 10);
		b->set_text(buff);
	}


	void on_pre()
	{
		using namespace ns_base;
		h_windows* hw; get(hw);
		st_window_style style;
		//style.m_layered = true;
		style.m_bar = false;
		w1 = hw->create_window(0, 100, 100, 1024, 128, "test16_a", &style);
		w1->init_GDI();
		w1->get_GDI()->begin_draw(0x00000000);
		w1->get_GDI()->push_transform(0, 0, 3);
		w1->get_GDI()->draw_text("世界是不平的", "微软雅黑", 24, 0xffff8800, 0, 0);
		w1->get_GDI()->end_draw();
		w1->set_layered_alpha(100);
		w2 = hw->create_static(w1, 100, 100, 64, 64, "事实");
		//w2->get_window()->s_on_enter += std::make_pair(this, st_test16::on_enter);
		//w2->get_window()->s_on_ldown += std::make_pair(this, st_test16::on_lclick);
		
		//w1->s_on_key_down += std::make_pair(this, st_test16::on_key);
		//w1->update_layered();
		//i_static* s1 = hw->create_static(w1, 20, 20, 80, 80, "这是一个static");
		//i_edit* e1 = hw->create_edit(w1, 180, 20, 100, 30, "这是一个editor");
		

		w1->s_on_leave += std::make_pair(this, st_test16::on_leave);
		w1->s_on_enter += std::make_pair(this, st_test16::on_enter);
		w1->s_on_ldown += std::make_pair(this, st_test16::on_lclick);

		w3 = hw->create_button(w1, 200, 100, 125, 25, "push");
		w3->s_on_push += std::make_pair(this, st_test16::on_push_button);
		w3->get_window()->s_on_key_down += std::make_pair(this, st_test16::on_key);
		w3->get_window()->s_on_enter += std::make_pair(this, st_test16::on_enter);
		w3->get_window()->s_on_leave += std::make_pair(this, st_test16::on_leave);
		std::cout<<"w3"<<w3->get_window()->get_HWND()<<std::endl;

	}

	void on_run()
	{
		using namespace ns_base;
		h_windows* hw; get(hw);
		if(!hw->run_once() )
		{
			ns_base::h_driver* hd;
			ns_base::get(hd);
			hd->exit();
		}
	}

	void on_post()
	{
		w1->release();
		w2->release();
	}
};
int test16(int argc, char** argv)
{
	using namespace ns_base;

	h_driver* hd;
	get(hd);

	st_test16 ins;
	hd->get_pre_delegate(2) += std::make_pair(&ins, &st_test16::on_pre );
	hd->get_on_delegate(2) += std::make_pair(&ins, &st_test16::on_run );
	hd->get_post_delegate(2) += std::make_pair(&ins, &st_test16::on_post );

	hd->run();
	return 0;
}

#include "../script/interface.h"
#include "../head/smart_ptr.h"

int test17(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_script* hs;
	get(hs);

	try
	{
		smart_ptr<i_lua> p_lua = hs->create_lua();
		//p_lua->load_string("pxrint \"lala\"");
		//p_lua->load_file("lala.lua");
		//p_lua->do_script();
		std::cout<<p_lua->exists("t1");
		p_lua->load_string("t1 = {}");
		p_lua->do_script();

		p_lua->add_string_in_table("t1", "lala", "asdf");
		p_lua->load_string("print(t1[\"lala\"])");
		p_lua->do_script();

		p_lua->load_string("function myadd(a, b) return a+b end");
		p_lua->do_script();
		p_lua->push_in_para_int(100);
		p_lua->push_in_para_int(2100);
		int res;
		p_lua->push_out_para_int(res);
		p_lua->call_function("myadd");

		std::cout<<"out res:"<<res<<std::endl;
	}
	catch(ns_common::st_exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
	
	return 0;
}


int test18(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_script* hs;
	get(hs);

	h_filesystem* hf;
	get(hf);

	try
	{
		smart_ptr<i_lua_project> proj = hs->create_lua_project();
		smart_ptr<i_pak> pak =  hf->create_pak("c:\\test_lua");
		

		proj->add_pak(pak.get() );
		
		smart_ptr<i_lua> l = proj->create_lua("asdf.lua");
	}
	catch(ns_common::st_exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}

	return 0;
}


int test19(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_script* hs;
	get(hs);

	h_filesystem* hf;
	get(hf);

	try
	{
		smart_ptr<i_lua> pl = hs->create_lua_from_file("test.lua");
		pl->root_section();
		pl->enter_section("root");
		pl->enter_section("c");
		std::cout<<pl->get_string("cc1")<<std::endl;
		pl->leave_section();
		int ret;
		pl->get_int("a", ret);
		std::cout<<ret<<std::endl;
	}
	catch(ns_common::st_exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}

	return 0;
}

#include "../config/interface.h"

int test20(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_config* hc;
	get(hc);

	try
	{
		smart_ptr<i_config> pc = hc->create_from_file("./config/test.ini");
		pc->root_section();
		bool b = pc->get_bool("bool_val");
		int n = pc->get_int("int_val");

		pc->enter_section("sec1");
		double d = pc->get_double("double_val");
		pc->enter_section("sec2");
		const char* s = pc->get_string("str_val");
		pc->leave_section();
		pc->leave_section();
		pc->enter_section("sec3");
		int count = pc->get_idx_count();
		int i1 = pc->get_int_idx(1);
		int i2 = pc->get_int_idx(2);
		const char* s3 = pc->get_string_idx(3);
	}
	catch (st_exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}




	return 0;
}


int test21(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;
	
	h_console_script* hcs;
	get(hcs);

	hcs->entry_thread();

	while(1)
	{
		hcs->run_once();
	}

	return 0;
}





ns_base::i_window* g_w;
ns_base::i_GDI* g_gdi;

void on_run()
{
	using namespace ns_base;
	using namespace ns_common;

	g_gdi->begin_draw(0xff000000);
	
	g_gdi->end_draw();

	ns_base::h_windows* p_handle = 0;
	ns_base::get(p_handle);
	if(!p_handle->run_once() )
	{
		ns_base::h_driver* p_drv;
		ns_base::get(p_drv);
		p_drv->exit();
	}

	h_console_script* hcs;
	get(hcs);
	hcs->run_once();

}

int test22(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_driver* hd;
	get(hd);
	h_filesystem* hf;
	get(hf);
	h_script* hs;
	get(hs);
	h_console_script* hcs;
	get(hcs);

	ns_delegate::Delegate<void(void)>& pre = hd->get_pre_delegate(1);
	ns_delegate::Delegate<void(void)>& on = hd->get_on_delegate(1);
	ns_delegate::Delegate<void(void)>& post = hd->get_post_delegate(1);

	
	h_windows* hw;
	get(hw);
	st_window_style st;
	st.m_sizeable = false;
	g_w = hw->create_window(0, 0, 0, 512, 512, "测试", 0);
	g_gdi = g_w->init_GDI();
	


	hcs->entry_thread();

	on += &on_run;

	hd->run();

	



	return 0;
}




/************************************************************************/
/* 

内部指令:
__print //output
__dump //输出日志
__set_console_lines_show //console输出的条目数
__set_console_lines_dump //console中保留的的条目数
__set_console_auto(<文件名>, show_line, dump_line) //到达dump后，自动dump到文件中

esc+enter, 禁止/打开所有output输出, 纯命令状态
shift+esc, 

*/
/************************************************************************/


using namespace ns_base;
using namespace ns_common;

//文件列表
std::vector<std::string> g_files;

//将目录下的全部文件放入列表
void find_file_all(const char* path, std::vector<std::string>& files)
{	
	h_filesystem* hf;
	get(hf);
	smart_ptr<i_path> p_path = hf->create_path();

	const char* cur_path = p_path->first(path);
	for(;cur_path;)
	{
		std::vector<std::string> dirs;
		if(p_path->is_directory(cur_path) )
		{
			dirs.push_back(std::string(cur_path) );
		}
		else
		{
			files.push_back(cur_path);
		}

		for(size_t i = 0; i<dirs.size(); ++i)
		{
			find_file_all(dirs[i].c_str(), files);
		}
	}

}



#include "../file_transfer/interface.h"
int test24(int argc, char** argv)
{
	ns_base::h_file_transfer* hfs;
	get(hfs);
	smart_ptr<i_file_transfer_syn> ifs = hfs->create_file_transfer("http://127.0.0.1");
	ifs->download("debug.c", "new_debug.c");
	
	return 0;
}

#include "../data/interface.h"
int test25(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_data* hd;
	get(hd);

	h_filesystem* hf;
	get(hf);

	smart_ptr<i_buffer> buff = hf->create_buff("12345", 5);
	smart_ptr<i_buffer> buff2 = hd->buff2hex(buff.get() );
	smart_ptr<i_buffer> buff3 = hd->hex2buff(buff2.get() );
	

	return 0;
}

#include "../net/interface.h"
int main(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_net* hn;
	get(hn);
	i_DNS* pdns = hn->create_winsock_dns();
	std::cout<<"host_name:"<<pdns->get_host_name()<<std::endl;

	pdns->get_host_by_name("www.sina.com.cn");
	long p = pdns->addr_first();
	while(p)
	{
		std::cout<<p<<std::endl;
		std::cout<<pdns->to_ip_str(p)<<std::endl;
		p = pdns->addr_next();
	}


	const char* name = pdns->alias_first();
	while(name)
	{
		std::cout<<name<<std::endl;
		name = pdns->alias_next();
	}

	return 0;
}

