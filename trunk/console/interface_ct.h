#pragma once

#include "interface.h"
#include "../ct/interface.h"

namespace ns_base
{
	using namespace ns_c_toy;
	//console��lua������
	struct h_console_script_ct
	{
		//ct, ʵ�������� get(ct);
		virtual h_c_toy* get_ct() = 0;
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

M_DECL(ns_base::h_console_script_ct, "console.dll");
