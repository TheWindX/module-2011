%{
#include "flex_user.h"
#include "bison_header.h"
#include <string>

void set_color();
void set_normal();
%}

%union
{
	char m_id[1024];
	double m_number;
}

%token <m_number> NUMBER
%token <m_id> ID


%nonassoc '+'
%nonassoc '*'
%nonassoc E_PLUS_E
%nonassoc E_MULTI_E


%%

root : 
	statments	{system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;

statments :
	statment	{system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| statments ';' statment {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;
	
statment :
	| assignment {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| expr {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;

assignment :
	ID '=' expr {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;

expr :
	expr_multi {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| expr '+' expr %prec E_PLUS_E {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;
	
expr_multi :
	expr_apply {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| expr_inner {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| ID
	| NUMBER {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| expr '*' expr %prec E_MULTI_E {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;
	
expr_apply :
	func_name '(' para_list ')' {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	; 
	
expr_inner :
	'(' expr ')' {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;
	
func_name :
	ID
	;
	
para_list :
	| para {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	| para_list ',' para {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;
	
para :
	expr {system("cls");set_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_color();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_normal();system("pause");}
	;
%%
