
#include "flex_header.h"

#include <vector>
#include <string>


struct st_flex_use
{
	//for yylex buffer use
	std::string	m_str;
	int m_idx;
	
	//for yylloc use
	int m_pos;
	int m_col;
	int m_row;

	std::vector<int> m_line_pos;

	void set(const char* buff, size_t sz)
	{
		std::string str_tmp(buff, buff+sz);
		m_str.swap(str_tmp);
		m_idx = 0;

		m_pos = 0;
		m_col = 0;
		m_row = 1;
		m_line_pos.clear();
		m_line_pos.push_back(0);

		m_buffers.clear();

		m_new_line_handler = 0;
	}

	std::vector<std::string> m_buffers;

	handle_new_line_t m_new_line_handler;
};


void i_flex_use::reset_buffer(const char* buff, size_t sz)
{
	m_impl->set(buff, sz);
	
	yyrestart(0);
}

int i_flex_use::lex()
{
	return yylex();
}

const char* i_flex_use::get_buffer_ptr()
{
	return m_impl->m_str.c_str();
}

size_t i_flex_use::get_buffer_size()
{
	return m_impl->m_str.size();
}

void i_flex_use::set_new_line_handler(handle_new_line_t h)
{
	m_impl->m_new_line_handler = h;
}

//当前行
size_t i_flex_use::get_cur_row()
{
	return m_impl->m_row;
}
//当前列
size_t i_flex_use::get_cur_col()
{
	return m_impl->m_col;
}
//当前位置
size_t i_flex_use::get_cur_pos()
{
	return yylloc.pos;
}


const char* i_flex_use::get_segment(int pos1, int len)
{
	static std::string ret;
	ret = m_impl->m_str.substr(pos1, len);
	return ret.c_str();
}


//////////////////////////////////////////////////////////////////////////
//for flex use

void i_flex_use::new_token()//在flex里调用, 每一个token使用
{	
	yylloc.pos = m_impl->m_pos;
	yylloc.first_column = m_impl->m_col;
	yylloc.first_line = m_impl->m_row;
	
	for(int i = 0; i<yyleng; ++i)
	{
		m_impl->m_pos++;
		if(yytext[i] == '\n')
		{	
			if(m_impl->m_new_line_handler)
				m_impl->m_new_line_handler(m_impl->m_pos);

			m_impl->m_row++;
			m_impl->m_col = 0;
			m_impl->m_line_pos.push_back(m_impl->m_pos);
		}
		else
		{
			m_impl->m_col++;
		}
	}

	yylloc.last_line = m_impl->m_row;
	yylloc.last_column = m_impl->m_col;
	yylloc.len = yyleng;
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

const char* i_flex_use::get_line(int ln)
{
	static std::string ret;
	ret = "";
	
	std::vector<int>& lines = m_impl->m_line_pos;
	
	int sz = (int)lines.size();
	if(ln>=sz)
		return "";

	char ch;
	for(size_t i = lines[ln]; i<m_impl->m_str.size()&&(ch = m_impl->m_str[i]) != '\n'; ++i)
	{
		ret.push_back(ch);
	}

	return ret.c_str();

}


int i_flex_use::copy_buffer(char* buff, int max_size)
{
	int left_sz = (int)(m_impl->m_str.size() )-m_impl->m_idx;
	int n = max_size < left_sz ? max_size:left_sz;

	if(n>0)
	{
		memcpy(buff, m_impl->m_str.c_str(), n);
		m_impl->m_idx += n;
	}

	return n;
}



char* i_flex_use::new_buffer(const char* buff, int buff_sz)
{
	m_impl->m_buffers.push_back(std::string(buff, buff_sz) );
	return &(m_impl->m_buffers.back().at(0) );
}

void i_flex_use::delete_all()
{
	m_impl->m_buffers.clear();
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

//YYLTYPE yylloc;