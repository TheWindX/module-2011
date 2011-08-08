
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

	size_t get_left();
	size_t get_right();

	//////////////////////////////////////////////////////////////////////////
	//for flex use

	void new_token();//在flex里调用, 每一个token使用

	//token.text
	const char* get_text();
	//token.length
	size_t get_length();

	//当前行
	const char* get_current_line();
	//行到当前位置
	const char* get_current_line_segment();

	
	int copy_buffer(char* buff, int max_size);
	
	//////////////////////////////////////////////////////////////////////////
	i_flex_use();

	virtual ~i_flex_use();
};

extern i_flex_use g_flex_user;

