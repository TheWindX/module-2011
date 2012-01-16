#include "impl.h"
#include <map>
#include <boost/unordered_map.hpp>

#include "../head/utility_new.h"//必须放在包含最后

Timer g_tick_timer;
namespace ns_base
{
	using ns_common::impl_ref_counter;


	void impl_timer::restart()
	{	
		m_bpause = false;
		m_time_counter = g_tick_timer.getElapsedTimeInMilliSec();
		m_time_pause_count = 0;
		m_time_pause_start = 0;
		m_time_pause_count = 0;
	}
	void impl_timer::pause()
	{
		if(m_bpause) return;
		m_bpause = true;
		m_time_pause_start = g_tick_timer.getElapsedTimeInMilliSec();
	}
	void impl_timer::resume()
	{
		if(!m_bpause) return;
		m_bpause = false;
		m_time_pause_count += 
			g_tick_timer.getElapsedTimeInMilliSec()-m_time_pause_start;
	}

	unsigned int impl_timer::get_ms()
	{
		if(m_bpause)
		{
			return m_time_pause_start-m_time_counter;
		}
		else
		{
			return g_tick_timer.getElapsedTimeInMilliSec()-m_time_counter-m_time_pause_count;
		}
	}

	ns_delegate::Delegate<void(void)>& impl_driver::get_pre_delegate(unsigned char stage)
	{
		return get_stage(stage).pre_stage;
	}

	ns_delegate::Delegate<void(void)>& impl_driver::get_on_delegate(unsigned char stage)
	{
		return get_stage(stage).on_stage;
	}

	ns_delegate::Delegate<void(void)>& impl_driver::get_post_delegate(unsigned char stage)
	{
		return get_stage(stage).post_stage;
	}

	st_stage& impl_driver::get_stage(unsigned char level)
	{
		std::map<unsigned char, st_stage>::iterator it = m_stages.find(level);
		if(it != m_stages.end() )
		{
			return it->second;
		}
		return m_stages[level];
	}

	void impl_driver::init()
	{
		m_bexit = false;
		reset();
	}
	
	void impl_driver::release()
	{
		m_stages.clear();
		m_fps_interval = 0;
		if(m_timeout_heap) m_timeout_heap->release();
	}

	void impl_driver::pre_run_once()
	{	
		std::map<unsigned char, st_stage>::iterator it = m_stages.begin();
		for(; it != m_stages.end(); ++it)
		{
			st_stage& st = it->second;
			st.pre_stage();
		}
	}

	void impl_driver::post_run_once()
	{
		std::map<unsigned char, st_stage>::reverse_iterator it = m_stages.rbegin();
		for(; it != m_stages.rend(); ++it)
		{
			st_stage& st = it->second;
			st.post_stage();
		}
	}

	void impl_driver::run()
	{	
		while(!m_bexit)
		{
			pre_run_once();
			run_once();
			post_run_once();
		}
		
	}
	
	void impl_driver::reset()
	{
		m_time_start = g_tick_timer.getElapsedTimeInMilliSec();
		m_time_count = 0;
		m_time_delta = 0;

		m_fps_time_counter = 0;
		m_fps = 0;
	}

	void impl_driver::run_once()
	{
		std::map<unsigned char, st_stage>::iterator it = m_stages.begin();
		for(; it != m_stages.end(); ++it)
		{
			st_stage& st = it->second;
			st.on_stage();
		}

		unsigned int now = g_tick_timer.getElapsedTimeInMilliSec();
		double old_time_count = m_time_count;
		m_time_count = now-m_time_start;
		m_time_delta = m_time_count-old_time_count;
		m_fix_frame_time_count += m_fps_interval;

		m_fps_time_counter += m_time_delta;
		m_fps_counter++;
		if(m_fps_time_counter>m_fix_time_interval)
		{
			m_fps = m_fps_counter*1000/m_fps_time_counter;
			m_fps_time_counter = 0;
			m_fps_counter = 0;
		}

		idle();
	}

	void impl_driver::idle()
	{
		if(m_time_count<m_fix_frame_time_count)
		{ 
			Sleep(m_fix_frame_time_count-m_time_count);
		}
	}

	void impl_driver::exit()
	{
		m_bexit = true;
	}

	bool impl_driver::is_exit()
	{
		return m_bexit;
	}

	void impl_driver:: set_fps_interval(long interval)
	{
		m_fps_interval = interval;
	}

	void impl_driver::set_fix_time_fps(long interval)
	{
		m_fix_time_interval = interval;
	}

	long impl_driver::get_fps()
	{
		return m_fps;
	}


	float impl_driver::get_system_s()
	{
		return g_tick_timer.getElapsedTimeInSec();
	}

	unsigned int impl_driver::get_system_ms()
	{
		return g_tick_timer.getElapsedTimeInMilliSec();
	}

	unsigned int impl_driver::get_delta_ms()
	{
		return m_time_delta;
	}

	i_timer* impl_driver::create_timer()
	{
		impl_timer* p_timer = new impl_timer;
		return p_timer;
	}





	impl_driver::impl_driver()
	{
		m_bexit = true;
		m_fix_time_interval = 500;//ms
		m_fps_counter = 0;
		m_fps_time_counter = 0;
		m_fps = 0;

		m_time_start = 0;
		m_time_delta = 0;
		m_time_count = 0;

		m_fps_interval = 0;

		m_timeout_heap = 0;
		m_timeout_id_count = 0;
	}

	impl_driver::~impl_driver()
	{	
	}
	

	impl_timer::impl_timer()
	{
		restart();
	}

	impl_timer::~impl_timer()
	{
		
	}

	void impl_driver::run_time_out()
	{
		if(m_timeout_heap->size() == 0) return;
		st_on_time* time = (st_on_time*)m_timeout_heap->top();
		
		if(time->m_till<m_time_count)
		{
			long next = time->handle(m_time_count-time->m_start);
			if(next > 0)
			{
				m_timeout_heap->pop();
				time->m_start = m_time_count;
				time->m_till = m_time_count+next;
				m_timeout_heap->push(time);
			}
			else
			{
				m_timeout_heap->pop();
				m_timeouts.erase(time->m_id);
			}
		}
	}

	long impl_driver::set_time_out(st_on_time* time_out, long last)
	{	
		if(!m_timeout_heap)
		{	
			ns_base::h_data* hd;
			ns_base::get(hd);
			m_timeout_heap = hd->create_heap();

			struct st_cmp
			{
				static bool less(void* l, void* r)
				{
					st_on_time* timeinfo1 = (st_on_time*) l;
					st_on_time* timeinfo2 = (st_on_time*) r;
					
					return timeinfo1->m_till<timeinfo2->m_till;
				}
			};
			m_timeout_heap->s_cmp += &st_cmp::less;
			this->get_on_delegate(1000) += std::make_pair(this, &impl_driver::run_time_out);
		}

		time_out->m_start = m_time_count;
		time_out->m_till = m_time_count+last;
		m_timeouts.insert(std::make_pair(m_timeout_id_count, time_out) );
		time_out->m_id = m_timeout_id_count;
		
		m_timeout_heap->push(time_out);
		return m_timeout_id_count++;
	}

	bool impl_driver::is_time_out_exist(long id)
	{
		boost::unordered_map<long ,st_on_time* /* time_out */ >::iterator it = m_timeouts.find(id);
		if(it != m_timeouts.end() )return true;
		return false;
	}
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}
#include "../head/M_interface.h"


M_IMPL(ns_base::h_driver, ns_base::impl_driver);//2. 接口实现
M_OPEN();//3. 模块建立
