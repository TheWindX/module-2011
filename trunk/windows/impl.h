#pragma once

#include <vector>
#include <string>

#include "interface.h"
#include "../head/delegate.h"

#include <gdiplus.h>
#include <GdiPlusColor.h>
#pragma comment(lib, "gdiplus.lib")
#include <objidl.h>

namespace ns_base
{
	using namespace Gdiplus;
	struct impl_drop_files : public i_drop_files, public ns_common::impl_ref_counter
	{
		std::vector<std::string> m_files;
		size_t m_idx;
		impl_drop_files():m_idx(0){}
		const char* first();
		const char* next();
	};

	struct st_rect
	{
		float x;
		float y;
		float wid;
		float height;
		st_rect(float _x, float _y, float _wid, float _height):
		x(_x), y(_y),wid(_wid),height(_height){}

	};

	struct st_transform
	{
		float m_offsetx;
		float m_offsety;
		float m_zoom;
		st_transform(float ox, float oy, float z):m_offsetx(ox), m_offsety(oy), m_zoom(z){}
	};

	struct st_graphic_state
	{
		Gdiplus::Pen* m_pen;
		Gdiplus::SolidBrush* m_brush;
		
		st_transform* m_transform;
		st_rect* m_clip_rect;

		st_graphic_state()
		{
			m_pen = new Gdiplus::Pen(0xffffffff);
			m_brush = new Gdiplus::SolidBrush(0xffffffff);
			m_transform = new st_transform(0, 0, 1);
			m_clip_rect = 0;//it may be use
		}

		~st_graphic_state()
		{
			delete m_pen;
			delete m_brush;
			delete m_transform;
			if(m_clip_rect)
				delete m_clip_rect;
		}
	};

	struct st_graphic_state_stk
	{
		st_graphic_state* m_cur;
		std::vector<st_graphic_state*> m_states;

		void reset()
		{
			delete m_cur;
			for(size_t i = 0; i<m_states.size(); ++i)
			{
				delete m_states[i];
			}
			m_states.clear();
			m_cur = new st_graphic_state;
		}

		void save()
		{
			m_states.push_back(m_cur);
			m_cur = new st_graphic_state;
		}
		void restore()
		{
			if(m_states.size() == 0) return;
			delete m_cur;
			m_cur = m_states.back();
			m_states.pop_back();
		}
		st_graphic_state_stk()
		{
			m_cur = new st_graphic_state;
		}

		Gdiplus::Pen* get_pen()
		{
			return m_cur->m_pen;
		}

		Gdiplus::Brush* get_brush()
		{
			return m_cur->m_brush;
		}

		void set_pen_color(long color)
		{
			m_cur->m_pen->SetColor(Gdiplus::Color(color) );
		}
		
		void set_pen_width(float wid)
		{
			m_cur->m_pen->SetWidth(wid);
		}

		void set_brush(long color)
		{
			m_cur->m_brush->SetColor(Gdiplus::Color(color) );
		}
	};


	struct impl_GDI : public i_GDI
	{
		i_window* m_window;

		Gdiplus::Bitmap m_bmp;
		Gdiplus::Graphics* m_graph;
		unsigned char m_alpha;

		st_graphic_state_stk m_states;

		//graphic states
		void set_pen_color(long color);
		void set_pen_width(float width);
		void set_brush(long color);
		void set_transform(float x, float y, float zoom);
		void set_clip(float x, float y, float wid, float height);

		void reset_state();
		void save_state();
		void restore_state();

		std::vector<PointF> m_points;
		
		impl_GDI(int cx, int cy, i_window* win):m_bmp(cx, cy,PixelFormat32bppARGB), m_window(win), m_alpha(255)
		{
			m_graph = new Gdiplus::Graphics(&m_bmp);
		}

		~impl_GDI()
		{
			delete m_graph;
		}

		//draw
		void draw_point(float x, float y);
		void draw_line(float x1, float y1, float x2, float y2);
		void draw_rect(float x1, float y1, float wid, float height);
		void draw_text(const char* text, const char* str_font, long sz, float x1, float y1);
		void draw_image(i_image* img, float x, float y);

		void fill_rect(float x1, float y1, float wid, float height);

		void move_to(float x, float y);
		void line_to(float x, float y);
		void draw_path();
		void draw_polygon();
		void fill_polygon();

		void begin_draw(long color);
		void end_draw();
		i_image* create_img();//输出img;//create!

		void apply();
	};

	struct impl_window : public i_window, public virtual ns_common::impl_ref_counter
	{
		HWND m_wnd;
		impl_GDI* m_canvas;

		impl_window():m_wnd(0), m_canvas(0){};
		~impl_window();
		
		void create_canvas();

		void set_pos(long x, long y);
		void set_size(long cx, long cy);

		void get_pos(long& xout, long& yout);
		void get_size(long& cxout, long& cyout);

		i_window* get_paresent();

		HWND get_HWND();
		HINSTANCE get_instance();

		bool is_accept_file();
		void set_accept_file(bool accept);

		void set_layered(bool layered);
		bool is_layered();
		void update_layered();
		void set_layered_alpha(unsigned char val);

		void set_sizable(bool );
		bool is_sizable();

		void set_as_child(i_window* paresent);

		void set_as_tool(bool btool);
		bool is_as_tool();

		void set_bar(bool bbar);
		bool is_bar();

		void set_enable(bool able);
		bool is_enable();

		void set_visible(bool bshow);
		bool is_visible();

		//改变风格的提交;
		void redraw();

		i_GDI* init_GDI();
		i_GDI* get_GDI();
	};


	struct impl_static : public i_static, public impl_window
	{
		i_window* get_window();
		void set_text(const char* text);
		const char* get_text();
	};

	struct impl_edit : i_edit, public impl_window 
	{
		i_window* get_window();
		void set_text(const char* text);
		const char* get_text();
	};

	struct impl_button : public i_button, public impl_window
	{
		void set_text(const char* text);
		const char* get_text();

		i_window* get_window();
	};

	struct impl_h_windows : public h_windows
	{
		impl_h_windows();
		~impl_h_windows();
		void get_mouse_pos(long& xout, long& yout);
		bool is_key_press(long key);

		bool run_once();

		i_window* create_window(i_window* paresent, long x, long y, long cx, long cy, const char* str_title, st_window_style* pstyle);
		i_button* create_button(i_window* paresent, long x, long y, long cx, long cy, const char* str_title);
		i_static* create_static(i_window* paresent, long x, long y, long cx, long cy, const char* str_title);
		i_edit* create_edit(i_window* paresent, long x, long y, long cx, long cy, const char* text);
	};
}
