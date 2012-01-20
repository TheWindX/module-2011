#pragma once
#include "../head/ref_counter.h"
#include "../head/delegate.h"

#include "../image/interface.h"

namespace ns_base
{
	using namespace ns_delegate;

	struct i_drop_files : public virtual i_ref_counter
	{
		virtual const char* first() = 0;
		virtual const char* next() = 0;
	};

	struct i_GDI
	{
		//draw
		virtual void draw_point(long color, float x, float y) = 0;
		virtual void draw_line(long color, float x1, float y1, float x2, float y2) = 0;
		virtual void draw_rect(bool solid, long color, float x1, float y1, float wid, float height) = 0;
		virtual void draw_text(const char* text, const char* str_font, long sz, long color, float x1, float y1) = 0;//str_font 查看系统字体名称
		virtual void draw_image(i_image* img, float x, float y) = 0;


		//transform
		virtual void reset_transform() = 0;
		virtual void push_transform(float x, float y, float zoom) = 0;
		virtual void pop_transform() = 0;

		//单纯计算
		virtual void transform_pt(float lx, float ly, float zoom, float xin, float yin, float& xout, float& yout) = 0;
		virtual void invert_transform_pt(float lx, float ly, float zoom, float xin, float yin, float& xout, float& yout) = 0;

		//裁剪范围
		virtual void push_clip(float x, float y, float wid, float height) = 0;
		virtual void pop_clip() = 0;
		virtual void reset_clip() = 0;

		virtual void begin_draw(long color) = 0;
		virtual void end_draw() = 0;

		virtual i_image* create_img() = 0;//输出img;
	};

	struct i_window : public virtual i_ref_counter
	{
		//property
		virtual void set_pos(long x, long y) = 0;
		virtual void set_size(long cx, long cy) = 0;
		
		virtual void get_pos(long& xout, long& yout) = 0;
		virtual void get_size(long& cxout, long& cyout) = 0;

		virtual i_window* get_paresent() = 0;

		virtual HWND get_HWND() = 0;
		virtual HINSTANCE get_instance() = 0;

		virtual bool is_accept_file() = 0;
		virtual void set_accept_file(bool accept) = 0;

		virtual void set_sizable(bool ) = 0;
		virtual bool is_sizable() = 0;

		virtual void set_as_child(i_window* paresent) = 0;
		
		virtual void set_as_tool(bool btool) = 0;
		virtual bool is_as_tool() = 0;

		virtual void set_bar(bool bbar) = 0;
		virtual bool is_bar() = 0;

		virtual void set_enable(bool able) = 0;
		virtual bool is_enable() = 0;
		
		virtual void set_visible(bool bshow) = 0;
		virtual bool is_visible() = 0;

		virtual void set_layered(bool layered) = 0;
		virtual bool is_layered() = 0;
		virtual void set_layered_alpha(unsigned char val) = 0;
		virtual void update_layered() = 0;
		

		virtual void redraw() = 0;

		virtual i_GDI* init_GDI() = 0;
		virtual i_GDI* get_GDI() = 0;

		Delegate<void(i_window*) > s_on_create;
		
		Delegate<void(i_window*) > s_on_erase;
		Delegate<void(i_window*, long, long) > s_on_size;


		Delegate<void(i_window*, long, long) > s_on_mouse_move;
		Delegate<void(i_window*, long, long) > s_on_ldown;
		Delegate<void(i_window*, long, long) > s_on_lup;
		Delegate<void(i_window*, long, long) > s_on_dclick;

		Delegate<void(i_window*, long) > s_on_key_down;
		Delegate<void(i_window*, long) > s_on_key_up;
		Delegate<void(i_window*, char) > s_on_char;

		Delegate<void(i_window*) > s_on_leave;
		Delegate<void(i_window*) > s_on_enter;

		Delegate<void(i_window*, i_drop_files*)> s_drop_files;
	};


	struct st_window_style
	{
		bool m_show;//是否显示
		bool m_as_tool;//是否是tool窗口
		bool m_bar;//是否有标题栏
		bool m_sizeable;//是否可调整大小
		bool m_layered;//是否是layered窗口

		st_window_style():m_show(true),m_as_tool(false),m_bar(true),m_layered(false),m_sizeable(false){}
	};


	struct i_button : public virtual ns_base::i_ref_counter
	{
		ns_delegate::Delegate<void(i_button*)> s_on_push;

		virtual i_window* get_window() = 0;
		virtual void set_text(const char* text) = 0;
		virtual const char* get_text() = 0;
	};

	struct i_static : public virtual ns_base::i_ref_counter
	{
		virtual i_window* get_window() = 0;
		virtual void set_text(const char* text) = 0;
		virtual const char* get_text() = 0;
	};

	struct i_edit : public virtual ns_base::i_ref_counter
	{
		virtual i_window* get_window() = 0;
		virtual void set_text(const char* text) = 0;
		virtual const char* get_text() = 0;
	};

	struct h_windows
	{
		virtual void get_mouse_pos(long& xout, long& yout) = 0;
		virtual bool is_key_press(long key) = 0;

		virtual i_window* create_window(i_window* paresent, long x, long y, long cx, long cy, const char* str_title, st_window_style* pstyle = 0) = 0;
		
		virtual i_button* create_button(i_window* paresent, long x, long y, long cx, long cy, const char* str_title) = 0;

		virtual i_static* create_static(i_window* paresent, long x, long y, long cx, long cy, const char* str_title) = 0;

		virtual i_edit* create_edit(i_window* paresent, long x, long y, long cx, long cy, const char* text) = 0;

		virtual bool run_once() = 0;
		Delegate<void(void)> s_on_idle;//在处理完所有消息后
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_windows, "windows.dll");
