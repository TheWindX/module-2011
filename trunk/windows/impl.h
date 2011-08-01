#pragma once

#include <vector>
#include <string>

#include "gdiplus_user.h"
#include "interface.h"
#include "../head/delegate.h"


namespace ns_base
{
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
		float lx;
		float ly;
		float zoom;
		std::vector<st_rect> rects;
		st_transform(float _lx, float _ly, float _zoom)
			:lx(_lx),ly(_ly),zoom(_zoom){}
		st_transform()
			:lx(0),ly(0),zoom(1){}
	};

	struct impl_GDI : public i_GDI
	{
		Gdiplus::Bitmap m_bmp;
		Gdiplus::Graphics* m_graph;
		i_window* m_window;
		std::vector<st_transform> m_transform;

		unsigned char m_alpha;

		impl_GDI(int cx, int cy, i_window* win):m_bmp(cx, cy,PixelFormat32bppARGB), m_window(win), m_alpha(255)
		{	
			m_graph = new Gdiplus::Graphics(&m_bmp);
		}

		~impl_GDI()
		{
			delete m_graph;
		}

		//draw
		void draw_line(long color, float x1, float y1, float x2, float y2);
		void draw_rect(bool solid, long color, float x1, float y1, float wid, float height);
		void draw_text(const char* text, const char* str_font, long sz, long color, float x1, float y1);
		void draw_image(i_image* img, float x, float y);

		//transform
		void reset_transform();
		void push_transform(float x, float y, float zoom);
		void pop_transform();

		//单纯计算
		void transform_pt(float lx, float ly, float zoom, float xin, float yin, float& xout, float& yout);
		void invert_transform_pt(float lx, float ly, float zoom, float xin, float yin, float& xout, float& yout);

		//裁剪范围
		void push_clip(float x, float y, float wid, float height);
		void pop_clip();
		void reset_clip();

		void begin_draw(long color);
		void end_draw();

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
