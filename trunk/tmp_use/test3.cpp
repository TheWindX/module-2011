#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../driver/interface.h"

using namespace ns_common;
using namespace ns_base;

struct st_user
{
	int m_count;
	h_driver* hd;

	st_user():m_count(0){}

	void on_time(long time, long last)
	{
		printf("on_time!");
	}

	void main()
	{
		
		get(hd);

		ns_delegate::Delegate<void(void)>& s_on_run0 = hd->get_on_delegate(0);
		ns_delegate::Delegate<void(void)>& s_on_pre0 = hd->get_pre_delegate(0);
		ns_delegate::Delegate<void(void)>& s_on_post0 = hd->get_post_delegate(0);
		s_on_run0 += std::make_pair(this, st_user::test);
		//s_on_pre0 += std::make_pair(this, st_user::test_pre);
		//s_on_post0 += std::make_pair(this, st_user::test_post);
		hd->set_fps_interval(150);
		hd->set_fix_time_fps(1000);
		hd->init();

		i_timer* t = hd->create_timer();
		handler<st_time_evt> th = t->get_evt(15000);
		if(th.get() )
		{
			th.get()->s_evt += std::make_pair(this, st_user::on_time);
		}
		

		hd->run();
		
	}
	
	
	void test()
	{	
		static int fps = 0;
		int now_fps = hd->get_fps();

		//	printf("%d\n", now_fps );
			fps = now_fps;

		
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
}