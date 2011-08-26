
#include <string>
#include <vector>

#include "path.h"


namespace ns_path
{
		st_path* st_path_service::reg_path(st_path* up, std::string name)
		{
			st_node* nd = get_node_in_path(up, name);
			if(nd)
			{
				if(nd->m_type == e_path)
				{
					return nd;
				}
				else
				{
					m_last_error = e_is_not_path;
					return 0;
				}
			}
			
			st_node* nnd = new st_node;
			nnd->m_type = e_path;
			m_id_count++;
			nnd->m_id = m_id_count;
			nnd->m_name = name;
			nnd->m_up = up;
			nnd->m_low = 0;
			nnd->m_left = 0;
			nnd->m_right = up->m_low;
			if(nnd->m_right)
			{
				nnd->m_right->m_left = nnd;
			}
			up->m_low = nnd;
			return nnd;
		}

		st_entity* st_path_service::reg_entity(st_path* up, std::string name)
		{
			st_node* nd = get_node_in_path(up, name);
			if(nd)
			{
				if(nd->m_type == e_entity)
				{
					return nd;
				}
				else
				{
					m_last_error = e_is_not_entity;
					return 0;
				}
			}

			st_node* nnd = new st_node;
			m_id_count++;
			nnd->m_type = e_entity;
			nnd->m_id = m_id_count;
			nnd->m_name = name;
			nnd->m_up = up;
			nnd->m_low = 0;
			nnd->m_left = 0;
			nnd->m_right = nd->m_low;
			if(nnd->m_right)
			{
				nnd->m_right->m_left = nnd;
			}
			return nnd;
		}


		std::string st_path_service::get_node_string(st_node* path)
		{
			std::string ret;
			std::vector<std::string> name_stk;
			st_node* nd = path;
			while(nd != m_root)
			{
				name_stk.push_back(nd->m_name);
				nd = nd->m_up;
			}
			if(name_stk.size() != 0)
			{
				ret += name_stk.back();
				name_stk.pop_back();
			}
			while(name_stk.size() != 0)
			{
				ret += ".";
				ret += name_stk.back();
				name_stk.pop_back();
			}
			return ret;
		}

		bool st_path_service::add_path(st_path* path)
		{
			for(size_t i = 0; i<m_search_path.size(); ++i)
			{
				if(m_search_path[i] == path)
				{
					m_last_error = e_add_yet;
					return false;
				}
			}

			m_search_path.push_back(path);
			return true;
		}

		void st_path_service::reset_path()
		{
			m_search_path.clear();
		}

		st_node* st_path_service::get_node_in_path(st_path* path, const std::string& name)
		{
			st_node* nd = path->m_low;
			while(nd)
			{
				if(nd->m_name == name)
				{
					return nd;
				}
				nd = nd->m_right;
			}
			return 0;
		}

		st_path* st_path_service::get_path(const std::string& pname)
		{
			st_path* ret = 0;

			for(size_t i = 0; i<m_search_path.size(); ++i)
			{
				st_node* nd = get_node_in_path(m_search_path[i], pname);
				if(nd)
				{
					if(ret)
					{
						m_last_error = e_no_only_path_or_entity;
						return 0;
					}
					if(nd->m_type != e_path)
					{
						m_last_error = e_is_not_path;
						return 0;
					}
					else
						ret = nd;
				}
				
			}
			return ret;
		}

		st_entity* st_path_service::get_entity(const std::string& pname)
		{
			st_path* ret = 0;

			for(size_t i = 0; i<m_search_path.size(); ++i)
			{
				st_node* nd = get_node_in_path(m_search_path[i], pname);
				if(nd)
				{
					if(ret)
					{
						m_last_error = e_no_only_path_or_entity;
						return 0;
					}
					if(nd->m_type != e_entity)
					{
						m_last_error = e_is_not_entity;
						return 0;
					}
					else
						ret = nd;
				}

			}
			return ret;
		}

		int st_path_service::get_error()
		{
			return m_last_error;
		}

		st_path_service::st_path_service()
		{
			m_id_count = 0;
			m_last_error = -1;
			m_search_path.clear();
			m_root = new st_node;
			m_root->m_id = m_id_count;
			m_root->m_type = e_path;
		}


		void remove_node(st_node* nd)
		{
			if(!nd) return;
			st_node* n1 = nd->m_low;
			st_node* n2 = nd->m_right;
			remove_node(n1);
			remove_node(n2);
			delete nd;
		}
		st_path_service::~st_path_service()
		{
			remove_node(m_root);
		}
	
}