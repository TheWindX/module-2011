%{
#include "flex_user.h"
#include "bison_header.h"
#include <string>
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
	statments	
	;

statments :
	statment	
	| statments ';' statment 
	;
	
statment :
	| assignment 
	| expr 
	;

assignment :
	ID '=' expr {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;

expr :
	expr_multi 
	| expr '+' expr %prec E_PLUS_E {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;
	
expr_multi :
	expr_apply 
	| expr_inner 
	| ID {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	| NUMBER {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	| expr '*' expr %prec E_MULTI_E {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;
	
expr_apply :
	func_name '(' para_list ')' {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	; 
	
expr_inner :
	'(' expr ')' {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;
	
func_name :
	ID {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;
	
para_list :
	| para 
	| para_list ',' para {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;
	
para :
	expr {system("cls");set_text_normal();printf("%s",g_flex_user.get_segment(0, @$.pos) );set_text_red();printf("%s\n\n",g_flex_user.get_segment(@$.pos, @$.len) );set_text_normal();system("pause");}
	;
%%
