#pragma once
#include "../head/ref_counter.h"
#include "../head/delegate.h"
#include "../head/handler.h"
#include "../head/M_interface.h"

namespace ns_base
{
	using ns_common::i_ref_counter;
	using ns_common::i_handler_service;
	using ns_common::handler;
	
	struct i_timer : public virtual i_ref_counter
	{
		virtual void restart() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;
		
		virtual unsigned int get_ms() = 0;
	};

	struct st_on_time//to override on time handler
	{
		//@para: last: 实际持续时间
		//@return: -1 停止， others下次定时时间
		long m_id;
		long m_start;
		long m_till;
		virtual long handle(long last) = 0;
	};

	struct h_driver 
	{
		virtual ns_delegate::Delegate<void(void)>& get_pre_delegate(unsigned char stage) = 0;
		virtual ns_delegate::Delegate<void(void)>& get_on_delegate(unsigned char stage) = 0;
		virtual ns_delegate::Delegate<void(void)>& get_post_delegate(unsigned char stage) = 0;

		
		virtual void init() = 0;

		virtual void run() = 0;
		virtual void release() = 0;
		
		virtual void pre_run_once() = 0;
		virtual void post_run_once() = 0;
		virtual void run_once() = 0;
		
		virtual void exit() = 0;
		virtual bool is_exit() = 0;
		virtual void set_fix_time_fps(long interval) = 0;
		virtual long get_fps() = 0;
		virtual void set_fps_interval(long interval) = 0;

		virtual float get_system_s() = 0;
		virtual unsigned int get_system_ms() = 0;
		virtual unsigned int get_delta_ms() = 0;

		virtual i_timer* create_timer() = 0;

		//@return: timer_trigger id
		virtual long set_time_out(st_on_time* handler, long last) = 0;
		//@return: is timer_trigger id exist
		virtual bool is_time_out_exist(long id) = 0;
	};
}


#include "../head/M_interface.h"
M_DECL(ns_base::h_driver, "driver.dll");
