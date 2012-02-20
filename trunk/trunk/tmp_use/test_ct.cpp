
/************************************************************************/
/* 测试脚本读入接口                                                                     */
/************************************************************************/

#include <iostream>
#include <string>


#include "../ct/interface.h"
#include "../console/interface_ct.h"

using namespace ns_base;

struct st_console_print : public ns_base::ns_c_toy::i_functor
{
	h_console_script_ct* m_console;
	std::string str_show;
	virtual void on_eval(i_context* ctx)
	{
		str_show = "";
		for(int i = 0; ;++i)
		{
			str_show += ctx->to_printable_string(i);
			if(i<ctx->in_size()-1 )
			{
				str_show += "\t";
			}
			else break;
		}
		ctx->begin_push();
		m_console->output(str_show.c_str() );
	}

	st_console_print(h_console_script_ct* console):m_console(console){};
};

void test_console()
{
	
	h_console_script_ct* hcsc;
	get(hcsc);
	hcsc->set_show_reserve(20);

	st_console_print my_print(hcsc);

	hcsc->get_ct()->reg_functor("print", &my_print);
	hcsc->get_ct()->reg_functor("std.sys.print", &my_print);

	hcsc->entry_thread();
	while(1)
	{
		hcsc->run_once();
	}
}


int main_ct(int argc, char** argv)
{

	test_console();
	return 0;
	using namespace ns_c_toy;
	
	h_c_toy* hct;
	get(hct);

	hct->load_file("test.txt");
	hct->run();

	for (int i = 0; i<hct->get_code_size(); ++i)
	{
		printf("%d %s\n", i, hct->get_code_string(i) );
	}
	system("pause");

	return 0;
}