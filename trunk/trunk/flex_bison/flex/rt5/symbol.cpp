#include <cassert>

#include <string>
#include <iostream>
#include <sstream>

#include "easy_map.h"
#include "stack.h"

#include "symbol.h"

namespace ns_util
{
	bool st_path::is_branch()
	{
		return !m_is_leaf;
	}

	bool st_path::is_leaf()
	{
		return m_is_leaf;
	}

	const char* st_path::part_name()
	{
		if(m_name)
			return m_name;
		else
			return "";
	}

	const char* st_path::full_name()
	{	
		static std::string ret = "";
		
		array<char*> path;
		path.push(m_name);
		st_path* p = m_up;
		for(; p; p=p->upper() )
		{
			path.push(p->m_name);
		}
		if(path.top() == 0) path.pop();
		if(path.size() == 0) return "";
		ret = path.pop();
		for(; path.size() != 0; )
		{
			ret+=".";
			ret+=path.pop();
		}
		return ret.c_str();
	}

	st_path* st_path::upper()
	{
		return m_up;
	}

	st_path* st_path::first()
	{
		bool b = m_downs.first();
		if(!b) return 0;
		return m_downs.get();
	}

	st_path* st_path::next()
	{
		bool b = m_downs.next();
		if(!b) return 0;
		return m_downs.get();
	}

	bool st_path::find(const char* path, st_path*& ret)
	{	
		//分词
		std::stringstream stm_path(path);
		st_path* p_tmp = this;
		ret = p_tmp;
		std::string name = "";
		for(;p_tmp;)
		{
			getline(stm_path, name, '.');	
			if(stm_path.eof() )
			{
				p_tmp = p_tmp->find_part(name.c_str() );
				if(p_tmp) ret = p_tmp;
				else return false;
				break;
			}
			else
			{
				p_tmp = p_tmp->find_part(name.c_str() );
				if(p_tmp) ret = p_tmp;
				else return false;
			}

		}
		return true;
	}

	st_path* st_path::reg_branch(const char* path)
	{
		//分词
		std::stringstream stm_path(path);
		st_path* p_tmp = this;
		std::string name = "";
		for(;;)
		{
			getline(stm_path, name, '.');	
			if(stm_path.eof() )
			{
				p_tmp = p_tmp->reg_part_path(name.c_str() );
				break;
			}
			else
				p_tmp = p_tmp->reg_part_path(name.c_str() );

		}
		return p_tmp;
	}

	st_path* st_path::reg_leaf(const char* path)
	{
		//分词
		std::stringstream stm_path(path);
		st_path* p_tmp = this;
		std::string name = "";
		for(;;)
		{
			getline(stm_path, name, '.');	
			if(stm_path.eof() )
			{
				p_tmp = p_tmp->reg_part_name(name.c_str() );
				break;
			}
			else
				p_tmp = p_tmp->reg_part_path(name.c_str() );

		}
		return p_tmp;
	}

	st_path::st_path(st_path* up, const char* name, bool is_leaf)
	{
		m_name = strdup(name);
		m_is_leaf = is_leaf;
		m_up = up;
	}

	st_path::st_path()
	{
		m_name = 0;
		m_is_leaf = false;
		m_up = 0;
	}

	st_path::~st_path()
	{
		free(m_name);
		st_path* p = first();
		for(;p;p = next() )
		{
			delete p;
		}
	}

	st_path* st_path::reg_part_name(const char* name)
	{
		st_path* p = find_part(name);
		if(!p)
		{
			p = new st_path(this, name, true);
			m_downs.insert(p);
		}
		return p;
	}

	st_path* st_path::reg_part_path(const char* name)
	{
		st_path* p = find_part(name);
		if(!p)
		{
			p = new st_path(this, name, false);
			m_downs.insert(p);
		}
		return p;
	}

	st_path* st_path::find_part(const char* name)
	{
		st_path p(0, name);
		bool b = m_downs.find(&p);
		if(!b)return 0;
		return m_downs.get();
	}

	void st_path::set_id(u32 id)
	{
		m_id = id;
	}

	u32 st_path::get_id()
	{
		return m_id;
	}

	void st_path::print(const char* head)
	{
		st_path* p = first();
		for(;p;p = next() )
		{
			if(p->m_is_leaf)
			{
				std::cout<<head<<p->get_id()<<":"<<p->full_name()<<std::endl;
			}
			else
			{
				std::string next_head = head;
				next_head += "\t";
				p->print(next_head.c_str() );
			}
		}
	}

	st_path* st_global::get_root()
	{
		return &m_root;
	}

	void st_global::moudle_enter()
	{
		m_cur_path.push(&m_root);
		m_using_tags.push(m_usings.size() );
	}

	void st_global::moudle_exit()
	{
		m_cur_path.pop();
		m_using_tags.resize(m_using_tags.pop() );
	}

