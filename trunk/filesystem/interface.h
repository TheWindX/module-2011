#pragma once
#include "../head/ref_counter.h"

namespace ns_base
{
	using ns_common::i_ref_counter;

	struct i_file;


	struct i_path : public virtual i_ref_counter
	{
		/* 路径计算*/
		virtual const char* append(const char* path, const char* branch) = 0;

		//解析
		virtual const char* extension(const char* path) = 0;//后缀
		virtual const char* leaf(const char* path) = 0;//文件名
		virtual const char* stem(const char* path) = 0;//文件名, 去掉后缀
		virtual const char* parent_path(const char* path) = 0;

		virtual const char* normalize(const char* path) = 0;


		/* 作为系统文件*/

		//转为完整路径
		virtual const char* system_complete(const char* path) = 0;
		//是否存在
		virtual bool exists(const char* path) = 0;
		//是否目录
		virtual bool is_directory(const char* path) = 0;
		//目录迭代
		virtual const char* first(const char* path) = 0;
		virtual const char* next() = 0;
	};



	struct i_buffer : public virtual i_ref_counter
	{	
		//指针
		virtual void* ptr() = 0;
		//大小
		virtual long size() = 0;
		//重置大小
		virtual void resize(long sz) = 0;
		//写入
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

	//文件读取
	struct i_pak : public virtual i_ref_counter
	{	
		virtual i_buffer* get_buffer(const char* path) = 0;//return null for no found
		virtual bool exist(const char* path) = 0;
	};



	//接口导出
	struct h_filesystem
	{
		//创造路径
		virtual i_path* create_path() = 0;

		//模块所在的路径
		virtual const char* create_module_path() = 0;
		//工作路径
		virtual const char* create_work_directory() = 0;
		//创造buff
		virtual i_buffer* create_buff(const char* buff, long sz) = 0;
		//创建目录
		virtual bool make_directories(const char* path) = 0;

		//读文件
		virtual i_read_file* create_read_file(const char* path) = 0;
		//写文件
		virtual i_write_file* create_write_file(const char* path, bool append = false) = 0;

		//将目录作为一个pak使用
		virtual i_pak* create_pak(const char* location) = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_filesystem, "filesystem.dll");
