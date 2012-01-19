
#pragma once
#include <windows.h>
#include <string>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

namespace ns_gdiplus
{
	void init();
	void release();

	void draw_point(Gdiplus::Graphics& g, unsigned int color, float x, float y);

	void draw_line(Gdiplus::Graphics& g, unsigned int color, float x1, float y1, float x2, float y2);

	void draw_rect(Gdiplus::Graphics& g, bool solid, unsigned int color, float x1, float y1, float wid, float height);

	void draw_text(Gdiplus::Graphics& g, const char* text, const char* str_font, unsigned int sz, unsigned int color, float x1, float y1);
}
	
