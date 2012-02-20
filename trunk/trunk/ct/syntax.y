%{
#include "flex_user.h"
#include "bison_header.h"
#include <string>
#include "context.h"
%}

%union
{
	char* m_id;
	char* m_str;
	int m_number;
}

%token EQUAL YIELD RETURN FUNCTION MODULE EXPORT USING
%token IF ELSE TABLE_HEAD FOR SELF_ADD SELF_SUB GLOBAL TRUE FALSE BREAK CONTINUE
 /* key word here! */
%token XF

%token <m_id> ID
%token <m_number> NUMBER
%token <m_str> STRING

%nonassoc EMPTY_ELSE
%nonassoc ELSE

%nonassoc ELSE_PRE
%nonassoc IF

%nonassoc IF_PRE

%left '='
%left '<' '>' EQUAL
%left '+' '-' 
%left '*' '/' '%'
%nonassoc '('//apply½áºÏ

%nonassoc INDEX
%nonassoc '['

%%
root : 
	prepare sentences	{g_ast.p_exit(@2.pos, @2.pos+@2.len);}
	;

prepare :
	{g_ast.p_enter(); g_ast.p_null_path(); g_ast.p_null_stat();}
	;

sentences :
	sentence
	|sentences sentence
	;
	
sentence :
	statement {g_ast.p_stat();}
	| declare
	| ';'
	;

declare :
	module {g_ast.p_module();}
	| using {g_ast.p_using();}
	| export {g_ast.p_export();}
	;
	
statement :
	sep_statement ';'
	| no_sep_statement
	;
	
sep_statement :
	assignment
	| expr
	| return
	| yield
	| break
	| continue
	| expr index_list '=' expr {g_ast.p_insert(); }
	;
no_sep_statement :
	if_stat
	| for_stat
	| function_def
	;
	
index_list :
	'[' expr ']'
	/*|index_list '[' expr ']' */
	;


module :
	MODULE path
	;
	
using :
	USING path
	;
	
export :
	EXPORT symbol_list
	;
	
path :
	ID {g_ast.p_string($1);g_ast.p_new_path(); }
	|path '.' ID {g_ast.p_string($3);g_ast.p_path();}
	;

var_list : 
	expr_var {g_ast.p_new_var_list(); }
	|var_list ',' expr_var {g_ast.p_var_list(); }
	;
	

symbol_list :
	ID {g_ast.p_string($1); g_ast.p_new_path(); }
	|symbol_list ',' ID {g_ast.p_string($3);g_ast.p_path();}
	;
	
assignment :
	var_list '='{g_ast.p_null_para_list(); }
	 para_list {g_ast.p_assign(@1.pos, @1.pos+@$.len); }
	;

expr :
	SELF_ADD expr_var  {g_ast.p_self_op(true, true); };
	| SELF_SUB expr_var {g_ast.p_self_op(false, true); };
	| expr_var  SELF_ADD {g_ast.p_self_op(true, false); };
	| expr_var SELF_SUB {g_ast.p_self_op(false, false); };
	| '-' expr {g_ast.p_unitop("-");}
	| expr '+' expr   {g_ast.p_binop("+", @$.pos, @$.pos+@$.len);}
	| expr '-' expr   {g_ast.p_binop("-", @$.pos, @$.pos+@$.len);}
	| expr '*' expr   {g_ast.p_binop("*", @$.pos, @$.pos+@$.len);}
	| expr '/' expr   {g_ast.p_binop("/", @$.pos, @$.pos+@$.len);}
	| expr '%' expr   {g_ast.p_binop("%", @$.pos, @$.pos+@$.len);}
	| expr EQUAL expr  {g_ast.p_binop("==", @$.pos, @$.pos+@$.len);}
	| expr '<' expr {g_ast.p_binop("<", @$.pos, @$.pos+@$.len);}
	| expr '>' expr {g_ast.p_binop(">", @$.pos, @$.pos+@$.len);}
	| '(' expr ')'
	| expr_apply
	| expr_function
	| expr_var 
	| TRUE {g_ast.p_bool(true);}
	| FALSE {g_ast.p_bool(false);}
	| NUMBER {g_ast.p_number($1, @1.pos, @1.pos+@1.len); }
	| STRING {g_ast.p_quot_string($1);}
	| array_expr
	| table_expr
	| expr '[' expr ']' %prec INDEX{g_ast.p_index(); };
	;
	
expr_var :
	path {g_ast.p_var(false); }
	| GLOBAL path {g_ast.p_var(true); }
	;
	
