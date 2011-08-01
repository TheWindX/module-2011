#pragma once
#include "../head/ref_counter.h"

namespace ns_base
{
	using ns_common::i_ref_counter;

	struct i_file;


	struct i_path : public virtual i_ref_counter
	{
		/* ·������*/
		virtual const char* append(const char* path, const char* branch) = 0;

		//����
		virtual const char* extension(const char* path) = 0;//��׺
		virtual const char* leaf(const char* path) = 0;//�ļ���
		virtual const char* stem(const char* path) = 0;//�ļ���, ȥ����׺
		virtual const char* parent_path(const char* path) = 0;

		virtual const char* normalize(const char* path) = 0;


		/* ��Ϊϵͳ�ļ�*/

		//תΪ����·��
		virtual const char* system_complete(const char* path) = 0;
		//�Ƿ����
		virtual bool exists(const char* path) = 0;
		//�Ƿ�Ŀ¼
		virtual bool is_directory(const char* path) = 0;
		//Ŀ¼����
		virtual const char* first(const char* path) = 0;
		virtual const char* next() = 0;
	};



	struct i_buffer : public virtual i_ref_counter
	{	
		//ָ��
		virtual void* ptr() = 0;
		//��С
		virtual long size() = 0;
		//���ô�С
		virtual void resize(long sz) = 0;
		//д��
		virtual void write(const char* ptr, long len) = 0;
	};


	struct i_read_file : public virtual i_ref_counter
	{
		virtual size_t read(void* buffer, size_t sz_to_read) = 0;
		virtual i_buffer* read_all() = 0;

		virtual bool seek(long final_pos, bool relative = false) = 0;

		virtual size_t size() const = 0;
		virtual size_t pos() const = 0;
	};

	struct i_write_file : public virtual i_ref_counter
	{
		virtual size_t write(const void* buffer, size_t sz_to_write) = 0;
		virtual bool seek(long final_pos, bool relative = false) = 0;
		virtual size_t pos() const = 0;
	};

	//�ļ���ȡ
	struct i_pak : public virtual i_ref_counter
	{	
		virtual i_buffer* get_buffer(const char* path) = 0;//return null for no found
		virtual bool exist(const char* path) = 0;
	};



	//�ӿڵ���
	struct h_filesystem
	{
		//����·��
		virtual i_path* create_path() = 0;

		//ģ�����ڵ�·��
		virtual const char* create_module_path() = 0;
		//����·��
		virtual const char* create_work_directory() = 0;
		//����buff
		virtual i_buffer* create_buff(const char* buff, long sz) = 0;
		//����Ŀ¼
		virtual bool make_directories(const char* path) = 0;

		//���ļ�
		virtual i_read_file* create_read_file(const char* path) = 0;
		//д�ļ�
		virtual i_write_file* create_write_file(const char* path, bool append = false) = 0;

		//��Ŀ¼��Ϊһ��pakʹ��
		virtual i_pak* create_pak(const char* location) = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_filesystem, "filesystem.dll");
