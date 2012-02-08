#include <cassert>
#include <string>

#include "vm.h"
#include "context.h"
#include "code.h"
#include "value.h"

#include "primarys.h"

namespace ns_core
{
	const char* st_value::to_string(st_vm* rt)
	{
		if(rt->m_proto_values.size()>m_tag)
		{
			i_value_proto* p = rt->m_proto_values[m_tag];
			return p->to_string(*this, rt);
		}
		else
		{
			return "(NA)";
		}
	}

	const char* st_value::to_code_string(st_vm* rt)
	{
		if(rt->m_proto_codes.size()>m_tag)
		{
			i_code_proto* p = rt->m_proto_codes[m_tag];
			return p->to_string(*this);
		}
		else
		{
			return "(NA)";
		}
	}

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


	u32 st_vm::reg_proto_code(i_code_proto* code)
	{
		u32 new_id = m_proto_codes.size();
		m_proto_codes.push(code);
		code->m_tag = new_id;
		return new_id;
	}

	u32 st_vm::reg_proto_value(i_value_proto* value)
	{
		u32 new_id = m_proto_values.size();
		m_proto_values.push(value);
		value->m_tag = new_id;
		return new_id;
	}

	i_code_proto* st_vm::get_code_proto(u32 tag_id)
	{
		return m_proto_codes[tag_id];
	}

	i_value_proto* st_vm::get_value_proto(u32 tag_id)
	{
		return m_proto_values[tag_id];
	}

	void st_vm::init()
	{	
		m_cur_eval_tag = U32_NA;
		m_cur_func = 0;
		m_cur_local_tag = U32_NA;
		m_cur_pc = U32_NA-1;

		m_dbg = false;
		m_dbg_b_step = false;
		m_dbg_breaks.clear();
		
		reg_proto_value(&st_singleton<st_v_null>::instance() );
		reg_proto_value(&st_singleton<st_v_bool>::instance() );
		reg_proto_value(&st_singleton<st_v_int>::instance() );
		reg_proto_value(&st_singleton<st_v_string>::instance() );
		reg_proto_value(&st_singleton<st_v_ref>::instance() );
		reg_proto_value(&st_singleton<st_v_function>::instance() );
		reg_proto_value(&st_singleton<st_v_primary_function>::instance() );
		reg_proto_value(&st_singleton<st_v_array>::instance() );
		reg_proto_value(&st_singleton<st_v_map>::instance() );

		reg_proto_code(&st_singleton<st_c_push_local>::instance() );
		reg_proto_code(&st_singleton<st_c_pop_local>::instance() );
		reg_proto_code(&st_singleton<st_c_push_ref>::instance() );
		reg_proto_code(&st_singleton<st_c_pop_ref>::instance() );
		reg_proto_code(&st_singleton<st_c_push_global>::instance() );
		reg_proto_code(&st_singleton<st_c_pop_global>::instance() );
		reg_proto_code(&st_singleton<st_c_push_bool>::instance() );
		reg_proto_code(&st_singleton<st_c_push_int>::instance() );
		reg_proto_code(&st_singleton<st_c_push_string>::instance() );
		reg_proto_code(&st_singleton<st_c_push_function>::instance() );
		reg_proto_code(&st_singleton<st_c_function_ref>::instance() );
		reg_proto_code(&st_singleton<st_c_goto>::instance() );
		reg_proto_code(&st_singleton<st_c_goto_true>::instance() );
		reg_proto_code(&st_singleton<st_c_goto_false>::instance() );
		reg_proto_code(&st_singleton<st_c_apply_begin>::instance() );
		reg_proto_code(&st_singleton<st_c_apply>::instance() );
		reg_proto_code(&st_singleton<st_c_apply_instant>::instance() );
		reg_proto_code(&st_singleton<st_c_ret_begin>::instance() );
		reg_proto_code(&st_singleton<st_c_ret>::instance() );

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

		idx = reg_function("std.core.include", &ns_primary::_include);
		idx = reg_function("std.core.load", &ns_primary::load);
		
		idx = reg_function("std.debug.step", &ns_primary::debug_step);
		idx = reg_function("std.debug.print_symbol", &ns_primary::print_symbol);
	}

