#pragma once
#include "../head/ref_counter.h"
#include "../head/delegate.h"

#include "../filesystem/interface.h"

namespace ns_base
{
	using ns_common::i_ref_counter;

	//��hash
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
		//16byte�� md5
		virtual const char* process_buff(const char* ptr, long sz) = 0;
		//64byte�� string��ʾmd5//%f%f,
		virtual const char* process_buff2str(const char* ptr, long sz) = 0;
	};

	//���Ա���
	struct i_vector : public virtual i_ref_counter
	{
		ns_delegate::Delegate<bool(void*, void*)> s_cmp;
		//Ԫ�ط���, Ԫ�ز�Ϊ0
		virtual void push(void* ptr) = 0;
		virtual void* pop() = 0;

		//�������
		virtual long size() = 0;
		virtual void* get_at(long idx) = 0;
		virtual void set_at(long idx, void* ptr) = 0;
		
		//����
		virtual void* first() = 0;
		virtual void* next() = 0;
		
		virtual void sort() = 0;//����
		virtual long lower_bound(void* to_serach) = 0;//-1��ʾδ�ҵ�
	};

	//���ұ�
	struct i_map : public virtual i_ref_counter
	{
		ns_delegate::Delegate<bool(void*, void*)> s_cmp;
		//����Ԫ��
		virtual void insert(void* key, void* val) = 0;
		virtual void erase(void* key) = 0;

		//����
		virtual bool find_key(void* key) = 0;
		virtual void* get_value() = 0;
		virtual void set_value(void* val) = 0;

		//����
		virtual void* first() = 0;
		virtual void* next() = 0;
	};

	//��
	struct i_heap : public virtual i_ref_counter
	{
		ns_delegate::Delegate<bool(void*, void*)> s_cmp;

		//����
		virtual void sink(size_t pos) = 0;
		virtual void rise(size_t pos) = 0;
		virtual void update(size_t pos) = 0;
		virtual void push(void* ele) = 0;
		virtual void pop() = 0;
		virtual void* top() = 0;

		//����
		virtual size_t size() = 0;
		virtual bool first() = 0;
		virtual bool next() = 0;
		virtual void* get() = 0;
	};


	//�ӿ���
	struct h_data
	{
		virtual i_hash* create_hasher() = 0;
		virtual i_md5* create_md5() = 0;
		virtual i_vector* create_vector() = 0;
		virtual i_map* create_map() = 0;
		virtual i_heap* create_heap() = 0;

		//buff�ɼ��ַ���ת��
		virtual i_buffer* buff2hex(i_buffer* buff) = 0;
		virtual i_buffer* hex2buff(i_buffer* hex) = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_data, "data.dll");