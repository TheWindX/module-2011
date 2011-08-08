
%{
#include "flex_header.h"
%}

/* 这里就像是#define */
DIGIT [0-9]
DIGIT_NZERO [1-9]
INTERGER {DIGIT_NZERO}+{DIGIT}*
FLOAT \.{DIGIT}+

BLANK [ \t\n\r]

%%
-?{INTERGER}{FLOAT}?	{return 1;} /* 匹配数字 */

BLANK+	{return 1;}

.	return 0;
%%
int yywrap(){return 1;}