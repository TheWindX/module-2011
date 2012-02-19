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
		bool m_input;//�Ƿ�������
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

		//ȡ�õ�ǰ��lua_state,ע�ⲻ�йܶ���
		h_c_toy* get_ct(){return m_ct;}
		
		void init();

		void entry_thread();
		void run_once();


		void wait_for_input();

		//dump����
		void set_dump_reserve(long sz)
		{
			m_dump_sz = sz;
		}
		//��ʾ����
		void set_show_reserve(long sz)
		{
			m_show_sz = sz;
		}
		//
		void dump(const char* path);
		//���
		void output(const char* content, int fc, int bc);
		//��ʽ�����
		void format_output();

		void clear();

		void release();
	};
}