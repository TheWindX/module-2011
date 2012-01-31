#pragma once
#include "interface.h"
#include "../filesystem/interface.h"

namespace ns_base
{
	struct impl_compress : public h_compress
	{
		i_buffer* compress(int type, const char* src, size_t sz_src, size_t sz_des_gress);
		i_buffer* uncompress(int type, const char* src, size_t sz_src, size_t sz_des_gress);
	};
}
