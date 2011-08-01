#pragma once
#include "../head/ref_counter.h"
#include "../head/M_interface.h"
#include "../filesystem/interface.h"

namespace ns_base
{
	enum
	{
		e_bmp = 0,e_tga,e_png,e_gif,e_jpg,e_ico,
	};

	struct st_color
	{
		union{struct{
			unsigned char blue, green, red, alpha;}channel;
			long value;
		};

		st_color(long v):value(v){};
		st_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			channel.alpha = a;
			channel.red = r;
			channel.green = g;
			channel.blue = b;
		}
	};

	struct i_image : public virtual ns_common::i_ref_counter
	{
		//转化格式
		virtual i_image* to_image() = 0;
		virtual ns_base::i_buffer* to_buff(long img_type) = 0;
		virtual void to_file(const char* fname, long img_type) = 0;

		//象素
		virtual void flood(st_color col) = 0;
		virtual st_color get_pixel_argb(long x, long y) = 0;
		virtual void set_pixel_argb(long x, long y, st_color col) = 0;
		virtual void set_pixel_argb(long x, long y, long col) = 0;
		
		//transform
		//剪切
		virtual i_image* crop_to(long left, long top, long right, long bottom) = 0;
		virtual void crop(long left, long top, long right, long bottom) = 0;
		
		//旋转
		virtual void rotate(float angle) = 0;

		//采样
		virtual void resample(long width, long height, long filter_type = 1) = 0;//0:good, 1:fast, 2:best but slow
		virtual void thumbnail(long width, long height) = 0;

		//图象处理
		virtual void gaussian_blur(float radius) = 0;

		//属性
		virtual void size(long& x, long& y) = 0;

		//绘制
		virtual void draw_line(long fromx, long fromy, long tox, long toy, st_color col) = 0;
		virtual HBITMAP get_bitmap(HDC hdc) = 0;
	};


	struct h_image
	{
		//创建
		virtual i_image* create(long width, long height) = 0;

		//读取
		virtual i_image* create_from_buffer(ns_base::i_buffer* buff, long img_type) = 0;
		virtual i_image* create_from_file(const char* fname, long img_type) = 0;
	};
}

M_DECL(ns_base::h_image, "image.dll");
