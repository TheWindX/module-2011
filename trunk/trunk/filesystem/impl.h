#pragma once
#include <string>
#include <iostream>
#include <map>

#include "interface.h"

#include "../head/ref_counter.h"
#include <boost/filesystem.hpp>

namespace ns_base
{
	using ns_common::impl_ref_counter;

	namespace fs = boost::filesystem;
	struct impl_path : public i_path, public virtual impl_ref_counter
	{
		//�ִ�
		const char* append(const char* path, const char* branch);


		//תΪ����·��
		const char* system_complete(const char* path);
		//�Ƿ����
		bool exists(const char* path);
		//�Ƿ�Ŀ¼
		bool is_directory(const char* path);
		
		//Ŀ¼����
		const char* first(const char* path);
		const char* next();

		//����
		const char* extension(const char* path);//��չ��
		const char* leaf(const char* path);//�ļ���Ŀ¼��
		const char* stem(const char* path);//�ļ���, ȥ����׺
		const char* parent_path(const char* path);//��Ŀ¼��

		i_path* clone(const char* path);
		const char* normalize(const char* path);
		
		//member
		fs::directory_iterator m_it;

	};


	struct impl_buffer : public i_buffer, public virtual impl_ref_counter
	{	
		//ָ��
		void* ptr();
		//��С
		long size();
		
		void resize(long sz);

		void write(const char* ptr, long len);
		//member
		std::vector<char> m_buff;

		~impl_buffer()
		{

		}
	};

	struct impl_read_file : public i_read_file, public virtual impl_ref_counter
	{
		size_t read(void* buffer, size_t sz_to_read);
		i_buffer* read_all();

		bool seek(long final_pos, bool relative);

		size_t size() const;
		size_t pos() const;


		std::string m_file_name;
		FILE* m_file;
		size_t m_sz_file;

		impl_read_file(const char* file_name);
		~impl_read_file();
	};

	struct impl_write_file : public i_write_file, public virtual impl_ref_counter
	{
		size_t write(const void* buffer, size_t sz_to_write);
		bool seek(long final_pos, bool relative);
		size_t pos() const;

		std::string m_file_name;;
		FILE* m_file;
		size_t m_sz_file;

		impl_write_file(const char* file_name, bool append);
		~impl_write_file();
	};

	struct impl_fs_pak : public i_pak, public virtual impl_ref_counter
	{
		std::string m_loaction;
		std::map<std::string, i_buffer*> m_cache;//(path, buff)

		impl_fs_pak(const char* location);
		~impl_fs_pak();

		bool exist(const char* path);
		i_buffer* get_buffer(const char* path);
	};

	//�ӿڵ���
	struct impl_filesystem : public h_filesystem
	{
		//ģ�����ڵ�·��
		const char* create_module_path();
		//����·��
		const char* create_work_directory();
		//����·��
		i_path* create_path();
		//����buff
		i_buffer* create_buff(const char* buff, long sz);
		//����Ŀ¼
		bool make_directories(const char* path);

		//���ļ�
		i_read_file* create_read_file(const char* path);
		//д�ļ�
		i_write_file* create_write_file(const char* path, bool append);

		//��Ŀ¼��Ϊһ��pakʹ��
		i_pak* create_pak(const char* location);
	};
}