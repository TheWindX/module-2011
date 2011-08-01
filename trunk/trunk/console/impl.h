#pragma once
#include "interface.h"
#include <string>
#include <deque>
#include "../head/ref_counter.h"

#pragma comment(lib,"lua5.1.lib")
namespace ns_base
{
	struct impl_console : public h_console
	{
		bool alloc();
		bool free();
		bool set_title (const char* title);
		bool set_size (long columns, long lines);
		bool get_size (long * pcolumns, long * plines);
		bool set_cursor_pos (long x, long y);
		bool get_cursor_pos (long * px, long * py);
		bool set_cursor_size (long dwPercentShown, bool bVisible);
		bool set_text_color (int fc, int bc = black);
		bool clear();
	};

	struct st_console_item
	{
		std::string m_item;//
		bool m_input;//是否是输入
		int m_fc;
		int m_bc;
	};

	
	struct h_impl_console_script : public h_console_script
	{
		static const int DUMP_SIZE = 1024;
		static const int SHOW_SIZE = 10;

		std::deque<st_console_item> m_items;
		HANDLE m_thread_handle;

		bool m_bfirst;
		i_lua* m_internal;
		i_lua* m_current;

		bool m_input_stat;
		std::string m_str_cmd;

		int m_dump_sz;
		int m_show_sz;

		h_impl_console_script():
		m_bfirst(true),m_internal(0),m_current(0),m_input_stat(true),m_str_cmd(""),
			m_dump_sz(DUMP_SIZE),m_show_sz(SHOW_SIZE),m_thread_handle(0)
		{	
			
		};

		
		void init();

		i_lua* get_lua();
		void set_lua(i_lua* cur);
		void reset_lua();
		void entry_thread();
		void run_once();


		void wait_for_input();

		//dump保留
		void set_dump_reserve(long sz)
		{
			m_dump_sz = sz;
		}
		//显示保留
		void set_show_reserve(long sz)
		{
			m_show_sz = sz;
		}
		//
		void dump(const char* path);
		//输出
		void output(const char* content, int fc, int bc);
		//格式化输出
		void format_output();

		void clear();

		void release();
	};
}