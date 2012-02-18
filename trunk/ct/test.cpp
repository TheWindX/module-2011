
/************************************************************************/
/* 测试脚本读入接口                                                                     */
/************************************************************************/

#include <iostream>
#include <string>

#include "interface.h"

int main1(int argc, char** argv)
{
	using namespace ns_base::ns_c_toy;

	h_c_toy* hc = get_handler();
	bool no_err = hc->load_string("global print = std.sys.print; ");
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
	no_err = hc->load_string("print(1234,5678); ");
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