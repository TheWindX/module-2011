
#pragma once

#include "utilies.h"

namespace ns_core
{
	using namespace ns_base;
	struct st_sym_path//��ʾһ��·���еĽ��
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
		st_scope* enter();//�����½�����local
		st_scope* exit();//�����ϲ�local
		void reset_visitor();

		st_scope(st_scope* upper, st_global* g);

		void print(const char* head);
	private:
		st_sym_var* ref_var(st_sym_var* var);
	};

	struct st_symbols
	{	
		st_global* m_global;
		st_scope* m_root_scope;
		st_scope* m_cur_scope;
		
		void moudle_enter();
		void moudle_exit();
		void module_path(const char*);

		//�����ÿ�α���ʱ�����ģ����ű���ֻ����ȫ�ַ��ű�������
		//TODO, �������ű�����ÿһ������ӳ��һ�����ű�(module_name, scope), ���趨��, ����ϵͳ��������
		void clean();
		
		bool using_path(const char*);
		bool export_symbol(const char*);
		

		st_sym_var* reg_global_name(const char*);
		st_sym_var* reg_name(const char*);
		st_sym_var* reg_arg_name(const char*);
		st_sym_var* find_name(const char* name);

		void enter();
		void exit();
		void reset_visitor();//ÿ�η�����,��Ҫ����״̬
		st_scope* get_cur_scope();
		
		void print();
		
		st_symbols();
		~st_symbols();
	};
}