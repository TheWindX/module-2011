
#pragma once

struct st_bison_use;

extern void yyerror (char const *);//´íÎó´¦Àí

struct i_bison_use
{
	st_bison_use* m_impl;

	void reset_buffer(const char* buff, size_t sz);
	void parse();

	
	//////////////////////////////////////////////////////////////////////////
	i_bison_use();

	virtual ~i_bison_use();
};

extern i_bison_use g_bison_use;

