
#pragma once

struct st_flex_use;

struct i_flex_use
{
	st_flex_use* m_impl;

	void reset_buffer(const char* buff, size_t sz);
	int lex();
	

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
	
	//////////////////////////////////////////////////////////////////////////
	i_flex_use();

	virtual ~i_flex_use();
};

extern i_flex_use g_flex_user;

