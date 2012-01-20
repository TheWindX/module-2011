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

#include <complex>

#include "math.h"
#include "stdlib.h"

using namespace ns_common;
using namespace ns_base;



std::complex<float> map_plane(float x, float y)
{
	float fx = (x+85) * 0.005 - 2.0;
	float fy = (y-35) * 0.005 - 1.0;
	return std::complex<float>(fx, fy);
}

long fade(float scale)
{
	long r = 0xff*scale;
	long g = 0xff*scale*0.98;
	long b = 0xff*scale*0.95;
	return (g|g<<8|r<<16|0xff<<24);
}


typedef std::complex<float> c_t;
void on_draw(i_window* w)
{
	i_GDI* gdi = w->get_GDI();
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
				z = z*z + c + std::complex<float>(0, -0);
			}
			gdi->draw_point(fade(1-i/100.0), x, y);
			;
		}
	}
}

i_image* g_img = 0;
void on_erase(i_window* w)
{
	w->get_GDI()->begin_draw(0xff000000);
	w->get_GDI()->draw_image(g_img, 0, 0);
	w->get_GDI()->end_draw();
}


int main(int argc, char** argv)
{
	h_driver* hd;
	get(hd);

	h_windows* hw;
	get(hw);

	st_window_style ws;
	ws.m_sizeable = true;
	i_window* w = hw->create_window(0, 100, 100, 512, 512, "test", &ws);
    
	w->init_GDI();
	

	i_GDI* gdi = w->get_GDI();
	

	gdi->begin_draw(0xff000000);
	on_draw(w);
	gdi->end_draw();

	g_img = gdi->create_img();
	

	

	w->s_on_erase += &on_erase;
	
	hd->set_fix_time_fps(500);
	//hd->set_fps_interval(10);

	while(1)
	{
		hd->run_once();
		gdi->begin_draw(0xff000000);
		//gdi->draw_rect(true, 0xffff0000, 64, 64, 256, 256);
		char strtem[256];
		sprintf(strtem, "fps:%d", hd->get_fps() );
		//system("cls");
		//printf(strtem);
		w->get_GDI()->draw_image(g_img, 0, 0);
		gdi->draw_text(strtem, "Î¢ÈíÑÅºÚ", 24, 0xff00ff00, 0, 0 );
		gdi->end_draw();
		hw->run_once();
	}
	return 0;
}