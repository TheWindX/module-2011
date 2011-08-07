

#include "flex_user.h"

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	std::string str = "asdf 1234, 5678";
	g_flex_use.reset_buffer(str.c_str(), str.size() );

	int r = 0;
	do
	{
		r = g_flex_use.lex();
		std::cout<<g_flex_use.get_cur_pos()<<std::endl;
		printf(g_flex_use.get_text() );

	}while(r != 0);



	

	return 0;
}