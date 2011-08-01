#pragma once
#include "../head/ref_counter.h"
#include "../head/M_interface.h"

#include "../script/interface.h"

namespace ns_base
{
	enum
	{
		black       = 0,
		white,
		grey,
		light_grey,
		blue,
		green,
		cyan,
		red,
		purple,
		light_blue,
		light_green,
		light_cyan,
		light_red,
		light_purple,
		orange,
		yellow,
	};

	//console����
	struct h_console
	{
		virtual bool alloc() = 0;
		virtual bool free() = 0;

		virtual bool set_title (const char* title) = 0;

		virtual bool set_size (long columns, long lines) = 0;
		virtual bool get_size (long * pcolumns, long * plines) = 0;

		virtual bool set_cursor_pos (long x, long y) = 0;
		virtual bool get_cursor_pos (long * px, long * py) = 0;
		virtual bool set_cursor_size (long dwPercentShown, bool bVisible = false) = 0;
		
		virtual bool set_text_color (int fc, int bc = black) = 0;
		
		virtual bool clear() = 0;
	};

	//console��lua������
	struct h_console_script
	{
		//ȡ�õ�ǰ��lua_state,ע�ⲻ�йܶ���
		virtual i_lua* get_lua() = 0;
		//����lua_state,���йܶ���
		virtual void set_lua(i_lua* cur) = 0;
		//����Ĭ�ϵ�lua_state
		virtual void reset_lua() = 0;
		
		//������������thread(�ڴ�ʱ��ʼ������)
		virtual void entry_thread() = 0;
		//�߼�ѭ����ÿ�ε���
		virtual void run_once() = 0;

		//��¼�������� 
		//static const int DUMP_SIZE = 1024;
		//static const int SHOW_SIZE = 10;
		//dump����
		virtual void set_dump_reserve(long sz) = 0;
		//��ʾ����
		virtual void set_show_reserve(long sz) = 0;
		
		//����ʷ����������dump���ļ�
		virtual void dump(const char* path) = 0;
		//�й������������
		virtual void output(const char* content, int fc = white, int bc = black) = 0;
		virtual void clear() = 0;

		virtual void release() = 0;
	};

}

M_DECL(ns_base::h_console, "console.dll");
M_DECL(ns_base::h_console_script, "console.dll");
