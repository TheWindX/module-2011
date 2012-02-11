
#include "context.h"

#include "bison_user.h"

#include "proto_value.h"
#include "proto_code.h"

#include "exception.h"

namespace ns_core
{
	void st_context::gen_var()
	{
		ns_core::ns_ast::st_ast* pa = get_ast_cons().get_p_value(0);
		get_vm_cons().m_symbols.reset_visitor();//符号表的访问重置
		pa->gen_var(this);
	}

	void st_context::gen_code()
	{
		ns_core::ns_ast::st_ast* pa = get_ast_cons().get_p_value(0);
		get_vm_cons().m_symbols.reset_visitor();//符号表的访问重置
		pa->gen_code(this);
	}

	void st_context::gen_idx()
	{
		for(u32 i = 0; i<m_functions_reg.size(); ++i)
		{
			st_function* f = m_functions_reg[i];
			f->gen_idx(this);
		}
	}

	void st_context::patch()
	{
		for(u32 i = 0; i<m_functions_reg.size(); ++i)
		{
			st_function* f = m_functions_reg[i];
			f->patch(this);
		}
	}

	st_context::st_context()
	{
		m_ast.set_vm_cons(&m_vm);
	}

	void st_context::enter_function(ns_ast::st_function* func)
	{
		m_functions_reg.push(func);
		m_functions_stk.push(func);
	}

	void st_context::exit_function()
	{
		m_functions_stk.pop();
	}

	void st_context::enter_for(ns_ast::st_for* _for)
	{
		m_fors.push(_for);
	}

	void st_context::exit_for()
	{
		m_fors.pop();
	}

	ns_ast::st_for* st_context::get_current_for()
	{
		return m_fors.top();
	}

	ns_ast::st_function* st_context::get_cur_function()
	{
		if(m_functions_stk.size() == 0) return 0;
		return m_functions_stk.top();
	}

	void st_context_user::load_file(const char* file)
	{
		FILE* fin = fopen(file, "rb");
		std::string str = "";
		fseek(fin, 0, SEEK_END);
		long sz = ftell(fin);
		fseek(fin, 0, SEEK_SET);

		str.resize(sz);
		fread(&str[0], 1, sz, fin);
		fclose(fin);

		load_buffer(str.c_str(), str.size() );
	}

	void st_context_user::run()
	{
		get_vm_cons().apply_instant();
		get_vm_cons().eval();
	}

	void st_context_user::load_buffer(const char* buff, u32 buff_sz)
	{
		try
		{
			g_bison_use.reset_buffer(buff, buff_sz);
			get_vm_cons().m_symbols.reset_visitor();//符号表的访问重置

			g_bison_use.parse();//这样生成了parse tree
			assert(get_ast_cons().m_p_values.size() == 1);

			gen_var();//生成 parse tree 上的 var info
			gen_code();//生成parse tree 上的 code info
			gen_idx();//从parse tree 到 vm codes
			patch();//完成后对vm code 的 goto index 的修正

			//把编译得到的 function置到 vm 里
			st_function* f = m_functions_stk[0];
			st_value v = st_v_function::make_value(&get_vm_cons(), f->m_code);
			get_vm_cons().m_evals.push(v);

			//清除编译中间状态
			m_functions_reg.clear();
			m_functions_stk.clear();
			get_ast_cons().clean();
			get_vm_cons().clean();
		}
		catch(st_compile_exception ex)
		{	
			//清除编译中间状态
			m_functions_reg.clear();
			m_functions_stk.clear();
			get_ast_cons().clean();
			get_vm_cons().clean();
			throw ex;
		}
		
	}


	void st_context_user::load_string(const char* str)
	{
		load_buffer(str, strlen(str) );
	}

	void st_context_user::print_codes()
	{
		u32 sz = get_vm_cons().m_codes.size();
		for(u32 i = 0; i<get_vm_cons().m_codes.size(); ++i)
		{
			printf("%d %s\n", i, code_to_string(get_vm_cons().m_codes[i], &get_vm_cons() ) );
		}		
	}

	st_context_user& st_context_user::instance()
	{
		static st_context_user ins;
		return ins;
	}

}
