
#include <iostream>
#include <map>
#include <windows.h>
#include <CommCtrl.h>
//#include <Ole2.h>


#include "impl.h"
#include "../head/utility_new.h"

namespace ns_base
{
	std::wstring MtbToWstr( const std::string& str, UINT uCodePage = CP_ACP )   
	{   
		using namespace std;
		LPWSTR lpwszWide = NULL;   
		DWORD cbszWide = 0U;   
		DWORD dwRet = 0U;   
		wstring wstrRet;   

		/// calculate the require size   
		cbszWide = MultiByteToWideChar( uCodePage, 0U, str.c_str(), -1, lpwszWide, 0 );   
		if ( 0U == cbszWide )   
			goto Exit0;   

		/// allocate specify size   
		lpwszWide = (LPWSTR)HeapAlloc( GetProcessHeap(), 0, cbszWide * sizeof( WCHAR ) );   
		if ( NULL == lpwszWide )   
			goto Exit0;   

		/// start convert   
		dwRet = MultiByteToWideChar( uCodePage, 0U, str.c_str(), -1, lpwszWide, cbszWide );   
		if ( 0 == dwRet )   
			goto Exit0;   
		wstrRet = lpwszWide;   

Exit0:   
		if ( NULL != lpwszWide )   
			HeapFree( GetProcessHeap(), 0, lpwszWide );   
		return wstrRet;   
	}  



	LRESULT CALLBACK wnd_proc
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	namespace ns_wnd_register
	{
		std::map<HWND, i_window*> m_hwnd2iwindow;
		std::map<HWND, WNDPROC> m_hwnd2proc;
		void clear()
		{
			m_hwnd2iwindow.clear();
			m_hwnd2proc.clear();
		}

		void reg(HWND hwnd, i_window* w)
		{
			m_hwnd2iwindow.insert(std::make_pair(hwnd, w) );
			WNDPROC OldMsgProc = (WNDPROC)SetWindowLong (hwnd, GWL_WNDPROC, (LONG)wnd_proc);
			if(OldMsgProc == wnd_proc) return;
			m_hwnd2proc.insert(std::make_pair(hwnd, OldMsgProc) );
		}

		void unreg(HWND hwnd)
		{
			m_hwnd2iwindow.erase(hwnd);
			m_hwnd2proc.erase(hwnd);
		}

		i_window* find_window(HWND hwnd)
		{
			std::map<HWND, i_window*>::iterator m_it;
			m_it = m_hwnd2iwindow.lower_bound(hwnd);
			if(m_it != m_hwnd2iwindow.end() )
			{
				if( !m_hwnd2iwindow.key_comp()(hwnd, m_it->first) )
				{
					//found
					return m_it->second;
				}
			}
			return 0;
		}

		WNDPROC find_proc(HWND hwnd)
		{
			std::map<HWND, WNDPROC>::iterator m_it;
			m_it = m_hwnd2proc.lower_bound(hwnd);
			if(m_it != m_hwnd2proc.end() )
			{
				if( !m_hwnd2proc.key_comp()(hwnd, m_it->first) )
				{
					//found
					return m_it->second;
				}
			}
			return 0;
		}
	}


