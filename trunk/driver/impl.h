#pragma once
#include "interface.h"

#include "../head/ref_counter.h"
#include "Timer.h"

#include <vector>
#include <map>
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

		ns_base::i_heap* m_evt_heap;
		st_heap_run* m_runner;
		
		handler<st_time_evt> get_evt(long last);

		impl_timer();
		~impl_timer();
	};
	
	//for timer heap
	struct st_heap_run
	{
		impl_timer* m_time;
		void run()
		{
			void* p_evt = m_time->m_evt_heap->top();
			for(; p_evt; p_evt = m_time->m_evt_heap->top() )
			{
				st_time_evt* p_time_evt = (st_time_evt*)p_evt;
				unsigned int now = m_time->get_ms();
				if(p_time_evt->m_begin+p_time_evt->m_till<m_time->get_ms() )
				{
					//��ʱ��
					p_time_evt->s_evt(m_time->get_ms(), now-p_time_evt->m_begin);
					//�ͷ�
					m_time->m_evt_heap->pop();
					delete p_time_evt;
				}
				else
				{
					break;
				}
			}
		}
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

		void pre_run();
		void post_run();
		void run();
		void reset();
		void run_once();
		void exit();
		bool is_exit();

		long m_fps_interval;
		long m_fps_counter;
		double m_fps_time_counter;
		long m_fps;
		void set_fps_interval(long interval);
		long get_fps();

		double m_time_start;
		double m_time_count;
		double m_time_delta;
		float get_system_s();
		unsigned int get_system_ms();
		unsigned int get_delta_ms();

		i_timer* create_timer();

		i_handler_service* get_handler_service();

		impl_driver();
	};

}