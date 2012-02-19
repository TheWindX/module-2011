#pragma once
#include "interface_ct.h"
#include <string>
#include <deque>
#include "../head/ref_counter.h"

namespace ns_base
{

	struct st_console_item
	{
		std::string m_item;//
		bool m_input;//是否是输入
		int m_fc;
		int m_bc;
	};

	
	struct h_impl_console_script_ct : public h_console_script_ct
	{
		static const int DUMP_SIZE = 1024;
		static const int SHOW_SIZE = 10;

		std::deque<st_console_item> m_items;
		HANDLE m_thread_handle;

		bool m_bfirst;
		h_c_toy* m_ct;

		bool m_input_stat;
		std::string m_str_cmd;

		int m_dump_sz;
		int m_show_sz;

		h_impl_console_script_ct():
		m_bfirst(true),m_input_stat(true),m_str_cmd(""),
			m_dump_sz(DUMP_SIZE),m_show_sz(SHOW_SIZE),m_thread_handle(0)
		{	
			get(m_ct);
		};

		//取得当前的lua_state,注意不托管对象
		h_c_toy* get_ct(){return m_ct;}
		
		void init();

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