	LRESULT CALLBACK wnd_proc
		(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		h_windows* p_handle = 0;
		ns_base::get(p_handle);

		static bool _bMouseTrack = true;

		i_window* p_win = ns_wnd_register::find_window(hwnd);
		if(!p_win) goto end;

		switch (message)
		{
			//创建
		case WM_CREATE:
			{
				if(p_win->s_on_create.IsEmpty() )
					goto end;
				p_win->s_on_create(p_win);

				return 0;
			}
		case   WM_COMMAND: 
			{

				if   (HIWORD(wParam)   ==   BN_CLICKED) 
				{ 
					   HWND hwndButton =   (HWND) lParam;
					   i_window* wnd = ns_wnd_register::find_window(hwndButton);
					   impl_button* button = (impl_button*)wnd;
					   button->s_on_push(button);
					   return 0;
				}
			}


			//擦除
		case WM_ERASEBKGND:
			{	
				if(p_win->s_on_erase.IsEmpty() )
				goto end;
				p_win->s_on_erase(p_win);

				return 0;
			}
			//键盘按下
		case WM_KEYDOWN:
			{
				if(p_win->s_on_key_down.IsEmpty() )
					goto end;
				p_win->s_on_key_down(p_win, wParam);

				return 0;
			}
			//键盘弹上
		case WM_KEYUP:
			{
				if(p_win->s_on_key_up.IsEmpty() )
					goto end;
				p_win->s_on_key_up(p_win, wParam);

				return 0;
			}
			//键盘弹上
		case WM_CHAR:
			{
				if(p_win->s_on_char.IsEmpty() )
					goto end;
				p_win->s_on_char(p_win, wParam);

				return 0;
			}
			//关闭
		case WM_DESTROY:
			{	
				::PostQuitMessage (0);
				return 0;
			}
			//鼠标移动
		case WM_MOUSEMOVE:
			{	
				if(_bMouseTrack)
				{
					TRACKMOUSEEVENT  tme = {0};
					tme.cbSize  = sizeof(TRACKMOUSEEVENT);
					tme.dwFlags = TME_HOVER|TME_LEAVE;
					tme.dwHoverTime = 10;
					tme.hwndTrack = hwnd;
					TrackMouseEvent(&tme);
					_bMouseTrack = false;
				}

				if(p_win->s_on_mouse_move.IsEmpty() )
					goto end;
				
				p_win->s_on_mouse_move(p_win, LOWORD(lParam), HIWORD(lParam) );
				return 0;
			}
		case WM_NCHITTEST:
			{	
				//WNDPROC proc = ns_wnd_register::find_proc(hwnd);
				//if(proc != wnd_proc && proc != 0)
				//	return 0;

				if(p_win->is_layered() )
				{
					SendMessage(hwnd, WM_NCLBUTTONDOWN, 
						HTCAPTION, 0); 
					return 0;
				}
				goto end;
			}
			//左键点击
		case WM_LBUTTONDOWN:
			{
				if(p_win->s_on_ldown.IsEmpty() )
					goto end;

				p_win->s_on_ldown(p_win, LOWORD(lParam), HIWORD(lParam) );
				return 0;
			}
			//左键弹起
		case WM_LBUTTONUP:
			{
				if(p_win->s_on_lup.IsEmpty() )
					goto end;

				p_win->s_on_lup(p_win, LOWORD(lParam), HIWORD(lParam) );
				return 0;
			}
			//双击
		case WM_LBUTTONDBLCLK:
			{	
				if(p_win->s_on_dclick.IsEmpty() )
					goto end;

				p_win->s_on_dclick(p_win, LOWORD(lParam), HIWORD(lParam) );
				return 0;
			}
			//进入窗口
		case WM_MOUSEHOVER:
			{	
				if(p_win->s_on_enter.IsEmpty() )
					goto end;

				p_win->s_on_enter(p_win);
				return 0;
			}
			//离开窗口
		case WM_MOUSELEAVE:
			{	
				_bMouseTrack=true;
				if(p_win->s_on_leave.IsEmpty() )
					goto end;

				p_win->s_on_leave(p_win);
				return 0;
			}
		case WM_SIZE:
			{
				impl_window* p_impl_win = (impl_window*)p_win;
				if(p_impl_win->m_canvas)
				{
					delete p_impl_win->m_canvas;
					p_impl_win->m_canvas = new impl_GDI(LOWORD(lParam), HIWORD(lParam), p_win);
				}

				if(p_win->s_on_size.IsEmpty() )
					goto end;

				p_win->s_on_size(p_win, LOWORD(lParam), HIWORD(lParam) );
				return 0;
			}
		case WM_PAINT:
			{
				impl_window* p_impl_win = (impl_window*)p_win;
				if(!p_impl_win->m_canvas)
					goto end;

				PAINTSTRUCT ps;

				BeginPaint (hwnd, &ps);

				Gdiplus::Graphics g(ps.hdc);
				g.DrawImage(&p_impl_win->m_canvas->m_bmp, 0, 0);

				EndPaint (hwnd, &ps);

				return 0;
			}
			//离开窗口
		case WM_DROPFILES:
			{	
				if(p_win->s_drop_files.IsEmpty() )
					goto end;
				
				HDROP hDrop = (HDROP) wParam;
				
				// How many files were dropped? 
				int count = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

				impl_drop_files* pf = new impl_drop_files;
				const int max_path = 1024;
				char path[max_path];
				for(int i = 0; i<count; ++i)
				{
					DragQueryFile(hDrop, i, path, max_path);
					pf->m_files.push_back(path);
				}
				DragFinish(hDrop);

				p_win->s_drop_files(p_win, pf);
				pf->release();
				return 0;
			}


		}
end:
		WNDPROC proc = ns_wnd_register::find_proc(hwnd);
		if(proc == wnd_proc || proc == 0)
			return ::DefWindowProc (hwnd, message, wParam, lParam );
		else
			return CallWindowProc(proc,hwnd,message,wParam,lParam);
			//return proc(hwnd, message, wParam, lParam );
	}


