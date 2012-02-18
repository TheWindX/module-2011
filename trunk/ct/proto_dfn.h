push_local
pop_local
push_ref
pop_ref
push_global
pop_global
push_bool
push_int
push_string
push_function
function_ref
goto
goto_true
goto_false
apply_begin
apply
apply_instant
ret_begin
ret
inc
dec


	//for codes
	enum
	{
		proto_code_push_bool = 0,
		proto_code_push_int,
		proto_code_push_string,
		proto_code_push_function,
		proto_code_function_ref,
		proto_code_goto,
		proto_code_goto_true,
		proto_code_goto_false,
		proto_code_apply_begin,
		proto_code_apply,
		proto_code_apply_instant,
		proto_code_ret_begin,
		proto_code_ret,
		proto_code_inc,
		proto_code_dec,
	};
	
	
	
	enum
	{
		proto_code_push_local = 0,
		proto_code_pop_local,
		proto_code_push_ref,
		proto_code_pop_ref,
		proto_code_push_global,
		proto_code_pop_global,
		proto_code_push_bool,
		proto_code_push_int,
		proto_code_push_string,
		proto_code_push_function,
		proto_code_function_ref,
		proto_code_goto,
		proto_code_goto_true,
		proto_code_goto_false,
		proto_code_apply_begin,
		proto_code_apply,
		proto_code_apply_instant,
		proto_code_ret_begin,
		proto_code_ret,
		proto_code_inc,
		proto_code_dec,
		proto_code_num,//user define从这里开始
	};
	
	
	