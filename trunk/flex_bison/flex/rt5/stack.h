
#pragma once

#include <cstdlib>
#include <memory.h>
#include <cassert>

#include "types.h"

namespace ns_util
{
	using namespace ns_base;

	template<typename T, u32 min_bit_stack = 4>
	struct array
	{
		enum {min_size_stack = 1<<min_bit_stack };
		T* m_base;
		u32 m_uper;
		u32 m_lower;
		u32 m_top;

		void push(T val);
		T pop();
		bool empty();
		void clear();

		u32 size();
		void resize(u32 sz);//TODO, 

		T& at(u32 idx);
		T& operator[](u32 idx);
		T& top();

		u32 find(T val);
		bool insert(u32 idx, T elem);
		bool erase(u32 idx);

		void swap(array<T, min_bit_stack>& other);

		array(u32 ntime);
		array(array<T, min_bit_stack>& other)
		{
			m_base = 0;
			swap(other);
		}

		array();
		~array();
	};

	template<typename T, u32 min_bit_stack>
	void array<T, min_bit_stack>::push(T val)
	{
		m_top++;
		if(m_top == m_uper)
		{	
			m_lower = m_lower << 1;
			m_uper = m_uper << 1;
			
			m_base = (T*)realloc(m_base, m_uper*sizeof(T) );
		}

		m_base[m_top] = val;
	}

	template<typename T, u32 min_bit_stack>
		T array<T, min_bit_stack>::pop()
	{
		T ret = m_base[m_top];
		
		m_top--;
		if(m_uper>min_size_stack)
		{
			if(m_top < m_lower)
			{
				m_uper = m_uper>>1;
				m_lower = m_lower>>1;

				m_base = (T*)realloc(m_base, m_uper*sizeof(T) );
			}
		}

		return ret;
	}

	template<typename T, u32 min_bit_stack>
		bool array<T, min_bit_stack>::empty()
	{
		return m_top == U32_NA;
	}

	template<typename T, u32 min_bit_stack>
		void array<T, min_bit_stack>::clear()
	{	
		T* tmp = m_base;
		free(tmp);

		m_base = (T*)malloc(sizeof(T)*min_size_stack);
		m_top = U32_NA;
		m_uper = min_size_stack;
		m_lower = min_size_stack>>2;
	}

	template<typename T, u32 min_bit_stack>
		u32 array<T, min_bit_stack>::size()
	{
		return m_top+1;
	}

	template<typename T, u32 min_bit_stack>
		void array<T, min_bit_stack>::resize(u32 sz)
	{	
		u32 top = sz+1;
		m_top = sz-1;
		if(sz<min_size_stack) return;
		if(m_uper < top)
		{
			do
			{
				m_uper = m_uper<<1;
			}while(m_uper < top);
			m_lower = m_uper>>2;
			m_base = (T*)realloc(m_base, m_uper*sizeof(T) );
			return;
		}
		else if(m_uper == top)
		{
			m_uper = m_uper<<1;
			m_lower = m_uper>>2;
			m_base = (T*)realloc(m_base, m_uper*sizeof(T) );
		}
		if(m_lower > sz)
		{
			if(m_uper == min_size_stack)
			{
				return ;
			}

			do 
			{
				m_lower = m_lower>>1;
			}while(m_lower>sz);
			m_uper = m_lower<<2;
			m_base = (T*)realloc(m_base, m_uper*sizeof(T) );
			return;
		}
	}

	template<typename T, u32 min_bit_stack>
		T& array<T, min_bit_stack>::at(u32 idx)
	{
		assert(idx<=m_top);
		return m_base[idx];
	}

	template<typename T, u32 min_bit_stack>
		T& array<T, min_bit_stack>::operator[](u32 idx)
	{
		assert(idx<=m_top);
		return m_base[idx];
	}

	template<typename T, u32 min_bit_stack>
		T& array<T, min_bit_stack>::top()
	{
		return m_base[m_top];
	}

	template<typename T, u32 min_bit_stack>
		u32 array<T, min_bit_stack>::find(T val)
	{
		if(m_top == U32_NA) return U32_NA;
		u32 top = m_top+1;
		for(u32 i = 0; i != top; ++i)
		{
			if(m_base[i] == val)
			{
				return i;
			}
		}

		return U32_NA;
	}

	template<typename T, u32 min_bit_stack>
		bool array<T, min_bit_stack>::insert(u32 idx, T elem)
	{
		if(idx == U32_NA) return false;
		if(idx > m_top+1) return false;

		m_top++;
		T tmp = elem;
		for(u32 i = idx; i < m_top; ++i)
		{
			T tmp1 = m_base[i];
			m_base[i] = tmp;
			tmp = tmp1;
		}
		m_base[m_top] = tmp;
		return true;
	}

	template<typename T, u32 min_bit_stack>
		bool array<T, min_bit_stack>::erase(u32 idx)
	{
		if(idx == U32_NA) return false;
		if(idx > m_top) return false;

		T* ptr = m_base+idx;
		T* top = m_base+m_top;
		for(; ptr != top; ++ptr)
		{
			*ptr = *(ptr+1);
		}
		m_top--;

		return true;
	}
	template<typename T, u32 min_bit_stack>
		void array<T, min_bit_stack>::swap(array<T, min_bit_stack>& other)
	{
		array<T, min_bit_stack> tmp;
		tmp = *this;
		*this = other;
		other = tmp;
	}

	template<typename T, u32 min_bit_stack>
		array<T, min_bit_stack>::array(u32 ntime)
	{
		if(ntime<min_bit_stack) ntime = min_bit_stack;
		u32 sz = 1<<ntime;
		m_base = (T*)malloc(sizeof(T)*sz);
		m_top = U32_NA;
		m_uper = sz;
		m_lower = sz>>2;
	}
	template<typename T, u32 min_bit_stack>
	array<T, min_bit_stack>::array()
	{	
		u32 sz = min_size_stack;
		m_base = (T*)malloc(sizeof(T)*sz);
		m_top = U32_NA;
		m_uper = sz;
		m_lower = sz>>2;
	}

	template<typename T, u32 min_bit_stack>
		array<T, min_bit_stack>::~array()
	{
		free(m_base);
	}

}