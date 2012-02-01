
#include "gdiplus_user.h"
#include <objidl.h>

using namespace Gdiplus;


namespace ns_gdiplus
{
	void move_to(float x, float y)
	{
		g_points.clear();
		g_points.push_back(PointF(x, y) );
	}

	void line_to(float x, float y)
	{	
		g_points.push_back(PointF(x, y) );
	}

	void draw_path(Gdiplus::Graphics& g, unsigned int color)
	{
		Gdiplus::Color c(color);
		Gdiplus::Pen p(c );
		g.DrawLines(&p, &g_points[0], g_points.size() );
	}

	void draw_polygon(Gdiplus::Graphics& g, unsigned int color)
	{
		Gdiplus::Color c(color);
		Gdiplus::Pen p(c );
		g.DrawPolygon(&p, &g_points[0], g_points.size() );
	}

	void fill_polygon(Gdiplus::Graphics& g, unsigned int color)
	{

	}

	void draw_point(Gdiplus::Graphics& g, unsigned int color, float x, float y)
	{
		Gdiplus::Color c(color);
		Gdiplus::SolidBrush b(c );
		g.FillRectangle(&b, (int)x, (int)y, 1, 1);
	}

	void draw_line(Gdiplus::Graphics& g, unsigned int color, float x1, float y1, float x2, float y2)
	{	
		Gdiplus::Color c(color);
		Gdiplus::Pen p(c );
		g.DrawLine(&p, x1, y1, x2, y2);
	};

	void draw_rect(Gdiplus::Graphics& g, bool solid, unsigned int color, float x1, float y1, float wid, float height)
	{
		if(!solid)
		{
			Gdiplus::Color c(color);
			Gdiplus::Pen p(c );
			g.DrawRectangle(&p, x1, y1, wid, height);
		}
		else
		{
			Gdiplus::Color c(color);
			Gdiplus::SolidBrush b(c );
			g.FillRectangle(&b, x1, y1, wid, height);
		}
	};

	void draw_text(Gdiplus::Graphics& g, const char* text, const char* str_font, unsigned int sz, unsigned int color, float x1, float y1)
	{
		Gdiplus::PointF pointF(x1,y1);
		Gdiplus::Color c(color);
		Gdiplus::SolidBrush brush( c );  
		std::wstring wstr = MtbToWstr(std::string(text) );

		std::wstring wstr1 = MtbToWstr(std::string(str_font) );
		Gdiplus::FontFamily fontFamily(wstr1.c_str() );         //选择一种字体
		Gdiplus::Font font(&fontFamily, sz, Gdiplus::FontStyleRegular,Gdiplus::UnitPixel);
		g.DrawString(wstr.c_str(), -1, &font, pointF, &brush);
	};
	
	static ULONG_PTR           gdiplusToken;
	void init()
	{
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		g_points.clear();
	}

	void release()
	{
		GdiplusShutdown(gdiplusToken);
		g_points.clear();
	}
}