	void st_global::module_path(const char* path)
	{	
		if(path == 0) m_cur_path.top() = &m_root;
		if(0 == strcmp(path, "") )m_cur_path.top() = &m_root;
		else
		{
			st_path* p = m_root.reg_branch(path);
			m_cur_path.top() = p;
		}
	}

	st_path* st_global::export_symbol(const char* name)
	{
		st_path* p;
		if(m_cur_path.top()->find(name, p) )
		{
			return p;
		}
		p = m_cur_path.top()->reg_leaf(name);
		p->set_id(gen_id() );
		return p;
	}

	bool st_global::using_path(const char* path)
	{
		st_path* p;
		bool b = find_path(path, p);
		if(!b) return false;
		u32 idx = m_usings.find(p);
		if(idx == U32_NA)
		{
			m_usings.push(p);
		}
		return true;
	}

	bool st_global::find_path(const char* path, st_path*& ret_path)
	{
		//1.m_cur_path查找， 
		//2.在usings查找
		//3.在global查找
		for(u32 i = 0; i<m_cur_path.size(); ++i)
		{
			st_path* p = m_cur_path[i];
			bool b = p->find(path, ret_path);
			if(b) return true;
		}
		
		for(u32 i = 0; i<m_usings.size(); ++i)
		{
			st_path* p = m_usings[i];
			bool b = p->find(path, ret_path);
			if(b) return true;
		}

		return m_root.find(path, ret_path);
	}

	void st_global::print()
	{
		std::cout<<"(global):"<<std::endl;
		st_path* p = this->get_root();
		p->print("");
	}

	u32 st_global::gen_id()
	{
		return m_id_count++;
	}

	u32 st_global::get_current_id()
	{
		return m_id_count;
	}

	st_global::st_global():m_id_count(0)
	{
	}
	
	st_global::~st_global()
	{ 
	}

	st_var::st_var(st_path* p)//global
	{
		m_type = e_global;
		g.path = p;
	}

	st_var::st_var(st_scope* scope, const char* name)//local
	{
		m_type = e_local;
		l.scope = scope;
		l.name = strdup(name);
	}

	st_var::st_var(st_scope* scope, const char* name, st_var* ref)//ref
	{
		m_type = e_ref;
		r.scope = scope;
		r.ref = ref;
		r.name = strdup(name);
	}

	st_var::~st_var()
	{
		if(m_type == e_global) return;
		if(m_type == e_local) { free(l.name); return;}
		if(m_type == e_ref) {free(l.name); return; }
	}

	st_var* st_scope::find_name(const char* name)
	{
		//local find
		for(u32 i = 0; i<m_local_vars.size(); ++i)
		{
			st_var* ret = m_local_vars[i];
			if(strcmp(ret->l.name, name) == 0)
			{
				return ret;
			}
		}

		//ref find
		for(u32 i = 0; i<m_ref_vars.size(); ++i)
		{
			st_var* ret = m_ref_vars[i];
			if(strcmp(ret->l.name, name) == 0)
			{
				return ret;
			}
		}

		//global
		static st_map<st_path*, st_var*> g_vars;
		
		st_path* p;
		bool b = m_global->find_path(name, p);
		if(b)
		{
			bool bv = g_vars.find(p);
			if(bv)
			{
				return g_vars.get_val();
			}
			else
			{
				st_var* v = new st_var(p);
				g_vars.insert(p, v);
				return v;
			}
		}

		if(m_upper) return m_upper->find_name(name);
		return 0;
	}

	st_var* st_scope::reg_name(const char* name)
	{
		st_var* v = find_name(name);
		if(v)
		{
			st_scope* s;
			if(v->m_type == e_local) s = v->l.scope;
			else if(v->m_type == e_ref) s = v->r.scope;
			else return v;

			if(s == this) return v;
			else
			{
				return ref_var(v);
			}	
		}
		else
		{
			//new local
			st_var* var = new st_var(this, name);
			m_local_vars.push(var);
			
			return var;
		}
	}

	st_var* st_scope::reg_arg_name(const char* name)
	{
		st_var* v = find_name(name);
		if(v)
		{
			st_scope* s;
			if(v->m_type == e_local) s = v->l.scope;
			else if(v->m_type == e_ref) goto new_local;//TODO, warning?
			else goto new_local;//TODO, warning?

			if(s == this)
			{
				assert(false);//不能重复定义
			}
			else
			{
				goto new_local;//TODO, warning?
			}	
		}
		else
		{
new_local:	
			//new local
			st_var* var = new st_var(this, name);
			m_local_vars.push(var);

			return var;
		}
	}

	void st_scope::print(const char* head)
	{
		std::cout<<"visitor:"<<m_iter<<std::endl;
		std::cout<<head<<"(refs:)"<<std::endl;
		for(u32 i = 0; i<m_ref_vars.size(); ++i )
		{
			std::cout<<head<<m_ref_vars[i]->r.idx<<": "
				<<m_ref_vars[i]->r.name<<": ";
			st_var* ref = m_ref_vars[i]->r.ref;
			if(ref)
				std::cout<<ref->r.idx<<std::endl;
			else
				std::cout<<"null"<<std::endl;
		}

		std::cout<<head<<"(locals):"<<std::endl;
		for(u32 i = 0; i<m_local_vars.size(); ++i )
		{
			std::cout<<head<<m_local_vars[i]->l.idx<<": "
				<<m_local_vars[i]->l.name<<std::endl;
		}

		for(u32 i = 0; i<m_downs.size(); ++i)
		{
			std::string next_head = head;
			next_head += "\t";
			m_downs[i]->print(next_head.c_str() );
		}
	}

