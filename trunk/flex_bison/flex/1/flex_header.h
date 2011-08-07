

#pragma once

#include <cstdio>
#include <cstdlib>

//flex global
extern int yylex(void);		//flex routin
extern FILE *yyin, *yyout;	//IO for yylex()
extern int yyleng;			//length of yytext
extern char* yytext;		//token text
extern void yyrestart(FILE*);

#include "flex_user.h"

//这个flex用来取buff
#undef YY_INPUT
#define  YY_INPUT(b, r, ms){r = g_flex_use.copy_buffer(b, ms);}

//每个token action之前调用
#define YY_USER_ACTION	g_flex_use.new_token();



