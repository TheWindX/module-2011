#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../driver/interface.h"
#include "../windows/interface.h"

using namespace ns_common;
using namespace ns_base;

struct st_user : public st_on_time
{
	int m_count;
	h_driver* hd;
	h_windows* hw;
	i_window* m_w;

	st_user():m_count(0){}

	long handle(long t)
	{
		printf("on time: %d\n", t);
		return 1200;
	}

	void on_erase(i_window* w)
	{
		i_GDI* pgdi = w->get_GDI();
		pgdi->begin_draw(0xff000000);
		pgdi->set_pen_color(0xff00ff00);
		pgdi->draw_rect(0, 0, 100, 100);
		pgdi->set_pen_color(0xff00ffff);
		pgdi->set_brush(0xff00ffff);
		pgdi->draw_text("ÊÀ½ç", "Î¢ÈíÑÅºÚ", 48, 20, 20);
		pgdi->end_draw();
		//w->update_layered();
	}
	
	void on_runonce()
	{
		hw->run_once();
	}

	void main()
	{
		
		get(hd);
		get(hw);
		st_window_style sws;
		sws.m_sizeable = true;
		//sws.m_layered = true;
		sws.m_show = true;
		m_w = hw->create_window(0, 100, 100, 512, 512, "", &sws );
		m_w->init_GDI();
		
		i_GDI* pgdi = m_w->get_GDI();
		pgdi->begin_draw(0xff000000);
		pgdi->set_pen_color(0xff00ff00);
		pgdi->set_pen_width(8);
		pgdi->draw_rect(0, 0, 220, 220);
		pgdi->set_pen_color(0xff00ffff);
		pgdi->set_brush(0xff00ffff);
		pgdi->draw_text("ÊÀ½ç", "Î¢ÈíÑÅºÚ", 48, 20, 20);
		pgdi->end_draw();
		//m_w->update_layered();
		m_w->s_on_erase += std::make_pair(this, st_user::on_erase );
		//m_w->redraw()


		ns_delegate::Delegate<void(void)>& s_on_run0 = hd->get_on_delegate(0);
		ns_delegate::Delegate<void(void)>& s_on_pre0 = hd->get_pre_delegate(0);
		ns_delegate::Delegate<void(void)>& s_on_post0 = hd->get_post_delegate(0);
		s_on_run0 += std::make_pair(this, st_user::on_runonce);
		//s_on_pre0 += std::make_pair(this, st_user::test_pre);
		//s_on_post0 += std::make_pair(this, st_user::test_post);
		hd->set_fps_interval(0);
		hd->set_fix_time_fps(0);
		hd->init();

		//hd->set_time_out(this, 2500);
		hd->run();
		hd->release();
		
	}
	
	
	void test()
	{	
		static int fps = 0;
		int now_fps = hd->get_fps();

		//	printf("%d\n", now_fps );
			fps = now_fps;
		//hw->run_once();	
		
		m_count++;
	}

	void test_pre()
	{
		static int fps = 0;
		int now_fps = hd->get_fps();

			printf("on_pre\n");
			fps = now_fps;


		m_count++;
	}

	void test_post()
	{
		static int fps = 0;
		int now_fps = hd->get_fps();

			printf("on_post\n");
			fps = now_fps;


		m_count++;
	}
};




int main(int argc, char** argv)
{
	st_user user;
	user.main();
	return 0;
}




