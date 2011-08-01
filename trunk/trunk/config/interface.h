#pragma once
#include "../head/ref_counter.h"
#include "../head/M_interface.h"

#include "../filesystem/interface.h"


namespace ns_base
{
	struct i_config : public virtual ns_common::i_ref_counter
	{
		//���ݷ���, �õ���ǰ��ε�����Ԫ��(number key)
		virtual int get_idx_count() = 0;

		//�ص������
		virtual void root_section() = 0;//�����
		//string key ���������
		virtual void enter_section(const char* key) = 0;
		//number key ���������
		virtual void enter_section_idx(int idx) = 0;
		//�뿪���
		virtual void leave_section() = 0;

		//string key ������boolֵ
		virtual bool get_bool(const char* key) = 0;
		//number key ������boolֵ
		virtual bool get_bool_idx(int idx) = 0;

		//string key ������intֵ
		virtual int get_int(const char* key) = 0;
		//number key ������intֵ
		virtual int get_int_idx(int idx) = 0;
		//string key ������doubleֵ
		virtual double get_double(const char* key) = 0;
		//number key ������doubleֵ
		virtual double get_double_idx(int idx) = 0;

		//string key ������stringֵ
		virtual const char* get_string(const char* key) = 0;
		//number key ������stringֵ
		virtual const char* get_string_idx(int idx) = 0;
	};

	struct h_config
	{	
		//���ļ�����config
		virtual i_config* create_from_file(const char* path) = 0;
		//��pak����config
		virtual i_config* create_from_pak(i_pak* pak, const char* path) = 0;
	};
}

M_DECL(ns_base::h_config, "config.dll");
