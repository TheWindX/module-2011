

#include "flex_user.h"

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	std::string str = "abc,-123.01 abc";
	g_flex_use.reset_buffer(str.c_str(), str.size() );

	int r = 0;
	do
	{
		r = g_flex_use.lex();
		std::cout<<g_flex_use.get_cur_pos()<<std::endl;

	}while(r != 0);



	

	return 0;
}