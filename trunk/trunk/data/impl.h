#pragma once
#include "interface.h"


#include "../head/ref_counter.h"
#include <boost/functional/hash.hpp>
#include <map>
#include <vector>


namespace ns_base
{
	using ns_common::impl_ref_counter;
	struct impl_hash : public i_hash, public impl_ref_counter
	{
		size_t m_seed;
		impl_hash():m_seed(0){};
		//overrided
		void process_buff(const char* ptr, long sz);
		void process_cstr(const char* ptr);
		void process_char(char ch);
		void process_short(short sd);
		void process_long(long ld);
		long get_value();
		void reset();
	};

	//md5
	struct impl_md5 : public i_md5, public impl_ref_counter
	{
		const char* void process_buff(const char* ptr, long sz);
		const char* void process_buff2str(const char* ptr, long sz);
	};

	template<typename T>
	struct st_cmp : public std::binary_function<void*, void*, bool>
	{	
		T* m_this;
		bool operator()(void* left, void* right) const
		{
			return m_this->s_cmp(left, right);
		}

		st_cmp(T* p):m_this(p){};
	};

	struct impl_vector : public i_vector, public impl_ref_counter
	{
		std::vector<void*> m_vec;
		std::vector<void*>::iterator m_it;
		//overrided
		//元素放入, 元素不为0
		void push(void* ptr);
		void* pop();

		//随机访问
		long size();
		void* get_at(long idx);
		void set_at(long idx, void* ptr);

		//迭代
		void* first();
		void* next();

		void sort();//排序
		long lower_bound(void* to_serach);//-1表示未找到
	};

	struct impl_map :  public i_map, public impl_ref_counter
	{
		std::map<void*, void*, st_cmp<i_map> > m_map;
		std::map<void*, void*, st_cmp<i_map> >::iterator m_it;
		
		//overrided
		//加入元素
		void insert(void* key, void* val);
		void erase(void* key);

		//访问
		bool find_key(void* key);
		void* get_value();
		void set_value(void* val);

		//迭代
		void* first();
		void* next();

		impl_map():m_map(st_cmp<i_map>(this) )
		{	
		}
	};

	

	struct impl_data : public h_data
	{
		//overrided
		i_hash* create_hasher();
		i_md5* create_md5();
		i_vector* create_vector();
		i_map* create_map();
		i_heap* create_heap();

		i_buffer* buff2hex(i_buffer* buff);
		i_buffer* hex2buff(i_buffer* hex);
	};
}