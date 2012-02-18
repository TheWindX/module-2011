

#include "vm.h"
#include "functor.h"
#include "proto_value.h"

namespace ns_core
{
	u32 impl_context::in_size()
	{
		return m_vm->get_eval_size();
	}

	void* impl_context::get_value(u32 idx)
	{
		return &m_vm->get_eval(idx);
	}

	const char* impl_context::value_to_string(void* v)
	{
		return ns_core::value_to_string( *((st_value*)v), m_vm);
	}

	bool impl_context::to_int(long idx, int& out)
	{
		st_value& v = m_vm->get_eval(idx);
		if(v.m_tag == ns_base::singleton<st_v_int>::instance().m_tag )
		{
			out = v.m_num;
			return true;
		}
		return false;
	}

	bool impl_context::to_bool(long idx, bool& out)
	{
		st_value& v = m_vm->get_eval(idx);
		if(v.m_tag == ns_base::singleton<st_v_bool>::instance().m_tag )
		{
			out = v.get<bool>();
			return true;
		}
		return false;		
	}

	bool impl_context::to_string(long idx, char* buff, long max_sz)
	{
		st_value& v = m_vm->get_eval(idx);
		if(v.m_tag == ns_base::singleton<st_v_string>::instance().m_tag )
		{
			const char* s = v.get<const char*>();
			int sz = strlen(s);
			if(sz>=max_sz) return false;
			else
			{
				strcpy(buff, s);
				return true;
			}
			
		}
		return false;
	}

	void impl_context::begin_push()
	{
		m_vm->m_evals.resize(m_vm->m_cur_eval_tag);
	}

	void impl_context::push_bool(bool b)
	{
		st_value v = st_v_bool::make_value(b);
		m_vm->m_evals.push(v);
	}

	void impl_context::push_int(int num)
	{	
		st_value v = st_v_int::make_value(num);
		m_vm->m_evals.push(v);
	}

	void impl_context::push_string(const char* str)
	{
		st_value v = st_v_string::make_value(str);
		m_vm->m_evals.push(v);
	}
}