	WNDCLASS* get_window_class()
	{
		static WNDCLASS m_class;
		static bool bfirst = true;

		if(bfirst)
		{
			m_class.style = CS_HREDRAW | CS_VREDRAW ;
			m_class.lpfnWndProc = wnd_proc;  // window procedure: mandatory
			m_class.cbClsExtra = 0;
			m_class.cbWndExtra = 0;
			m_class.hInstance = GetModuleHandle(0);           // owner of the class: mandatory
			m_class.hIcon = 0;
			m_class.hCursor = ::LoadCursor (0, IDC_ARROW); // optional
			m_class.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // optional//背景
			m_class.lpszMenuName = 0;
			m_class.lpszClassName = "my_class";	
			::RegisterClass(&m_class);
		}
		
		return &m_class;
	}

	const char* impl_drop_files::first()
	{
		m_idx = 0;
		if(m_idx >= m_files.size() )
		{
			return 0;
		}

		return m_files[m_idx++].c_str();
	}

	const char* impl_drop_files::next()
	{
		if(m_idx >= m_files.size() )
		{
			return 0;
		}

		return m_files[m_idx++].c_str();
	}

	void impl_window::set_pos(long x, long y)
	{
		RECT rc;
		if(GetWindowRect(m_wnd, &rc) )
		{
			MoveWindow(m_wnd, x, y, rc.right-rc.left, rc.bottom-rc.top, false);
		}
	}

	void impl_window::set_size(long cx, long cy)
	{
		RECT rc;
		if(GetWindowRect(m_wnd, &rc) )
		{
			MoveWindow(m_wnd, rc.left, rc.top, rc.left+cx, rc.top+cy, false);
		}
	}
	
	impl_window::~impl_window()
	{
		if(m_canvas)delete m_canvas; 
		::DestroyWindow(m_wnd);
		ns_wnd_register::unreg(m_wnd);
	};

	void impl_window::create_canvas()
	{
		long cx, cy;
		this->get_size(cx, cy);
		m_canvas = new impl_GDI(cx, cy, this);
	}


	void impl_GDI::set_pen_color(long color)
	{
		m_states.set_pen_color(color);
	}

	void impl_GDI::set_pen_width(float width)
	{
		m_states.set_pen_width(width);
	}

	void impl_GDI::set_brush(long color)
	{
		m_states.set_brush(color);
	}

	void impl_GDI::set_transform(float x, float y, float zoom)
	{
		m_states.m_cur->m_transform->m_offsetx = x;
		m_states.m_cur->m_transform->m_offsety = y;
		m_states.m_cur->m_transform->m_zoom = zoom;
		apply();
	}

	void impl_GDI::set_clip(float x, float y, float wid, float height)
	{
		if(!m_states.m_cur->m_clip_rect) m_states.m_cur->m_clip_rect = new st_rect(x, y, wid, height);
		else
		{
			m_states.m_cur->m_clip_rect->x = x;
			m_states.m_cur->m_clip_rect->y = x;
			m_states.m_cur->m_clip_rect->wid = wid;
			m_states.m_cur->m_clip_rect->height = height;
		}
		apply();
	}

	void impl_GDI::reset_state()
	{
		m_states.reset();
		apply();
	}

	void impl_GDI::save_state()
	{
		m_states.save();
		apply();
	}

	void impl_GDI::restore_state()
	{
		m_states.restore();
		apply();
	}

	void impl_GDI::draw_point(float x, float y)
	{
		m_graph->DrawLine(m_states.get_pen(), (int)x, (int)y, (int)x+2, (int)y+2);
	}

	void impl_GDI::draw_line(float x1, float y1, float x2, float y2)
	{	
		m_graph->DrawLine(m_states.get_pen(), x1, y1, x2, y2);
	}

	void impl_GDI::draw_rect(float x1, float y1, float wid, float height)
	{	
		m_graph->DrawRectangle(m_states.get_pen(), x1, y1, wid, height);
	}