	void st_vm::eval()
	{
		++m_cur_pc;
		for(; m_cur_pc != U32_NA; ++m_cur_pc)
		{	
			dbg_eval();
			st_code& code = m_codes[m_cur_pc];
			i_code_proto* proc = get_code_proto(code.m_tag);
			proc->run(code.m_val, this);
		}
	}

	void st_vm::dbg_eval()
	{
		//打印出当前pc指令的名称
		if(!m_dbg) return;
		if(!m_dbg_b_step)
		{
			if(!m_dbg_breaks.find(m_cur_pc) )//查找断点
				return;
		}
		st_code& code = m_codes[m_cur_pc];

		u32 ref_sz = 0;
		if(m_cur_func->m_refs)
			ref_sz = m_cur_func->m_refs->size();

		printf("...%s...", g_ctx.m_debug.code2line(m_cur_pc).c_str() );

		printf("\npc:%d(%s(%d), %08x), ref:%08x(sz:%d), ins:%d, locs:%d\n\
eval_tag:%d, eval_stk:%d, eval_top:%d, local_tag:%d, local_stk:%d, local_top:%d\n",
			   m_cur_pc, 
			   m_proto_codes[code.m_tag]->get_name(),  code.m_tag, code.m_val,
			   m_cur_func->m_refs, ref_sz, m_cur_func->m_code->m_in_para_num, m_cur_func->m_code->m_loc_size,
			   m_cur_eval_tag, m_eval_tags.size(), m_evals.size(), m_cur_local_tag, m_local_tags.size(), m_locals.size()
			   );

		printf("evals:\n");
		for(u32 i = m_cur_eval_tag; i<m_evals.size(); ++i)
		{
			st_value& v = m_evals[i];
			printf("\t%s(%d), value of(%08x)\n", m_proto_values.at(v.m_tag)->get_name(), v.m_tag, v.m_val);
		}
		printf("locals:\n");
		for(u32 i = m_cur_local_tag; i<m_locals.size(); ++i)
		{
			st_value& v = m_locals[i];
			if(v.m_tag<m_proto_values.size() )
 				printf("\t%s(%d), value of(%08x)\n", m_proto_values.at(v.m_tag)->get_name(), v.m_tag, v.m_val);
		}
		
		refs_t cur_ref = m_cur_func->m_refs;
		if(cur_ref)
		{
			printf("refs:\n");
			for(u32 i = 0; i<cur_ref->size(); ++i)
			{
				st_value& v = get_ref(i);
				if(v.m_tag<m_proto_values.size() )
					printf("\t%s(%d), value of(%08x)\n", m_proto_values.at(v.m_tag)->get_name(), v.m_tag, v.m_val);
			}
		}

		printf("input_state:");
		char buff[256];
		scanf("%s", buff);
		if(std::string("stop") == (char*)buff) m_dbg = false;
		else if(std::string("step") == (char*)buff) m_dbg_b_step = true;
		else if(std::string("step=false") == (char*)buff) m_dbg_b_step = false;
		else if(std::string("break") == (char*)buff)
		{
			int n;
			scanf("%d", &n);
			m_dbg_b_step = false;
			m_dbg_breaks.insert(n);
		}
		else if(std::string("break=false") == (char*)buff)
		{
			m_dbg_breaks.clear();
		}
	}

	void st_vm::add_break(u32 pc_idx)
	{
		m_dbg_breaks.insert(pc_idx);
	}

	void st_vm::clear_break()
	{
		m_dbg_breaks.clear();
	}

	void st_vm::apply_begin()
	{
		//push_eval_tag
		m_eval_tags.push(m_cur_eval_tag);
		m_cur_eval_tag = m_evals.size();
	}

