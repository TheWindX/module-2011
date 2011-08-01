

#include "../head/exception.h"

#include <algorithm>
#include "heap.h"
#include "impl.h"
#include "md5.h"

#include "../head/system.h"
#include "../head/utility_new.h"

namespace ns_base
{
		//overrided
		void impl_hash::process_buff(const char* ptr, long sz)
		{
			for(long i=0; i<sz; ++i)
			{
				boost::hash_combine(m_seed, *(ptr+i) );
			}
		}

		void impl_hash::process_cstr(const char* ptr)
		{
			for(const char* i = ptr; *i != '\0'; ++i)
			{
				boost::hash_combine(m_seed, *i);
			}
		}

		void impl_hash::process_char(char ch)
		{
			boost::hash_combine(m_seed, ch);
		}

		void impl_hash::process_short(short sd)
		{
			boost::hash_combine(m_seed, sd);
		}

		void impl_hash::process_long(long ld)
		{
			boost::hash_combine(m_seed, ld);
		}
		long impl_hash::get_value()
		{
			return m_seed;
		}
		void impl_hash::reset()
		{
			m_seed = 0;
		}


		//md5
		const char* void impl_md5::process_buff(const char* ptr, long sz)
		{
			static MD5 md5;
			md5.init();
			md5.update((unsigned char*)ptr,sz);
			md5.finalize();
			return (const char*)md5._digest();
		}

		const char* void impl_md5::process_buff2str(const char* ptr, long sz)
		{
			MD5 md5;
			md5.init();
			md5.update((unsigned char*)ptr,sz);
			md5.finalize();
			static char buffer[MD5_STR_LEN];
			return md5.hex_digest(buffer);
		}


		//overrided
		//元素放入, 元素不为0
		void impl_vector::push(void* ptr)
		{
			m_vec.push_back(ptr);
		}

		void* impl_vector::pop()
		{
			m_vec.pop_back();
			if(m_vec.size() == 0)return 0;
			return m_vec.back();
		}

		//随机访问
		long impl_vector::size()
		{
			return m_vec.size();
		}
		void* impl_vector::get_at(long idx)
		{	
			return m_vec.at(idx);
		}
		void impl_vector::set_at(long idx, void* ptr)
		{
			m_vec[idx] = ptr;
		}

		//迭代
		void* impl_vector::first()
		{
			m_it = m_vec.begin();
			if(m_it == m_vec.end() ) return 0;
			return *m_it;
		}

		void* impl_vector::next()
		{	
			if(++m_it == m_vec.end() ) return 0;
			return *m_it;
		}

		void impl_vector::sort()//排序
		{
			st_cmp<i_vector> m_data_cmp(this);
			std::sort<std::vector<void*>::iterator, st_cmp<i_vector> >(m_vec.begin(), m_vec.end(), m_data_cmp );
		}

		long impl_vector::lower_bound(void* to_serach)//-1表示未找到
		{
			st_cmp<i_vector> m_data_cmp(this);
			std::vector<void*>::iterator it = std::lower_bound<std::vector<void*>::iterator, void*, st_cmp<i_vector> >(m_vec.begin(), m_vec.end(),  to_serach, m_data_cmp);

			if(it == m_vec.end() ) return -1;
			return it-m_vec.begin();
		}

		//overrided
		//加入元素
		void impl_map::insert(void* key, void* val)
		{
			m_map.insert(std::make_pair(key, val) );
		}

		void impl_map::erase(void* key)
		{
			m_map.erase(key);
		}

		//访问
		bool impl_map::find_key(void* key)
		{
			m_it = m_map.lower_bound(key);
			if(m_it != m_map.end() )
			{
				if( !m_map.key_comp()(key, m_it->first) )
				{
					//found
					return true;
				}
			}
			return false;
		}

		void* impl_map::get_value()
		{
			return m_it->second;
		}

		void impl_map::set_value(void* val)
		{
			m_it->second = val;
		}

		//迭代
		void* impl_map::first()
		{
			m_it = m_map.begin();
			if(m_it == m_map.end() ) return 0;
			return m_it->first;
		}

		void* impl_map::next()
		{
			++m_it;
			if(m_it == m_map.end() ) return 0;
			return m_it->first;
		}

		i_hash* impl_data::create_hasher()
		{
			impl_hash* p_ret = new impl_hash();
			return p_ret;
		}

		i_md5* impl_data::create_md5()
		{
			impl_md5* p_ret = new impl_md5();
			return p_ret;
		}

		i_vector* impl_data::create_vector()
		{
			impl_vector* p_ret = new impl_vector();
			return p_ret;
		}

		i_map* impl_data::create_map()
		{
			impl_map* p_ret = new impl_map;
			p_ret->m_map.key_comp();
			return p_ret;
		}

		i_heap* impl_data::create_heap()
		{
			return new impl_heap;
		}

		i_buffer* impl_data::buff2hex(i_buffer* buff)
		{
			h_filesystem* hf;
			get(hf);

			i_buffer* buff_out = hf->create_buff("", 0);
			long sz = buff->size();
			unsigned char* ptr = (unsigned char*)buff->ptr();
			
			for(size_t i = 0; i<sz; ++i)
			{
				unsigned char c = ptr[i];
				unsigned char high = (c&0xf0)>>4;
				unsigned char low = (c&0x0f);

				if(high<0x0a)
					high = high+'0';
				else
					high = high-0x0a+'a';

				if(low<0x0a)
					low = low+'0';
				else
					low = low-0x0a+'a';

				buff_out->write((const char*)&high, 1);
				buff_out->write((const char*)&low, 1);
			}
			return buff_out;
		}

		i_buffer* impl_data::hex2buff(i_buffer* hex)
		{
			h_filesystem* hf;
			get(hf);

			i_buffer* buff_out = hf->create_buff("", 0);
			long sz = hex->size();
			unsigned char* ptr = (unsigned char*)hex->ptr();

			if(sz % 2 != 0)
			{
				buff_out->release();
				RAISE_EXCEPTION("");
				return 0;
			}
			
			for(size_t i = 0; i<sz; i+=2)
			{
				unsigned char high = ptr[i];
				unsigned char low = ptr[i+1];

				if(isdigit(high) )
					high -= '0';
				else
					high = high-'a'+0x0a;

				if(isdigit(low) )
					low -= '0';
				else
					low = low-'a'+0x0a;

				unsigned char c = (high<<4)|low;
				buff_out->write((const char*)&c, 1);
			}
			return buff_out;

		}
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}

#include "../head/M_interface.h"

M_IMPL(ns_base::h_data, ns_base::impl_data);//2. 接口实现

M_OPEN();//3. 模块建立

