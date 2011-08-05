#pragma once

#include "../head/delegate.h"
#include "../head/ref_counter.h"
#include "../script/interface.h"

namespace ns_base
{
	//接口导出 
	struct i_telnet : public virtual ns_common::i_ref_counter
	{	
		//接入及状态
		virtual void bind(unsigned short port) = 0;
		virtual void listen(bool btrue) = 0;

		
		ns_delegate::Delegate<void(long)> s_accept;
		ns_delegate::Delegate<void(long)> s_except;
		ns_delegate::Delegate<void(long, long)> s_session_break;

		//内部处理了
		//BS, DEL, LEFT, RIGHT, UP, DOWN, 
		//ENTER(换行)
		//CTRL+ENTER 完成命令
		//ctrl+k/l 历史命令
		ns_delegate::Delegate<void(long, const char*)> s_command_from_client;

		enum
		{
			e_establish = 0,
			e_close,
		};
		virtual int get_status() = 0;

		//遍历
		virtual bool first(long& id) = 0;
		virtual bool next(long& id) = 0;

		virtual bool exist(long id) = 0;
		virtual void remove(long id) = 0;

		//terminor print
		virtual void output_ostr(long id, const char* str) = 0;
		virtual void output_istr(long id, const char* str) = 0;

		virtual void clear(long id) = 0;

		//回显行数
		virtual void set_max_line(long ln) = 0;
		virtual size_t get_max_line() = 0;
	};


	struct  i_telnet_srcipt : public virtual i_telnet
	{	
		virtual i_lua* get_script(long id) = 0;
	};


	struct h_telnet
	{
		virtual i_telnet* create_telnet() = 0;
		virtual i_telnet_srcipt* create_telnet_script() = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_telnet, "telnet.dll");
