
#include "vm.h"
#include "proto_code.h"
#include "proto_value.h"

namespace ns_core
{
	st_function_value::st_function_value(st_vm* rt, st_function_code* code)
	{
		m_yield = 0;
		m_code = code;
		u32 sz = code->m_ref_map.size();
		if(sz != 0)
		{
			m_refs = new array<st_value>;
			for(u32 i = 0; i<sz; ++i)
			{
				u32 ref_idx = code->m_ref_map[i];
				if(ref_idx == U32_NA)
				{
					st_value* rv = new st_value();
					m_refs->push(st_v_ref::make_value(rv) );
				}
				else
				{
					m_refs->push(rt->get_ref_raw(ref_idx) );
				}
			}
		}
		else
			m_refs = 0;

	}
}

