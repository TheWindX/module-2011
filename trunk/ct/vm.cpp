

#include "vm.h"
#include "functor.h"
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

	//for debug
	u32 st_vm_state::s_cur_pc()
	{
		return m_cur_pc;
	}

	st_code st_vm_state::s_cur_code()
	{
		return m_codes[m_cur_pc];
	}

	u32 st_vm_state::s_eval_size()
	{
		return get_eval_size();
	}

	st_value st_vm_state::s_eval_value(u32 idx)
	{
		return get_eval(idx);
	}

	u32 st_vm_state::s_local_size()
	{
		return get_local_size();
	}
	st_value st_vm_state::s_local_value(u32 idx)
	{
		return get_local(idx);
	}
	u32 st_vm_state::s_ref_size()
	{
		return get_ref_size();
	}
	st_value st_vm_state::s_ref_value(u32 idx)
	{
		return get_ref(idx);
	}

	st_value st_vm_state::s_ref_raw(u32 idx)
	{
		return get_ref_raw(idx);
	}

	st_vm::st_vm()
	{
		m_ctx = new impl_context;
		static_cast<impl_context*>(m_ctx)->m_vm = this;
	}

	st_vm::~st_vm()
	{
		delete m_ctx;
	}

	std::string st_vm::code_to_string(u32 idx)
	{
		if(idx<m_codes.size() )
		{
			st_code c = m_codes[idx];
			return ns_core::code_to_string(c, this);
		}
		else return "code idx is overflow!";
	}
}