	void impl_GDI::draw_text(const char* text, const char* str_font, long sz, float x1, float y1)
	{
		Gdiplus::PointF pointF(x1,y1);
		
		std::wstring wstr = MtbToWstr(std::string(text) );
		std::wstring wstr1 = MtbToWstr(std::string(str_font) );
		Gdiplus::FontFamily fontFamily(wstr1.c_str() );         //选择一种字体
		Gdiplus::Font font(&fontFamily, sz, Gdiplus::FontStyleRegular,Gdiplus::UnitPixel);
		m_graph->DrawString(wstr.c_str(), -1, &font, pointF, m_states.get_brush() );
		//Gdiplus::Graphics Graphic(m_wnd);
		//Graphic.DrawImage(&m_canvas->m_bmp, 0, 0);
	}

	void impl_GDI::draw_image(i_image* img, float x, float y)
	{
		using namespace Gdiplus;

		long w, h;
		img->size(w, h);

		char* buff = new char[w*h*4];//TODO: OPMISE IT
		char* idx = buff;
		for(size_t ih=0;ih<h; ++ih)
			for(size_t iw=0;iw<w; ++iw)
			{
				st_color col = img->get_pixel_argb(iw, ih);
				*((long*)idx) = col.value;
				idx += 4;
			}
		Bitmap bmp(w, h, w*4, PixelFormat32bppARGB, (BYTE*)buff);
		m_graph->DrawImage(&bmp, (int)x, (int)y, (int)w, (int)h);
		delete[] buff;

		//long w, h;
		//img->size(w, h);
		//
		//i_buffer* buff = img->to_buff(e_bmp);
		//HGLOBAL hMemBmp = GlobalAlloc(GMEM_FIXED, buff->size() );
		//IStream* pStmBmp = NULL;
		//CreateStreamOnHGlobal(hMemBmp, FALSE, &pStmBmp);
		//if (pStmBmp == NULL)
		//{
		//	GlobalFree(hMemBmp);
		//	return;
		//}
		//BYTE* pbyBmp = (BYTE *)GlobalLock(hMemBmp);
		//memcpy(pbyBmp, buff->ptr(), buff->size() );

		//Image* imImage = NULL;
		//imImage = Image::FromStream(pStmBmp, true);
		//PixelFormat px = imImage->GetPixelFormat();
		//g.SetCompositingMode(CompositingModeSourceCopy );
		//g.SetCompositingQuality(CompositingQualityGammaCorrected);
		//if (imImage == NULL)
		//{
		//	GlobalUnlock(hMemBmp);
		//	GlobalFree(hMemBmp);
		//	return;
		//}
		//g.DrawImage(imImage, (int)x, (int)y, (int)w, (int)h);
		//GlobalUnlock(hMemBmp);
		//GlobalFree(hMemBmp);


//		BITMAP bmpInfo;
//		::GetObject(img->get_bitmap(0 ), sizeof(BITMAP), &bmpInfo);
//		int cxBitmap = bmpInfo.bmWidth;
//		int cyBitmap = bmpInfo.bmHeight;
//		void* bits = bmpInfo.bmBits;
//;
//		Gdiplus::Bitmap bitmap(cxBitmap, cyBitmap, cxBitmap*4, PixelFormat32bppPARGB, (BYTE*)bits);
//		
//		g.DrawImage(&bitmap, x, y);

		//HDC dc_des= g.GetHDC();
		//HDC  dc_src  = CreateCompatibleDC(dc_des);//创建存放图象的显示缓冲
		//SelectObject(dc_src,img->get_bitmap(dc_src) );    //将位图资源装入显示缓冲
		//
		//BLENDFUNCTION bf;
		//bf.BlendOp = AC_SRC_OVER; 
		//bf.BlendFlags = 0; 
		//bf.AlphaFormat = AC_SRC_ALPHA; 
		//bf.SourceConstantAlpha = 33; 

		//bool ret = BitBlt(dc_des,x,y,w,h,dc_src,0,0, SRCPAINT);
		//g.ReleaseHDC(dc_des);
		//DeleteDC(dc_src);

		//long w, h;
		//img->size(w, h);
		//Bitmap bmp(w, h, PixelFormat32bppPARGB);
		//BitmapData bmd;
		//Rect rect(0, 0, w, h);
		//bmp.LockBits(&rect, ImageLockMode::ImageLockModeWrite,
		//	PixelFormat32bppPARGB, &bmd)
		//
		//int lineSize = w * 4;//4BYTE
		//byte* destBytes = (byte*)(bmd.Scan0);
		//for (int y = 0; y < h; y++)
		//{
		//	memcpy(destBytes + (y * lineSize), img->get_line_bits(y), lineSize);
		//}
		//bmp.UnlockBits(&bmd);
		//
	}

