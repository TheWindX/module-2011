
#pragma once

#include "types.h"
#include "stack.h"
#include "list.h"
#include "easy_set.h"
#include "easy_map.h"

namespace ns_core
{
	u32 gen_id();//ID Éú³ÉÆ÷

	struct st_vm;
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

		const char* to_string(st_vm* rt);
		const char* to_code_string(st_vm* rt);
	};

	typedef st_value st_code;
}

