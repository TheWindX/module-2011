
#pragma once

#include "data_struct.h"
//#include "symbol.h"

namespace ns_core
{
	using namespace ns_util;

	struct st_vm;
	struct i_code_proto
	{
		u32 m_tag;

		virtual void run(void* opr, st_vm* rt) = 0;
		virtual const char* get_name() = 0;
		virtual const char* to_string(st_code c){return "";};
		virtual ~i_code_proto(){};
	};

	struct i_value_proto
	{
		u32 m_tag;
		virtual const char* get_name(){return "";};
		virtual const char* to_string(st_value v, st_vm* rt){return "";};
		virtual bool compare(st_value v1, st_value v2){return v1.m_num<v2.m_num;};//TODO
	};

	typedef u32 (*f_proto)(st_vm* rt);
	typedef array<st_value>* refs_t;
	struct st_function_code
	{
		u32 m_code_idx;//字节码位置
		u32 m_in_para_num;//入参个数
		u32 m_loc_size;//布局长度

		array<u32> m_ref_map;//作用域向上引用查找表

		st_function_code(u32 code_idx, u32 ins, u32 locs, bool byield = false):
		m_code_idx(code_idx),m_in_para_num(ins),m_loc_size(locs){}

		void add_ref(u32 ref_idx){m_ref_map.push(ref_idx);}
	};

	struct st_yield
	{
		//when yield, save the state of enviroment
		u32 m_pc;
		array<st_value> m_locals;
	};

	struct st_function_value
	{
		st_function_code* m_code;
		//state for env of function
		refs_t m_refs;//环境中的逃逸变量
		st_yield* m_yield;//yield for state

		//用rt 是生成逃逸变量列表
		st_function_value(st_vm* rt, st_function_code* func);

	private:
		//st_function_value();
	};


	typedef void (*debug_proto_t)(st_vm* vm);
	struct st_vm
	{
		/************************************************************************/
		/* 
		vm
			runtime_state
				local_var
				eval
				pc
				function_value，
					ref
					yield

			(code, value) protos


		*/
		/************************************************************************/
		//global
		array<st_value> m_globals;
		st_value& get_global(u32 idx){return m_globals[idx]; }

		//eval env,
		array<st_value> m_locals;
		array<u32> m_local_tags;
		u32 m_cur_local_tag;
		st_value& get_local(u32 idx){return m_locals[m_cur_local_tag+idx]; }

		array<st_value> m_evals;
		array<u32> m_eval_tags;
		u32 m_cur_eval_tag;
		st_value& get_eval(s32 idx){if(idx<0)return m_evals[m_evals.size()+idx]; else return m_evals[m_cur_eval_tag+idx]; }
		u32 get_eval_size(){return m_evals.size()-m_cur_eval_tag; }
		void set_eval_top(u32 idx){m_evals.resize(m_cur_eval_tag+idx); }

		//function env
		array<st_function_value*> m_funcs;
		st_function_value* m_cur_func;
		
		st_value& get_ref(u32 idx){return *(st_value*)m_cur_func->m_refs->at(idx).m_val; }//取引用的变量
		st_value& get_ref_raw(u32 idx){return m_cur_func->m_refs->at(idx); }//引用本身

		array<st_code> m_codes;//代码段
		array<u32> m_pcs;//stack for pc
		u32 m_cur_pc;

		array<i_code_proto*> m_proto_codes;
		array<i_value_proto*> m_proto_values;
		u32 reg_proto_code(i_code_proto* code);
		u32 reg_proto_value(i_value_proto* value);
		i_code_proto* get_code_proto(u32 tag_id);
		i_value_proto* get_value_proto(u32 tag_id);
		void init();//init all proto for code & value & other init state

		void set_debug(debug_proto_t dbg);
		void clear_debug();
		void eval();//求值

		st_vm():m_cur_pc(U32_NA){}

		void apply_begin();
		void apply_function(st_function_value* func);
		void apply_primary(f_proto pfunc);
		void apply_instant();//直接执行 栈顶的 function(非primary)

		void ret_begin();
		void ret(bool byield = false);

		
		//st_symbols m_symbols;
		
		//注册到全局符号表和全局变量表
		//u32 reg_function(const char* func_name, f_proto func);
		//ns_util::st_var* reg_global(const char* func_name);

		//debugs
		//bool m_dbg;
		//void set_dbg(bool b){m_dbg = b; }
		//bool m_dbg_b_step;
		//void set_dbg_step(bool b){m_dbg_b_step = b; }
		//void dbg_eval();
		//st_set<u32> m_dbg_breaks;
		//void add_break(u32 pc_idx);
		//void clear_break();
	};

	struct st_vm_cor : public st_vm
	{
		u32 c_function_begin();
		u32 c_ret_begin(st_code* code = 0);
		u32 c_ret(st_code* code = 0, bool byield = false);
		u32 c_push_bool(bool b, st_code* code = 0);
		u32 c_push_int(s32 num, st_code* code = 0);
		u32 c_push_string(const char* str, st_code* code = 0);

		u32 c_push_function(u32 code_idx, u32 ins, u32 locs, st_code* code = 0);
		u32 c_apply_begin(st_code* code = 0);
		u32 c_apply(st_code* code = 0);

		u32 c_goto(u32 code_idx, st_code* code = 0);
		u32 c_goto_true(u32 code_idx, st_code* code = 0);
		u32 c_goto_false(u32 code_idx, st_code* code = 0);

		//u32 c_push_global(const char* name, st_code* code = 0);//TODO, 这里改成global id，与符号表脱离，
		//u32 c_pop_global(const char* name, st_code* code = 0);
		u32 c_push_global(u32 gid, st_code* code = 0);//TODO, 这里改成global id，与符号表脱离，
		u32 c_pop_global(u32 gid, st_code* code = 0);

		u32 c_push_local(u32 idx, st_code* code = 0);
		u32 c_pop_local(u32 idx, st_code* code = 0);

		u32 c_push_ref(u32 idx, st_code* code = 0);
		u32 c_pop_ref(u32 idx, st_code* code = 0);
	};
}