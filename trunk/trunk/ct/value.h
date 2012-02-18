
#pragma once

#include "utilies.h"

namespace ns_core
{
	using namespace ns_base;
	//value
	struct st_value
	{
		u32 m_tag;
		union
		{
			u32 m_num;
			void* m_val;
		};

		template<typename T>
			T& get()
		{
			return (T&)m_val;
		}

		template<typename T>
			void set(T& val)
		{
			m_val = (void*)val;
		}

		template<>
			void set<s32>(s32& val)
		{
			m_num = val;
		}

		template<>
			void set<u32>(u32& val)
		{
			m_num = val;
		}
	};

	typedef st_value st_code;

	struct st_vm;
	typedef u32 (*f_proto)(st_vm* rt);//function proto
}