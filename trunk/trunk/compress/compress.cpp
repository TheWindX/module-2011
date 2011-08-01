#include <cstdio>
#include "zlib.h"
#include "lzo/lzoconf.h"
#include "lzo/lzo1x.h"
#include "lzma/LzmaLib.h"
extern "C"
{
#include "qlz/quicklz.h"
};

namespace ns_compress
{
	namespace ns_comp
	{
		bool zlib(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{
			int r = compress2( (Bytef*)des, reinterpret_cast<uLongf*>(&sz_des), (Bytef*)src, sz_src, 9);
			if(r == Z_OK)
			{
				return true;
			}
			else
			{
				printf("压缩方法:zlib error!\n");
				return false;
			}
		}

		bool qlz(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{
			char *scratch = (char *)malloc(sz_des);
			sz_des = qlz_compress(src, des, sz_src, scratch);
			free(scratch);
			if(sz_des == 0)
			{
				printf("压缩方法:qlz error!\n");
				return false;
			}
			else
			{	
				return true;
			}

		}

		bool lzo(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{
			if (lzo_init() != LZO_E_OK)
			{
				printf("internal error - lzo_init() failed !!!\n");
				printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable `-DLZO_DEBUG' for diagnostics)\n");
				return false;
			} 
			char* wrkmem = (char*)malloc(LZO1X_999_MEM_COMPRESS);
			int r = lzo1x_999_compress( (unsigned char*)src,sz_src,(unsigned char*)des,(lzo_uint*)(&sz_des),wrkmem);
			free(wrkmem);
			if (r == LZO_E_OK) 
			{	
				return true;
			}
			else
			{
				printf("压缩方法:lzo error!\n");
				return false;
			}
		}


		bool lzma(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{
			size_t sizeProp = 5;
			int rc = LzmaCompress( (unsigned char*)(des+6), &sz_des, (unsigned char*)src, sz_src, (unsigned char*)des, &sizeProp, 9, (1<<24), 3, 0, 2, 32, 2);
			*(des+5) = sizeProp;
			sz_des += 6;//多六个字节的写入
			if(rc != SZ_OK) 
			{
				printf("压缩方法:lzma error!\n");
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	namespace ns_uncomp
	{
		bool lzo(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{
			int r = lzo1x_decompress( (const unsigned char*)src,sz_src,(unsigned char*)des, (lzo_uint*)&sz_des, NULL);
			if (r == LZO_E_OK)
			{	
				return true;
			}
			else
			{
				/* this should NEVER happen */
				printf("internal error - decompression failed: %d\n", r);
				return false;
			} 
		}

		bool qlz(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{
			char *scratch = (char *)malloc(sz_des);
			sz_des = qlz_decompress(src, des, scratch);
			free(scratch);
			if(sz_des == 0)
			{
				printf("test_decompress_qlz error!\n");
				return false;
			}
			else
			{	
				return true;
			}
		}

		bool zlib(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{

			int r = uncompress( (Bytef*)des, reinterpret_cast<uLongf*>(&sz_des), (Bytef*)src, sz_src);
			if(r == Z_OK)
			{
				return true;
			}
			else
			{
				printf("test_decompress_zlib error!\n");
				return false;
			}
		}

		bool lzma(char* des, size_t& sz_des, const char* src, size_t sz_src)
		{	
			int sizeProp = *(src+5);//leave 5 for prop
			sz_src -= 6;
			int r = LzmaUncompress( (unsigned char*)des, &sz_des, (unsigned char*)(src+6), &sz_src, (unsigned char*)src, sizeProp);

			if(r == SZ_OK || r == SZ_ERROR_INPUT_EOF)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}