	void impl_GDI::fill_rect(float x1, float y1, float wid, float height)
	{
		m_graph->FillRectangle(m_states.get_brush(), x1, y1, wid, height);
	}

	void impl_GDI::move_to(float x, float y)
	{
		m_points.clear();
		m_points.push_back(PointF(x, y) );
	}

	void impl_GDI::line_to(float x, float y)
	{
		m_points.push_back(PointF(x, y) );
	}

	void impl_GDI::draw_path()
	{
		m_graph->DrawLines(m_states.get_pen(), &m_points[0], m_points.size() );
	}

	void impl_GDI::draw_polygon()
	{
		m_graph->DrawPolygon(m_states.get_pen(), &m_points[0], m_points.size() );
	}

	void impl_GDI::fill_polygon()
	{
		m_graph->FillPolygon(m_states.get_brush(), &m_points[0], m_points.size() );
	}
	
	void impl_GDI::apply()
	{
		m_graph->ResetClip();
		m_graph->ResetTransform();
		
		Gdiplus::Matrix m1;
		Gdiplus::Region reg;
		reg.MakeInfinite();

		for(size_t i=0; i<m_states.m_states.size(); ++i)
		{
			st_graphic_state* st = m_states.m_states[i];
			st_transform* tran = st->m_transform;
			m1.Translate(tran->m_offsetx, tran->m_offsety);
			m1.Scale(tran->m_zoom, tran->m_zoom);

			if(st->m_clip_rect)
			{
				st_rect& rc = *(st->m_clip_rect);
				Gdiplus::Region reg1(Gdiplus::Rect(rc.x, rc.y, rc.wid, rc.height) );
				reg1.Transform(&m1);
				reg.Intersect(&reg1);
			}
		}

		st_graphic_state* st = m_states.m_cur;
		st_transform* tran = st->m_transform;
		m1.Translate(tran->m_offsetx, tran->m_offsety);
		m1.Scale(tran->m_zoom, tran->m_zoom);

		if(st->m_clip_rect)
		{
			st_rect& rc = *(st->m_clip_rect);
			Gdiplus::Region reg1(Gdiplus::Rect(rc.x, rc.y, rc.wid, rc.height) );
			reg1.Transform(&m1);
			reg.Intersect(&reg1);
		}

		//HRGN hrng = reg.GetHRGN(get_canvas() );
		m_graph->SetClip(&reg);

		//set transform
		m_graph->SetTransform(&m1);
	}

	void impl_GDI::begin_draw(long color)
	{
		this->m_graph->Clear(color);
		reset_state();
	}

	void impl_GDI::end_draw()
	{
		Gdiplus::Graphics Graphic(m_window->get_HWND() );
		Graphic.DrawImage(&m_bmp, 0, 0);
	}

	i_image* impl_GDI::create_img()//输出img;
	{
		h_image* hi;
		get(hi);
		long w = m_bmp.GetWidth();
		long h = m_bmp.GetHeight();
		i_image* img = hi->create(w, h);
		Gdiplus::Color c;
		for(long x = 0; x<w; ++x)
			for(long y = 0; y<h; ++y)
			{	
				m_bmp.GetPixel(x, y, &c);
				img->set_pixel_argb(x, y, c.GetValue() );
			}
		return img;
	}

	void impl_window::get_pos(long& xout, long& yout)
	{
		RECT rc;
		GetWindowRect(m_wnd, &rc);
		xout = rc.left;
		yout = rc.top;
	}

	void impl_window::get_size(long& cxout, long& cyout)
	{
		RECT rc;
		GetWindowRect(m_wnd, &rc);
		cxout = rc.right-rc.left;
		cyout = rc.bottom-rc.top;
	}

	i_window* impl_window::get_paresent()
	{
		HWND hwnd = ::GetParent(m_wnd);
		return ns_wnd_register::find_window(hwnd);
	}

	HWND impl_window::get_HWND()
	{
		return m_wnd;
	}

	HINSTANCE impl_window::get_instance()
	{
		return (HINSTANCE)GetWindowLong(m_wnd, GWL_HINSTANCE);
	}

	bool impl_window::is_accept_file()
	{
		return GetWindowLong(m_wnd, GWL_EXSTYLE)&WS_EX_ACCEPTFILES;
	}

