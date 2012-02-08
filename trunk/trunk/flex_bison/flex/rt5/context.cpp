#include "flex_user.h"
#include "context.h"
#include "bison_user.h"

#include <cassert>

#include "code.h"
#include "value.h"

namespace ns_core
{
	void st_context::enter_function(st_function* func)
	{
		m_functions_reg.push(func);
		m_functions_stk.push(func);
	}

	void st_context::exit_function()
	{
		m_functions_stk.pop();
	}

	st_function* st_context::get_cur_function()
	{
		if(m_functions_stk.size() == 0) return 0;
		return m_functions_stk.top();
	}

	void st_context::load_file(const char* file)
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

	void st_context::load_buffer(const char* buff, u32 buff_sz)
	{
		g_bison_use.reset_buffer(buff, buff_sz);
		get_vm_cor().m_symbols.reset_visitor();//���ű�ķ�������

		m_debug.m_src_text.reset(buff, buff_sz);//debug text��ʼ��
		g_flex_user.set_new_line_handler(&ns_core::ns_debug::on_new_line);//����[(line, pos)]

		g_bison_use.parse();//����������parse tree
		assert(this->m_ast_cor.m_p_values.size() == 1);

		gen_var();//���� parse tree �ϵ� var info
		gen_code();//����parse tree �ϵ� code info
		gen_idx();//��parse tree �� vm codes
		patch();//��ɺ��vm code �� goto index ������
		gen_debug();//���� vm <-> sources �� debug��Ϣ, 
		
		push_function();
		clean();
	}

	void st_context::load_string(const char* buff)
	{
		load_buffer(buff, strlen(buff) );
	}

	st_context::st_context()
	{
		m_ast_cor.m_vm_cor.init();
	}

	st_ast* st_context::get_ast_root()
	{
		if(m_ast_cor.m_p_values.size() == 0) return 0;
		return m_ast_cor.m_p_values[0];
	}

	void st_context::gen_var()
	{
		ns_core::ns_ast::st_ast* pa = m_ast_cor.get_p_value(0);
		get_vm_cor().m_symbols.reset_visitor();//���ű�ķ�������
		pa->gen_var(this);
	}

	void st_context::gen_code()
	{
		ns_core::ns_ast::st_ast* pa = m_ast_cor.get_p_value(0);
		get_vm_cor().m_symbols.reset_visitor();//���ű�ķ�������
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

	void st_context::gen_debug()
	{
		for(u32 i = 0; i<m_functions_reg.size(); ++i)
		{
			st_function* f = m_functions_reg[i];
			f->gen_debug(this);
		}

		m_debug.m_src2code.analyze();
	}

	void st_context::patch()
	{
		for(u32 i = 0; i<m_functions_reg.size(); ++i)
		{
			st_function* f = m_functions_reg[i];
			f->patch(this);
		}
	}

	void st_context::push_function()
	{
		st_function* f = m_functions_stk[0];

		st_value v = st_v_function::make_value(&m_ast_cor.m_vm_cor, f->m_code);
		m_ast_cor.m_vm_cor.m_evals.push(v);
	}

	void st_context::clean()
	{
		m_functions_reg.clear();
		m_functions_stk.clear();
		m_ast_cor.clean();
	}

	void st_context::run()
	{
		get_vm_cor().apply_instant();
		get_vm_cor().eval();
	}

	void st_context::print_codes()
	{
		for(u32 i = 0; i<m_functions_reg.size(); ++i)
		{
			st_function* f = m_functions_reg[i];
			f->print_codes(this);
		}
	}

}