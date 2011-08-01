
#pragma once

namespace drawing
{
	draw_line(float x, float y);
	draw_rect(bool solid, float x, float y, float x1, float y1);
	draw_image(const char* fname);

	//在on draw里调用
}