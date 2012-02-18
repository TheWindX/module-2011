
%{
#include "flex_header.h"
#include "syntax.tab.hpp"
%}


%x comment
%x comment_line


/* 这里就像是#define */
DIGIT [0-9]
DIGIT_NZERO [1-9]
INTERGER ({DIGIT_NZERO}+{DIGIT}*)?{DIGIT}
FLOAT \.{DIGIT}+
BLANK [ \t\n\r]

ID	[a-zA-Z_]

%{
	/* 注释 */
	static int comment_count = 0;
	static void comment_left()
	{
		comment_count++;
	}
	static void comment_right()
	{
		comment_count--;
		if(comment_count == 0)
		{
			BEGIN(INITIAL);
		}
	}
%}

%%
"//"		{ BEGIN(comment_line); }
"/*"		{ BEGIN(comment); comment_left(); }
<comment_line>.		{/* eat up putchar(yytext[0]);*/}
<comment_line>\n	{ BEGIN(INITIAL); }
<comment>"/*"		{ comment_left(); }
<comment>"*/"		{ comment_right();}
<comment>.		{/* eat up */}
<comment>{BLANK}+		{/* eat up */}
"*/"		{yyerror("语法错误: 是否忘记了/*");}


"module"	{return MODULE;}
"export"	{return EXPORT;}
"using"		{return USING;}

"return"	{return RETURN;}
"yield"		{return YIELD;}
"function"	{return FUNCTION;}

"if"		{return IF;}
"else"		{return ELSE;}

"for"		{return FOR;}
"global"	{return GLOBAL;}

"true"		{return TRUE;}
"false"		{return FALSE;}

"break"		{return BREAK;}
"continue"		{return CONTINUE;}

{BLANK}+	{/*eat up*/;}

{ID}+({ID}|{DIGIT})*	{yylval.m_id = g_flex_user.new_buffer(yytext, yyleng); yylval.m_id[yyleng] = '\0';return ID; }


\"(\\.|[^\\"])*\"		{
		std::string s = yytext; 
		s = s.substr(1, s.size()-2); 
		yylval.m_str = g_flex_user.new_buffer(s.c_str(), s.size() );
		return STRING;
		}

{INTERGER}{FLOAT}?	{
yylval.m_number = atof(yytext); 
return NUMBER;
} /* 匹配数字 */

";"		{return yytext[0];}
"+"		{return yytext[0];}
"-"		{return yytext[0];}
"*"		{return yytext[0];}
"/"		{return yytext[0];}
"("		{return yytext[0];}
")"		{return yytext[0];}
"{"		{return yytext[0];}
"}"		{return yytext[0];}
","		{return yytext[0];}
"."		{return yytext[0];}
"="		{return yytext[0];}
"<"		{return yytext[0];}
">"		{return yytext[0];}
"%"		{return yytext[0];}
"["		{return yytext[0];}
"]"		{return yytext[0];}
":"		{return yytext[0];}
"#"		{return yytext[0];}
"m{"	{return TABLE_HEAD;}
"=="	{return EQUAL;}
"++"	{return SELF_ADD;}
"--"	{return SELF_SUB;}

.	{
	char str_tmp[256];
	sprintf(str_tmp, "invalid: %d\n", yytext[0]);
	yyerror(str_tmp);
}

%%
int yywrap(){return 1;}


