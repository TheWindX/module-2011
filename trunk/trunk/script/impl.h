#pragma once
#include "interface.h"
#include <sstream>
#include "../head/ref_counter.h"

#pragma comment(lib,"lua5.1.lib")
namespace ns_base
{
	struct impl_lua : public i_lua, public ns_common::impl_ref_counter
	{
		lua_State* m_state;
		~impl_lua()
		{
			lua_close(m_state);
		}

		lua_State* get_state();

		//����һ��function�ŵ�ջ��
		void load_string(const char* str);
		void load_file(const char* fname);
		void load_buffer(const char* name, i_buffer* buff);
		void do_script();


		int get_idx_count();

		void root_section();//�����
		bool enter_section(const char* key);
		bool enter_section_idx(int idx);
		bool leave_section();//����

		bool get_bool(const char* key, bool& out);
		bool get_bool_idx(int idx, bool& out);
		bool get_int(const char* key, int& out);
		bool get_int_idx(int idx, int& out);
		bool get_double(const char* key, double& out);
		bool get_double_idx(int idx, double& out);
		const char* get_string(const char* key);
		const char* get_string_idx(int idx);

		//ע�ắ��
		void reg_lib(lua_CFunction lib);
		void reg_func(const char* func_name, lua_CFunction func);
		void reg_funcs(luaL_reg funcs[]);

		//ִ�к���
		void push_in_para_bool(bool p);
		void push_in_para_int(int p);
		void push_in_para_double(double p);
		void push_in_para_string(const char* p);
		void push_out_para_bool(bool& p);
		void push_out_para_int(int& p);
		void push_out_para_double(double& p);
		void push_out_para_string(char* p);
		void call_function(const char *func);

		//ȫ�ֱ���
		void add_string_global(const char* key, const char* val);
		const char* get_string_global(const char* key);

		void add_number_global(const char* key, double val);
		double get_number_global(const char* key);

		void add_bool_global(const char* key, bool val);
		bool get_bool_global(const char* key);

		//������ı���
		void add_string_in_table(const char* table_name, const char* key, const char* val);
		const char* get_string_in_table(const char* table_name, const char* key);

		void add_number_in_table(const char* table_name, const char* key, double val);
		double get_number_in_table(const char* table_name, const char* key);

		void add_bool_in_table(const char* table_name, const char* key, bool val);
		bool get_bool_in_table(const char* table_name, const char* key);

		bool exists( const char* key);
		bool exists_in_table_str( const char* table_name, const char* key);
		bool exists_in_table_num( const char* table_name, const int index);

		const char* dump_stack();
	};


	struct impl_lua_project : public i_lua_project, public ns_common::impl_ref_counter
	{
		
		std::vector<i_pak*> m_paks;
		std::vector<std::string> m_includes;
		std::vector<std::string> m_libs;

		std::vector<i_pak*> m_pak_stk;
		std::vector<std::string> m_paths_stk;

		i_pak* current_pak()
		{
			if(m_pak_stk.size() == 0)
			{
				RAISE_EXCEPTION("");
			}
			return m_pak_stk.back();
		}

		std::string current_path()
		{
			if(m_paths_stk.size() == 0)
			{
				RAISE_EXCEPTION("");
			}
			return m_paths_stk.back();
		}

		void push(i_pak* pak, const std::string& path)
		{
			m_pak_stk.push_back(pak);
			m_paths_stk.push_back(path);
		}

		void pop()
		{
			m_pak_stk.pop_back();
			m_paths_stk.pop_back();
		}

		bool find_include(const char* path, i_pak*& pak_out, std::string& path_out);

		bool find_lib(const char* path, std::string& path_out);
		
		//����pak����Ŀ¼�б�, ��˳��
		void add_pak(i_pak* pak);
		//����lua����, ��˳��
		void add_include_path(const char* path);
		//����dll����, ��˳��
		void add_lib_path(const char* path);
		//lua entry
		i_lua* create_lua(const char* path);

		//ʹ�õ�����state�õ�lua_project����, ������ʽ, Ҫע��project������
		void reg_state(lua_State* st);

		impl_lua_project();
		~impl_lua_project();
	};


	struct impl_h_script : public h_script
	{
		i_lua* create_lua();
		i_lua* create_lua_from_file(const char* file);
		i_lua* create_lua_from_buffer(const char* name, i_buffer* buff);
		i_lua* create_lua_from_string(const char* name, const char* str);
		i_lua_project* create_lua_project();
	};
}