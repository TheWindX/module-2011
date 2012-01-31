#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../windows/interface.h"
#include "../driver/interface.h"
#include "../console/interface.h"

#include <complex>

#include "math.h"
#include "stdlib.h"

using namespace ns_common;
using namespace ns_base;





struct st_m
{
	i_window* m_w;
	i_image* m_img;
	float m_scale;
	float m_x_offset;
	float m_y_offset;

	float m_iter_times;
	
	typedef std::complex<float> c_t;

	void reflesh(i_window* w)
	{
		m_w->get_GDI()->begin_draw(0xff000000);
		m_w->get_GDI()->draw_image(m_img, 0, 0);
		m_w->get_GDI()->end_draw();
	}

	void on_char(i_window*, char c)
	{
		if(c == '1')
		{
			m_scale *= 1.1;
		}
		else if(c == '2')
		{
			m_scale /= 1.1;
		}
		else if(c == '3')
		{
			m_x_offset += 30;
		}
		else if(c == '4')
		{
			m_x_offset -= 30;
		}
		else if(c == '5')
		{
			m_y_offset += 30;
		}
		else if(c == '6')
		{
			m_y_offset -= 30;
		}
		draw_map();
		//reflesh(0);
	}

	st_m(i_window* w)
	{
		m_scale = 200.0;
		m_x_offset = 85.0;
		m_y_offset = 35.0;

		m_iter_times = 100;

		m_w = w;
		m_img = 0;
		m_w->init_GDI();
		w->s_on_erase += std::make_pair(this, st_m::reflesh);
		w->s_on_char += std::make_pair(this, st_m::on_char);
		draw_map();
		reflesh(0);
	}

	c_t map_plane(float x, float y)
	{
		float fx = (x+m_x_offset) /m_scale - 2.0;
		float fy = (y-m_y_offset) /m_scale - 1.0;
		return c_t(fx, fy);
	}

	long fade(float scale)
	{
		long r = 0xff*scale;
		long g = 0xff*scale*0.98;
		long b = 0xff*scale*0.95;
		return (g|g<<8|r<<16|0xff<<24);
	}


	
	void draw_map()
	{
		if(m_img) m_img->release();
		i_GDI* gdi = m_w->get_GDI();
		gdi->begin_draw(0xff000000);
		for(float x = 0; x<512; ++x)
		{
			for(float y = 0; y<512; ++y)
			{
				c_t z = map_plane(x, y);
				c_t c = z;
				int i = 0;
				for(i = 0; i<100; ++i)
				{
					float n = norm(z);
					if(n == 0) continue;
					if(n > 2.5 ) break;
					z = z*z + c + c_t(0, -0);
				}
				gdi->draw_point(fade(1-i/100.0), x, y);
			}
		}
		gdi->end_draw();

		m_img = gdi->create_img();
	}
};

st_m* g_m;
i_lua* g_lua;
int lua_update(lua_State* st)
{
	g_m->m_scale = g_lua->get_number_global("scale");
	g_m->m_x_offset = g_lua->get_number_global("ofx");
	g_m->m_y_offset = g_lua->get_number_global("ofy");
	g_m->draw_map();
	return 0;
}

int main5(int argc, char** argv)
{
	h_driver* hd;
	get(hd);

	h_windows* hw;
	get(hw);

	h_console_script* hcs;
	get(hcs);

	g_lua = hcs->get_lua();
	g_lua->reg_func("update", &lua_update);

	st_window_style ws;
	ws.m_sizeable = true;
	i_window* w = hw->create_window(0, 100, 100, 512, 512, "test", &ws);
    
	st_m m(w);
	g_m = &m;
	
	hd->set_fix_time_fps(500);
	//hd->set_fps_interval(10);
	hcs->entry_thread();

	while(1)
	{
		hd->run_once();
		hw->run_once();
		hcs->run_once();
		
	}
	return 0;
}