
%{
#include "flex_header.h"
%}

/* ���������#define */
DIGIT [0-9]
DIGIT_NZERO [1-9]
INTERGER {DIGIT_NZERO}+{DIGIT}*
FLOAT \.{DIGIT}+

%%
-?{INTERGER}{FLOAT}?	{std::cout<<"match! "<<atof(yytext)+2000.0<<std::endl; return 1;} /* ƥ������ */

. /* eat up */
%%
int yywrap(){return 1;}