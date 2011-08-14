#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>
#include <map>
#include <stack>

//值
/************************************************************************/
/* 
val: (tag, val)
每个值的方法,

enum
{
	e_nil,//()
	e_int,//(int)
	e_string,//(c_str)
	e_enum,//(array<(string, val) >)
	e_struct,//(array<(string, val) >)
	e_evn,//(map<string, val) )
	e_func,//(evn,codes)
	e_codes,//(array<code>)
	e_c_push_int,//(int),
	e_c_push,//(string),
	e_c_set,//(string),
	e_c_pop,//(string),
	e_c_apply,//()
	c_c_evn,//()
};

*/
/************************************************************************/

//虚拟机
//实现 求值栈，环境, 基本函数，struct，enum，

//指令
/************************************************************************/
/* 
push_int(1234), int 值放到求值栈

push(<string>), 从环境中取出放到求值栈
set(<string>), 设置环境


pop(<string>), 从求值栈弹出环境, 

apply(),
	1. push运行时
	2. 根据栈顶函数，设置运行时, 
		2.0 push env， 复制一份evn, 设置为当前的evn
		2.2. pc设置为0，


//建立一个function
evn(<string>), 建立新环境, 并设置string当前的值;
func(), 根据前面建立的evn, 和codes建立func_val

return
	1. pop运行时;
	2. pop env;



*/
/************************************************************************/






/************************************************************************/
/* code sample

a = 1234
b = 4567
d = add(a,b)
print(d)



push_int(1234);
set("a")
push_int(4567);
set("4567")
push("a")
push("b")
push("add")
apply();
push("d")
push("print")
apply()
*/
/************************************************************************/


enum
{
	e_nil = 0,//()
	e_int,//(int)
	e_string,//(c_str)
	e_enum,//(array<(string, val) >)
	e_struct,//(array<(string, val) >)
	e_evn,//(map<string, val) )
	e_func,//(evn,codes)
	e_codes,//(array<code>)
	e_c_push_int,//(int),
	e_c_push,//(string),
	e_c_set,//(string),
	e_c_pop,//(string),
	e_c_apply,//()
	c_c_evn,//()
};


struct st_value
{
	int _tag;
	void* _val;
};




struct st_value
{
	int _tag;
	void* _val;
};

struct st_run_time
{
	typedef st_value (* v_copy_t)(st_value);
	typedef bool (* v_eq_t)(st_value, st_value);
	typedef void (* v_del_t)(st_value);
	

	int reg_value(const std::string& name, v_copy_t f_cp, v_eq_t f_eq, v_del_t f_del);
	int get_value_id_by_name(const std::string& name);
	v_copy_t get_value_copy(int id);
	v_eq_t get_value_eq(int id);
	v_del_t get_value_del(int id);

	typedef void (* action_t)(st_run_time* run_time);
	int reg_code(const std::string& code_name, int num_arg, int num_ret, action_t act);
	
	//求值栈
	std::stack<st_value> _eval_stk;
	void push_val(st_value val);
	bool pop_val(st_value& val);


	//环境栈
	std::stack<st_value> _env_stk;
	void push_env(st_value val);
	bool pop_env(st_value& val);

	//codes
	std::map<std::string, st_value> _codes;
	void begin_code();
	void add_code(st_value code);
	void end_code(const std::string& name);
	
	void compile(const std::string& code_name, const std::string& str_code);
	void set_code(const std::string& code_name);
	void run();

	//pc
	int _pc;
	st_run_time()
		:_pc(0)
	{	
	}

};



int main(int argc, char** argv)
{
	return 0;
}


