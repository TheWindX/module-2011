#pragma once
#include "interface.h"

#include "../head/ref_counter.h"
#include "Timer.h"

#include <vector>
#include <map>
#include <boost/unordered_map.hpp>
#include "../data/interface.h"

namespace ns_base
{
	using ns_common::impl_ref_counter;

	struct st_heap_run;
	struct impl_timer : public i_timer, public virtual impl_ref_counter
	{
		double m_time_counter;
		double m_time_pause_start;
		double m_time_pause_count;
		bool m_bpause;

		void restart();
		void pause();
		void resume();
		
		unsigned int get_ms();

		impl_timer();
		~impl_timer();
	};
	
	struct st_stage
	{	
		ns_delegate::Delegate<void(void) > pre_stage;
		ns_delegate::Delegate<void(void) > on_stage;
		ns_delegate::Delegate<void(void) > post_stage;
	};
	struct impl_driver : public h_driver
	{
		ns_delegate::Delegate<void(void)>& get_pre_delegate(unsigned char stage);
		ns_delegate::Delegate<void(void)>& get_on_delegate(unsigned char stage);
		ns_delegate::Delegate<void(void)>& get_post_delegate(unsigned char stage);

		bool m_bexit;
		
		std::map<unsigned char, st_stage> m_stages;

		st_stage& get_stage(unsigned char level);


		void init();
		void release();

		void pre_run_once();
		void post_run_once();
		void run();
		void reset();
		void run_once();
		void idle();

		void exit();
		bool is_exit();

		
		long m_fps_counter;
		double m_fps_time_counter;
		long m_fps;
		long m_fps_interval;
		long get_fps();
		void set_fps_interval(long interval);
		void set_fix_time_fps(long interval);

		double m_time_start;//开始时间, 从init开始
		double m_time_count;//计时
		double m_time_delta;//每帧时
		double m_fix_frame_time_count;
		long m_fix_time_interval;

		float get_system_s();
		unsigned int get_system_ms();
		unsigned int get_delta_ms();

		i_timer* create_timer();

		i_handler_service* get_handler_service();

		//@return: timer_trigger id
		long set_time_out(st_on_time* handler, long last);
		//@return: is timer_trigger id exist
		bool is_time_out_exist(long id);

		void run_time_out();

		boost::unordered_map<long ,st_on_time*> m_timeouts;
		long m_timeout_id_count;//TODO, init
		i_heap* m_timeout_heap;

		impl_driver();
	};

}