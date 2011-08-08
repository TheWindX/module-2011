

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


void yyerror (char const * error_info)
{
	std::string str_err = error_info;
	if(str_err.find("syntax error", 0) != std::string::npos )
	{
		str_err.replace(0, 12, "”Ô∑®¥ÌŒÛ");
	}

	std::cout<<str_err.c_str()<<" at line: "<<g_flex_user.get_cur_row()<<"  col: "<<g_flex_user.get_cur_col()<<std::endl;
	std::string err_line = g_flex_user.get_current_line();
	std::cout<<err_line.c_str()<<std::endl;

	int col = g_flex_user.get_cur_col()-g_flex_user.get_length()+1;
	for(size_t i=0; i<col-1; ++i)
	{
		if(err_line[i] != '\t')
			std::cout<<' ';
		else
			std::cout<<"        ";
	}
	std::cout<<"^\n";
};
