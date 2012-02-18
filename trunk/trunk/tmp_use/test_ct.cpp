
/************************************************************************/
/* 测试脚本读入接口                                                                     */
/************************************************************************/

#include <iostream>
#include <string>


#include "../c_toy/interface.h"


using namespace ns_base;

int main(int argc, char** argv)
{
	using namespace ns_c_toy;
	h_c_toy* hc;
	get(hc);
	hc->load_string("std.sys.print(1234,5678);");
	hc->run();

	return 0;
}