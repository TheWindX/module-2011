#include "misc.h"

namespace ns_util
{
	char* st_str_pool::reg(const char* str)
	{
		strset_t::iterator it = m_pool.find(const_cast<char*>(str) );
		if(it != m_pool.end() )
		{
			return const_cast<char*>(*it);
		}
		else
		{
			char* tmp = strdup(str);
			m_pool.insert(tmp);
			return tmp;
		}
	}

	st_str_pool::~st_str_pool()
	{
		strset_t::iterator it = m_pool.begin();
		for(;it != m_pool.end(); ++it)
		{
			free(*it);
		}
	}
}