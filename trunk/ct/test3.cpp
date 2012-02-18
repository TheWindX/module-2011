
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 测试调试接口                                                                     */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include "interface.h"

using namespace ns_base::ns_c_toy;


void test31()
{
	h_c_toy* hc = get_handler();

	bool no_err = hc->load_file("user_file3.txt");
	long sz = hc->get_code_size();
	for(long i = 0; i<sz; ++i)
	{
		printf("%d %s\n", i, hc->get_code_string(i) );
	}
}

//src <-> code, map
void test32()
{
	h_c_toy* hc = get_handler();

	bool no_err = hc->load_file("user_file3.txt");
	long left_code_idx;
	long right_code_idx = hc->src_to_code(2/*std.sys.print(1234, 5678); //in user_file3.txt*/, left_code_idx);

	hc->debug_step(true);
	bool done = hc->debug_run();
	while(!done)
	{
		printf("cur_code: %s\n", hc->get_current_code_string() );
		printf("本地:");
		for(long i = 0; i<hc->get_local_size(); ++i)
		{
			printf("%d:%s, ", i, hc->get_local_value_string(i) );
		}
		printf("\n\n");

		printf("表达式栈:");
		for(long i = 0; i<hc->get_eval_size(); ++i)
		{
			printf("%d:%s, ", i, hc->get_eval_value_string(i) );
		}
		printf("\n\n");

		printf("逃逸:");
		for(long i = 0; i<hc->get_ref_size(); ++i)
		{
			printf("%d:%s, ", i, hc->get_ref_value_string(i) );
		}
		printf("\n\n");
		printf("\n\n");

		done = hc->debug_continue();
	}

}

int main(int argc, char** argv)
{	
	test32();
}