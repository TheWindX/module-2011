
#pragma once

#include "vm.h"
#include "code_seg.h"

namespace ns_core
{
	using ns_base::array;
	struct st_context;
	
	namespace ns_ast
	{	
		struct st_function;

		struct st_code_info
		{
			st_code m_code;
			u32 m_idx;
			u32 m_goto_id;
		};

		struct st_ast
		{
			//first:
			virtual void gen_var(st_context* ctx){};
			virtual void gen_code(st_context* ctx){};
			//virtual void gen_debug(st_context* ctx){};//注意，有debug.add操作的，必须填充src_pos
			virtual ~st_ast(){} 

			//function of code location in
			st_function* m_function;
			u32 m_code_id1;
			u32 m_code_id2;
			u32 m_src_pos1;
			u32 m_src_pos2;
			st_ast():m_code_id1(0),m_code_id2(0),m_src_pos1(0),m_src_pos2(0){}
		};

		struct st_stat;
		struct st_stat_list : public st_ast
		{
			array<st_stat*> m_stats;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};
		
		struct st_stat : public st_ast
		{
			
		};
		
		struct st_string : public st_ast
		{
			char* m_str;
		};

		struct st_expr : public st_stat{};
		struct st_path : st_ast
		{
			array<st_string*> m_strs;
			const char* to_string();
		};

		struct st_var : public st_expr
		{
			bool m_extern;
			char* m_name;

			ns_core::st_sym_var* m_var;
			void gen_var(st_context* ctx);

			void gen_code(st_context* ctx);
		};

		struct st_var_list : public st_ast
		{
			array<st_var*> m_vars;
		};

		struct st_para_list;
		struct st_assign : public st_stat
		{
			st_var_list* m_left;
			st_para_list* m_right;

			array<ns_core::st_sym_var*> m_left_var;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};
		
		struct st_unitary : public st_expr
		{
			st_expr* m_right;
			std::string m_op;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_binary : public st_expr
		{
			st_expr* m_left;
			st_expr* m_right;
			std::string m_op;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_bool : public st_expr
		{
			bool m_b;
			void gen_code(st_context* ctx);
		};

		struct st_number : public st_expr
		{
			u32 m_number;
			void gen_code(st_context* ctx);
		};

		struct st_quoto_string : public st_expr
		{
			char* m_str;
			void gen_code(st_context* ctx);
		};

		struct st_para_list : public st_ast
		{
			ns_base::array<st_expr*> m_exprs;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_apply : public st_expr
		{
			st_expr* m_function_head;
			st_para_list* m_paras;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_function : public st_expr
		{
			st_path* m_args;
			st_stat_list* m_stats;

			array<st_code_info> m_codes;

			u32 m_code_idx;

			st_function_code* m_code;

			array<ns_core::st_sym_var*> m_arg_vars;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);

			void gen_idx(st_context* ctx);
			void patch(st_context* ctx);
			void print_codes(st_context* ctx);
		};

		struct st_return : public st_stat
		{
			bool m_byield;
			st_para_list* m_exprs;
			void gen_var(st_context* ctx);

			void gen_code(st_context* ctx);
		};
		
		struct st_if : public st_stat
		{
			st_expr* m_expr;
			st_stat_list* m_stats;

			u32 m_goto_else;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};
		
		struct st_if_list : public st_ast
		{
			array<st_if*> m_ifs;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_else : public st_ast
		{
			st_stat_list* m_stats;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_if_else : public st_stat
		{
			st_if_list* m_if_list;
			st_else* m_else;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_for : public st_stat
		{
			st_stat_list* m_start;
			st_expr* m_condition;
			st_stat_list* m_every;

			st_stat_list* m_stats;

			s32 m_break_code;
			s32 m_continue_code;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_array_expr : public st_expr
		{
			st_para_list* m_para_list;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_key_value
		{
			st_expr* m_key;
			st_expr* m_value;
		};

		struct st_map_expr : public st_expr
		{
			array<st_key_value> m_key_values;
			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_self_op : public st_expr
		{
			bool m_add_or_sub;
			bool m_pre_or_post;
			st_var* m_var;

			//translate
			st_assign* m_assign;

			void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_break : public st_stat
		{
			//void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};

		struct st_continue : public st_stat
		{
			//void gen_var(st_context* ctx);
			void gen_code(st_context* ctx);
		};
	}
}