	void st_vm::apply_function(st_function_value* vfunc)
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
				memcpy(&m_locals.at(m_cur_local_tag), y->m_locals.m_base, loc_sz*sizeof(st_value) );
			m_cur_pc = y->m_pc;
		}
	}

	void st_vm::apply_primary(f_proto pfunc)
	{
		u32 ret_num = pfunc(this);
		set_eval_top(ret_num);//可能不 需要?
		//pop eval env
		m_cur_eval_tag = m_eval_tags.pop();
	}

	void st_vm::apply_instant()
	{
		st_value v = m_evals.pop();
		apply_begin();
		st_function_value* vf = v.get<st_function_value*>();
		apply_function(vf);
	}

	void st_vm::ret_begin()
	{
		set_eval_top(0);
	}

	void st_vm::ret(bool byield)
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
				memcpy(y->m_locals.m_base, &m_locals.at(m_cur_local_tag), local_sz*sizeof(st_value) );
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

	u32 st_vm::reg_function(const char* func_name, f_proto func)
	{
		ns_util::st_var* var = reg_global(func_name);
		u32 id = var->g.path->get_id();
		st_value& v = get_global(id );
		v = st_v_primary_function::make_value(func);
		return id;
	}

	ns_util::st_var* st_vm::reg_global(const char* func_name)
	{
		ns_util::st_var* v = m_symbols.reg_global_name(func_name);
		u32 id = v->g.path->get_id();
		if(m_globals.size() <= id) m_globals.resize(id+1);
		return v;
	}


	u32 st_vm_cor::c_function_begin()
	{
		return m_codes.size();
	}

	u32 st_vm_cor::c_ret_begin(st_code* c)
	{
		st_code code = st_c_ret_begin::make();
		if(!c)
			m_codes.push(code);
		else
			*c = code; 
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_ret(st_code* code, bool byield)
	{
		st_code c = st_c_ret::make(byield);
		if(!code)
			m_codes.push(c);
		else
			*code = c;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_bool(bool b, st_code* pc)
	{
		st_code c = st_c_push_bool::make(b);	
		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_int(s32 num, st_code* pc)
	{
		st_code code = st_c_push_int::make(num);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;

		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_string(const char* str, st_code* pc)
	{
		st_code c = st_c_push_string::make(str);
		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_global(const char* name, st_code* pc)
	{
		ns_util::st_var* var = m_symbols.find_name(name);
		assert(var->m_type == e_global);
		u32 idx = var->g.path->get_id();
		st_code c = st_c_push_global::make(idx);
		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_pop_global(const char* name, st_code* pc)
	{
		ns_util::st_var* var = m_symbols.find_name(name);
		assert(var->m_type == e_global);
		u32 idx = var->g.path->get_id();
		st_code c = st_c_pop_global::make(idx);

		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_function(u32 code_idx, u32 ins, u32 locs, st_code* pc)
	{
		st_code c = st_c_push_function::make(code_idx, ins, locs);

		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_apply_begin(st_code* pc)
	{
		st_code code = st_c_apply_begin::make();

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_apply(st_code* pc)
	{
		st_code code = st_c_apply::make();

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_goto(u32 code_idx, st_code* pc)
	{
		st_code code = st_c_goto::make(code_idx);

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_goto_true(u32 code_idx, st_code* pc)
	{
		st_code code = st_c_goto_true::make(code_idx);

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_goto_false(u32 code_idx, st_code* pc)
	{
		st_code code = st_c_goto_false::make(code_idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_local(u32 idx, st_code* pc)
	{
		st_code code = st_c_push_local::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_pop_local(u32 idx, st_code* pc)
	{
		st_code code = st_c_pop_local::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_push_ref(u32 idx, st_code* pc)
	{
		st_code code = st_c_push_ref::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

	u32 st_vm_cor::c_pop_ref(u32 idx, st_code* pc)
	{
		st_code code = st_c_pop_ref::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.m_top;
	}

}