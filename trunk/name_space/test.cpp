#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>


#include <string>
#include <vector>
#include <iostream>

#include "path.h"

#include "../head/utility_new.h"
using namespace ns_path;
int main(int argc, char** argv)
{
	detect_memory_leaks(true);
	int* pi = new int(1234);
	st_path_service serv;
	st_path* p = serv.reg_path(serv.m_root, "pa");
	p = serv.reg_path(p, "paa");
	p = serv.reg_path(p, "paaa");
	
	std::cout<<serv.get_node_string(p)<<std::endl;
	return 0;
}


