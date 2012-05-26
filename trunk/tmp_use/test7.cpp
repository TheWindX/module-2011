
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../windows/interface.h"

using namespace ns_base;


struct st_point
{
	float x, y;
};

struct st_lin_seg
{
	st_point a, b;
};

bool IsLineSegmentCross(st_point pFirst1, st_point pFirst2, st_point pSecond1, st_point pSecond2)  
{  
    //ÿ���߶ε����㶼����һ���߶ε����Ҳ�ͬ�࣬���ܶ϶��߶��ཻ  
    //��ʽ��������(x1,y1)->(x2,y2),�жϵ�(x3,y3)�����������,�ұ�,��������.  
    //p=x1(y3-y2)+x2(y1-y3)+x3(y2-y1).p<0 ���,    p=0 ����, p>0 �Ҳ�  
    long Linep1,Linep2;  
    //�ж�pSecond1��pSecond2�Ƿ���pFirst1->pFirst2����  
    Linep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +  
        pFirst2.x * (pFirst1.y - pSecond1.y) +  
        pSecond1.x * (pFirst2.y - pFirst1.y);  
    Linep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +  
        pFirst2.x * (pFirst1.y - pSecond2.y) +  
        pSecond2.x * (pFirst2.y - pFirst1.y);  
    if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//����λ���Ϊ0:pSecond1��pSecond2��pFirst1->pFirst2ͬ��  
    {  
        return false;  
    }  
    //�ж�pFirst1��pFirst2�Ƿ���pSecond1->pSecond2����  
    Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +  
        pSecond2.x * (pSecond1.y - pFirst1.y) +  
        pFirst1.x * (pSecond2.y - pSecond1.y);  
    Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +  
        pSecond2.x * (pSecond1.y - pFirst2.y) +  
        pFirst2.x * (pSecond2.y - pSecond1.y);  
    if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//����λ���Ϊ0:pFirst1��pFirst2��pSecond1->pSecond2ͬ��  
    {  
        return false;  
    }  
    //������Ϊ�ཻ  
    return true;  
}  
/* 
����ֱ�߽��㣬ǰ��������ֱ�߱����н��� 
���ཻ������£�����Ӧ���������(��ֱ��ϵ����) 
*/  
st_point GetCrossst_point(st_point p1, st_point p2, st_point q1, st_point q2)  
{  
    //�����ཻ����Ĳ����߶εĽ��㣬��������ĳ������ͨ�õ�  
    assert(IsLineSegmentCross(p1,p2,q1,q2));  
    /*��������ʽ��Ϊ��׼ʽ�����������Է�����*/  
    st_point crossst_point;  
    long tempLeft,tempRight;  
    //��x����  
    tempLeft = (q2.x - q1.x) * (p1.y - p2.y) - (p2.x - p1.x) * (q1.y - q2.y);  
    tempRight = (p1.y - q1.y) * (p2.x - p1.x) * (q2.x - q1.x) + q1.x * (q2.y - q1.y) * (p2.x - p1.x) - p1.x * (p2.y - p1.y) * (q2.x - q1.x);  
    crossst_point.x =(int)( (double)tempRight / (double)tempLeft );  
    //��y����    
    tempLeft = (p1.x - p2.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q1.x - q2.x);  
    tempRight = p2.y * (p1.x - p2.x) * (q2.y - q1.y) + (q2.x- p2.x) * (q2.y - q1.y) * (p1.y - p2.y) - q2.y * (q1.x - q2.x) * (p2.y - p1.y);  
    crossst_point.y =(int)( (double)tempRight / (double)tempLeft );  
    return crossst_point;  
} 


class cTest
{
	h_windows* m_hw;
	i_window* m_win;
	i_GDI* m_gdi;

	bool m_running;

