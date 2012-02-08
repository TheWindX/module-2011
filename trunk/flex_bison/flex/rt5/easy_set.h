
#pragma once


#include <set>


namespace ns_util
{
	template<typename K_T, typename P_T = std::less<K_T> >
	struct st_set
	{	
		bool insert(K_T key);
		bool find(K_T key);
		void erase(K_T key);
		void erase();

		bool first();
		bool next();

		const K_T& get();

		ns_base::u32 size();
		void clear();
	
	private:
		typedef std::set<K_T,P_T> set_t;
		typedef typename set_t::iterator iter_t;
		set_t m_set;
		iter_t m_iter;
	};
	
	template<typename K_T, typename P_T >
		bool st_set<K_T, P_T>::insert(K_T key)
	{
		typedef std::pair<iter_t,bool> pair_t;
		pair_t r = m_set.insert(key);
		m_iter = r.first;
		return r.second;
	};

	template<typename K_T, typename P_T >
		bool st_set<K_T, P_T>::find(K_T key)
	{
		m_iter = m_set.find(key);
		if(m_iter == m_set.end() ) return false;
		else return true;
	};

	template<typename K_T, typename P_T >
		void st_set<K_T, P_T>::erase(K_T key)
	{
		if(find(key) )
			m_set.erase(m_iter++);
	}

	template<typename K_T, typename P_T >
		void st_set<K_T, P_T>::erase()
	{
		m_set.erase(m_iter++);
	}

	template<typename K_T, typename P_T >
		bool st_set<K_T, P_T>::first()
	{	
		m_iter = m_set.begin();
		if(m_iter == m_set.end() )return false;
		return true;
	}

	template<typename K_T, typename P_T >
		bool st_set<K_T, P_T>::next()
	{	
		++m_iter;
		if(m_iter == m_set.end() )return false;
		return true;
	}


	template<typename K_T, typename P_T >
		const K_T& st_set<K_T, P_T>::get()
	{
		return *m_iter;
	}

	template<typename K_T, typename P_T >
		void st_set<K_T, P_T>::clear()
	{
		m_set.clear();
	}

	template<typename K_T, typename P_T >
		ns_base::u32 st_set<K_T, P_T>::size()
	{
		return (u32)m_set.size();
	}

}

