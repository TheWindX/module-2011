
#pragma once

#include <math.h>
#include <stdio.h>
#include "flex_header.h"


extern int yyparse (void);//解析主函数
extern void yyerror (char const *);//错误处理





#define YY_SYNTAX_ERROR std::cout<<"syntax error: in line :"<<g_flex_user.m_row<<"    column: "<<g_flex_user.m_col<<std::endl; YYABORT;