	int m_draw_stat;

public:
	void init()
	{
		m_draw_stat = 0;
		get(m_hw);
		st_window_style ws;
		m_win = m_hw->create_window(0, 0, 0, 512, 512, "asdf", &ws);	
		m_win->init_GDI();
		m_gdi = m_win->get_GDI();

		m_win->s_on_key_down += std::make_pair(this, cancel);
		m_win->s_on_ldown += std::make_pair(this, on_mouse_down);

		m_running = true;
	}

	
	void on_mouse_down(i_window*, long x, long y)
	{
		m_draw_stat++;
		if(m_draw_stat > 4) m_draw_stat = 4;
		if(m_draw_stat == 1) {m_s1.a.x = x; m_s1.a.y = y; }
		if(m_draw_stat == 2) {m_s1.b.x = x; m_s1.b.y = y; }
		if(m_draw_stat == 3) {m_s2.a.x = x; m_s2.a.y = y; }
		if(m_draw_stat == 4) {m_s2.b.x = x; m_s2.b.y = y; }
	}

	void cancel(i_window*, long kc)
	{
		if(kc != 90) return;
		m_draw_stat--;
		if(m_draw_stat<0) m_draw_stat = 0;
	}

	void run()
	{
		while(m_running)
		{
			draw();
			m_hw->run_once();
		}
	}
	
	st_lin_seg m_s1;
	st_lin_seg m_s2;

	void draw_point(float x, float y)
	{
		m_gdi->draw_rect(x-5, y-5, 10, 10);
	}
	void draw_1()
	{
		m_gdi->set_pen_color(0xffff0000);
		draw_point(m_s1.a.x, m_s1.a.y);
	}

	void draw_2()
	{
		m_gdi->set_pen_color(0xffff0000);
		draw_point(m_s1.a.x, m_s1.a.y);
		draw_point(m_s1.b.x, m_s1.b.y);
		m_gdi->draw_line(m_s1.a.x, m_s1.a.y, m_s1.b.x, m_s1.b.y);
	}

	void draw_3()
	{
		m_gdi->set_pen_color(0xffff0000);
		draw_point(m_s1.a.x, m_s1.a.y);
		draw_point(m_s1.b.x, m_s1.b.y);
		m_gdi->draw_line(m_s1.a.x, m_s1.a.y, m_s1.b.x, m_s1.b.y);

		draw_point(m_s2.a.x, m_s2.a.y);
		
	}

	void draw_4()
	{
		m_gdi->set_pen_color(0xffff0000);
		draw_point(m_s1.a.x, m_s1.a.y);
		draw_point(m_s1.b.x, m_s1.b.y);
		m_gdi->draw_line(m_s1.a.x, m_s1.a.y, m_s1.b.x, m_s1.b.y);
		
		draw_point(m_s2.a.x, m_s2.a.y);
		draw_point(m_s2.b.x, m_s2.b.y);
		m_gdi->draw_line(m_s2.a.x, m_s2.a.y, m_s2.b.x, m_s2.b.y);

		bool b = IsLineSegmentCross(m_s1.a, m_s1.b, m_s2.a, m_s2.b);
		if(b) m_gdi->draw_text("�ཻ", "΢���ź�", 14, 0, 0);
		else m_gdi->draw_text("���ཻ", "΢���ź�", 14, 0, 0);

	}

	
	void draw_common()
	{
		long x, y;
		m_hw->get_mouse_pos(x, y);
		long px, py;
		m_win->get_pos(px, py);
		m_gdi->set_pen_color(0xddffff00);
		draw_point(x-px, y-py);
	}


	void draw()
	{	
		m_gdi->begin_draw(0xff000000);

		draw_common();

		if(m_draw_stat == 1)
		{
			draw_1();
		}
		else if(m_draw_stat == 2)
		{
			draw_2();
		}
		else if(m_draw_stat == 3)
		{
			draw_3();
		}
		else if(m_draw_stat == 4)
		{
			draw_4();
		}
		
		m_gdi->end_draw();
	}
};





int main(int argc, char** argv)
{
	
	cTest t;
	t.init();
	t.run();
	
	return 0;
}