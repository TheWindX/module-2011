#pragma once
#include "interface.h"

#include "../head/ref_counter.h"

#include "../script/interface.h"

namespace ns_base
{
	struct impl_config : public i_config, public ns_common::impl_ref_counter
	{
		i_lua* m_lua;

		impl_config(i_lua* lua):m_lua(lua){}
		~impl_config(){m_lua->release();}

		//数据访问
		int get_idx_count();

		void root_section();//根结点
		void enter_section(const char* key);
		void enter_section_idx(int idx);
		void leave_section();//向上

		bool get_bool(const char* key);
		bool get_bool_idx(int idx);
		int get_int(const char* key);
		int get_int_idx(int idx);
		double get_double(const char* key);
		double get_double_idx(int idx);
		const char* get_string(const char* key);
		const char* get_string_idx(int idx);

	};

	struct impl_h_config : public h_config
	{
		i_config* create_from_file(const char* path);
		i_config* create_from_pak(i_pak* pak, const char* path);
	};
}