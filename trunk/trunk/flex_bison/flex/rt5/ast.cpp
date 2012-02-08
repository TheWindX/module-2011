
#include "ast.h"
#include <string>
#include <cassert>

#include "context.h"

namespace ns_core
{
	namespace ns_ast
	{
		const char* st_path::to_string()
		{	
			u32 sz = m_strs.size();
			if(sz == 0) return "";
			static std::string ret;
			ret = m_strs.at(0)->m_str;
			
			for(u32 i = 1; i<sz; ++i)
			{
				char* str = m_strs.at(i)->m_str;
				ret += ".";
				ret += str;
			}

			return ret.c_str();
		}

		void st_stat_list::gen_var(st_context* ctx)
		{
			for(u32 i = 0; i<m_stats.size(); ++i)
			{
				m_stats[i]->gen_var(ctx);
			}
		}

		void st_stat_list::gen_code(st_context* ctx)
		{	
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();
			
			for(u32 i = 0; i<m_stats.size(); ++i)
			{
				m_stats[i]->gen_code(ctx);
			}

			m_code_id2 = m_function->m_codes.size();
		}

		void st_stat_list::gen_debug(st_context* ctx)
		{
			for(u32 i = 0; i<m_stats.size(); ++i)
			{
				m_stats[i]->gen_debug(ctx);
			}
		}

		void st_function::gen_var(st_context* ctx)
		{
			ctx->get_vm_cor().m_symbols.enter();
			array<st_string*>& strs = this->m_args->m_strs;
			for(u32 i = 0; i<strs.size(); ++i)
			{
				ns_util::st_var* v = ctx->get_vm_cor().m_symbols.reg_arg_name(strs[i]->m_str);
				m_arg_vars.push(v);
			}
			this->m_stats->gen_var(ctx);
			ctx->get_vm_cor().m_symbols.exit();
		}

		void st_function::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			if(m_function)m_code_id1 = m_function->m_codes.size();
			else m_code_id1 = U32_NA;

			ctx->get_vm_cor().m_symbols.enter();
			ctx->enter_function(this);

			st_code_info code;
			for(u32 i = m_arg_vars.size()-1; i != U32_NA; --i)
			{
				ns_util::st_var* v = m_arg_vars[i];
				if(v->m_type == e_local)
				{
					ctx->get_vm_cor().c_pop_local(v->l.idx, &code.m_code);
					m_codes.push(code);
				}
				else if(v->m_type == e_ref)
				{
					ctx->get_vm_cor().c_pop_ref(v->r.idx, &code.m_code);
					m_codes.push(code);
				}
				else
				{
					//可能这个名字未有定义
					assert(false);
				}
			}
			m_stats->gen_code(ctx);
			
			//不管存在不存在, 先填充
			//if(m_codes.top().m_code.m_tag != ns_util::st_singleton<st_c_ret>::instance().m_tag )
			//{
				//function尾填ret_begein, ret
				ctx->get_vm_cor().c_ret_begin(&code.m_code);
				m_codes.push(code);

				ctx->get_vm_cor().c_ret(&code.m_code);
				m_codes.push(code);
			//}
			
			ctx->exit_function();

			//st_function_code生成
			ns_util::st_scope* scope = ctx->get_vm_cor().m_symbols.get_cur_scope();
			ctx->get_vm_cor().c_push_function(U32_NA, 
				m_args->m_strs.size(), 
				scope->m_local_vars.size(),
				&code.m_code
				);

			m_code = code.m_code.get<st_function_code*>();
			array<ns_util::st_var*>& refs = scope->m_ref_vars;
			for(u32 i = 0; i<refs.size(); ++i)
			{
				if(refs[i]->r.ref)
					m_code->add_ref(refs[i]->r.ref->r.idx);
				else
					m_code->add_ref(U32_NA);
			}

			if(m_function) m_function->m_codes.push(code);

			ctx->get_vm_cor().m_symbols.exit();

			if(m_function)m_code_id2 = m_function->m_codes.size();
			else m_code_id2 = U32_NA;
		}