	void impl_window::set_accept_file(bool accept)
	{
		if(accept)
			SetWindowLong(m_wnd, GWL_EXSTYLE, GetWindowLong(m_wnd, GWL_EXSTYLE)|WS_EX_ACCEPTFILES );
		else
			SetWindowLong(m_wnd, GWL_EXSTYLE, GetWindowLong(m_wnd, GWL_EXSTYLE)&~WS_EX_ACCEPTFILES );
	}

	void impl_window::set_layered(bool layered)
	{
		if(layered)
			SetWindowLong(m_wnd, GWL_EXSTYLE, GetWindowLong(m_wnd, GWL_EXSTYLE)|WS_EX_LAYERED );
		else
			SetWindowLong(m_wnd, GWL_EXSTYLE, GetWindowLong(m_wnd, GWL_EXSTYLE)&~WS_EX_LAYERED );
	}

	bool impl_window::is_layered()
	{
		return GetWindowLong(m_wnd, GWL_EXSTYLE)&WS_EX_LAYERED;
	}

	void impl_window::set_sizable(bool bsizable)
	{
		if(bsizable)
			SetWindowLong(m_wnd, GWL_STYLE, GetWindowLong(m_wnd, GWL_STYLE)|WS_SIZEBOX  );
		else
			SetWindowLong(m_wnd, GWL_STYLE, GetWindowLong(m_wnd, GWL_STYLE)&~WS_SIZEBOX);	
	}

	bool impl_window::is_sizable()
	{
		return GetWindowLong(m_wnd, GWL_STYLE)&WS_SIZEBOX;
	}

	//ref: http://www.codeproject.com/KB/GDI/pxalphablend.aspx?msg=1442856
	//<<Per Pixel Alpha Blend>>
	void impl_window::update_layered()
	{	
		if(!m_canvas) return;

		using namespace Gdiplus;
		HDC dcScreen;
		HDC dcMemory;

		dcScreen = ::GetDC(NULL);
		HBITMAP bmp;
		Color c(0,0,0,0);

		m_canvas->m_bmp.GetHBITMAP(c, &bmp);
		dcMemory  = ::CreateCompatibleDC(dcScreen);

		HBITMAP pOldBitmap= (HBITMAP)::SelectObject(dcMemory, bmp);


		// get the bitmap dimensions
		BITMAP bmpInfo;
		::GetObject(&m_canvas->m_bmp, sizeof(BITMAP), &bmpInfo);
		int cxBitmap = bmpInfo.bmWidth;
		int cyBitmap = bmpInfo.bmHeight;
		void* bits = bmpInfo.bmBits;
		
		POINT pt;
		SIZE sz;
		this->get_pos(pt.x, pt.y);
		get_size(sz.cx, sz.cy);
		
		//// get the window rectangule (we are only interested in the top left position)
		//CRect rectDlg;
		//wnd.GetWindowRect(rectDlg);

		//// calculate the new window position/size based on the bitmap size
		//CPoint ptWindowScreenPosition(rectDlg.TopLeft());
		//CSize szWindow(bmpInfo.bmWidth, bmpInfo.bmHeight);


		// Perform the alpha blend

		// setup the blend function
		BLENDFUNCTION blendPixelFunction= { AC_SRC_OVER, 0, m_canvas->m_alpha, AC_SRC_ALPHA };
		POINT ptSrc = {0,0}; // start point of the copy from dcMemory to dcScreen

		// perform the alpha blend
		BOOL bRet= ::UpdateLayeredWindow(m_wnd, dcScreen, &pt, &sz, dcMemory,
			&ptSrc, 0, &blendPixelFunction, ULW_ALPHA);

		//ASSERT(bRet); // ops... something bad just occured....

		// clean up
		SelectObject(dcMemory, pOldBitmap);
	}

	void impl_window::set_layered_alpha(unsigned char val)
	{
		m_canvas->m_alpha = val;
		update_layered();
	}

	void impl_window::set_as_child(i_window* paresent)
	{
		if(paresent)
		{
			SetWindowLong(m_wnd, GWL_STYLE, GetWindowLong(m_wnd, GWL_STYLE)|WS_CHILD  );
			::SetParent(m_wnd, paresent->get_HWND() );
		}
		else
		{
			SetWindowLong(m_wnd, GWL_STYLE, GetWindowLong(m_wnd, GWL_STYLE)&~WS_CHILD  );	
			::SetParent(m_wnd, 0 );
		}
	}

