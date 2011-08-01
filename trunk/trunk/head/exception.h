
#pragma once

#define MAX_ERR_DESC 512
namespace ns_common
{
	struct st_exception
	{
		char m_desc[MAX_ERR_DESC];
		const char *  what ()
		{
			return m_desc;
		}
	};
}

//TODO, MAX LENGTH OVERFLOW, SAFE COPY
#define RAISE_EXCEPTION(desc)\
	{	ns_common::st_exception ret_exception;\
	sprintf(ret_exception.m_desc, "(%s)(%s)(%d)(%s)", __FILE__, __FUNCTION__, __LINE__, desc);\
	throw ret_exception;}
