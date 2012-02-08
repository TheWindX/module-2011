#include "config.h"
#include <iostream>

#include "ast_cor.h"

using namespace ns_core::ns_ast;

namespace ns_core
{

	void st_ast_cor::clean()
	{
		m_p_values.clear();
		m_vm_cor.m_symbols.clean();
	}

	st_ast* st_ast_cor::get_p_value(s32 index)
	{
		if(index < 0)
		{
			u32 idx2 = m_p_values.size()+index;
			return m_p_values.at(idx2);
		}
		return m_p_values.at(index);
	}

	void st_ast_cor::push_p_value(st_ast* v)
	{
		m_p_values.push(v);
	}

	void st_ast_cor::pop_p_value(u32 num)
	{
		for(u32 i = 0; i<num; ++i)
		{
			m_p_values.pop();
		}
	}

	void st_ast_cor::p_null_stat()
	{
#ifdef _AST_DEBUG
		std::cout<<"null_stat"<<std::endl;
#endif
		st_ast* past = new st_stat_list;
		m_p_values.push(past);
	}

	void st_ast_cor::p_stat()
	{
#ifdef _AST_DEBUG
		std::cout<<"stat"<<std::endl;
#endif
		st_stat_list* stat_ls = dynamic_cast<st_stat_list*>(this->get_p_value(-2) );
		st_stat* stat = dynamic_cast<st_stat*>(this->get_p_value(-1) );
		stat_ls->m_stats.push(stat);
		pop_p_value(2);
		push_p_value(stat_ls);
	};

	void st_ast_cor::p_module()
	{
#ifdef _AST_DEBUG
		std::cout<<"module"<<std::endl;
#endif
		ns_ast::st_path* stat = dynamic_cast<ns_ast::st_path*>(this->get_p_value(-1) );
		std::string str = stat->to_string();
		//m_ctx->m_symbol.m_global.module_by_string(str.c_str() );
		m_vm_cor.m_symbols.module_path(str.c_str() );

		pop_p_value(1);
	};

	void st_ast_cor::p_using()
	{
#ifdef _AST_DEBUG
		std::cout<<"using"<<std::endl;
#endif
		ns_ast::st_path* stat = dynamic_cast<ns_ast::st_path*>(this->get_p_value(-1) );
		std::string str = stat->to_string();
		//m_ctx->m_symbol.m_global.using_path_by_string(str.c_str() );
		m_vm_cor.m_symbols.using_path(str.c_str() );
		pop_p_value(1);
	};

	void st_ast_cor::p_export()
	{
#ifdef _AST_DEBUG
		std::cout<<"export"<<std::endl;
#endif
		ns_ast::st_path* stat = dynamic_cast<ns_ast::st_path*>(this->get_p_value(-1) );
		array<st_string*> str = stat->m_strs;
		u32 sz = str.size();
		for(u32 i = 0; i<sz; ++i)
		{
			char* cstr = str.at(i)->m_str;
			bool b = m_vm_cor.m_symbols.export_symbol(cstr);
			ns_util::st_var* var = m_vm_cor.m_symbols.reg_name(cstr);

			u32 idx = var->g.path->get_id();
			if(idx >= m_vm_cor.m_globals.size() ) m_vm_cor.m_globals.resize(idx+1);
		}
		pop_p_value(1);
	};

	void st_ast_cor::p_null_path()
	{
#ifdef _AST_DEBUG
		std::cout<<"null_path"<<std::endl;
#endif
		ns_ast::st_path* p = new ns_ast::st_path;
		push_p_value(p);
	}

	void st_ast_cor::p_new_path()
	{
#ifdef _AST_DEBUG
		std::cout<<"new_path"<<std::endl;
#endif
		ns_ast::st_string* str = dynamic_cast<ns_ast::st_string*>(this->get_p_value(-1) );
		ns_ast::st_path* p = new ns_ast::st_path;
		p->m_strs.push(str);
		pop_p_value(1);
		push_p_value(p);
	}

