
#pragma once

#include "types.h"
#include <map>

namespace ns_base
{
	template<typename K_T, typename V_T, typename P_T = std::less<K_T> >
	struct st_map
	{	
		bool insert(K_T key, V_T val);
		bool find(K_T key);
		void erase(K_T key);
		void erase();

		bool first();
		bool next();

		const K_T& get_key();
		V_T& get_val();

		ns_base::u32 size();
		void clear();
		st_map(const P_T& cmp):m_map(cmp){}
		st_map():m_map(P_T() ){}
	private:
		typedef std::map<K_T,V_T,P_T> map_t;
		typedef typename map_t::iterator iter_t;
		map_t m_map;
		iter_t m_iter;
	};

	template<typename K_T, typename V_T, typename P_T >
		bool st_map<K_T, V_T, P_T>::insert(K_T key, V_T val)
	{
		typedef std::pair<iter_t,bool> pair_t;
		pair_t r = m_map.insert(std::make_pair(key, val) );
		m_iter = r.first;
		return r.second;
	};

	template<typename K_T, typename V_T, typename P_T >
		bool st_map<K_T, V_T, P_T>::find(K_T key)
	{
		m_iter = m_map.find(key);
		if(m_iter == m_map.end() ) return false;
		else return true;
	};

	template<typename K_T, typename V_T, typename P_T >
		void st_map<K_T, V_T, P_T>::erase(K_T key)
	{
		if(find(key) )
			m_map.erase(m_iter++);
	}

	template<typename K_T, typename V_T, typename P_T >
		void st_map<K_T, V_T, P_T>::erase()
	{
		m_map.erase(m_iter++);
	}

	template<typename K_T, typename V_T, typename P_T >
		bool st_map<K_T, V_T, P_T>::first()
	{	
		m_iter = m_map.begin();
		if(m_iter == m_map.end() )return false;
		return true;
	}

	template<typename K_T, typename V_T, typename P_T >
		bool st_map<K_T, V_T, P_T>::next()
	{	
		++m_iter;
		if(m_iter == m_map.end() )return false;
		return true;
	}


	template<typename K_T, typename V_T, typename P_T >
		const K_T& st_map<K_T, V_T, P_T>::get_key()
	{
		return m_iter->first;
	}

	template<typename K_T, typename V_T, typename P_T >
		V_T& st_map<K_T, V_T, P_T>::get_val()
	{
		return m_iter->second;
	}

	template<typename K_T, typename V_T, typename P_T >
		void st_map<K_T, V_T, P_T>::clear()
	{
		m_map.clear();
	}

	template<typename K_T, typename V_T, typename P_T >
		ns_base::u32 st_map<K_T, V_T, P_T>::size()
	{
		return (u32)m_map.size();
	}
}