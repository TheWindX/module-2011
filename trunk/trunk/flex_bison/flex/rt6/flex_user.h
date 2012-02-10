
#pragma once

struct st_flex_use;

typedef void (*handle_new_line_t)(size_t/* pos */);

struct i_flex_use
{
	st_flex_use* m_impl;

	void reset_buffer(const char* buff, size_t sz);
	int lex();
	

	//整个buffer
	const char* get_buffer_ptr();
	size_t get_buffer_size();

	void set_new_line_handler(handle_new_line_t h);

	//当前行
	size_t get_cur_row();
	//当前列
	size_t get_cur_col();
	//当前位置
	size_t get_cur_pos();
	//取字串段
	const char* get_segment(int pos1, int pos2);


	//////////////////////////////////////////////////////////////////////////
	//for flex use

	void new_token();//在flex里调用, 每一个token使用

	//token.text
	const char* get_text();
	//token.length
	size_t get_length();

	//当前行
	const char* get_line(int ln);
	
	
	int copy_buffer(char* buff, int max_size);
	

	//for the yylvalue string buffer need
	char* new_buffer(const char* buff, int buff_sz);
	void delete_all();

	//////////////////////////////////////////////////////////////////////////
	i_flex_use();

	virtual ~i_flex_use();
};

extern i_flex_use g_flex_user;