	void st_ast_cor::p_string(const char* str)
	{
#ifdef _AST_DEBUG
		std::cout<<"string:"<<str<<std::endl;
#endif
		st_string* str1 = new st_string;
		str1->m_str = strdup(str);

		push_p_value(str1);
	};

	void st_ast_cor::p_path()
	{
#ifdef _AST_DEBUG
		std::cout<<"path"<<std::endl;
#endif
		ns_ast::st_path* path = dynamic_cast<ns_ast::st_path*>(this->get_p_value(-2) );
		st_string* str = dynamic_cast<st_string*>(this->get_p_value(-1) );
		path->m_strs.push(str);
		pop_p_value(2);
		push_p_value(path);
	};

	void st_ast_cor::p_var(bool is_extern)
	{
#ifdef _AST_DEBUG
		std::cout<<"var"<<std::endl;
#endif
		st_path* p = dynamic_cast<st_path*>(this->get_p_value(-1) );

		st_var* v = new st_var;
		v->m_name = strdup(p->to_string() );

		if(p->m_strs.size() > 1)
			v->m_extern = true;
		else
			v->m_extern = is_extern;
		pop_p_value(1);
		push_p_value(v);
	}

	void st_ast_cor::p_new_var_list()
	{
#ifdef _AST_DEBUG
		std::cout<<"new_path_list"<<std::endl;
#endif
		ns_ast::st_var* var = dynamic_cast<ns_ast::st_var*>(this->get_p_value(-1) );
		ns_ast::st_var_list* pl = new ns_ast::st_var_list;
		pl->m_vars.push(var);
		pop_p_value(1);
		push_p_value(pl);
	}

	void st_ast_cor::p_var_list()
	{
#ifdef _AST_DEBUG
		std::cout<<"var_list"<<std::endl;
#endif
		ns_ast::st_var_list* pl = dynamic_cast<ns_ast::st_var_list*>(this->get_p_value(-2) );
		ns_ast::st_var* var  = dynamic_cast<ns_ast::st_var*>(this->get_p_value(-1) );

		pl->m_vars.push(var);
		pop_p_value(1);
	}

	void st_ast_cor::p_assign(u32 l, u32 r)
	{
#ifdef _AST_DEBUG
		std::cout<<"assign"<<std::endl;
#endif

		ns_ast::st_var_list* vars = dynamic_cast<ns_ast::st_var_list*>(this->get_p_value(-2) );
		st_para_list* exprs = dynamic_cast<st_para_list*>(this->get_p_value(-1) );

		st_assign* assign = new st_assign;
		assign->m_left = vars;
		assign->m_right = exprs;
		assign->m_src_pos1 = l;
		assign->m_src_pos2 = r;

		pop_p_value(2);
		push_p_value(assign);
	};

	void st_ast_cor::p_unitop(const char* op)
	{
#ifdef _AST_DEBUG
		std::cout<<"unit_op:"<<op<<std::endl;
#endif
		st_expr* right = dynamic_cast<st_expr*>(this->get_p_value(-1) );
		st_unitary* uop = new st_unitary;
		uop->m_right = right;
		uop->m_op = op;

		pop_p_value(1);
		push_p_value(uop);
	}

	void st_ast_cor::p_binop(const char* op, u32 l, u32 r)
	{
#ifdef _AST_DEBUG
		std::cout<<"bin_op:"<<op<<std::endl;
#endif
		st_expr* left = dynamic_cast<st_expr*>(this->get_p_value(-2) );
		st_expr* right = dynamic_cast<st_expr*>(this->get_p_value(-1) );

		st_binary* binop = new st_binary;
		binop->m_left = left;
		binop->m_right = right;
		binop->m_op = op;
		binop->m_src_pos1 = l;
		binop->m_src_pos2 = r;

		pop_p_value(2);
		push_p_value(binop);
	}

