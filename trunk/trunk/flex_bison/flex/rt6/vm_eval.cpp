
#include "vm.h"

#include "proto_code.h"
#include "proto_value.h"

#include "primarys.h"

namespace ns_core
{
	void st_vm_eval::init()
	{	
		m_cur_eval_tag = U32_NA;
		m_cur_func = 0;
		m_cur_local_tag = U32_NA;
		m_cur_pc = U32_NA-1;

		//reg proto value& proto code
		{
			reg_proto_value(&singleton<st_v_null>::instance() );
			reg_proto_value(&singleton<st_v_bool>::instance() );
			reg_proto_value(&singleton<st_v_int>::instance() );
			reg_proto_value(&singleton<st_v_string>::instance() );
			reg_proto_value(&singleton<st_v_ref>::instance() );
			reg_proto_value(&singleton<st_v_function>::instance() );
			reg_proto_value(&singleton<st_v_primary_function>::instance() );
			reg_proto_value(&singleton<st_v_array>::instance() );
			reg_proto_value(&singleton<st_v_map>::instance() );
		}
		{
			reg_proto_code(&singleton<st_c_push_local>::instance() );
			reg_proto_code(&singleton<st_c_pop_local>::instance() );
			reg_proto_code(&singleton<st_c_push_ref>::instance() );
			reg_proto_code(&singleton<st_c_pop_ref>::instance() );
			reg_proto_code(&singleton<st_c_push_global>::instance() );
			reg_proto_code(&singleton<st_c_pop_global>::instance() );
			reg_proto_code(&singleton<st_c_push_bool>::instance() );
			reg_proto_code(&singleton<st_c_push_int>::instance() );
			reg_proto_code(&singleton<st_c_push_string>::instance() );
			reg_proto_code(&singleton<st_c_push_function>::instance() );
			reg_proto_code(&singleton<st_c_function_ref>::instance() );
			reg_proto_code(&singleton<st_c_goto>::instance() );
			reg_proto_code(&singleton<st_c_goto_true>::instance() );
			reg_proto_code(&singleton<st_c_goto_false>::instance() );
			reg_proto_code(&singleton<st_c_apply_begin>::instance() );
			reg_proto_code(&singleton<st_c_apply>::instance() );
			reg_proto_code(&singleton<st_c_apply_instant>::instance() );
			reg_proto_code(&singleton<st_c_ret_begin>::instance() );
			reg_proto_code(&singleton<st_c_ret>::instance() );
		}
		{
			//注册函数
			u32 idx = reg_function("std.sys.pause", &ns_primary::_pause);
			idx = reg_function("std.sys.print", &ns_primary::print);
			idx = reg_function("std.core.minus", &ns_primary::minus);
			idx = reg_function("std.core.add", &ns_primary::add);
			idx = reg_function("std.core.sub", &ns_primary::sub);
			idx = reg_function("std.core.mul", &ns_primary::mul);
			idx = reg_function("std.core.div", &ns_primary::div);
			idx = reg_function("std.core.mod", &ns_primary::mod);
			idx = reg_function("std.core.equal", &ns_primary::equal_num);
			idx = reg_function("std.core.gt", &ns_primary::GT_num);
			idx = reg_function("std.core.lt", &ns_primary::LT_num);

			idx = reg_function("std.core.null_array", &ns_primary::null_array);
			idx = reg_function("std.core.array_push", &ns_primary::array_push);
			idx = reg_function("std.core.array_cor", &ns_primary::array_cor);
			idx = reg_function("std.core.null_map", &ns_primary::null_map);
			idx = reg_function("std.core.map_insert", &ns_primary::map_insert);
			idx = reg_function("std.core.insert", &ns_primary::insert);
			idx = reg_function("std.core.index", &ns_primary::index);
			idx = reg_function("std.core.push", &ns_primary::a_push);
			idx = reg_function("std.core.pop", &ns_primary::a_pop);
			idx = reg_function("std.core.size", &ns_primary::a_size);

			idx = reg_function("std.core.type", &ns_primary::_type);

		}
	}

	void st_vm_eval::eval()//求值
	{
		++m_cur_pc;
		for(; m_cur_pc != U32_NA; ++m_cur_pc)
		{	
			st_code& code = m_codes[m_cur_pc];
			i_code_proto* proc = get_code_proto(code.m_tag);
			proc->run(code.m_val, static_cast<st_vm*>(this) );
		}
	}

	void st_vm_eval::apply_begin()
	{
		//push_eval_tag
		m_eval_tags.push(m_cur_eval_tag);
		m_cur_eval_tag = m_evals.size();
	}

	void st_vm_eval::apply_function(st_function_value* vfunc)
	{	
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