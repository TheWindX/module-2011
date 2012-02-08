

#pragma once

#include <set>

namespace ns_util
{
	struct st_str_pool
	{
		struct st_cmp
		{
			typedef char* c_t;
			bool operator() (const char *s1, const char *s2) const
			{
				return strcmp(s1, s2) < 0;
			}

		};

		typedef std::set<char*, st_cmp> strset_t;
		strset_t m_pool;
		char* reg(const char* str);

		~st_str_pool();
	};
	
}