#include <cassert>

#include "vm.h"

#include "proto_code.h"
#include "proto_value.h"

#include "functor.h"

#define TYPE_CHECK(v, T) (assert((v).m_tag == singleton<T>::instance().m_tag) );

namespace ns_core
{
	//push_local
	void st_c_push_local::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		rt->m_evals.push(rt->get_local(idx) );
	}

	const char* st_c_push_local::get_name()
	{
		return "push_local";
	}

	st_code st_c_push_local::make(u32 local_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_push_local>::instance().m_tag;
		ret.set(local_idx);
		return ret;
	}

	const char* st_c_push_local::to_string(st_code c)
	{
		static std::string str;
		
		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	//pop_local
	void st_c_pop_local::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		st_value& v = rt->get_local(idx);
		if(rt->m_evals.empty() )
			v = st_v_null::make_value();
		else
			v = rt->m_evals.pop();
	}

	st_code st_c_pop_local::make(u32 local_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_pop_local>::instance().m_tag;
		ret.set(local_idx);
		return ret;
	}

	const char* st_c_pop_local::get_name()
	{
		return "pop_local";
	}

	const char* st_c_pop_local::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	//push_ref
	void st_c_push_ref::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		rt->m_evals.push(rt->get_ref(idx) );
	}

	const char* st_c_push_ref::get_name()
	{
		return "push_ref";
	}

	const char* st_c_push_ref::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_push_ref::make(u32 local_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_push_ref>::instance().m_tag;
		ret.set(local_idx);
		return ret;
	}

	//pop_ref
	void st_c_pop_ref::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		st_value& v = rt->get_ref(idx);
		if(rt->m_evals.empty() )
			v = st_v_null::make_value();
		else
			v = rt->m_evals.pop();
	}

	const char* st_c_pop_ref::get_name()
	{
		return "pop_ref";
	}

	const char* st_c_pop_ref::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_pop_ref::make(u32 local_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_pop_ref>::instance().m_tag;
		ret.set(local_idx);
		return ret;
	}

	//push_global
	void st_c_push_global::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		rt->m_evals.push(rt->get_global(idx) );
	}

	const char* st_c_push_global::get_name()
	{
		return "push_global";
	}

	const char* st_c_push_global::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_push_global::make(u32 idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_push_global>::instance().m_tag;
		ret.set(idx);
		return ret;
	}

	//pop_global
	void st_c_pop_global::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		st_value& v = rt->get_global(idx);
		if(rt->m_evals.empty() )
			v = st_v_null::make_value();
		else
			v = rt->m_evals.pop();
	}

	const char* st_c_pop_global::get_name()
	{
		return "pop_global";
	}

	const char* st_c_pop_global::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_pop_global::make(u32 idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_pop_global>::instance().m_tag;
		ret.set(idx);
		return ret;
	}

	//push_bool
	void st_c_push_bool::run(void* opr, st_vm* rt)
	{
		bool b = reinterpret_cast<bool>(opr);
		st_value v = st_v_bool::make_value(b);
		rt->m_evals.push(v);
	}

	const char* st_c_push_bool::get_name()
	{
		return "push_bool";
	}

	const char* st_c_push_bool::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		//char buff[128];
		bool b = c.get<bool>();
		if(b)
			str += "true";
		else
			str += "false";

		return str.c_str();
	}


	st_code st_c_push_bool::make(bool b)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_push_bool>::instance().m_tag;
		ret.m_num = b;
		return ret;
	}

	//push_int
	void st_c_push_int::run(void* opr, st_vm* rt)
	{
		s32 b = reinterpret_cast<s32>(opr);
		st_value v = st_v_int::make_value(b);
		rt->m_evals.push(v);
	}

	const char* st_c_push_int::get_name()
	{
		return "push_int";
	}

	const char* st_c_push_int::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		s32 v = c.get<s32>();
		itoa(v, buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_push_int::make(s32 num)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_push_int>::instance().m_tag;
		ret.m_num = num;
		return ret;
	}

	//push_string
	void st_c_push_string::run(void* opr, st_vm* rt)
	{
		char* s = reinterpret_cast<char*>(opr);
		st_value v = st_v_string::make_value(s);
		rt->m_evals.push(v);
	}

	const char* st_c_push_string::get_name()
	{
		return "push_string";
	}

	const char* st_c_push_string::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char* v = c.get<char*>();
		str += v;

		return str.c_str();
	}

	st_code st_c_push_string::make(const char* str)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_push_string>::instance().m_tag;
		ret.m_val = const_cast<char*>(str);
		return ret;
	}

	//push_function
	void st_c_push_function::run(void* opr, st_vm* rt)
	{
		st_function_code* func = reinterpret_cast<st_function_code*>(opr);
		st_value v = st_v_function::make_value(rt, func);
		rt->m_evals.push(v);
	}

	const char* st_c_push_function::get_name()
	{
		return "push_function";
	}

	const char* st_c_push_function::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		st_function_code* f = c.get<st_function_code*>();
		assert(f);
		itoa(f->m_code_idx, buff, 10);
		str += "code_idx:";
		str += buff;
		str += " ";

		itoa(f->m_in_para_num, buff, 10);
		str += "ins:";
		str += buff;
		str += " ";

		itoa(f->m_loc_size, buff, 10);
		str += "locs:";
		str += buff;
		str += " ";

		str += "ref_map:";
		for(u32 i = 0; i<f->m_ref_map.size(); ++i)
		{
			itoa(f->m_ref_map[i], buff, 10);
			str += buff;
			str += " ";
		}

		return str.c_str();
	}

	st_code st_c_push_function::make(u32 code_idx, u32 ins, u32 locs)
	{
		st_function_code* f = new st_function_code(code_idx, ins, locs);

		st_code ret;
		ret.m_tag = singleton<st_c_push_function>::instance().m_tag;
		ret.m_val = f;

		return ret;
	}

	//function_ref
	void st_c_function_ref::run(void* opr, st_vm* rt)
	{
		st_value& vf = rt->get_eval(-1);
		st_function_value* func = reinterpret_cast<st_function_value*>(vf.m_val);
		u32 idx = reinterpret_cast<u32>(opr);
		if(idx == U32_NA) func->m_refs = new array<st_value>;
		else
		{
			st_value& v = rt->get_ref(idx);
			func->m_refs->push(v);
		}
	}

	const char* st_c_function_ref::get_name()
	{
		return "function_ref";
	}

	//goto
	void st_c_goto::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);
		rt->m_cur_pc = idx-1;
	}

	const char* st_c_goto::get_name()
	{
		return "goto";
	}

	const char* st_c_goto::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_goto::make(u32 code_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_goto>::instance().m_tag;
		ret.set(code_idx);
		return ret;
	}

	//goto_true
	void st_c_goto_true::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);

		st_value v = rt->get_eval(-1);
		bool b = v.get<bool>();
		if(b) rt->m_cur_pc = idx-1;
		rt->m_evals.pop();
	}

	const char* st_c_goto_true::get_name()
	{
		return "goto_true";
	}

	const char* st_c_goto_true::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_goto_true::make(u32 code_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_goto_true>::instance().m_tag;
		ret.set(code_idx);
		return ret;
	}

	//goto_false
	void st_c_goto_false::run(void* opr, st_vm* rt)
	{
		u32 idx = reinterpret_cast<u32>(opr);

		st_value v = rt->get_eval(-1);
		bool b = v.get<bool>();
		if(!b) rt->m_cur_pc = idx-1;
		rt->m_evals.pop();
	}

	const char* st_c_goto_false::get_name()
	{
		return "goto_false";
	}

	const char* st_c_goto_false::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		char buff[128];
		itoa(c.get<u32>(), buff, 10);
		str += buff;

		return str.c_str();
	}

	st_code st_c_goto_false::make(u32 code_idx)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_goto_false>::instance().m_tag;
		ret.set(code_idx);
		return ret;
	}

	//apply_begin
	void st_c_apply_begin::run(void* opr, st_vm* rt)
	{
		rt->apply_begin();
	}

	const char* st_c_apply_begin::get_name()
	{
		return "apply_begin";
	}

	const char* st_c_apply_begin::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		//char buff[128];
		//itoa(c.get<u32>(), buff, 10);
		//str += buff;

		return str.c_str();
	}

	st_code st_c_apply_begin::make()
	{
		st_code ret;
		ret.m_tag = singleton<st_c_apply_begin>::instance().m_tag;
		return ret;
	}

	//apply

	void st_c_apply::run(void* opr, st_vm* rt)
	{
		st_value v = rt->get_eval(-1);
		rt->m_evals.pop();
		if(v.m_tag == ns_base::singleton<st_v_primary_function>::instance().m_tag)
		{	
			f_proto pf = v.get<f_proto>();
			rt->apply_primary(pf);
		}
		else if(v.m_tag == ns_base::singleton<st_v_function>::instance().m_tag)
		{
			st_function_value* f = v.get<st_function_value*>();
			rt->apply_function(f);
		}
		else if(v.m_tag == ns_base::singleton<st_v_extern_function>::instance().m_tag)
		{	
			i_functor* pf = v.get<i_functor*>();
			pf->on_eval(rt->get_i_context() );
			rt->m_cur_eval_tag = rt->m_eval_tags.pop();
		}
		else assert(false);//TODO，这个名不是函数
	}

	const char* st_c_apply::get_name()
	{
		return "apply";
	}

	const char* st_c_apply::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		//char buff[128];
		//itoa(c.get<u32>(), buff, 10);
		//str += buff;

		return str.c_str();
	}

	st_code st_c_apply::make()
	{
		st_code code;
		code.m_tag = singleton<st_c_apply>::instance().m_tag;
		return code;
	}


	//apply alone
	void st_c_apply_instant::run(void* opr, st_vm* rt)
	{
		rt->apply_instant();
	}

	const char* st_c_apply_instant::get_name()
	{
		return "apply_instant";
	}

	const char* st_c_apply_instant::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		//char buff[128];
		//itoa(c.get<u32>(), buff, 10);
		//str += buff;

		return str.c_str();
	}

	st_code st_c_apply_instant::make()
	{
		st_code code;
		code.m_tag = singleton<st_c_apply_instant>::instance().m_tag;
		return code;
	}

	//ret_begin
	void st_c_ret_begin::run(void* opr, st_vm* rt)
	{
		rt->ret_begin();
		//rt->set_eval_top(0);
	}

	const char* st_c_ret_begin::get_name()
	{
		return "ret_begin";
	}

	const char* st_c_ret_begin::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		//char buff[128];
		//itoa(c.get<u32>(), buff, 10);
		//str += buff;

		return str.c_str();
	}

	st_code st_c_ret_begin::make()
	{
		st_code ret;
		ret.m_tag = singleton<st_c_ret_begin>::instance().m_tag;
		return ret;
	}

	//ret
	void st_c_ret::run(void* opr, st_vm* rt)
	{
		bool byield = reinterpret_cast<bool>(opr);
		rt->ret(byield);
	}

	const char* st_c_ret::get_name()
	{
		return "ret";
	}

	const char* st_c_ret::to_string(st_code c)
	{
		static std::string str;

		str = "";
		str += get_name();
		str += " ";

		//char buff[128];
		//itoa(c.get<u32>(), buff, 10);
		//str += buff;
		return str.c_str();
	}

	st_code st_c_ret::make(bool byield)
	{
		st_code ret;
		ret.m_tag = singleton<st_c_ret>::instance().m_tag;
		ret.set<bool>(byield);
		return ret;
	}
}