
#pragma once

#include "stack.h"
#include "types.h"

struct st_vm
{
	//////////////////////////////////////////////////////////////////////////
	//evn
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

