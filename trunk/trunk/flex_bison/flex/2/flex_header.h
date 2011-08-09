

#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>

//flex global
extern int yylex(void);		//flex routin
extern FILE *yyin, *yyout;	//IO for yylex()
extern int yyleng;			//length of yytext
extern char* yytext;		//token text
extern void yyrestart(FILE*);

#include "flex_user.h"

//����ȡstr �� buffer
#undef YY_INPUT
#define  YY_INPUT(b, r, ms){r = g_flex_user.copy_buffer(b, ms);}

//ÿ��token action֮ǰ����
#define YY_USER_ACTION	g_flex_user.new_token();


//YYLTYPE ����
struct YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	int pos;
	int len;
};
#define  YYLTYPE YYLTYPE
extern YYLTYPE yylloc;

