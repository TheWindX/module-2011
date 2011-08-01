#pragma once
#include "interface.h"

namespace ns_base
{
	struct impl_datetime : public h_datetime
	{
		const char* now_local_format(const char* cstr_format);
		const char* now_gregorian_format(const char* cstr_format);
		const char* clock_local_format(long time, const char* cstr_format);
		const char* clock_gregorian_format(long time, const char* cstr_format);
	};
}