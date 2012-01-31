
%{
#include "flex_header.h"
#include "test.tab.hpp"
%}

/* ���������#define */
DIGIT [0-9]
DIGIT_NZERO [1-9]
INTERGER {DIGIT_NZERO}+{DIGIT}*
FLOAT \.{DIGIT}+
BLANK [ \t\n\r]

ID	[a-zA-Z]



%%
-?{INTERGER}{FLOAT}?	{yylval.m_number = atof(yytext); return NUMBER;} /* ƥ������ */

{BLANK}+	{/*eat up*/;}

{ID}+({ID}|{DIGIT})*	{memcpy(yylval.m_id, yytext, yyleng); return ID; }

";"		{return yytext[0];}
"+"		{return yytext[0];}
"*"		{return yytext[0];}
"("		{return yytext[0];}
")"		{return yytext[0];}
","		{return yytext[0];}
"="		{return yytext[0];}
.	{printf("invalid: %d\n", yytext[0]);}
%%
int yywrap(){return 1;}