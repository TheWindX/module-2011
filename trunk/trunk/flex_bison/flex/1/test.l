
%{
#include "flex_header.h"
%}

DIGIT [0-9]+
ALPHA [a-zA-z]+


%%
{DIGIT}	{return 1;}
{ALPHA} {return 1;}


.	{return 1;}
%%
int yywrap(){return 1;}