

#include "flex_user.h"

#include "bison_user.h"
#include "bison_header.h"


struct st_bison_use
{
	
};

void i_bison_use::reset_buffer(const char* buff, size_t sz)
{
	g_flex_user.reset_buffer(buff, sz);
}

void i_bison_use::parse()
{
	yyparse();
}

//////////////////////////////////////////////////////////////////////////
i_bison_use::i_bison_use()
{
	m_impl = new st_bison_use;
}

i_bison_use::~i_bison_use()
{
	delete m_impl;
}

i_bison_use g_bison_use;

#include <sstream>
#include "exception.h"
void yyerror (char const * error_info)
{
	std::stringstream ss;
	std::string str_err = error_info;
	if(str_err.find("syntax error", 0) != std::string::npos )
	{
		str_err.replace(0, 12, "”Ô∑®¥ÌŒÛ");
	}

	ss<<str_err.c_str()<<" at line: "<<g_flex_user.get_cur_row()<<"  col: "<<g_flex_user.get_cur_col()<<std::endl;
	std::string err_line = g_flex_user.get_line(yylloc.first_line-1 );
	ss<<err_line.c_str()<<std::endl;

	size_t col = g_flex_user.get_cur_col()-g_flex_user.get_length()+1;
	for(size_t i=0; i<col-1; ++i)
	{
		if(err_line[i] != '\t')
			ss<<' ';
		else
			ss<<"        ";
	}
	ss<<"^\n";

	st_compile_exception ex;
	ex.m_type = st_compile_exception::e_comile_err;
	ex.m_desc = ss.str();
	throw ex;
};


#include <windows.h>
//#include <conio.h>
//#include <wincon.h>
//#include <fcntl.h>
//#include <io.h>



void set_text_red()
{
	HANDLE consolehwnd; 
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(consolehwnd,FOREGROUND_RED|FOREGROUND_INTENSITY); 
}
void set_text_normal()
{
	HANDLE consolehwnd; 
	consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(consolehwnd,FOREGROUND_INTENSITY); 
}