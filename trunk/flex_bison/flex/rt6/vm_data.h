
#pragma once

#include "value.h"
#include "symbol.h"

namespace ns_core
{
	struct st_yield
	{
		//when yield, save the state of enviroment
		u32 m_pc;
		array<st_value> m_locals;
	};

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

	typedef array<st_value>* refs_t;
	struct st_function_value
	{
		st_function_code* m_code;
		
		//states for env of function
		refs_t m_refs;//环境中的逃逸变量
		st_yield* m_yield;//yield for state
		st_function_value(st_vm* rt, st_function_code* func);//用rt 是生成逃逸变量列表
	};


	struct st_vm_env_data
	{
		//global
		array<st_value> m_globals;
		//local
		array<st_value> m_locals;
		array<u32> m_local_tags;
		u32 m_cur_local_tag;
		//eval
		array<st_value> m_evals;
		array<u32> m_eval_tags;
		u32 m_cur_eval_tag;
		//function env
		array<st_function_value*> m_funcs;
		st_function_value* m_cur_func;
	};

	struct st_vm_eval_data
	{
		array<st_code> m_codes;//代码段
		array<u32> m_pcs;//stack for pc
		u32 m_cur_pc;
	};

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
		virtual bool compare(st_value v1, st_value v2){return v1.m_num<v2.m_num;};
	};

	struct st_vm_data_plugs
	{
		array<i_code_proto*> m_proto_codes;
		array<i_value_proto*> m_proto_values;
	};

	struct st_vm_global_data
	{
		st_symbols m_symbols;
	};

	struct st_vm_data : 
		public st_vm_env_data,
		public st_vm_eval_data,
		public st_vm_global_data,
		public st_vm_data_plugs
	{};
}