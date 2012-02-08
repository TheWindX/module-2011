
#pragma once

#include "vm.h"

namespace ns_core
{
	//for codes

	//push_local
	struct st_c_push_local : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();

		static st_code make(u32 local_idx);
		const char* to_string(st_code c);
	};
	
	//pop_local
	struct st_c_pop_local : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 local_idx);

	};

	//push_ref
	struct st_c_push_ref : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 local_idx);
	};

	//pop_local
	struct st_c_pop_ref : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 local_idx);
	};


	//push_global
	struct st_c_push_global : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 idx);
	};

	//pop_global
	struct st_c_pop_global : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 idx);
	};

	//push_bool
	struct st_c_push_bool : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(bool b);
	};

	//push_int
	struct st_c_push_int : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(s32 num);
	};

	//push_string
	struct st_c_push_string : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(const char* str);
	};


	//push_function
	struct st_c_push_function : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 code_idx, u32 ins, u32 locs);
	};

	//function_ref
	struct st_c_function_ref : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
	};

	//goto_false
	struct st_c_goto : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 code_idx);
	};

	//goto_true
	struct st_c_goto_true : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 code_idx);
	};

	//goto_false
	struct st_c_goto_false : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(u32 code_idx);
	};


	//apply begin
	struct st_c_apply_begin : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make();
	};

	//apply
	struct st_c_apply : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make();
	};

	//apply
	struct st_c_apply_instant : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make();
	};

	//ret_begin
	struct st_c_ret_begin : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make();
	};

	//ret
	struct st_c_ret : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make(bool byield = false);
	};

	struct st_c_inc : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make();
	};

	struct st_c_dec : public i_code_proto
	{
		virtual void run(void* opr, st_vm* rt);
		virtual const char* get_name();
		virtual const char* to_string(st_code c);

		static st_code make();
	};



}