#pragma once
#include "../head/ref_counter.h"
#include "../head/M_interface.h"

#include "../filesystem/interface.h"

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}


namespace ns_base
{
	struct i_lua : public virtual i_ref_counter
	{
		virtual lua_State* get_state() = 0;

		//生成一个function放到栈顶
		virtual void load_string(const char* str) = 0;
		virtual void load_file(const char* fname) = 0;
		virtual void load_buffer(const char* name, i_buffer* buff) = 0;
		virtual void do_script() = 0;

		//数据访问
		virtual int get_idx_count() = 0;

		virtual void root_section() = 0;//根结点
		virtual bool enter_section(const char* key) = 0;
		virtual bool enter_section_idx(int idx) = 0;
		virtual bool leave_section() = 0;//向上

		virtual bool get_bool(const char* key, bool& out) = 0;
		virtual bool get_bool_idx(int idx, bool& out) = 0;
		virtual bool get_int(const char* key, int& out) = 0;
		virtual bool get_int_idx(int idx, int& out) = 0;
		virtual bool get_double(const char* key, double& out) = 0;
		virtual bool get_double_idx(int idx, double& out) = 0;
		virtual const char* get_string(const char* key) = 0;
		virtual const char* get_string_idx(int idx) = 0;


		//注册函数
		virtual void reg_lib(lua_CFunction lib) = 0;
		virtual void reg_func(const char* func_name, lua_CFunction func) = 0;
		virtual void reg_funcs(luaL_reg funcs[]) = 0;

		//执行函数
		virtual void push_in_para_bool(bool p) = 0;
		virtual void push_in_para_int(int p) = 0;
		virtual void push_in_para_double(double p) = 0;
		virtual void push_in_para_string(const char* p) = 0;
		virtual void push_out_para_bool(bool& p) = 0;
		virtual void push_out_para_int(int& p) = 0;
		virtual void push_out_para_double(double& p) = 0;
		virtual void push_out_para_string(char* p) = 0;
		virtual void call_function(const char *func) = 0;
		
		

		//全局变量
		virtual void add_string_global(const char* key, const char* val) = 0;
		virtual const char* get_string_global(const char* key) = 0;

		virtual void add_number_global(const char* key, double val) = 0;
		virtual double get_number_global(const char* key) = 0;

		virtual void add_bool_global(const char* str_name, bool val) = 0;
		virtual bool get_bool_global(const char* str_name) = 0;

		//表里面的变量
		virtual void add_string_in_table(const char* table_name, const char* key, const char* val) = 0;
		virtual const char* get_string_in_table(const char* table_name, const char* key) = 0;

		virtual void add_number_in_table(const char* table_name, const char* key, double val) = 0;
		virtual double get_number_in_table(const char* table_name, const char* key) = 0;

		virtual void add_bool_in_table(const char* table_name, const char* key, bool val) = 0;
		virtual bool get_bool_in_table(const char* table_name, const char* key) = 0;

		virtual bool exists( const char* key) = 0;
		virtual bool exists_in_table_str( const char* table_name, const char* key) = 0;
		virtual bool exists_in_table_num( const char* table_name, const int index) = 0;

		virtual const char* dump_stack() = 0;
	};

	/************************************************************************/
	/* 
	lua_project定义工程的查找路径, 查找按照下面规则,
	当前pak, 起始为第一个pak
	当前路径, 起始为./
	查找顺序：
	先相对路径，
		当前pak查找, 当前路径+路径
	再绝对路径,
		每个include路径+路径, 
			每个pak查找
		每个pak查找绝对路径
	*/
	/************************************************************************/
	struct i_lua_project : public virtual i_ref_counter
	{
		//增加pak索引目录列表, 按顺序
		virtual void add_pak(i_pak* pak) = 0;
		//增加lua引用, 按顺序
		virtual void add_include_path(const char* path) = 0;
		//增加dll引用, 按顺序
		virtual void add_lib_path(const char* path) = 0;
		//lua entry
		virtual i_lua* create_lua(const char* path) = 0;
		
		//直接执行
		inline void run(const char* path)
		{
			i_lua* p_lua = create_lua(path);
			if(p_lua)
			{
				p_lua->do_script();
				p_lua->release();
			}
		}

		//使得第三方state得到lua_project功能, 非侵入式, 要注意project生命期
		virtual void reg_state(lua_State* st) = 0;
	};



	struct h_script
	{
		virtual i_lua* create_lua() = 0;
		virtual i_lua* create_lua_from_file(const char* file) = 0;
		virtual i_lua* create_lua_from_buffer(const char* name, i_buffer* buff) = 0;
		virtual i_lua* create_lua_from_string(const char* name, const char* str) = 0;

		virtual i_lua_project* create_lua_project() = 0;
	};
}

M_DECL(ns_base::h_script, "script.dll");