		void st_function::gen_debug(st_context* ctx)
		{
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, m_codes[0].m_idx, m_codes.top().m_idx+1/*闭区间*/);
			m_stats->gen_debug(ctx);
		}

		void st_function::gen_idx(st_context* ctx)
		{	
			m_code->m_code_idx = ctx->get_vm_cor().m_codes.size();
			
			for(u32 i = 0; i<m_codes.size(); ++i)
			{
				st_code_info& pc = m_codes[i];
				ctx->get_vm_cor().m_codes.push(pc.m_code);
				pc.m_idx = ctx->get_vm_cor().m_codes.m_top;
			}
		}

		void st_function::patch(st_context* ctx)
		{
			for(u32 i = 0; i<m_codes.size(); ++i)
			{
				st_code_info& code = m_codes[i];
				if(code.m_code.m_tag == ns_util::st_singleton<st_c_goto_false>::instance().m_tag
					||code.m_code.m_tag == ns_util::st_singleton<st_c_goto_true>::instance().m_tag
					||code.m_code.m_tag == ns_util::st_singleton<st_c_goto>::instance().m_tag
					)
				{
					u32 idx_goto = m_codes[code.m_goto_id].m_idx;
					code.m_code.set<u32>(idx_goto);
					ctx->get_vm_cor().m_codes[code.m_idx].set<u32>(idx_goto);
				}
				//no need
				//else if(code.m_code.m_tag == ns_util::st_singleton<st_c_push_function>::instance().m_tag)
				//{
				//	st_function_code* c = code.m_code.get<st_function_code*>();
				//	c->m_code_idx = code.m_fptr->m_codes[0].m_idx;
				//}
			}
		}

		void st_function::print_codes(st_context* ctx)
		{
			for(u32 i = 0; i<m_codes.size(); ++i)
			{
				printf("%d: %s\n", m_codes[i].m_idx, m_codes[i].m_code.to_code_string(&ctx->get_vm_cor() ) );
			}
		}

		void st_assign::gen_var(st_context* ctx)
		{
			u32 sz = m_left->m_vars.size();
			for(u32 i = 0; i<sz; ++i)
			{
				st_var* p = m_left->m_vars[i];
				ns_util::st_var* var = ctx->get_vm_cor().m_symbols.reg_name(p->m_name);
				assert(var);
				m_left_var.push(var);
			}
			m_right->gen_var(ctx);
		}

		void st_assign::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			m_right->gen_code(ctx);

			u32 sz = m_left_var.size();
			for(u32 i = sz-1; i != U32_NA; --i)
			{	
				ns_util::st_var* p = m_left_var[i];
				if(p->m_type == ns_util::e_global)
				{
					st_code_info code; 
					ctx->get_vm_cor().c_pop_global(p->g.path->full_name(), &code.m_code);
					m_function->m_codes.push(code);
				}
				else if(p->m_type == ns_util::e_local)
				{
					st_code_info code; 
					ctx->get_vm_cor().c_pop_local(p->l.idx, &code.m_code);
					m_function->m_codes.push(code);
				}
				else if(p->m_type == ns_util::e_ref)
				{
					st_code_info code; 
					ctx->get_vm_cor().c_pop_ref(p->r.idx, &code.m_code);
					m_function->m_codes.push(code);
				}
			}

			m_code_id2 = m_function->m_codes.size();
		}

		void st_assign::gen_debug(st_context* ctx)
		{	
			u32 c1 = m_function->m_codes[m_code_id1].m_idx;
			u32 c2 = m_function->m_codes[m_code_id2].m_idx;
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, c1, c2);
			m_right->gen_debug(ctx);
		}

		void st_return::gen_var(st_context* ctx)
		{
			m_exprs->gen_var(ctx);
		}

		void st_return::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_ret_begin(&code.m_code);
			m_function->m_codes.push(code);

			m_exprs->gen_code(ctx);

			ctx->get_vm_cor().c_ret(&code.m_code, m_byield);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_para_list::gen_var(st_context* ctx)
		{
			for(u32 i = 0; i<m_exprs.size(); ++i)
			{
				m_exprs[i]->gen_var(ctx);
			}
		}

		void st_para_list::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			for(u32 i = 0; i<m_exprs.size(); ++i)
			{
				m_exprs[i]->gen_code(ctx);
			}
			
			m_code_id2 = m_function->m_codes.size();
		}

		void st_para_list::gen_debug(st_context* ctx)
		{

		}

		void st_var::gen_var(st_context* ctx)
		{
			if(m_extern)
			{
				m_var = ctx->get_vm_cor().reg_global(m_name);//注册在全局符号表和全局变量表里
			}
			else
				m_var = ctx->get_vm_cor().m_symbols.reg_name(m_name);
			assert(m_var);
		}

		void st_var::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			if(m_var->m_type == ns_util::e_global)
			{
				ctx->get_vm_cor().c_push_global(m_var->g.path->full_name(), &code.m_code);
			}
			else if(m_var->m_type == ns_util::e_local)
			{
				ctx->get_vm_cor().c_push_local(m_var->l.idx, &code.m_code);
			}
			else if(m_var->m_type == ns_util::e_ref)
			{
				ctx->get_vm_cor().c_push_ref(m_var->r.idx, &code.m_code);
			}
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_unitary::gen_var(st_context* ctx)
		{
			m_right->gen_var(ctx);
		}

		void st_unitary::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_apply_begin(&code.m_code);

			m_function->m_codes.push(code);

			m_right->gen_code(ctx);

			if(m_op == "-")
				ctx->get_vm_cor().c_push_global("std.core.minus", &code.m_code);
			else
				assert(false);

			m_function->m_codes.push(code);

			ctx->get_vm_cor().c_apply(&code.m_code);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_binary::gen_var(st_context* ctx)
		{
			m_left->gen_var(ctx);
			m_right->gen_var(ctx);
		}

		void st_binary::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_apply_begin(&code.m_code);

			m_function->m_codes.push(code);

			m_left->gen_code(ctx);
			m_right->gen_code(ctx);

			if(m_op == "+")
				ctx->get_vm_cor().c_push_global("std.core.add", &code.m_code);
			else if(m_op == "-")
				ctx->get_vm_cor().c_push_global("std.core.sub", &code.m_code);
			else if(m_op == "*")
				ctx->get_vm_cor().c_push_global("std.core.mul", &code.m_code);
			else if(m_op == "/")
				ctx->get_vm_cor().c_push_global("std.core.div", &code.m_code);
			else if(m_op == "%")
				ctx->get_vm_cor().c_push_global("std.core.mod", &code.m_code);
			else if(m_op == ">")
				ctx->get_vm_cor().c_push_global("std.core.gt", &code.m_code);
			else if(m_op == "<")
				ctx->get_vm_cor().c_push_global("std.core.lt", &code.m_code);
			else if(m_op == "==")
				ctx->get_vm_cor().c_push_global("std.core.equal", &code.m_code);
			else
				assert(false);

			m_function->m_codes.push(code);

			ctx->get_vm_cor().c_apply(&code.m_code);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_binary::gen_debug(st_context* ctx)
		{
			u32 c1 = m_function->m_codes[m_code_id1].m_idx;
			u32 c2 = m_function->m_codes[m_code_id2].m_idx;
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, c1, c2);	
		}

		void st_bool::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_push_bool(m_b, &code.m_code);
			m_function->m_codes.push(code);
			
			m_code_id2 = m_function->m_codes.size();
		}

		void st_number::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_push_int(m_number, &code.m_code);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_number::gen_debug(st_context* ctx)
		{
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, m_function->m_codes[0].m_idx, m_function->m_codes.top().m_idx);
		}

		void st_quoto_string::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_push_string(m_str, &code.m_code);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}
		
		void st_apply::gen_var(st_context* ctx)
		{
			m_function_head->gen_var(ctx);
			m_paras->gen_var(ctx);
		}

		void st_apply::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			st_code_info code;
			ctx->get_vm_cor().c_apply_begin(&code.m_code);
			m_function->m_codes.push(code);

			m_paras->gen_code(ctx);
			m_function_head->gen_code(ctx);

			ctx->get_vm_cor().c_apply(&code.m_code);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_apply::gen_debug(st_context* ctx)
		{
			u32 c1 = m_function->m_codes[m_code_id1].m_idx;
			u32 c2 = m_function->m_codes[m_code_id2].m_idx;
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, c1, c2);
		}

		void st_if::gen_var(st_context* ctx)
		{
			m_expr->gen_var(ctx);
			m_stats->gen_var(ctx);
		}

		void st_if::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			m_expr->gen_code(ctx);
			
			
			st_code_info code;

			ctx->get_vm_cor().c_goto_false(U32_NA, &code.m_code);
			m_function->m_codes.push(code);
			u32 idx = m_function->m_codes.m_top;

			m_stats->gen_code(ctx);

			ctx->get_vm_cor().c_goto(U32_NA, &code.m_code);
			m_function->m_codes.push(code);
			m_goto_else = m_function->m_codes.m_top;

			st_code_info& c = m_function->m_codes[idx];
			c.m_goto_id = m_function->m_codes.size();;

			m_code_id2 = m_function->m_codes.size();
		}

		void st_if::gen_debug(st_context* ctx)
		{
			m_expr->gen_debug(ctx);
			m_stats->gen_debug(ctx);
		}

		void st_if_list::gen_var(st_context* ctx)
		{
			for(u32 i = 0; i<m_ifs.size(); ++i)
			{
				m_ifs[i]->gen_var(ctx);
			}
		}

		void st_if_list::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			for(u32 i = 0; i<m_ifs.size(); ++i)
			{
				m_ifs[i]->gen_code(ctx);
			}

			m_code_id2 = m_function->m_codes.size();
		}

		void st_if_list::gen_debug(st_context* ctx)
		{
			for(u32 i = 0; i<m_ifs.size(); ++i)
			{
				m_ifs[i]->gen_debug(ctx);
			}
		}

		void st_else::gen_var(st_context* ctx)
		{
			this->m_stats->gen_var(ctx);
		}

		void st_else::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			m_stats->gen_code(ctx);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_else::gen_debug(st_context* ctx)
		{
			m_stats->gen_debug(ctx);
		}

		void st_if_else::gen_var(st_context* ctx)
		{
			m_if_list->gen_var(ctx);
			m_else->gen_var(ctx);
		}

		void st_if_else::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			m_if_list->gen_code(ctx);
			m_else->gen_code(ctx);

			//patch goto
			array<st_if*>& ifs = m_if_list->m_ifs;
			for(u32 i = 0; i<ifs.size(); ++i)
			{
				st_code_info& ci = m_function->m_codes[ifs[i]->m_goto_else];
				ci.m_goto_id = m_else->m_code_id2;
			}
			
			m_code_id2 = m_function->m_codes.size();
		}

		void st_if_else::gen_debug(st_context* ctx)
		{
			u32 c1 = m_function->m_codes[m_code_id1].m_idx;
			u32 c2 = m_function->m_codes[m_code_id2].m_idx;
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, c1, c2);

			m_if_list->gen_debug(ctx);
			m_else->gen_debug(ctx);
		}

		void st_for::gen_var(st_context* ctx)
		{
			if(m_start) m_start->gen_var(ctx);
			m_condition->gen_var(ctx);
			if(m_every) m_every->gen_var(ctx);
			m_stats->gen_var(ctx);
		}

		void st_for::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			if(m_start) m_start->gen_code(ctx);
			m_condition->gen_code(ctx);
			st_code_info code;
			ctx->get_vm_cor().c_goto_false(U32_NA, &code.m_code);
			m_function->m_codes.push(code);
			u32 idx = m_function->m_codes.m_top;

			m_stats->gen_code(ctx);
			if(m_every) m_every->gen_code(ctx);

			ctx->get_vm_cor().c_goto(U32_NA, &code.m_code);
			m_function->m_codes.push(code);
			u32 idx2 = m_function->m_codes.m_top;
			//patch
			m_function->m_codes[idx2].m_goto_id = m_condition->m_code_id1;
			m_function->m_codes[idx].m_goto_id = m_function->m_codes.size();

			m_code_id2 = m_function->m_codes.size();
		}

		void st_for::gen_debug(st_context* ctx)
		{
			u32 c1 = m_function->m_codes[m_code_id1].m_idx;
			u32 c2 = m_function->m_codes[m_code_id2].m_idx;
			ctx->m_debug.m_src2code.add(m_src_pos1, m_src_pos2, c1, c2);
			
			if(m_start)
				m_start->gen_debug(ctx);
			if(m_condition)
				m_condition->gen_debug(ctx);
			if(m_every)
				m_every->gen_debug(ctx);
			if(m_stats)
				m_stats->gen_debug(ctx);
		}

		void st_array_expr::gen_var(st_context* ctx)
		{
			m_para_list->gen_var(ctx);
		}

		void st_array_expr::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			//这里需要做的是，
			//new array
			//array.push(arr, expr)
			st_code_info code;
			ctx->get_vm_cor().c_apply_begin(&code.m_code);
			m_function->m_codes.push(code);

			ctx->get_vm_cor().c_apply_begin(&code.m_code);
			m_function->m_codes.push(code);
			ctx->get_vm_cor().c_push_global("std.core.null_array", &code.m_code);
			m_function->m_codes.push(code);
			ctx->get_vm_cor().c_apply(&code.m_code);
			m_function->m_codes.push(code);

			if(m_para_list)
			{
				ns_util::array<st_expr*> exprs = m_para_list->m_exprs;
				for(u32 i = 0; i<exprs.size(); ++i)
				{
					exprs[i]->gen_code(ctx);
				}
			}
			ctx->get_vm_cor().c_push_global("std.core.array_cor", &code.m_code);
			m_function->m_codes.push(code);
			ctx->get_vm_cor().c_apply(&code.m_code);
			m_function->m_codes.push(code);

			m_code_id2 = m_function->m_codes.size();
		}

		void st_map_expr::gen_var(st_context* ctx)
		{
			for(u32 i = 0; i<m_key_values.size(); ++i)
			{
				m_key_values[i].m_key->gen_var(ctx);
				m_key_values[i].m_value->gen_var(ctx);
			}
		}

		void st_map_expr::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			//这里需要做的是，
			//new map
			//map.insert(m, key, value)
			st_code_info code;

			for(u32 i = 0; i<m_key_values.size(); ++i)
			{
				ctx->get_vm_cor().c_apply_begin(&code.m_code);
				m_function->m_codes.push(code);
			}

			ctx->get_vm_cor().c_apply_begin(&code.m_code);
			m_function->m_codes.push(code);
			ctx->get_vm_cor().c_push_global("std.core.null_map", &code.m_code);
			m_function->m_codes.push(code);
			ctx->get_vm_cor().c_apply(&code.m_code);
			m_function->m_codes.push(code);
			
			for(u32 i = 0; i<m_key_values.size(); ++i)
			{
				m_key_values[i].m_key->gen_code(ctx);
				m_key_values[i].m_value->gen_code(ctx);
				ctx->get_vm_cor().c_push_global("std.core.map_insert", &code.m_code);
				m_function->m_codes.push(code);
				ctx->get_vm_cor().c_apply(&code.m_code);	
				m_function->m_codes.push(code);
			}


			m_code_id2 = m_function->m_codes.size();
		}

		void st_self_op::gen_var(st_context* ctx)
		{
			m_var->gen_var(ctx);

			//translate， v = v+1, v
			st_binary* binop = new st_binary;
			binop->m_op = "+";
			binop->m_left = m_var;
			st_number* num = new st_number;
			if(m_add_or_sub)
				num->m_number = 1;
			else
				num->m_number = -1;
			binop->m_right = num;

			m_assign = new st_assign;
			m_assign->m_left = new st_var_list;
			m_assign->m_right = new st_para_list;
			
			m_assign->m_left->m_vars.push(m_var);
			m_assign->m_right->m_exprs.push(binop);

			m_assign->gen_var(ctx);

		}

		void st_self_op::gen_code(st_context* ctx)
		{
			m_function  = ctx->get_cur_function();
			m_code_id1 = m_function->m_codes.size();

			if(m_pre_or_post)
			{
				m_assign->gen_code(ctx);
				m_var->gen_code(ctx);
			}
			else
			{
				m_var->gen_code(ctx);
				m_assign->gen_code(ctx);
			}
			
			m_code_id2 = m_function->m_codes.size();
		}

	}
}