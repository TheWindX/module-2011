#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>
#include <map>
#include <stack>

//ֵ
/************************************************************************/
/* 
val: (tag, val)
ÿ��ֵ�ķ���,

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

//�����
//ʵ�� ��ֵջ������, ����������struct��enum��

//ָ��
/************************************************************************/
/* 
push_int(1234), int ֵ�ŵ���ֵջ

push(<string>), �ӻ�����ȡ���ŵ���ֵջ
set(<string>), ���û���


pop(<string>), ����ֵջ��������, 

apply(),
	1. push����ʱ
	2. ����ջ����������������ʱ, 
		2.0 push env�� ����һ��evn, ����Ϊ��ǰ��evn
		2.2. pc����Ϊ0��


//����һ��function
evn(<string>), �����»���, ������string��ǰ��ֵ;
func(), ����ǰ�潨����evn, ��codes����func_val

return
	1. pop����ʱ;
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
	
	//��ֵջ
	std::stack<st_value> _eval_stk;
	void push_val(st_value val);
	bool pop_val(st_value& val);


	//����ջ
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


