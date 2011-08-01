#pragma once
#include "../head/ref_counter.h"
#include "../filesystem/interface.h"

namespace ns_base
{
	typedef ns_base::i_buffer i_buffer;

	enum	{	e_zlib = 0,e_qlz, e_lzo, e_lzma	};
	
	struct h_compress
	{
		virtual i_buffer* compress(int type, const char* src, size_t sz_src, size_t sz_des_gress) = 0;
		virtual i_buffer* uncompress(int type, const char* src, size_t sz_src, size_t sz_des_gress) = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_compress, "compress.dll");