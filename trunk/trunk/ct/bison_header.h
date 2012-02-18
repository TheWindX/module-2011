
#pragma once

#include <math.h>
#include <stdio.h>
#include "flex_header.h"


extern int yyparse (void);//解析主函数
extern void yyerror (char const *);//错误处理

#define YY_SYNTAX_ERROR std::cout<<"syntax error: in line :"<<g_flex_user.m_row<<"    column: "<<g_flex_user.m_col<<std::endl; YYABORT;

# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
	do                                                                  \
	if (N)                                                            \
{                                                               \
	(Current).first_line   = YYRHSLOC(Rhs, 1).first_line;         \
	(Current).first_column = YYRHSLOC(Rhs, 1).first_column;       \
	(Current).last_line    = YYRHSLOC(Rhs, N).last_line;          \
	(Current).last_column  = YYRHSLOC(Rhs, N).last_column;        \
	(Current).pos   = YYRHSLOC (Rhs, 1).pos;\
	(Current).len   = YYRHSLOC(Rhs, N).pos - YYRHSLOC(Rhs, 1).pos + YYRHSLOC(Rhs, N).len;\
}                                                               \
		   else                                                              \
{                                                               \
	(Current).first_line   = (Current).last_line   =              \
	YYRHSLOC(Rhs, 0).last_line;                                 \
	(Current).first_column = (Current).last_column =              \
	YYRHSLOC(Rhs, 0).last_column;                               \
	(Current).pos   = YYRHSLOC (Rhs, 0).pos;\
	(Current).len = YYRHSLOC (Rhs, 0).len;\
}                                                               \
	while (0)



//debug
void set_text_red();
void set_text_normal();
//用于reduce测试
//{system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}