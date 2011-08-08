%{
	#include "flex_use.h"

	//#define YY_USER_INIT yy_scan_string( st_flex_use::get_instance().get_buffer().c_str() );
%}

/*%option prefix="LC"*/
NUM	[1-90]+


%%
{NUM}		{yylval.ival = atoi(yytext);return NUM;}
[ \t]*	;
.			{return yytext[0];}
"\n"		{return yytext[0];}

%%
int yywrap(){return 1;}