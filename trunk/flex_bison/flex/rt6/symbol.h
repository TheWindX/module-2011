
#pragma once

#include "utilies.h"

namespace ns_core
{
	using namespace ns_base;
	struct st_sym_path//表示一个路径中的结点
	{
		bool is_branch();
		bool is_leaf();
		const char* part_name();
		const char* full_name();
		
		st_sym_path* upper();
		st_sym_path* first();
		st_sym_path* next();
		
		bool find(const char* name, st_sym_path*& ret_path);
		st_sym_path* reg_branch(const char* name);
		st_sym_path* reg_leaf(const char* name);

		st_sym_path* reg_part_name(const char*);
		st_sym_path* reg_part_path(const char*);
		st_sym_path* find_part(const char* name);

		void set_id(u32 id);
		u32 get_id();

		void print(const char* head);//for debug

		st_sym_path(st_sym_path* up, const char* name, bool is_leaf = true);
		st_sym_path();
		~st_sym_path();
	private:
		bool m_is_leaf;
		char* m_name;
		u32 m_id;

		struct st_cmp{	bool operator() (st_sym_path *s1, st_sym_path *s2) 
			const{return strcmp(s1->m_name, s2->m_name) < 0;}};

		st_sym_path* m_up;
		st_set<st_sym_path*, st_cmp> m_downs;
	};

	struct st_global
	{
		st_sym_path* get_root();

		void moudle_enter();
		void moudle_exit();
		void module_path(const char* path);
		st_sym_path* export_symbol(const char* name);
		bool using_path(const char* path);

		bool find_path(const char* path, st_sym_path*& ret_path);
	
		void print();
		st_global();
		~st_global();

		u32 gen_id();
	private:
		st_sym_path m_root;
		array<st_sym_path*> m_cur_path;
		array<st_sym_path*> m_usings;
		array<u32> m_using_tags;

		u32 m_id_count;
		
		u32 get_current_id();
	};

	struct st_scope;
	enum
	{
		e_global = 0,
		e_local,
		e_ref,
	};
	struct st_sym_var
	{
		u32 m_type;
		union
		{
			struct
			{
				st_sym_path* path;
			}g;

			struct
			{
				char* name;
				st_scope* scope;
				u32 idx;
			}l;

			struct
			{
				char* name;
				st_scope* scope;
				u32 idx;
				st_sym_var* ref;
			}r;
		};

		st_sym_var(st_sym_path*);//global
		st_sym_var(st_scope* scope, const char* name);//local
		st_sym_var(st_scope* scope, const char* name, st_sym_var* ref);//ref

		~st_sym_var();
	};

	//local
	struct st_scope
	{
		st_scope* m_upper;
		array<st_scope*> m_downs;

		st_global* m_global;
		array<st_sym_var*> m_local_vars;
		array<st_sym_var*> m_ref_vars;
		

		st_sym_var* find_name(const char* name);
		st_sym_var* reg_name(const char* name);
		st_sym_var* reg_arg_name(const char* name);

		u32 m_iter;
		st_scope* enter();//返回新建立的local
		st_scope* exit();//返回上层local
		void reset_visitor();

		st_scope(st_scope* upper, st_global* g);

		void print(const char* head);
	private:
		st_sym_var* ref_var(st_sym_var* var);
	};

	struct st_symbols
	{	
		st_global* m_global;//全局符号表
		st_scope* m_root_scope;//根符号表
		st_scope* m_cur_scope;//当前环境符号表
		
		void moudle_enter();
		void moudle_exit();
		void module_path(const char*);

		//这个在每次编译时，清除模块符号表，只保留全局符号表，重置
		//TODO, 保留符号表，给每一个编译映射一个符号表(module_name, scope), 无设定名, 就用系统生成名字
		void clean();
		
		bool using_path(const char*);//加入了查找路径
		bool export_symbol(const char*);//定义全局符号名
		
		st_sym_var* reg_global_name(const char*);//注册全局符号名
		st_sym_var* reg_name(const char*);//这里不可注册 x.y
		st_sym_var* reg_arg_name(const char*);//这里不可注册 x.y
		st_sym_var* find_name(const char* name);//在当前环境下, 查找包括 x.y这样的名字, 

		void enter();
		void exit();
		void reset_visitor();//每次访问完,需要重置状态
		st_scope* get_cur_scope();
		
		void print();
		
		st_symbols();
		~st_symbols();
	};
}
