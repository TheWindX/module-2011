#include "impl.h"
#include "../head/exception.h"
#include "../head/utility_new.h"

namespace ns_base
{
	long type2cxtype(long t)
	{
		switch (t)
		{
		case e_bmp:
			return CXIMAGE_FORMAT_BMP;
			break;
		case e_tga:
			return CXIMAGE_FORMAT_TGA;
			break;
		case e_jpg:
			return CXIMAGE_FORMAT_JPG;
			break;
		default:
			RAISE_EXCEPTION("");
			return 0;
			;
		}
	}

	//转化格式
	i_image* impl_image::to_image()
	{
		return new impl_image(*this);
	}

	ns_base::i_buffer* impl_image::to_buff(long img_type)
	{
		char* buff = 0;
		long size = 0;
		m_img.Encode((BYTE*&)buff, size, type2cxtype(img_type) );

		ns_base::h_filesystem* fs;
		ns_base::get(fs);
		ns_base::i_buffer* ret = fs->create_buff(buff, size);
		m_img.FreeMemory(buff);

		return ret;
	}

	void impl_image::to_file(const char* fname, long img_type)
	{
		if(!m_img.Save(fname, type2cxtype(img_type) ) )
		{
			RAISE_EXCEPTION(fname);
		}
	}

	//象素
	void impl_image::flood(st_color col)
	{
		RGBQUAD c;
		c.rgbBlue = col.channel.blue;
		c.rgbGreen = col.channel.green;
		c.rgbRed = col.channel.red;
		c.rgbReserved = col.channel.alpha;

		long h  = m_img.GetHeight();
		long w  = m_img.GetWidth();
		for(long ih = 0; ih<h; ++ih)
		{
			for(long iw = 0; iw<w; ++iw)
			{
				m_img.SetPixelColor(iw, ih, c, true);
			}
		}

	}

	st_color impl_image::get_pixel_argb(long x, long y)
	{	
		RGBQUAD c = m_img.GetPixelColor(x, y, true);
		st_color col(c.rgbReserved, c.rgbRed, c.rgbGreen, c.rgbBlue);
		return col;
	}

	void impl_image::set_pixel_argb(long x, long y, st_color col)
	{
		RGBQUAD c;
		c.rgbBlue = col.channel.blue;
		c.rgbGreen = col.channel.green;
		c.rgbRed = col.channel.red;
		c.rgbReserved = col.channel.alpha;

		m_img.SetPixelColor(x, y, c, true);
	}

	void impl_image::set_pixel_argb(long x, long y, long color)
	{
		st_color col(color);
		RGBQUAD c;
		c.rgbBlue = col.channel.blue;
		c.rgbGreen = col.channel.green;
		c.rgbRed = col.channel.red;
		c.rgbReserved = col.channel.alpha;

		m_img.SetPixelColor(x, y, c, true);
	}

	//transform
	//剪切
	i_image* impl_image::crop_to(long left, long top, long right, long bottom)
	{
		impl_image* ret = new impl_image;
		
		if(!m_img.Crop(left, top, right, bottom, &ret->m_img) )
		{
			RAISE_EXCEPTION("");
			delete ret;
			return 0;
		}
		return ret;
	}

	void impl_image::crop(long left, long top, long right, long bottom)
	{
		if(!m_img.Crop(left, top, right, bottom) )
		{
			RAISE_EXCEPTION("");
		}
	}

	//旋转
	void impl_image::rotate(float angle)
	{
		if(!m_img.Rotate(angle) )
		{
			RAISE_EXCEPTION("");
		}
	}

	//采样
	void impl_image::resample(long width, long height, long filter_type)//0:good, 1:fast, 2:best but slow
	{
		if(!m_img.Resample(width, height, filter_type) )
		{
			RAISE_EXCEPTION("");
		}
	}

	void impl_image::thumbnail(long width, long height)
	{
		RGBQUAD border;
		memset(&border, 0, sizeof(border) );
		if(!m_img.Thumbnail(width, height, border) )
		{
			RAISE_EXCEPTION("");
		}
	}

	//图象处理
	void impl_image::gaussian_blur(float radius)
	{
		if(!m_img.GaussianBlur(radius) )
		{
			RAISE_EXCEPTION("");
		}
	}

	//属性
	void impl_image::size(long& x, long& y)
	{
		x = m_img.GetWidth();
		y = m_img.GetHeight();
	}

	//绘制
	void impl_image::draw_line(long fromx, long fromy, long tox, long toy, st_color col)
	{
		RGBQUAD c;
		c.rgbBlue = col.channel.blue;
		c.rgbGreen = col.channel.green;
		c.rgbRed = col.channel.red;
		c.rgbReserved = col.channel.alpha;
		m_img.DrawLine(fromx, tox, fromy, toy, c, true);
	}

	HBITMAP impl_image::get_bitmap(HDC hdc)
	{
		return m_img.MakeBitmap(hdc);
	}

	//创建
	i_image* impl_h_image::create(long width, long height)
	{
		impl_image* ret = new impl_image;
		if(!ret->m_img.Create(width, height, 24) )
		{
			delete ret;
			RAISE_EXCEPTION("");
			return 0;
		}
		if(!ret->m_img.AlphaCreate() )
		{
			delete ret;
			RAISE_EXCEPTION("Alpha创建失败");
			return 0;
		}
		return ret;
	}

	//读取
	i_image* impl_h_image::create_from_buffer(ns_base::i_buffer* buff, long img_type)
	{
		impl_image* ret = new impl_image;

		if(!ret->m_img.Decode((BYTE*)buff->ptr(), buff->size(), type2cxtype(img_type) ) )
		{
			delete ret;
			RAISE_EXCEPTION("读取buff失败");
			return 0;
		}

		if(ret->m_img.GetBpp() != 24)
		{
			if(!ret->m_img.IncreaseBpp(24) )
			{
				delete ret;
				RAISE_EXCEPTION("IncreaseBpp(24)");
				return 0;
			}
		}
		if(!ret->m_img.AlphaIsValid() )
		{
			if(!ret->m_img.AlphaCreate() )
			{
				delete ret;
				RAISE_EXCEPTION("IncreaseBpp(24)");
				return 0;
			}
		}
		return ret;
	}

	i_image* impl_h_image::create_from_file(const char* fname, long img_type)
	{
		impl_image* ret = new impl_image;

		if(!ret->m_img.Load(fname, type2cxtype(img_type) ) )
		{
			delete ret;
			RAISE_EXCEPTION(fname);
			return 0;
		}

		if(ret->m_img.GetBpp() != 24)
		{
			if(!ret->m_img.IncreaseBpp(24) )
			{
				delete ret;
				RAISE_EXCEPTION("IncreaseBpp(24)失败");
				return 0;
			}
		}
		if(!ret->m_img.AlphaIsValid() )
		{
			if(!ret->m_img.AlphaCreate() )
			{
				delete ret;
				RAISE_EXCEPTION("alpha创建失败");
				return 0;
			}
		}
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

M_IMPL(ns_base::h_image, ns_base::impl_h_image);//2. 接口实现
M_OPEN();//3. 模块建立


