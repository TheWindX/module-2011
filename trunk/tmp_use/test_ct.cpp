
/************************************************************************/
/* 测试脚本读入接口                                                                     */
/************************************************************************/

#include <iostream>
#include <string>


#include "../ct/interface.h"
#include "../console/interface_ct.h"

using namespace ns_base;

int main(int argc, char** argv)
{
	h_console_script_ct* hcsc;
	get(hcsc);

	hcsc->entry_thread();
	while(1)
	{
		hcsc->run_once();
	}

	return 0;
}