	void impl_window::set_as_tool(bool btool)
	{
		if(btool)
		{
			SetWindowLong(m_wnd, GWL_EXSTYLE, GetWindowLong(m_wnd, GWL_EXSTYLE)|WS_EX_TOOLWINDOW  );
		}
		else
		{
			SetWindowLong(m_wnd, GWL_EXSTYLE, GetWindowLong(m_wnd, GWL_EXSTYLE)&~WS_EX_TOOLWINDOW  );
		}
		//InvalidateRect(m_wnd, 0, true);
		//RECT rc;
		//GetWindowRect(m_wnd, &rc);
		//RedrawWindow(m_wnd, 0, 0, RDW_FRAME|RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_ERASE);
		//InvalidateRect(m_wnd, &rc, false);
		
	}

	bool impl_window::is_as_tool()
	{
		return GetWindowLong(m_wnd, GWL_EXSTYLE)&WS_EX_TOOLWINDOW;
	}

	void impl_window::set_bar(bool bbar)
	{
		if(bbar)
		{
			SetWindowLong(m_wnd, GWL_STYLE, GetWindowLong(m_wnd, GWL_STYLE)|WS_CAPTION  );
		}
		else
		{
			SetWindowLong(m_wnd, GWL_STYLE, GetWindowLong(m_wnd, GWL_STYLE)&~WS_CAPTION  );
		}
	}

	bool impl_window::is_bar()
	{
		return GetWindowLong(m_wnd, GWL_STYLE)&WS_CAPTION;
	}

	void impl_window::set_enable(bool able)
	{
		::EnableWindow(m_wnd, able);
	}

	bool impl_window::is_enable()
	{
		return IsWindowEnabled(m_wnd);
	}

	void impl_window::set_visible(bool bshow)
	{
		ShowWindow(m_wnd, bshow);
	}

	bool impl_window::is_visible()
	{
		return ::IsWindowVisible(m_wnd);
	}
	
