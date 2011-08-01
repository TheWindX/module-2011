#pragma once
#include "../head/ref_counter.h"
#include "../head/delegate.h"

#include "../filesystem/interface.h"

namespace ns_base
{
	using ns_common::i_ref_counter;

	//求hash
	struct i_hash : public virtual i_ref_counter
	{	
		virtual void process_buff(const char* ptr, long sz) = 0;
		virtual void process_cstr(const char* ptr) = 0;
		virtual void process_char(char ch) = 0;
		virtual void process_short(short sd) = 0;
		virtual void process_long(long ld) = 0;
		
		//hash value
		virtual long get_value() = 0;
		//reset to init state
		virtual void reset() = 0;
	};

	//md5
	struct i_md5 : public virtual i_ref_counter
	{	
		static const long MD5_LEN = 16;
		static const long MD5_STR_LEN = 64;
		//16byte的 md5
		virtual const char* process_buff(const char* ptr, long sz) = 0;
		//64byte的 string表示md5//%f%f,
		virtual const char* process_buff2str(const char* ptr, long sz) = 0;
	};

	//线性表类
	struct i_vector : public virtual i_ref_counter
	{
		ns_delegate::Delegate<bool(void*, void*)> s_cmp;
		//元素放入, 元素不为0
		virtual void push(void* ptr) = 0;
		virtual void* pop() = 0;

		//随机访问
		virtual long size() = 0;
		virtual void* get_at(long idx) = 0;
		virtual void set_at(long idx, void* ptr) = 0;
		
		//迭代
		virtual void* first() = 0;
		virtual void* next() = 0;
		
		virtual void sort() = 0;//排序
		virtual long lower_bound(void* to_serach) = 0;//-1表示未找到
	};

	//查找表
	struct i_map : public virtual i_ref_counter
	{
		ns_delegate::Delegate<bool(void*, void*)> s_cmp;
		//加入元素
		virtual void insert(void* key, void* val) = 0;
		virtual void erase(void* key) = 0;

		//访问
		virtual bool find_key(void* key) = 0;
		virtual void* get_value() = 0;
		virtual void set_value(void* val) = 0;

		//迭代
		virtual void* first() = 0;
		virtual void* next() = 0;
	};

	//堆
	struct i_heap : public virtual i_ref_counter
	{
		ns_delegate::Delegate<bool(void*, void*)> s_cmp;

		//操作
		virtual void sink(size_t pos) = 0;
		virtual void rise(size_t pos) = 0;
		virtual void update(size_t pos) = 0;
		virtual void push(void* ele) = 0;
		virtual void pop() = 0;
		virtual void* top() = 0;

		//迭代
		virtual size_t size() = 0;
		virtual bool first() = 0;
		virtual bool next() = 0;
		virtual void* get() = 0;
	};


	//接口类
	struct h_data
	{
		virtual i_hash* create_hasher() = 0;
		virtual i_md5* create_md5() = 0;
		virtual i_vector* create_vector() = 0;
		virtual i_map* create_map() = 0;
		virtual i_heap* create_heap() = 0;

		//buff可见字符的转换
		virtual i_buffer* buff2hex(i_buffer* buff) = 0;
		virtual i_buffer* hex2buff(i_buffer* hex) = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_data, "data.dll");