	st_var* st_scope::ref_var(st_var* v)
	{
		if(v->m_type == e_local)
		{
			u32 idx = v->l.scope->m_local_vars.find(v);
			v->l.scope->m_local_vars.erase(idx);
			v->l.scope->m_ref_vars.push(v);
			v->m_type = e_ref;
			char* tmp_name = v->l.name;
			st_scope* tmp_scope = v->l.scope;

			v->r.ref = 0;
			v->r.scope = tmp_scope;
			v->r.name = tmp_name;
		}

		array<st_scope*> stk;
		st_scope* tmp = this;
		for(; tmp != v->l.scope; tmp = tmp->m_upper)
		{
			stk.push(tmp);
		}

		//逐级生成ref
		st_var* tmp_var = v;
		
		do 
		{
			tmp = stk.pop();
			st_var* new_var = new st_var(tmp, v->l.name, tmp_var);
			tmp->m_ref_vars.push(new_var);
			tmp_var = new_var;
		} while(stk.size() != 0);

		return tmp_var;
	}

	st_scope* st_scope::enter()//返回新建立的local
	{
		if(m_downs.size() <= m_iter)
		{
			st_scope* s = new st_scope(this, m_global);
			m_downs.push(s);
			return s;
		}
		else return m_downs[m_iter];

		
	}

	st_scope* st_scope::exit()//返回上层local
	{
		//gen ids
		for(u32 i = 0; i<m_ref_vars.size(); ++i)
		{
			m_ref_vars[i]->r.idx = i;
		}

		for(u32 i = 0; i<m_local_vars.size(); ++i)
		{
			m_local_vars[i]->l.idx = i;
		}

		reset_visitor();
		if(m_upper) m_upper->m_iter++;
		return this->m_upper;
	}

	void st_scope::reset_visitor()
	{
		m_iter = 0;
	}

	st_scope::st_scope(st_scope* upper, st_global* g)
	{
		m_upper = upper;
		m_global = g;
		m_iter = 0;
	}

	void st_symbols::moudle_enter()
	{
		m_cur_scope->m_global->moudle_enter();
	}

	void st_symbols::moudle_exit()
	{
		m_cur_scope->m_global->moudle_exit();
	}

	void st_symbols::module_path(const char* path)
	{
		m_cur_scope->m_global->module_path(path);
	}

	void st_symbols::clean()
	{
		delete m_root_scope;
		m_root_scope = new st_scope(0, m_global);
		m_cur_scope = m_root_scope;
	}

	bool st_symbols::using_path(const char* path)
	{
		return m_cur_scope->m_global->using_path(path);
	}

	bool st_symbols::export_symbol(const char* name)
	{
		st_path* p = m_cur_scope->m_global->export_symbol(name);
		if(p) return true;
		return false;
	}

	st_var* st_symbols::reg_global_name(const char* name)
	{
		st_path* p;
		st_var* v = find_name(name);
		if(v)
		{
			if(v->m_type == e_global)
				return v;
		}
		else
		{
			p = m_global->get_root()->reg_leaf(name);
			p->set_id(m_global->gen_id() );
			return m_root_scope->find_name(name);
		}
	}

	st_var* st_symbols::reg_name(const char* name)
	{
		return m_cur_scope->reg_name(name);
	}

	st_var* st_symbols::reg_arg_name(const char* name)
	{
		return m_cur_scope->reg_arg_name(name);
	}

	st_var* st_symbols::find_name(const char* name)
	{
		return m_cur_scope->find_name(name);
	}

	void st_symbols::enter()
	{
		if(!m_cur_scope)
		{
			m_cur_scope = m_root_scope;
		}
		else
		{	
			m_cur_scope = m_cur_scope->enter();
		}
		m_root_scope->m_global->moudle_enter();
	}

	void st_symbols::exit()
	{
		m_cur_scope = m_cur_scope->exit();
	}

	void st_symbols::reset_visitor()//这个要enter/exit对完成后才有效，
	{
		m_root_scope->reset_visitor();
	}

	st_scope* st_symbols::get_cur_scope()
	{
		return m_cur_scope;
	}

	void st_symbols::print()
	{
		m_root_scope->m_global->print();
		m_root_scope->print("");
	}

	st_symbols::st_symbols()
	{
		m_global = new st_global;
		m_root_scope = new st_scope(0, m_global);
		m_cur_scope = m_root_scope;
	}

	st_symbols::~st_symbols()
	{
		delete m_root_scope;
	}
}