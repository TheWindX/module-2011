
#pragma once

struct st_flex_use;

typedef void (*handle_new_line_t)(size_t/* pos */);

struct i_flex_use
{
	st_flex_use* m_impl;

	void reset_buffer(const char* buff, size_t sz);
	int lex();
	

	//����buffer
	const char* get_buffer_ptr();
	size_t get_buffer_size();

	void set_new_line_handler(handle_new_line_t h);

	//��ǰ��
	size_t get_cur_row();
	//��ǰ��
	size_t get_cur_col();
	//��ǰλ��
	size_t get_cur_pos();
	//ȡ�ִ���
	const char* get_segment(int pos1, int pos2);


	//////////////////////////////////////////////////////////////////////////
	//for flex use

	void new_token();//��flex�����, ÿһ��tokenʹ��

	//token.text
	const char* get_text();
	//token.length
	size_t get_length();

	//��ǰ��
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