	void st_ast_cor::p_bool(bool b)
	{
#ifdef _AST_DEBUG
		std::cout<<"bool:"<<b<<std::endl;
#endif
		st_bool* pb = new st_bool;
		pb->m_b = b;
		push_p_value(pb);
	}

	void st_ast_cor::p_number(u32 num, u32 l, u32 r)
	{
#ifdef _AST_DEBUG
		std::cout<<"number:"<<num<<std::endl;
#endif
		st_number* num1 = new st_number;
		num1->m_number = num;

		num1->m_src_pos1 = l;
		num1->m_src_pos2 = r;

		push_p_value(num1);
	};

	void st_ast_cor::p_quot_string(const char* s)
	{
#ifdef _AST_DEBUG
		std::cout<<"quot:"<<s<<std::endl;
#endif
		st_quoto_string* str = new st_quoto_string;
		str->m_str = strdup(s);
		push_p_value(str);
	}

	void st_ast_cor::p_null_para_list()
	{
#ifdef _AST_DEBUG
		std::cout<<"null_para_list"<<std::endl;
#endif

		st_para_list* pl = new st_para_list;
		push_p_value(pl);
	};

	void st_ast_cor::p_para_list()
	{
#ifdef _AST_DEBUG
		std::cout<<"para_list"<<std::endl;
#endif
		st_para_list* left = dynamic_cast<st_para_list*>(this->get_p_value(-2) );
		st_expr* right = dynamic_cast<st_expr*>(this->get_p_value(-1) );

		left->m_exprs.push(right);
		pop_p_value(2);
		push_p_value(left);
	};

	void st_ast_cor::p_apply(u32 l, u32 r)
	{
#ifdef _AST_DEBUG
		std::cout<<"apply"<<std::endl;
#endif

		st_expr* func = dynamic_cast<st_expr*>(this->get_p_value(-2) );
		st_para_list* para_list = dynamic_cast<st_para_list*>(this->get_p_value(-1) );

		st_apply* apply = new st_apply;
		apply->m_function_head = func;
		apply->m_paras = para_list;
		apply->m_src_pos1 = l;
		apply->m_src_pos2 = r;

		pop_p_value(2);
		push_p_value(apply);
	};
	void st_ast_cor::p_enter()
	{
#ifdef _AST_DEBUG
		std::cout<<"enter"<<std::endl;
#endif
		m_vm_cor.m_symbols.enter();
	};

	void st_ast_cor::p_exit(u32 l, u32 r)
	{
#ifdef _AST_DEBUG
		std::cout<<"exit"<<std::endl;
#endif

		ns_ast::st_path* path = dynamic_cast<ns_ast::st_path*>(this->get_p_value(-2) );
		st_stat_list* stat_list = dynamic_cast<st_stat_list*>(this->get_p_value(-1) );

		st_function* func = new st_function;
		func->m_args = path;
		func->m_stats = stat_list;
		func->m_src_pos1 = l;
		func->m_src_pos2 = r;

		pop_p_value(2);
		push_p_value(func);

		//m_ctx->m_symbol.exit();
		m_vm_cor.m_symbols.exit();
	};

	void st_ast_cor::p_return(bool byield)//TODO
	{
#ifdef _AST_DEBUG
		std::cout<<"return"<<std::endl;
#endif

		st_para_list* exprs = dynamic_cast<st_para_list*>(this->get_p_value(-1) );
		st_return* ret = new st_return;
		ret->m_byield = byield;
		ret->m_exprs = exprs;

		pop_p_value(1);
		push_p_value(ret);	
	};


	void st_ast_cor::p_if()
	{
#ifdef _AST_DEBUG
		std::cout<<"if"<<std::endl;
#endif
		st_if_else* s_if = new st_if_else;
		s_if->m_if_list = new st_if_list;
		s_if->m_else = new st_else;
		s_if->m_else->m_stats  = new st_stat_list;
		m_p_values.push(s_if);
	}

