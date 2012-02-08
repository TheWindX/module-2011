
#pragma once

#include "flex_user.h"

namespace ns_base
{
	struct st_exception
	{
		char* m_desc;
		const char *  what ()
		{
			return m_desc;
		}

		st_exception(const char* str):m_desc(strdup(str) ){}
		virtual ~st_exception()
		{
			if(m_desc) free(m_desc);
		}
	};


	struct st_compile_exception : public st_exception
	{
		//location
		YYLTYPE m_location;
		st_compile_exception(const char* str):st_exception(str){};
	};
}

#define RAISE_EXCEPTION(desc)\
	{	ns_base::st_exception ret_exception;\
	ret_exception.m_desc = new char[256];\
	sprintf(ret_exception.m_desc, "(%s)(%s)(%d)(%s)", __FILE__, __FUNCTION__, __LINE__, desc);\
	throw ret_exception;}
