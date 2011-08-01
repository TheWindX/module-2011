#pragma once

#include <vector>
#include "interface.h"
#include "../head/ref_counter.h"


namespace ns_base
{
	using ns_common::impl_ref_counter;

	template<typename T>
	struct st_trait
	{
		bool less(T t1, T t2)
		{
			return true;
		}
		T npos;
	};

	//for int 
	//template<> struct st_trait<int>
	//{
	//	bool less(int t1, int t2)
	//	{
	//		return t1<t2;
	//	}
	//	int npos;
	//	st_trait():npos(-1){};
	//};

	template<typename ELEM_T, typename ELEM_T_TRAIT = st_trait<ELEM_T> >
	struct st_heap
	{
		std::vector<ELEM_T> m_arr;
		ELEM_T_TRAIT m_trait;

		//如果变化的值比原来小了，上浮，要么下沉
		void update(size_t p)
		{
			rise(p);
			sink(p);
		}


		void sink(size_t p)
		{
			size_t sz = m_arr.size();

			for(size_t pos = p+1; ;)
			{
				size_t p1 = pos<<1;
				size_t p2 = p1+1;
				if(p1>sz) return;
				ELEM_T* up = &m_arr[0]+pos-1;
				ELEM_T* left = &m_arr[0]+p1-1;
				if(p2>sz)
				{

					if( m_trait.less(*left, *up) ){ELEM_T t = *up;*up = *left;*left = t;}
					pos = p1;
					continue;
				}
				else
				{
					ELEM_T* right = left+1;
					if(m_trait.less(*left, *right)&&m_trait.less(*left, *up) )
					{
						ELEM_T t = *up;*up = *left;*left = t;
						pos = p1;
					}
					else if(m_trait.less(*right, *left)&&m_trait.less(*right, *up) )
					{
						ELEM_T t = *up;*up = *right;*right = t;
						pos = p2;
					}
					else if(m_trait.less(*right, *up) )
					{
						ELEM_T t = *up;*up = *right;*right = t;
						pos = p2;
					}
					else
					{
						return;
					}
				}
			}

		}

		void rise(size_t p)
		{
			for(size_t pos = p+1; ;)
			{
				size_t up_pos;

				up_pos = pos>>1;
				if(up_pos == 0) return;
				ELEM_T* up = (ELEM_T*)(&m_arr[0])+up_pos-1;
				ELEM_T* low = (ELEM_T*)(&m_arr[0])+pos-1;
				if(  m_trait.less(*low, *up) )
				{
					ELEM_T t = *up;*up = *low;*low = t;
				}
				pos = up_pos;
			}
		}

		void push(ELEM_T elem)
		{
			m_arr.push_back(elem);
			size_t sz = m_arr.size();

			rise(sz-1);
		}
		bool empty()
		{
			return m_arr.empty();
		}
		ELEM_T top()
		{
			if(empty()) return m_trait.npos;
			return m_arr[0];
		}
		void pop()
		{
			if(empty()) return;
			m_arr[0] = m_arr.back();
			size_t sz = m_arr.size();
			m_arr.resize(--sz);

			//sink
			sink(0);
		}

		void clear()
		{
			m_arr.clear();
		}
	};


	struct st_any	{		void* m_p;	st_any(void* p):m_p(p){}; st_any():m_p(0){} };
	template<> struct st_trait<st_any>
	{
		i_heap* m_heap;
		bool less(st_any t1, st_any t2)
		{
			return m_heap->s_cmp(t1.m_p, t2.m_p);
		}
		st_any npos;
		st_trait(i_heap* h):m_heap(h), npos(0){};
		st_trait():m_heap(0), npos(0){};
	};



	struct impl_heap : public i_heap, public virtual impl_ref_counter
	{

		st_heap<st_any> m_heap;
		std::vector<st_any>::iterator m_it;

		//操作
		void sink(size_t pos)
		{
			m_heap.sink(pos);
		}
		void rise(size_t pos)
		{
			m_heap.rise(pos);
		}
		void update(size_t pos)
		{
			sink(pos);
			rise(pos);
		}
		void push(void* ele)
		{
			m_heap.push(st_any(ele) );
		}

		void pop()
		{
			m_heap.pop();
		}

		void* top()
		{
			return m_heap.top().m_p;
		}

		//迭代
		size_t size()
		{
			return m_heap.m_arr.size();
		}

		bool first()
		{
			m_it = m_heap.m_arr.begin();
			if(m_it == m_heap.m_arr.end() ) return false;
			return true;
		}
		bool next()
		{
			++m_it;
			if(m_it == m_heap.m_arr.end() ) return false;
			return true;
		}
		void* get()
		{
			return m_it->m_p;
		}
		impl_heap(){m_heap.m_trait.m_heap = this;};
	};

}