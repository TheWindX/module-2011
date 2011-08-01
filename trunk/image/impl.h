#pragma once
#include "interface.h"

#include "CxImage\ximage.h"
#include "CxImage\xfile.h"

namespace ns_base
{
	struct impl_image : public i_image, public ns_common::impl_ref_counter
	{	
		CxImage m_img;
		impl_image(CxImage& img):m_img(img){}
		impl_image(){};

		//ת����ʽ
		i_image* to_image();
		ns_base::i_buffer* to_buff(long img_type);
		void to_file(const char* fname, long img_type);

		//����
		void flood(st_color col);
		st_color get_pixel_argb(long x, long y);
		void set_pixel_argb(long x, long y, st_color col);
		void set_pixel_argb(long x, long y, long col);

		//transform
		//����
		i_image* crop_to(long left, long top, long right, long bottom);
		void crop(long left, long top, long right, long bottom);

		//��ת
		void rotate(float angle);

		//����
		void resample(long width, long height, long filter_type);//0:good, 1:fast, 2:best but slow
		void thumbnail(long width, long height);

		//ͼ����
		void gaussian_blur(float radius);

		//����
		void size(long& x, long& y);

		//����
		void draw_line(long fromx, long fromy, long tox, long toy, st_color col);
		HBITMAP get_bitmap(HDC hdc);
	};


	struct impl_h_image : public h_image
	{
		//����
		i_image* create(long width, long height);

		//��ȡ
		i_image* create_from_buffer(ns_base::i_buffer* buff, long img_type);
		i_image* create_from_file(const char* fname, long img_type);
	};
}