	void st_ast_cor::p_if_comlete(u32 l, u32 r)
	{
		ns_ast::st_if_else* s_if_else = dynamic_cast<ns_ast::st_if_else*>(this->get_p_value(-1) );
		s_if_else->m_src_pos1 = l;
		s_if_else->m_src_pos2 = r;
	}

	void st_ast_cor::p_then()
	{
#ifdef _AST_DEBUG
		std::cout<<"then"<<std::endl;
#endif
		ns_ast::st_if_else* s_if_else = dynamic_cast<ns_ast::st_if_else*>(this->get_p_value(-3) );
		ns_ast::st_expr* expr = dynamic_cast<ns_ast::st_expr*>(this->get_p_value(-2) );
		st_stat_list* stat_list = dynamic_cast<st_stat_list*>(this->get_p_value(-1) );

		st_if* s_if = new st_if;
		s_if->m_expr = expr;
		s_if->m_stats = stat_list;
		s_if_else->m_if_list->m_ifs.push(s_if);
		pop_p_value(3);
		push_p_value(s_if_else);
	}

	void st_ast_cor::p_else()
	{
#ifdef _AST_DEBUG
		std::cout<<"else"<<std::endl;
#endif
		ns_ast::st_if_else* s_if_else = dynamic_cast<ns_ast::st_if_else*>(this->get_p_value(-2) );
		st_stat_list* stat_list = dynamic_cast<st_stat_list*>(this->get_p_value(-1) );

		st_else* s_else = new st_else;
		s_else->m_stats = stat_list;

		s_if_else->m_else = s_else;
		pop_p_value(2);
		push_p_value(s_if_else);
	}

	void st_ast_cor::p_null_for()
	{
#ifdef _AST_DEBUG
		std::cout<<"null_for"<<std::endl;
#endif
		st_for* p = new st_for;
		p->m_start = 0;
		p->m_condition = 0;
		p->m_every = 0;
		p->m_stats = 0;
		push_p_value(p);
	}

	void st_ast_cor::p_for_start()
	{
#ifdef _AST_DEBUG
		std::cout<<"for_start"<<std::endl;
#endif
		ns_ast::st_for* pfor = dynamic_cast<ns_ast::st_for*>(this->get_p_value(-2) );
		st_stat_list* pstats = dynamic_cast<st_stat_list*>(this->get_p_value(-1) );
		pfor->m_start = pstats;
		pop_p_value(1);
	}

	void st_ast_cor::p_for_condition()
	{
#ifdef _AST_DEBUG
		std::cout<<"for_condition"<<std::endl;
#endif
		ns_ast::st_for* pfor = dynamic_cast<ns_ast::st_for*>(this->get_p_value(-2) );
		st_expr* p_expr = dynamic_cast<st_expr*>(this->get_p_value(-1) );
		pfor->m_condition = p_expr;
		pop_p_value(1);
	}

	void st_ast_cor::p_for_every()
	{
#ifdef _AST_DEBUG
		std::cout<<"for_every"<<std::endl;
#endif
		ns_ast::st_for* pfor = dynamic_cast<ns_ast::st_for*>(this->get_p_value(-2) );
		st_stat_list* pstats = dynamic_cast<st_stat_list*>(this->get_p_value(-1) );
		pfor->m_every = pstats;
		pop_p_value(1);
	}

	void st_ast_cor::p_for_stats(u32 l, u32 r)
	{
#ifdef _AST_DEBUG
		std::cout<<"for_stats"<<std::endl;
#endif
		ns_ast::st_for* pfor = dynamic_cast<ns_ast::st_for*>(this->get_p_value(-2) );
		st_stat_list* pstats = dynamic_cast<st_stat_list*>(this->get_p_value(-1) );
		pfor->m_stats = pstats;
		pfor->m_src_pos1 = l;
		pfor->m_src_pos2 = r;
		pop_p_value(1);
	}

	void st_ast_cor::p_null_array()
	{
#ifdef _AST_DEBUG
		std::cout<<"null_array"<<std::endl;
#endif
		st_array_expr* expr = new st_array_expr;
		push_p_value(expr);
	}

