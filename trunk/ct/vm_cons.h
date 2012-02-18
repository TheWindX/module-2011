
#pragma once

#include "vm.h"

namespace ns_core
{
	//构造 vm_cons
	struct st_vm_cons : public st_vm
	{
		st_vm_cons();
		void init();//init all proto for code & value & other init state
		void release();//TODO, release all proto for code & value & other in init & runtime generate

		void clean();//TODO, 出错时，清除所有恢复状态

		
		u32 get_code_size();
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

		u32 c_push_global(const char* name, st_code* code = 0);//TODO, 这里改成global id，与符号表脱离，
		u32 c_pop_global(const char* name, st_code* code = 0);

		u32 c_push_local(u32 idx, st_code* code = 0);
		u32 c_pop_local(u32 idx, st_code* code = 0);

		u32 c_push_ref(u32 idx, st_code* code = 0);
		u32 c_pop_ref(u32 idx, st_code* code = 0);
	};

}