#pragma once

#include "interface.h"
#include "../ct/interface.h"

namespace ns_base
{
	using namespace ns_c_toy;
	//console的lua命令行
	struct h_console_script_ct
	{
		//ct, 实际上它是 get(ct);
		virtual h_c_toy* get_ct() = 0;
		//进入接收命令的thread(在打开时初始化调用)
		virtual void entry_thread() = 0;
		//逻辑循环中每次调用
		virtual void run_once() = 0;

		//记录保留长度 
		//static const int DUMP_SIZE = 1024;
		//static const int SHOW_SIZE = 10;
		//dump保留
		virtual void set_dump_reserve(long sz) = 0;
		//显示保留
		virtual void set_show_reserve(long sz) = 0;
		
		//把历史命令行内容dump到文件
		virtual void dump(const char* path) = 0;
		//托管输出到命令行
		virtual void output(const char* content, int fc = white, int bc = black) = 0;
		virtual void clear() = 0;

		virtual void release() = 0;
	};

}

M_DECL(ns_base::h_console_script_ct, "console.dll");
