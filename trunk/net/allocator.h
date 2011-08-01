
#pragma once

namespace ns_common
{
	template<typename T, int PRE_SZ>
	struct allocator
	{
		char* m_chunk;
		T** m_pieces;//预分配的数量
		int m_max;
		int m_idx;
		
		allocator<T, PRE_SZ>(int sz = PRE_SZ)
		{
			m_chunk = (char*)::malloc(sizeof(T)*sz);
			m_pieces = (T**)::malloc(sizeof(T*)*sz);

			for(int i = 0; i<sz; ++i)
			{
				m_pieces[i] = reinterpret_cast<T*>(m_chunk+sizeof(T)*i);
			}

			m_max = sz;
			m_idx = m_max-1;
		}
		~allocator<T, PRE_SZ>()
		{
			::free(m_chunk);
			::free(m_pieces);
		}

		T* malloc()
		{
			T* ret = m_pieces[m_idx--];
			if(m_idx == -1) assert(false);
			return ret;
		}

		void free(T* obj)
		{
			m_pieces[++m_idx] = obj;
		}
	};
}

