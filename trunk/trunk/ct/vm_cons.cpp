
#include "vm_cons.h"
#include "proto_value.h"
#include "proto_code.h"
#include "symbol.h"
#include "primarys.h"

namespace ns_core
{
	st_vm_cons::st_vm_cons()
	{
		init();
	}

	void st_vm_cons::init()
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
			reg_proto_value(&singleton<st_v_extern_function>::instance() );
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
			//×¢²áº¯Êý
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
			idx = reg_function("std.sys.dofile", &ns_primary::_include);

		}
	}

	void st_vm_cons::release()
	{
		m_symbols.clean();
		
		m_codes.clear();
		m_proto_codes.clear();
		m_proto_values.clear();
	}

	void st_vm_cons::clean()
	{
		//TODO, Çå³ý±àÒëÖÐ¼ä×´Ì¬
	}

	u32 st_vm_cons::get_code_size()
	{
		return m_codes.size();
	}

	u32 st_vm_cons::c_ret_begin(st_code* c)
	{
		st_code code = st_c_ret_begin::make();
		if(!c)
			m_codes.push(code);
		else
			*c = code; 
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_ret(st_code* code, bool byield)
	{
		st_code c = st_c_ret::make(byield);
		if(!code)
			m_codes.push(c);
		else
			*code = c;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_bool(bool b, st_code* pc)
	{
		st_code c = st_c_push_bool::make(b);	
		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_int(s32 num, st_code* pc)
	{
		st_code code = st_c_push_int::make(num);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;

		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_string(const char* str, st_code* pc)
	{
		st_code c = st_c_push_string::make(str);
		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_global(const char* name, st_code* pc)
	{
		ns_core::st_sym_var* var = m_symbols.find_name(name);
		assert(var->m_type == e_global);
		u32 idx = var->g.path->get_id();
		st_code c = st_c_push_global::make(idx);
		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_pop_global(const char* name, st_code* pc)
	{
		ns_core::st_sym_var* var = m_symbols.find_name(name);
		assert(var->m_type == e_global);
		u32 idx = var->g.path->get_id();
		st_code c = st_c_pop_global::make(idx);

		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_function(u32 code_idx, u32 ins, u32 locs, st_code* pc)
	{
		st_code c = st_c_push_function::make(code_idx, ins, locs);

		if(!pc)
			m_codes.push(c);
		else
			*pc = c;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_apply_begin(st_code* pc)
	{
		st_code code = st_c_apply_begin::make();

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_apply(st_code* pc)
	{
		st_code code = st_c_apply::make();

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_goto(u32 code_idx, st_code* pc)
	{
		st_code code = st_c_goto::make(code_idx);

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_goto_true(u32 code_idx, st_code* pc)
	{
		st_code code = st_c_goto_true::make(code_idx);

		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_goto_false(u32 code_idx, st_code* pc)
	{
		st_code code = st_c_goto_false::make(code_idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_local(u32 idx, st_code* pc)
	{
		st_code code = st_c_push_local::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_pop_local(u32 idx, st_code* pc)
	{
		st_code code = st_c_pop_local::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_push_ref(u32 idx, st_code* pc)
	{
		st_code code = st_c_push_ref::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}

	u32 st_vm_cons::c_pop_ref(u32 idx, st_code* pc)
	{
		st_code code = st_c_pop_ref::make(idx);
		if(!pc)
			m_codes.push(code);
		else
			*pc = code;
		return m_codes.top_idx();
	}
}