expr_apply :
	expr '('{g_ast.p_null_para_list(); }
	 para_list ')' { g_ast.p_apply(@$.pos, @$.pos+@$.len); }
	| expr'(' ')' {g_ast.p_null_para_list(); g_ast.p_apply(@$.pos, @$.pos+@$.len);}
	;
	
para_list :
	expr {g_ast.p_para_list();}
	| para_list ',' expr {g_ast.p_para_list();}
	;


expr_function :
	FUNCTION 
	{g_ast.p_enter(); g_ast.p_null_path(); }
	'(' arg_list ')' {g_ast.p_null_stat(); }
	'{' stats_in_function '}' {g_ast.p_exit(@$.pos, @$.pos+@$.len); }
	;
	
function_def :
	FUNCTION expr_var 
	{g_ast.p_new_var_list(); g_ast.p_null_para_list(); g_ast.p_enter(); g_ast.p_null_path(); }
	'(' arg_list ')' {g_ast.p_null_stat(); }
	'{' stats_in_function '}' {g_ast.p_exit(@$.pos, @$.pos+@$.len); g_ast.p_para_list(); g_ast.p_assign(@$.pos, @$.pos+@$.len); }
	;

stats_in_function :
	/* empty */ 
	|sentences 
	;
	
arg_list :
	/* empty */ 
	| ID {g_ast.p_string($1);g_ast.p_path();}
	| arg_list ',' ID {g_ast.p_string($3);g_ast.p_path();}
	;

break :
	BREAK {g_ast.p_break();}
	;

continue :
	CONTINUE {g_ast.p_continue();}
	;
return :
	RETURN{g_ast.p_null_para_list(); g_ast.p_return(); }
	| RETURN {g_ast.p_null_para_list(); } para_list {g_ast.p_return();}
	;

yield :
	YIELD{g_ast.p_null_para_list(); g_ast.p_return(true); }
	| YIELD {g_ast.p_null_para_list(); } para_list {g_ast.p_return(true); }
	;
	
statements :
	statement	{g_ast.p_stat();}
	| statements statement {g_ast.p_stat();}
	;
		
if_stat :
	if_list else 
	;

if_list :
	IF if_pre 
	if {g_ast.p_if_comlete(@$.pos, @$.pos+@$.len);}
	| if_list ELSE IF if {g_ast.p_if_comlete(@$.pos, @$.pos+@$.len);}
	;

if_pre:
	{g_ast.p_if();  } %prec IF_PRE
	;
	
if :
	'(' expr ')' {g_ast.p_null_stat(); }
	'{' statements '}' {g_ast.p_then(); }
	| '(' expr ')' {g_ast.p_null_stat(); }
	statement {g_ast.p_stat(); g_ast.p_then(); }
	;
	
else :
	%prec EMPTY_ELSE
	| ELSE else_pre
	'{' statements '}' {g_ast.p_else(); }
	| ELSE else_pre
	statement {g_ast.p_stat(); g_ast.p_else(); }
	;

else_pre :
	{g_ast.p_null_stat(); } %prec ELSE_PRE
	;

array_expr :
	'[' ']' {g_ast.p_null_array(); g_ast.p_null_para_list(); g_ast.p_array();}
	| '[' {g_ast.p_null_array(); g_ast.p_null_para_list(); }
	para_list ']' {g_ast.p_array(); }
	;
	
table_expr :
	TABLE_HEAD {g_ast.p_null_map(); }
	table_pair_list '}'
	;
	
table_pair_list :
	| expr ':' expr {g_ast.p_map(); }
	| table_pair_list ',' expr ':' expr {g_ast.p_map(); }
	| ID {g_ast.p_quot_string($1); }
	'=' expr {g_ast.p_map(); }
	;

for_stat :
	FOR {g_ast.p_null_for(); }
	'(' stats_option ';' expr {g_ast.p_for_condition(); } ';' stats_option1 ')' '{' {g_ast.p_null_stat(); }
	stats_in_for '}' {g_ast.p_for_stats(@$.pos, @$.pos+@$.len); }
	;
stats_in_for :
	| statements
	;

stats_option :
	| {g_ast.p_null_stat(); } stats_list {g_ast.p_for_start(); }
	;
	
stats_option1 :
	| {g_ast.p_null_stat(); } stats_list {g_ast.p_for_every(); }
	;
	
stats_list :
	stat_in_for {g_ast.p_stat(); }
	| stats_list '#' stat_in_for {g_ast.p_stat(); }
	;
	
stat_in_for :
	sep_statement
	| no_sep_statement
	;
%%
