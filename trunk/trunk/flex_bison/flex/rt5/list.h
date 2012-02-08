
#pragma once

namespace ns_util
{
	template <typename T>
	struct st_list_node
	{
		T m_value;
		st_list_node<T>* m_pre;
		st_list_node<T>* m_next;
		st_list_node<T>* insert_before(T val);//插入到前面
		st_list_node<T>* insert_after(T val);//插入到后面

		st_list_node(T val);
	};

	template<typename T>
	st_list_node<T>::st_list_node(T val)
	{
		m_pre = m_next = 0;
		m_value = val;
	}

	template <typename T>
	st_list_node<T>* st_list_node<T>::insert_before(T val)//插入到前面
	{
		st_list_node<T>* p = new st_list_node<T>(val);
		if(m_pre) m_pre->m_next = p;
		p->m_pre = m_pre;

		m_pre = p;
		p->m_next = this;
		return p;
	}
	
	template <typename T>
		st_list_node<T>* st_list_node<T>::insert_after(T val)//插入到后面
	{
		st_list_node<T>* p = new st_list_node<T>(val);
		if(m_next) m_next->m_pre = p;
		p->m_next = m_next;

		m_next = p;
		p->m_pre = this;
		return p;
	}

	template <typename T>
	struct st_list
	{
		typedef st_list_node<T>* iterator;
		iterator m_first;
		iterator m_last;
		iterator m_iter;

		void clear();

		void append(st_list& ls);
		void append_before(T val);
		void append_after(T val);

		iterator find(T val);
		iterator erase(T val);
		iterator erase(iterator it);
		
		iterator first();
		iterator next();

		st_list();
		~st_list();
	};

	template <typename T>
		void st_list<T>::clear()
	{
		iterator it = m_first;
		while(it)
		{
			iterator tmp = it->m_next;
			delete it;
			it = tmp;
		}
		m_iter = m_first = m_last = 0;
	}

	template <typename T>
		void st_list<T>::append(st_list<T>& ls)
	{
		m_last.m_next = ls.m_first;
		if(ls.m_first) ls.m_first->m_pre = m_last;
		m_last = ls.m_last;
		ls.clear();
	}

	template <typename T>
	void st_list<T>::append_before(T val)
	{
		if(m_first) m_first = m_first->insert_before(val);
		else
		{
			m_last = m_first = new st_list_node<T>(val);
		}
	}

	template <typename T>
	void st_list<T>::append_after(T val)
	{
		if(m_last) 
		{	
			m_last = m_last->insert_after(val);
		}
		else if(m_first)
		{
			m_last = m_first->insert_after(val);
		}
		else
		{
			m_last = m_first = new st_list_node<T>(val);
		}
	}

	template <typename T>
	st_list_node<T>* st_list<T>::find(T val)
	{
		st_list_node<T>* tmp = m_first;
		for(;tmp;tmp = tmp->m_next)
		{
			if(tmp->m_value == val)
				return tmp;
			
		}
		return tmp;
	}

	template <typename T>
	st_list_node<T>* st_list<T>::erase(T val)
	{
		iterator it = find(val);
		return erase(it);
	}

	template <typename T>
	st_list_node<T>* st_list<T>::erase(iterator it)
	{
		if(!it) return 0;

		iterator ret = it->m_next;

		if(it->m_pre) it->m_pre->m_next = it->m_next;
		else m_first = it->m_next;

		if(it->m_next) it->m_next->m_pre = it->m_pre;
		else m_last = it->m_pre;


		delete it;
		return ret;
	}


	template <typename T>
	st_list_node<T>* st_list<T>::first()
	{
		m_iter = m_first;
		return m_iter;
	}

	template <typename T>
	st_list_node<T>* st_list<T>::next()
	{
		if(m_iter) m_iter = m_iter->m_next;
		return m_iter;
	}

	template <typename T>
	st_list<T>::st_list()
	{
		m_iter = m_first = m_last = 0;
	}

	template <typename T>
	st_list<T>::~st_list()
	{
		clear();
	}

}