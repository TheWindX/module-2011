
#pragma once

typedef bool(*COMPRESS_PROTO)(char* des, size_t& sz_des, const char* src, size_t sz_src);
typedef bool(*UN_COMPRESS_PROTO)(char* des, size_t& sz_des, const char* src, size_t sz_src);

namespace ns_compress
{
	namespace ns_comp
	{
		bool zlib(char* des, size_t& sz_des, const char* src, size_t sz_src);

		bool qlz(char* des, size_t& sz_des, const char* src, size_t sz_src);

		bool lzo(char* des, size_t& sz_des, const char* src, size_t sz_src);

		bool lzma(char* des, size_t& sz_des, const char* src, size_t sz_src);
	}

	namespace ns_uncomp
	{
		bool lzo(char* des, size_t& sz_des, const char* src, size_t sz_src);

		bool qlz(char* des, size_t& sz_des, const char* src, size_t sz_src);

		bool zlib(char* des, size_t& sz_des, const char* src, size_t sz_src);

		bool lzma(char* des, size_t& sz_des, const char* src, size_t sz_src);
	}
}