	void impl_window::redraw()
	{
		RedrawWindow(m_wnd, 
			NULL, 
			NULL, 
			RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
	}

	i_GDI* impl_window::init_GDI()
	{
		if(!m_canvas) create_canvas();
		return m_canvas;
	}

	i_GDI* impl_window::get_GDI()
	{
		return m_canvas;
	}
	ULONG_PTR           gdiplusToken;
	impl_h_windows::impl_h_windows()
	{
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}

	impl_h_windows::~impl_h_windows()
	{	
		GdiplusShutdown(gdiplusToken);
	}

	void impl_h_windows::get_mouse_pos(long& xout, long& yout)
	{
		POINT pt;
		::GetCursorPos(&pt);
		xout = pt.x;
		yout = pt.y;
	}

	//What's the difference between GetKeyState and GetAsyncKeyState?
	bool impl_h_windows::is_key_press(long key)
	{
		return GetAsyncKeyState(key)&0x8000;
	}

	bool impl_h_windows::run_once()
	{
		MSG  msg;
		int status;
		if(PeekMessage (&msg, NULL, 0, 0, PM_REMOVE) )
		{

			if (msg.message == WM_QUIT) return false;

			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;
		}
		else
		{
			//your stuff here to process
			s_on_idle();
		}
		return true;
	}

	i_window* impl_h_windows::create_window(i_window* paresent, long x, long y, long cx, long cy, const char* str_title, st_window_style* pstyle)
	{
		long menu_id = 0;

		
		long style =  WS_OVERLAPPEDWINDOW;
		long ex_style = 0;

		if(pstyle)
		{
			if(pstyle->m_sizeable)
			{
				style |= WS_SIZEBOX;
			}
			else
			{
				style &= ~WS_SIZEBOX;
			}
			if(pstyle->m_bar)
			{
				style |= WS_CAPTION;
				style &= ~WS_POPUP;
			}
			else
			{
				style &= ~WS_CAPTION;
				style |= WS_POPUP;
				
			}
			if(pstyle->m_layered)
			{
				ex_style |= WS_EX_LAYERED;
				ex_style |= WS_EX_TOPMOST;
				style |= WS_POPUP;
				style &= ~WS_CAPTION;
			}
			if(pstyle->m_as_tool)
			{
				ex_style |= WS_EX_TOOLWINDOW;
			}
			else
			{
				ex_style &= ~WS_EX_TOOLWINDOW;
			}

		}
		if(paresent)
		{
			static long id = 1;
			menu_id = id++;
			style = WS_CHILDWINDOW | WS_VISIBLE;
		}

		impl_window* p_win = new impl_window;

		p_win->m_wnd = ::CreateWindowEx
			(ex_style, 
			get_window_class()->lpszClassName,
			str_title, 
			style,
			x, y, 
			cx, cy, 
			paresent == 0? 0 : ((impl_window*)paresent)->m_wnd, (HMENU)menu_id, //paresent, menu
			get_window_class()->hInstance, 0);

		//p_win->create_canvas();
		ns_wnd_register::reg(p_win->m_wnd, p_win);

		if(pstyle)
			::ShowWindow(p_win->m_wnd, pstyle->m_show);
		else
			::ShowWindow(p_win->m_wnd, true);

		//UpdateWindow(p_win->m_wnd);
		return p_win;
	}

	i_button* impl_h_windows::create_button(i_window* paresent, long x, long y, long cx, long cy, const char* str_title)
	{
		HWND hsT = CreateWindowEx(
			0,			"BUTTON",			str_title,
			WS_VISIBLE | WS_CHILD | BS_LEFT | WS_BORDER,
			x,			y,			cx,			cy,			paresent->get_HWND(),			NULL,
			paresent->get_instance(),			NULL);

		impl_button* ret = new impl_button;

		ret->m_wnd = hsT;
		ns_wnd_register::reg(ret->m_wnd, ret);

		return ret;
	}

	i_static* impl_h_windows::create_static(i_window* paresent, long x, long y, long cx, long cy, const char* str_title)
	{
		HWND hsT = CreateWindowEx(
			0,			"STATIC",			str_title,
			WS_VISIBLE | WS_CHILD | SS_LEFT | WS_TABSTOP,
			x,			y,			cx,			cy,			paresent->get_HWND(),			NULL,
			paresent->get_instance(),			NULL);

		impl_static* ret = new impl_static;
		
		ret->m_wnd = hsT;
		ns_wnd_register::reg(ret->m_wnd, ret);

		return ret;
	}
	
	i_window* impl_static::get_window()
	{
		return (impl_window*)this;
	}

	void impl_static::set_text(const char* text)
	{
		SendMessage(m_wnd, WM_SETTEXT, 0, (LPARAM)text); // for Win32 windows
	}


	const char* impl_static::get_text()
	{
		static char buff_out[1024];
		size_t length = SendMessage(m_wnd, WM_GETTEXT, (WPARAM) 1023, (LPARAM) buff_out);
		buff_out[length] = '\0';
		return buff_out;
	}

	i_window* impl_edit::get_window()
	{
		return (impl_window*)this;
	}

	void impl_edit::set_text(const char* text)
	{
		SendMessage(m_wnd, WM_SETTEXT, 0, (LPARAM)text); // for Win32 windows
	}

	const char* impl_edit::get_text()
	{
		static char buff_out[1024];
		size_t length = SendMessage(m_wnd, WM_GETTEXT, (WPARAM) 1023, (LPARAM) buff_out);
		buff_out[length] = '\0';
		return buff_out;
	}


	i_window* impl_button::get_window()
	{
		return (impl_window*)this;
	}

	void impl_button::set_text(const char* text)
	{
		SendMessage(m_wnd, WM_SETTEXT, 0, (LPARAM)text); // for Win32 windows
	}

	const char* impl_button::get_text()
	{
		static char buff_out[1024];
		size_t length = SendMessage(m_wnd, WM_GETTEXT, (WPARAM) 1023, (LPARAM) buff_out);
		buff_out[length] = '\0';
		return buff_out;
	}

	i_edit* impl_h_windows::create_edit(i_window* paresent, long x, long y, long cx, long cy, const char* text)
	{
		HWND hsT = CreateWindowEx(
			0,			"EDIT",			text,
			WS_VISIBLE | WS_CHILD | SS_LEFT | WS_TABSTOP,
			x,			y,			cx,			cy,			paresent->get_HWND(),			NULL,
			paresent->get_instance(),			NULL);

		impl_edit* ret = new impl_edit;
		ret->m_wnd = hsT;
		
		ns_wnd_register::reg(ret->m_wnd, ret);
		return ret;
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
namespace ns_base
{
	M_IMPL(h_windows, impl_h_windows);//2. 接口实现
	M_OPEN();//3. 模块建立
};
