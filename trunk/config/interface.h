#pragma once
#include "../head/ref_counter.h"
#include "../head/M_interface.h"

#include "../filesystem/interface.h"


namespace ns_base
{
	struct i_config : public virtual ns_common::i_ref_counter
	{
		//数据访问, 得到当前层次的序列元素(number key)
		virtual int get_idx_count() = 0;

		//回到根结点
		virtual void root_section() = 0;//根结点
		//string key 索引到层次
		virtual void enter_section(const char* key) = 0;
		//number key 索引到层次
		virtual void enter_section_idx(int idx) = 0;
		//离开层次
		virtual void leave_section() = 0;

		//string key 索引到bool值
		virtual bool get_bool(const char* key) = 0;
		//number key 索引到bool值
		virtual bool get_bool_idx(int idx) = 0;

		//string key 索引到int值
		virtual int get_int(const char* key) = 0;
		//number key 索引到int值
		virtual int get_int_idx(int idx) = 0;
		//string key 索引到double值
		virtual double get_double(const char* key) = 0;
		//number key 索引到double值
		virtual double get_double_idx(int idx) = 0;

		//string key 索引到string值
		virtual const char* get_string(const char* key) = 0;
		//number key 索引到string值
		virtual const char* get_string_idx(int idx) = 0;
	};

	struct h_config
	{	
		//从文件读入config
		virtual i_config* create_from_file(const char* path) = 0;
		//从pak读入config
		virtual i_config* create_from_pak(i_pak* pak, const char* path) = 0;
	};
}

M_DECL(ns_base::h_config, "config.dll");
