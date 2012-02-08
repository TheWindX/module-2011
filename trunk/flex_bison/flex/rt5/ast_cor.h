

#pragma once

#include "ast.h"

namespace ns_core
{
	using namespace ns_ast;

	struct st_ast_cor
	{	
		st_context* m_context;
		array<st_ast*> m_p_values;//伪代码求值栈, 用于建立AST, 最后在栈里的就是root
		void clean();

 		st_ast* get_p_value(s32 index);
		void pop_p_value(u32 num = 1);
		void push_p_value(st_ast*);

		////
		void p_null_stat();
		void p_stat();
		void p_module();
		void p_using();
		void p_export();
		void p_null_path();
		void p_new_path();
		void p_string(const char*);
		void p_path();
		void p_var(bool is_extern);
		void p_new_var_list();
		void p_var_list();
		void p_assign(u32 l, u32 r);
		void p_unitop(const char*);
		void p_binop(const char*, u32 l, u32 r);
		void p_bool(bool);
		void p_number(u32 num, u32 l, u32 r);
		void p_quot_string(const char*);
		void p_null_para_list();
		void p_para_list();
		void p_apply(u32 l, u32 r);
		void p_enter();
		void p_exit(u32 l, u32 r);

		void p_return(bool byield = false);

		void p_if();
		void p_if_comlete(u32, u32);
		void p_then();
		void p_else();

		void p_null_for();
		void p_for_start();
		void p_for_condition();
		void p_for_every();
		void p_for_stats(u32, u32);

		void p_null_array();
		void p_array();
		void p_null_map();
		void p_map();

		void p_insert();
		void p_index();

		void p_self_op(bool add_or_sub, bool pre_or_post);
	};

}