	void st_ast_cor::p_array()
	{
#ifdef _AST_DEBUG
		std::cout<<"array"<<std::endl;
#endif
		st_array_expr* expr_arr = dynamic_cast<ns_ast::st_array_expr*>(this->get_p_value(-2) );
		st_para_list* plist = dynamic_cast<st_para_list*>(this->get_p_value(-1) );

		expr_arr->m_para_list = plist;
		pop_p_value(1);
	}

	void st_ast_cor::p_null_map()
	{
#ifdef _AST_DEBUG
		std::cout<<"null_map"<<std::endl;
#endif
		st_map_expr* expr = new st_map_expr;
		push_p_value(expr);
	}

	void st_ast_cor::p_map()
	{
#ifdef _AST_DEBUG
		std::cout<<"map"<<std::endl;
#endif
		st_map_expr* expr_arr = dynamic_cast<ns_ast::st_map_expr*>(this->get_p_value(-3) );
		st_expr* expr = dynamic_cast<st_expr*>(this->get_p_value(-2) );
		st_expr* expr1 = dynamic_cast<st_expr*>(this->get_p_value(-1) );
		expr_arr->m_key_values.push(st_key_value() );
		expr_arr->m_key_values.top().m_key = expr;
		expr_arr->m_key_values.top().m_value = expr1;
		pop_p_value(2);
	}

	void st_ast_cor::p_insert()
	{
#ifdef _AST_DEBUG
		std::cout<<"insert"<<std::endl;
#endif
		st_expr* expr_arr = dynamic_cast<ns_ast::st_expr*>(this->get_p_value(-3) );
		st_expr* expr = dynamic_cast<st_expr*>(this->get_p_value(-2) );
		st_expr* expr1 = dynamic_cast<st_expr*>(this->get_p_value(-1) );
		st_apply* p_app = new st_apply;
		st_var* pvar = new st_var;
		pvar->m_name = strdup("std.core.insert");
		p_app->m_function_head = pvar;
		p_app->m_paras = new st_para_list;
		p_app->m_paras->m_exprs.push(expr_arr);
		p_app->m_paras->m_exprs.push(expr);
		p_app->m_paras->m_exprs.push(expr1);
		
		pop_p_value(3);
		push_p_value(p_app);
	}

	void st_ast_cor::p_index()
	{
#ifdef _AST_DEBUG
		std::cout<<"index"<<std::endl;
#endif
		st_expr* expr_arr = dynamic_cast<ns_ast::st_expr*>(this->get_p_value(-2) );
		st_expr* expr = dynamic_cast<st_expr*>(this->get_p_value(-1) );
		st_apply* p_app = new st_apply;
		st_var* pvar = new st_var;
		pvar->m_name = strdup("std.core.index");
		p_app->m_function_head = pvar;
		p_app->m_paras = new st_para_list;
		p_app->m_paras->m_exprs.push(expr_arr);
		p_app->m_paras->m_exprs.push(expr);
		pop_p_value(2);
		push_p_value(p_app);
	}

	void st_ast_cor::p_self_op(bool add_or_sub, bool pre_or_post)
	{
#ifdef _AST_DEBUG
		if(add_or_sub && pre_or_post)
			std::cout<<"++n"<<std::endl;
		else if(!add_or_sub && pre_or_post)
			std::cout<<"--n"<<std::endl;
		else if(add_or_sub && !pre_or_post)
			std::cout<<"n++"<<std::endl;
		else if(!add_or_sub && !pre_or_post)
			std::cout<<"n--"<<std::endl;
		
#endif
		st_self_op* p = new st_self_op;
		p->m_var = dynamic_cast<ns_ast::st_var*>(this->get_p_value(-1) );
		p->m_add_or_sub = add_or_sub;
		p->m_pre_or_post = pre_or_post;
		pop_p_value(1);
		push_p_value(p);
	}

}
