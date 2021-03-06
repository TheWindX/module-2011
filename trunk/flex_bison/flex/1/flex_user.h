
#pragma once

struct st_flex_use;

struct i_flex_use
{
	st_flex_use* m_impl;

	void reset_buffer(const char* buff, size_t sz);
	int lex();
	

	//当前行
	size_t get_cur_row();
	//当前列
	size_t get_cur_col();
	//当前位置
	size_t get_cur_pos();


	//////////////////////////////////////////////////////////////////////////
	//for flex use

	void new_token();//在flex里调用, 每一个token使用

	//token.text
	const char* get_text();
	//token.length
	size_t get_length();

	
	int copy_buffer(char* buff, int max_size);
	
	//////////////////////////////////////////////////////////////////////////
	i_flex_use();

	virtual ~i_flex_use();
};

extern i_flex_use g_flex_use;

