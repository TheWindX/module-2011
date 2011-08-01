#pragma once

namespace ns_base
{
	//接口导出
	struct h_datetime
	{
		virtual const char* now_local_format(const char* cstr_format) = 0;
		virtual const char* now_gregorian_format(const char* cstr_format) = 0;
		virtual const char* clock_local_format(long time, const char* cstr_format) = 0;
		virtual const char* clock_gregorian_format(long time, const char* cstr_format) = 0;

		//TODO, 
		/************************************************************************/
		/* clock

		*/
		/************************************************************************/
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_datetime, "datetime.dll");
