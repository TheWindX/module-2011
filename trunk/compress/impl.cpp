#pragma once
#include "impl.h"
#include "compress.h"
#include "../filesystem/interface.h"
#include <vector>

#include "../head/utility_new.h"

namespace ns_base
{
	i_buffer* impl_compress::compress(int type, const char* src, size_t sz_src, size_t sz_des_gress)
	{
		std::vector<char> buff_out;
		buff_out.resize(sz_des_gress);

		size_t sz_ret = sz_des_gress;
		bool ret = false;
		switch (type)
		{
		case e_zlib:
			ret = ns_compress::ns_comp::zlib(&buff_out[0], sz_ret, src, sz_src);
			break;
		case e_lzo:
			ret = ns_compress::ns_comp::lzo(&buff_out[0], sz_ret, src, sz_src);
			break;
		case e_qlz:
			ret = ns_compress::ns_comp::qlz(&buff_out[0], sz_ret, src, sz_src);
			break;
		case e_lzma:
			ret = ns_compress::ns_comp::lzma(&buff_out[0], sz_ret, src, sz_src);
			break;
		default:
			return 0;
		};

		if(!ret) return 0;

		ns_base::h_filesystem* p_fs;
		get(p_fs);
		i_buffer* p_buff = p_fs->create_buff(&buff_out[0], sz_ret);
		
		return p_buff;
	}

	i_buffer* impl_compress::uncompress(int type, const char* src, size_t sz_src, size_t sz_des_gress)
	{
		std::vector<char> buff_out;
		buff_out.resize(sz_des_gress);

		size_t sz_ret = sz_des_gress;
		bool ret = false;
		switch (type)
		{
		case e_zlib:
			ret = ns_compress::ns_uncomp::zlib(&buff_out[0], sz_ret, src, sz_src);
			break;
		case e_lzo:
			ret = ns_compress::ns_uncomp::lzo(&buff_out[0], sz_ret, src, sz_src);
			break;
		case e_qlz:
			ret = ns_compress::ns_uncomp::qlz(&buff_out[0], sz_ret, src, sz_src);
			break;
		case e_lzma:
			ret = ns_compress::ns_uncomp::lzma(&buff_out[0], sz_ret, src, sz_src);
			break;
		default:
			return 0;
		};

		if(!ret) return 0;

		ns_base::h_filesystem* p_fs;
		get(p_fs);
		i_buffer* p_buff = p_fs->create_buff(&buff_out[0], sz_ret);

		return p_buff;
	}

}


HINSTANCE g_moduler;
BOOL APIENTRY DllMain( HINSTANCE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
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

M_IMPL(ns_base::h_compress, ns_base::impl_compress);//2. 接口实现
M_OPEN();//3. 模块建立

