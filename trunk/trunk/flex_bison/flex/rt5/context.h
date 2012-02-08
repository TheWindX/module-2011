#pragma once

#include "ast_cor.h"
#include "singleton.h"
#include "debug.h"

namespace ns_core
{
	struct st_context
	{
		st_ast_cor m_ast_cor;

		st_vm_cor& get_vm_cor(){ return m_ast_cor.m_vm_cor; }
		st_ast_cor& get_ast_cor(){ return m_ast_cor; }

		ns_util::array<st_function*> m_functions_reg;
		ns_util::array<st_function*> m_functions_stk;
		void enter_function(st_function* func);
		void exit_function();
		st_function* get_cur_function();
		
		st_context();
		
		//TODO, 暂时先建立ast
		void load_file(const char* file);
		void load_buffer(const char* buff, u32 buff_sz);
		void load_string(const char* buff);

		st_ast* get_ast_root();
		void gen_var();
		void gen_code();
		void gen_idx();
		void gen_debug();
		void patch();

		void push_function();
		void clean();

		void run();

		void global_set();
		
		void print_codes();

		ns_debug::st_debug m_debug;
		
	};

#define g_ctx (ns_util::st_singleton<ns_core::st_context>::instance() )
#define g_vm (ns_util::st_singleton<ns_core::st_context>::instance().get_vm_cor() )
#define g_ast (ns_util::st_singleton<ns_core::st_context>::instance().get_ast_cor() )
}
