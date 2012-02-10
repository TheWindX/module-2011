
#pragma once

#include "vm_data.h"

namespace ns_core
{
	using namespace ns_base;
	struct st_vm_env : public st_vm_data
	{
		st_value& get_global(u32 idx){return m_globals[idx]; }
		st_value& get_local(u32 idx){return m_locals[m_cur_local_tag+idx]; }
		st_value& get_eval(s32 idx){if(idx<0)return m_evals[m_evals.size()+idx]; else return m_evals[m_cur_eval_tag+idx]; }
		u32 get_eval_size(){return m_evals.size()-m_cur_eval_tag; }
		void set_eval_top(u32 idx){m_evals.resize(m_cur_eval_tag+idx); }
		st_value& get_ref(u32 idx){return *(st_value*)m_cur_func->m_refs->at(idx).m_val; }//取引用的变量
		st_value& get_ref_raw(u32 idx){return m_cur_func->m_refs->at(idx); }//引用本身
	};

	struct st_vm_plugs : public st_vm_env
	{
		u32 reg_proto_code(i_code_proto* code);
		u32 reg_proto_value(i_value_proto* value);
		i_code_proto* get_code_proto(u32 tag_id);
		i_value_proto* get_value_proto(u32 tag_id);

		//注册到全局符号表和全局变量表
		u32 reg_function(const char* func_name, f_proto func);
		ns_core::st_sym_var* reg_global(const char* func_name);//注册全局符号名

		void clear();
	};

	struct st_vm_eval : public st_vm_plugs
	{
		void eval();//求值

		void apply_begin();
		void apply_function(st_function_value* func);
		void apply_primary(f_proto pfunc);
		void apply_instant();//直接执行 栈顶的 function(非primary)

		void ret_begin();
		void ret(bool byield = false);
	};

	struct st_vm : public st_vm_eval
	{	
	};
}