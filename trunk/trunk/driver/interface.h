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
	
	struct st_time_evt
	{
		ns_delegate::Delegate<void(long/*time*/, long/*elaps*/)> s_evt;
		long m_begin;
		long m_till;
	};

	struct i_timer : public virtual i_ref_counter
	{
		virtual void restart() = 0;
		virtual void pause() = 0;
		virtual void resume() = 0;
		
		virtual unsigned int get_ms() = 0;
		virtual handler<st_time_evt> get_evt(long last) = 0;
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

		virtual i_handler_service* get_handler_service() = 0;
	};
}


namespace ns_common
{
	using namespace ns_base;
	template<> i_handler_service* i_handler_service::instance<st_time_evt>()
	{
		h_driver* p_entry;
		ns_base::get(p_entry);
		return p_entry->get_handler_service();
	}
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_driver, "driver.dll");
