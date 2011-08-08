
#include "flex_header.h"

#include <string>


struct st_flex_use
{
	size_t m_column_count;
	size_t m_row_count;
	size_t m_pos_count;

	size_t m_idx;
	std::string	m_str;
	
	size_t m_line_pos;//当前行在整个字串的位置
};



void i_flex_use::reset_buffer(const char* buff, size_t sz)
{
	std::string str_tmp(buff, buff+sz);
	m_impl->m_str.swap(str_tmp);
	m_impl->m_idx = 0;

	m_impl->m_column_count = 0;
	m_impl->m_row_count = 0;
	m_impl->m_pos_count = 0;
	m_impl->m_line_pos = 0;

	//yyrestart
	yyrestart(0);
}

int i_flex_use::lex()
{
	return yylex();
}


//当前行
size_t i_flex_use::get_cur_row()
{
	return m_impl->m_row_count;
}
//当前列
size_t i_flex_use::get_cur_col()
{
	return m_impl->m_column_count;
}
//当前位置
size_t i_flex_use::get_cur_pos()
{
	return m_impl->m_pos_count;
}


//////////////////////////////////////////////////////////////////////////
//for flex use

void i_flex_use::new_token()//在flex里调用, 每一个token使用
{
	m_impl->m_pos_count += yyleng;

	for(size_t i = 0; i<yyleng; ++i)
	{
		if(yytext[i] == '\n')
		{
			m_impl->m_row_count++;
			m_impl->m_column_count = 0;
			m_impl->m_line_pos = m_impl->m_pos_count;
		}
		else
		{
			m_impl->m_column_count++;
		}
	}
}

//token.text
const char* i_flex_use::get_text()
{
	return yytext;
}
//token.length
size_t i_flex_use::get_length()
{
	return yyleng;
}

const char* i_flex_use::get_current_line_segment()
{
	static std::string ret;
	ret = m_impl->m_str.substr(m_impl->m_line_pos, m_impl->m_pos_count-m_impl->m_line_pos+1);
	return ret.c_str();
}

const char* i_flex_use::get_current_line()
{
	static std::string ret;
	ret = "";
	for(size_t i = m_impl->m_line_pos; i<m_impl->m_str.size(); ++i)
	{	
		if(m_impl->m_str[i] != '\n')
		{
			ret.push_back(m_impl->m_str[i]);
		}
	}
	
	return ret.c_str();
}


int i_flex_use::copy_buffer(char* buff, int max_size)
{
	int left_sz = m_impl->m_str.size()-m_impl->m_idx;
	int n = max_size < left_sz ? max_size:left_sz;

	if(n>0)
	{
		memcpy(buff, m_impl->m_str.c_str(), n);
		m_impl->m_idx += n;
	}

	return n;
}

//////////////////////////////////////////////////////////////////////////
i_flex_use::i_flex_use()
{
	m_impl = new st_flex_use;
}

i_flex_use::~i_flex_use()
{
	delete m_impl;
}

i_flex_use g_flex_user;