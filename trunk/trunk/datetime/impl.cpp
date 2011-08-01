#include "impl.h"


#include <stdio.h>
#include <time.h>
#include "windows.h"
#include "time.h"
#include "stdio.h"
#include <vector>
#include <map>

namespace ns_base
{
	const char* translate(const char* cstr_format, int Y, int M, int D, int h, int m, int s)
	{

		static const char* flag[6] = 
		{
			"%Y", "%M", "%D","%h", "%m", "%s"
		};

		std::string flagidx2strval[6];
		char str_tmp[16];
		sprintf(str_tmp, "%04d", Y);
		flagidx2strval[0] = str_tmp;
		sprintf(str_tmp, "%02d", M);
		flagidx2strval[1] = str_tmp;
		sprintf(str_tmp, "%02d", D);
		flagidx2strval[2] = str_tmp;
		sprintf(str_tmp, "%02d", h);
		flagidx2strval[3] = str_tmp;
		sprintf(str_tmp, "%02d", m);
		flagidx2strval[4] = str_tmp;
		sprintf(str_tmp, "%02d", s);
		flagidx2strval[5] = str_tmp;

		static std::string str_ret;
		str_ret.clear();

		std::string str_format = cstr_format;
		std::map<size_t, size_t> pos2flag;
		for(size_t i = 0; i<6; ++i)
		{	
			size_t sz = str_format.find(flag[i]);
			if(sz != std::string::npos)
				pos2flag[sz] = i;
		}

		std::map<size_t, size_t>::iterator it = pos2flag.begin();
		size_t old_idx = 0;
		for(; it!=pos2flag.end(); ++it)
		{
			size_t pos = it->first;
			size_t flag_idx = it->second;
			str_ret.insert(str_ret.end(),
				str_format.begin()+old_idx, str_format.begin()+pos);

			str_ret.insert(str_ret.end(), 
				flagidx2strval[flag_idx].begin(), flagidx2strval[flag_idx].end() );

			old_idx = pos+2;
		}
		str_ret.insert(str_ret.end(),
			str_format.begin()+old_idx, str_format.end() );
		return str_ret.c_str();
	}

	const char* local_format(time_t t, const char* format)
	{	
		struct tm *ptr = localtime(&t);
		return translate(format, ptr->tm_year+1900, ptr->tm_mon+1, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
	}

	const char* gregorian_format(time_t t, const char* format)
	{	
		struct tm *ptr = gmtime(&t);
		return translate(format, ptr->tm_year+1900, ptr->tm_mon+1, ptr->tm_mday, ptr->tm_hour, ptr->tm_min, ptr->tm_sec);
	}

	const char* impl_datetime::now_local_format(const char* cstr_format)
	{
		time_t t = time(0);
		return local_format(t, cstr_format);
	}
	const char* impl_datetime::now_gregorian_format(const char* cstr_format)
	{
		time_t t = time(0);
		return gregorian_format(t, cstr_format);
	}
	const char* impl_datetime::clock_local_format(long time, const char* cstr_format)
	{
		return local_format(time, cstr_format);
	}

	const char* impl_datetime::clock_gregorian_format(long time, const char* cstr_format)
	{
		return gregorian_format(time, cstr_format);
	}

}


#include "../head/M_interface.h"

M_IMPL(ns_base::h_datetime, ns_base::impl_datetime);//2. 接口实现
M_OPEN();//3. 模块建立
