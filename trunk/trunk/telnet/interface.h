#pragma once

#include "../head/delegate.h"
#include "../head/ref_counter.h"


namespace ns_base
{
	//接口导出 
	struct i_telnet_commander : public virtual ns_common::i_ref_counter
	{	
		//接入及状态
		virtual void bind(unsigned short port) = 0;
		virtual void listen(bool btrue) = 0;

		
		ns_delegate::Delegate<void(long)> s_accept;
		ns_delegate::Delegate<void(long)> s_except;
		ns_delegate::Delegate<void(long, long)> s_session_break;

		enum
		{
			e_establish = 0,
			e_close,
		};
		virtual int get_status() = 0;

		//内部处理了ESC, BS, DEL, LEFT, RIGHT, UP, DOWN, 
		ns_delegate::Delegate<void(long, const char*)> s_command_from_client;

		//遍历
		virtual bool first(unsigned int& id) = 0;
		virtual bool next(unsigned int& id) = 0;

		virtual bool exist(unsigned int id) = 0;

		//terminor print
		virtual void output_ostr(unsigned int id, const char* str) = 0;
		virtual void output_istr(unsigned int id, const char* str) = 0;
	};


	struct h_telnet
	{
		virtual i_telnet_commander* create_telnet() = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_telnet, "telnet.dll");
