
#include <iostream>
#include <string>

#include "exception.h"
#include "context.h"

int main(int argc, char** argv)
{
	using namespace  ns_core;

	st_context_user& user = st_context_user::instance();
	try
	{	
		user.load_string("extern g.x = 100; std.sys.prix nt(\"load_string\");");
		user.print_codes();
		user.run();
	}
	catch(st_compile_exception ex)
	{
		std::cout<<ex.m_desc<<std::endl;
	}

	try
	{
		user.load_file("user_file.txt");
		user.print_codes();
		user.run();
	}
	catch (st_compile_exception ex)
	{
		std::cout<<ex.m_desc<<std::endl;
	}
	
	return 0;
}