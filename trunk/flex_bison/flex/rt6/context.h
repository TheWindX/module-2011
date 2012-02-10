

#pragma once

//这里是用户入口
#include "vm_cons.h"
#include "ast_cons.h"

namespace ns_core
{
	namespace ns_ast{struct st_function;}//ast 结点上的st_function
	struct st_context
	{
		st_context();
		st_vm_cons m_vm;
		st_ast_cons m_ast;
		st_vm_cons& get_vm_cons(){return m_vm;}
		st_ast_cons& get_ast_cons(){return m_ast;}

		//for ast walker
		ns_base::array<ns_ast::st_function*> m_functions_reg;//这个在编译时把所有生成的function ast寄存在里面，最终根据这个填入代码
		ns_base::array<ns_ast::st_function*> m_functions_stk;//ast 遍历时每一个的function之下的结点，需要知道它的function环境，
		void enter_function(ns_ast::st_function* func);
		void exit_function();
		ns_ast::st_function* get_cur_function();

		//for 栈, 用以处理 当前的break, continue跳转
		array<ns_ast::st_for*> m_fors;
		void enter_for(ns_ast::st_for* func);
		void exit_for();
		ns_ast::st_for* get_current_for();
		
		//ast->code
		st_ast* get_ast_root();
		void gen_var();
		void gen_code();
		void gen_idx();
		void patch();
	};

	struct st_context_user : st_context
	{
		//
		void load_file(const char* file);
		void load_buffer(const char* buff, u32 buff_sz);
		void load_string(const char* str);

		void run();

		void print_codes();
		static st_context_user& instance();

	private:
		st_context_user(){}
	};
}

//for bison
#define g_ast (ns_core::st_context_user::instance().get_ast_cons() )

