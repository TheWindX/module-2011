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


	void impl_driver::pre_run()
	{
		reset();//计时reset
		m_bexit = false;
		
		std::map<unsigned char, st_stage>::iterator it = m_stages.begin();
		for(; it != m_stages.end(); ++it)
		{
			st_stage& st = it->second;
			st.pre_stage();
		}
	}

	void impl_driver::post_run()
	{
		std::map<unsigned char, st_stage>::reverse_iterator it = m_stages.rbegin();
		for(; it != m_stages.rend(); ++it)
		{
			st_stage& st = it->second;
			st.post_stage();
		}

		reset();//计时reset
		m_stages.clear();
		m_bexit = false;
	}

	void impl_driver::run()
	{	
		pre_run();
		while(!m_bexit)
		{
			run_once();
		}
		post_run();
	}
	void impl_driver::reset()
	{
		m_time_start = g_tick_timer.getElapsedTimeInMilliSec();
		m_time_count = 0;
		m_time_delta = 0;
	}
	void impl_driver::run_once()
	{
		if(m_bexit) return;
		
		std::map<unsigned char, st_stage>::iterator it = m_stages.begin();
		for(; it != m_stages.end(); ++it)
		{
			st_stage& st = it->second;
			st.on_stage();
		}


		unsigned int now = g_tick_timer.getElapsedTimeInMilliSec();
		m_time_delta = now-m_time_start-m_time_count;
		m_time_count = now-m_time_start;

		m_time_delta = now-m_time_start-m_time_count;
		m_time_count = now-m_time_start;
		m_fps_time_counter += m_time_delta;
		m_fps_counter++;
		if(m_fps_time_counter>m_fps_interval)
		{
			m_fps = m_fps_counter/m_fps_time_counter;
			m_fps_time_counter = 0;
			m_fps_counter = 0;
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

	void impl_driver::set_fps_interval(long interval)
	{
		m_fps_interval = interval;
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


	handler<st_time_evt> impl_timer::get_evt(long last)
	{
		st_time_evt* p_time = new st_time_evt;
		p_time->m_begin = get_ms();
		p_time->m_till = last;
		m_evt_heap->push(p_time);//生命周期交由i_timer管理
		h_driver* p;
		ns_base::get(p);

		handler<st_time_evt> ret;
		ret.id = p->get_handler_service()->reg(p_time);
		return ret;
	}


	impl_driver::impl_driver()
	{
		m_bexit = true;
		m_fps_interval = 500;//ms
		m_fps_counter = 0;
		m_fps_time_counter = 0;
		m_fps = 0;

		m_time_start = 0;
		m_time_delta = 0;
		m_time_count = 0;
	}

	impl_timer::impl_timer()
	{
		restart();
		ns_base::h_data* p_data;
		ns_base::get(p_data);
		m_evt_heap = p_data->create_heap();

		struct st_cmp
		{
			static bool less(void* l, void* r)
			{
				st_time_evt* t1 = (st_time_evt*)l;
				st_time_evt* t2 = (st_time_evt*)r;
				return t1->m_till<t2->m_till;
			}
		};
		m_evt_heap->s_cmp += &st_cmp::less;
		m_runner = new st_heap_run;
		m_runner->m_time = this;
		h_driver* drv;
		ns_base::get(drv);
		drv->get_on_delegate(2) += std::make_pair(m_runner, &st_heap_run::run);
	}

	impl_timer::~impl_timer()
	{
		h_driver* drv;
		ns_base::get(drv);
		
		for(bool good = m_evt_heap->first();good;good = m_evt_heap->next() )
		{
			void* p = m_evt_heap->get();
			st_time_evt* p_time_evt = (st_time_evt*)p;
			delete p_time_evt;
		}
		
		delete m_runner;
		delete m_evt_heap;
		
		drv->get_on_delegate(2) -= std::make_pair(m_runner, &st_heap_run::run);//todo 有问题?
	}

	IMPL_HANDLER_SEVICE(impl_handler_service);
	i_handler_service* impl_driver::get_handler_service()
	{
		return &_impl_handler_service;
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
