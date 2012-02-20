
/************************************************************************/
/* 测试脚本读入接口                                                                     */
/************************************************************************/

#include <iostream>
#include <string>


#include "../ct/interface.h"
#include "../console/interface_ct.h"

using namespace ns_base;

void test_console()
{
	h_console_script_ct* hcsc;
	get(hcsc);

	hcsc->entry_thread();
	while(1)
	{
		hcsc->run_once();
	}
}


int main(int argc, char** argv)
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