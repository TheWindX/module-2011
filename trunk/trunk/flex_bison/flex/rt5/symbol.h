
#pragma once

#include "types.h"
#include "misc.h"
#include "easy_set.h"

#include "stack.h"

namespace ns_util
{
	struct st_path
	{
		bool is_branch();
		bool is_leaf();
		const char* part_name();
		const char* full_name();
		
		st_path* upper();
		st_path* first();
		st_path* next();
		
		bool find(const char* name, st_path*& ret_path);
		st_path* reg_branch(const char* name);
		st_path* reg_leaf(const char* name);

		st_path* reg_part_name(const char*);
		st_path* reg_part_path(const char*);
		st_path* find_part(const char* name);

		void set_id(u32 id);
		u32 get_id();

		void print(const char* head);//for debug

		st_path(st_path* up, const char* name, bool is_leaf = true);
		st_path();
		~st_path();
	private:
		bool m_is_leaf;
		char* m_name;
		u32 m_id;

		struct st_cmp{	bool operator() (st_path *s1, st_path *s2) 
			const{return strcmp(s1->m_name, s2->m_name) < 0;}};

		st_path* m_up;
		st_set<st_path*, st_cmp> m_downs;
	};

	struct st_global
	{
		st_path* get_root();

		void moudle_enter();
		void moudle_exit();
		void module_path(const char* path);
		st_path* export_symbol(const char* name);
		bool using_path(const char* path);

		bool find_path(const char* path, st_path*& ret_path);
	
		void print();
		st_global();
		~st_global();

		u32 gen_id();
	private:
		st_path m_root;
		array<st_path*> m_cur_path;
		array<st_path*> m_usings;
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
	struct st_var
	{
		u32 m_type;
		union
		{
			struct
			{
				st_path* path;
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
				st_var* ref;
			}r;
		};

		st_var(st_path*);//global
		st_var(st_scope* scope, const char* name);//local
		st_var(st_scope* scope, const char* name, st_var* ref);//ref

		~st_var();
	};

	//local
	struct st_scope
	{
		st_scope* m_upper;
		array<st_scope*> m_downs;

		st_global* m_global;
		array<st_var*> m_local_vars;
		array<st_var*> m_ref_vars;
		

		st_var* find_name(const char* name);
		st_var* reg_name(const char* name);
		st_var* reg_arg_name(const char* name);

		u32 m_iter;
		st_scope* enter();//返回新建立的local
		st_scope* exit();//返回上层local
		void reset_visitor();

		st_scope(st_scope* upper, st_global* g);

		void print(const char* head);
	private:
		st_var* ref_var(st_var* var);
	};

	struct st_symbols
	{	
		st_global* m_global;
		st_scope* m_root_scope;
		st_scope* m_cur_scope;
		
		void moudle_enter();
		void moudle_exit();
		void module_path(const char*);

		//这个在每次编译时，清除模块符号表，只保留全局符号表，重置
		//TODO, 保留符号表，给每一个编译映射一个符号表(module_name, scope), 无设定名, 就用系统生成名字
		void clean();
		
		bool using_path(const char*);
		bool export_symbol(const char*);
		

		st_var* reg_global_name(const char*);
		st_var* reg_name(const char*);
		st_var* reg_arg_name(const char*);
		st_var* find_name(const char* name);

		void enter();
		void exit();
		void reset_visitor();//每次访问完,需要重置状态
		st_scope* get_cur_scope();
		
		void print();
		
		st_symbols();
		~st_symbols();
	};
}
