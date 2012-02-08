#include "stack.h"
#include "code.h"

using namespace ns_util;

namespace ns_core
{
	template<typename T>
	struct st_seg
	{
		enum{e_leaf = 0, e_branch};
		u32 m_type;

		array<st_seg*> m_subs;
		T m_val;

		st_seg():m_type(e_branch){}

		static st_seg* make_leaf(T val)
		{
			st_seg* seg = new st_seg;
			seg->m_type = e_leaf;
			seg->m_val = val;
			return seg;
		}

		static st_seg* make_branch()
		{
			st_seg* seg = new st_seg;
			seg->m_type = e_branch;
			return seg;
		}

		void append(st_seg* seg)
		{
			m_subs.push(seg);
		}

		st_seg<T>* append_leaf(T val)
		{
			st_seg<T>* leaf = st_seg<T>::make_leaf(val);
			m_subs.push(leaf);
			return leaf;
		}


		st_seg<T>* first()
		{
			iterator it = get_iterator();
			return it.get();
		}

		st_seg<T>* last()
		{
			iterator it = get_iterator();
			st_seg<T>* s = it.get();
			while(s)
			{
				it.next();
				st_seg<T>* s1 = it.get();
				if(!s1) return s;
				s = s1;
			}
		}

		struct iterator
		{
			array<st_seg*> m_stk;
			array<u32> m_idx;

			st_seg* m_cur;

			void step()
			{	
				if(m_idx.size() == 0)
				{
					if(m_cur) m_cur = 0;
					return;
				}
				st_seg* seg = m_stk.top();
				u32& idx = m_idx.top();
				if(idx == seg->m_subs.m_top)
				{
					m_stk.pop();
					m_idx.pop();
					step();
				}
				else
				{
					idx++;
					m_cur = seg->m_subs[idx];
				}
			}

			st_seg* get()
			{
				if(m_cur == 0) return 0;
				if(m_cur->m_type == e_leaf) return m_cur;

				if(m_cur->m_subs.size() != 0)
				{
					m_stk.push(m_cur);
					m_idx.push(0);
					m_cur = m_cur->m_subs[0];
					return get();
				}
				else
				{
					step();
					return get();
				}
			}

			void next()
			{
				if(get() == 0) return;
				step();
				get();
			}
		};

		iterator get_iterator()
		{
			iterator it;
			it.m_cur = this;
			return it;
		}

	};
	

}
