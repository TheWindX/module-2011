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
	statment |
	statments ';' statment
	;
	
statment :
	|
	assignment |
	expr
	;

assignment :
	ID '=' expr
	;

expr :
	expr_multi |
	expr '+' expr %prec E_PLUS_E
	;
	
expr_multi :
	expr_apply |
	expr_inner |
	ID |
	NUMBER |
	expr '*' expr %prec E_MULTI_E
	;
	
expr_apply :
	func_name '(' para_list ')'
	;
	
expr_inner :
	'(' expr ')'
	;
	
func_name :
	ID
	;
	
para_list :
	|
	para |
	para_list ',' para
	;
	
para :
	expr
	;
%%
