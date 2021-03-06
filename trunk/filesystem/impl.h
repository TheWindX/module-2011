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
	struct impl_path_iter : public i_path_iter, public virtual impl_ref_counter
	{
		impl_path_iter(fs::directory_iterator it):m_it(it){}

		//返回当前路径
		const char* get_path();

		//如果返回 0, 迭代完成
		void next();

		bool is_directory();
		
		//member
		fs::directory_iterator m_it;

	};


	struct impl_buffer : public i_buffer, public virtual impl_ref_counter
	{	
		//指针
		void* ptr();
		//大小
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

	//接口导出
	struct impl_filesystem : public h_filesystem
	{
		//模块所在的路径
		const char* get_module_path();
		//工作路径
		const char* get_work_directory();
		//路径迭代
		i_path_iter* create_path_iter(const char* path);

		//创造buff
		i_buffer* create_buff(const char* buff, long sz);
		//创建目录
		bool make_directories(const char* path);

		//读文件
		i_read_file* create_read_file(const char* path);
		//写文件
		i_write_file* create_write_file(const char* path, bool append);

		//将目录作为一个pak使用
		i_pak* create_pak(const char* location);


		//字串
		const char* append(const char* path, const char* branch);


		//转为完整路径
		const char* system_complete(const char* path);
		//是否存在
		bool exists(const char* path);
		//是否目录
		bool is_directory(const char* path);

		//解析
		const char* extension(const char* path);//扩展名
		const char* leaf(const char* path);//文件或目录名
		const char* stem(const char* path);//文件名, 去掉后缀
		const char* parent_path(const char* path);//父目录名
		
		const char* normalize(const char* path);



		//模块资源释放
		void release();
	};
}