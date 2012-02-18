#include "config.h"
#include "vm.h"

#include "proto_code.h"
#include "proto_value.h"

#include "primarys.h"

namespace ns_core
{
	//要实现 debug, 得在 debug 时退出循环,而且保持vm状态，之后可恢复，
	//VM状态，local, eval, function_value(ref, yield), pc
	u32 st_vm_eval::eval(bool _continue )//求值
	{
		u32 break_rc = 0;//断点处理的返回值

		if(!_continue)++m_cur_pc;
		else goto VM_CONTINUE;
		

			for(; m_cur_pc != U32_NA; ++m_cur_pc)
			{	
#ifdef _VM_DEBUG
				if(m_debug)
				{
					if(m_debug->is_step() )//每步
					{
						break_rc = m_debug->on_code(static_cast<st_vm*>(this) );
						goto VM_BREAK;
					}
					else if(m_debug->get_break_idx() == m_cur_pc)
					{
						break_rc = m_debug->on_code(static_cast<st_vm*>(this) );
						m_debug->next_break();//步进
						goto VM_BREAK;
					}
				}
#endif
VM_CONTINUE:
				st_code& code = m_codes[m_cur_pc];
				i_code_proto* proc = m_proto_codes[m_codes[m_cur_pc].m_tag];
				proc->run(code.m_val, static_cast<st_vm*>(this) );
			}
		--m_cur_pc;
		return 0;

VM_BREAK:
		return break_rc;
	}



	void st_vm_eval::apply_begin()//
	{
		//push_eval_tag
		m_eval_tags.push(m_cur_eval_tag);
		m_cur_eval_tag = m_evals.size();
	}

	void st_vm_eval::apply_function(st_function_value* vfunc)
	{	
		//function states
		m_funcs.push(m_cur_func);
		m_cur_func = vfunc;

		//save the states for current evn, include pc, local stk, yield, 
		//push function env
		m_pcs.push(m_cur_pc);
		m_cur_pc = vfunc->m_code->m_code_idx-1;

		//push local tag
		//grow local size
		m_local_tags.push(m_cur_local_tag );
		m_cur_local_tag = m_locals.size();
		u32 loc_sz = vfunc->m_code->m_loc_size;
		m_locals.resize(m_cur_local_tag+loc_sz);

		//填充yield
		st_yield* y = m_cur_func->m_yield;
		if(y)
		{
			if(loc_sz != 0)
				memcpy(&m_locals.at(m_cur_local_tag), &y->m_locals.at(0), loc_sz*sizeof(st_value) );
			m_cur_pc = y->m_pc;
		}
	}

	void st_vm_eval::apply_primary(f_proto pfunc)
	{
		u32 ret_num = pfunc(static_cast<st_vm*>(this) );
		set_eval_top(ret_num);//可能不 需要?
		//pop eval env
		m_cur_eval_tag = m_eval_tags.pop();
	}

	void st_vm_eval::apply_instant()
	{
		st_value v = m_evals.pop();
		apply_begin();
		st_function_value* vf = v.get<st_function_value*>();
		apply_function(vf);
	}

	void st_vm_eval::ret_begin()
	{
		set_eval_top(0);
	}

	void st_vm_eval::ret(bool byield)
	{
		//save the envs for yield
		if(byield)
		{	
			st_yield*& y = m_cur_func->m_yield;
			u32 local_sz = m_cur_func->m_code->m_loc_size;
			if(!y)
			{
				y = new st_yield;
				y->m_locals.resize(local_sz);
			}
			y->m_pc = m_cur_pc;
			if(local_sz != 0)
				memcpy(&y->m_locals.at(0), &m_locals.at(m_cur_local_tag), local_sz*sizeof(st_value) );
		}
		else
		{
			m_cur_func->m_yield = 0;
		}

		//pop function evn
		m_cur_func = m_funcs.pop();
		m_cur_pc = m_pcs.pop();

		//pop local env
		m_locals.resize(m_cur_local_tag);
		m_cur_local_tag = m_local_tags.pop();

		//pop eval env
		m_cur_eval_tag = m_eval_tags.pop();
	}


}