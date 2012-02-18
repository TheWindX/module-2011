

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 测试 嵌入函数接口                                                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include "interface.h"

using namespace ns_base::ns_c_toy;


struct st_functor1 : public i_functor
{
	void on_eval(i_context* ctx)
	{
		long sz = ctx->in_size();
		for(long i = 0; i<sz; ++i)
		{
			printf("%s, ", ctx->to_printable_string(i) );
		}
		printf("\n");
	}
};

struct st_my_add : public i_functor
{
	void on_eval(i_context* ctx)
	{
		long sz = ctx->in_size();
		if(sz != 2)
		{
			ctx->begin_push();
			ctx->push_string("have no 2 in_parameter!");
		}
		else
		{
			int p1;
			bool ret = ctx->to_int(0, p1);
			if(!ret)
			{
				ctx->begin_push();
				ctx->push_string("para1 is no int type!");
				return;
			}
			int p2;
			ret = ctx->to_int(1, p2);
			if(!ret)
			{
				ctx->begin_push();
				ctx->push_string("para2 is no int type!");
				return;
			}

			
			ctx->begin_push();
			ctx->push_int(p1+p2);
		}
	}
};


int main2(int argc, char** argv)
{
	st_functor1 f1;
	st_my_add f_add;
	h_c_toy* hc = get_handler();
	hc->reg_functor("test_print", &f1);
	hc->reg_functor("mylib.add", &f_add);

	bool no_err = hc->load_string("test_print(1, true, \"asdf\");");
	if(!no_err)
	{
		printf("%s\n", hc->get_last_error() );
		return -1;
	}
	no_err = hc->run();
	if(!no_err)
	{
		printf("%s\n", hc->get_last_error() );
		return -1;
	}


	no_err = hc->load_string("test_print(mylib.add(3, 4) );\
		test_print(mylib.add(3) );\
		test_print(mylib.add(3, true) );\
		test_print(mylib.add(true, true) );\
		");
	if(!no_err)
	{
		printf("%s\n", hc->get_last_error() );
		return -1;
	}
	no_err = hc->run();
	if(!no_err)
	{
		printf("%s\n", hc->get_last_error() );
		return -1;
	}
	return 0;
}