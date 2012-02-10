
#pragma once

#include "singleton.h"

namespace ns_core
{
	using namespace ns_base;
	
	const char* value_to_string(st_value v, st_vm* rt);

	//null
	struct st_v_null : public i_value_proto
	{
		const char* get_name(){return "v_null";}
		const char* to_string(st_value, st_vm*);
		
		static st_value make_value()
		{
			st_value ret;
			ret.m_tag = singleton<st_v_null>::instance().m_tag;
			return ret;
		}
	};

	//bool
	struct st_v_bool : public i_value_proto
	{
		const char* get_name(){return "v_bool";}
		const char* to_string(st_value, st_vm*);
		static st_value make_value(bool b)
		{
			st_value ret;
			ret.m_num = b;
			ret.m_tag = singleton<st_v_bool>::instance().m_tag;
			return ret;
		}
	};

	//int
	struct st_v_int : public i_value_proto
	{
		const char* get_name(){return "v_int";}
		const char* to_string(st_value, st_vm*);
		static st_value make_value(s32 val)
		{
			st_value ret;
			ret.m_num = val;
			ret.m_tag = singleton<st_v_int>::instance().m_tag;
			return ret;
		}
	};

	//string
	struct st_v_string : public i_value_proto
	{
		const char* get_name(){return "v_string";}
		const char* to_string(st_value, st_vm*);
		static st_value make_value(const char* val)
		{
			st_value ret;
			ret.m_val = strdup(val);
			ret.m_tag = singleton<st_v_string>::instance().m_tag;
			return ret;
		}

		bool compare(st_value v1, st_value v2);
	};

	//function
	struct st_v_ref : public i_value_proto
	{
		const char* get_name(){return "v_ref";}
		static st_value make_value()
		{
			st_value* pv = new st_value();

			st_value ret;
			ret.m_tag = singleton<st_v_ref>::instance().m_tag;
			ret.m_val = pv;
			return ret;
		}

		static st_value make_value(st_value v)
		{
			st_value* pv = new st_value(v);
			
			st_value ret;
			ret.m_tag = singleton<st_v_ref>::instance().m_tag;
			ret.m_val = pv;
			return ret;
		}

		static st_value make_value(st_value* v)
		{
			st_value ret;
			ret.m_tag = singleton<st_v_ref>::instance().m_tag;
			ret.m_val = v;
			return ret;
		}
	};

	struct st_v_function : public i_value_proto
	{
		const char* get_name(){return "v_function";}
		static st_value make_value(st_vm* rt, st_function_code* func)
		{	
			st_value ret;
			ret.m_val = new st_function_value(rt, func);
			ret.m_tag = singleton<st_v_function>::instance().m_tag;
			return ret;
		}
	};

	struct st_v_primary_function : public i_value_proto
	{
		const char* get_name(){return "v_primary_function";}
		static st_value make_value(f_proto func)
		{
			st_value ret;
			ret.m_val = func;
			ret.m_tag = singleton<st_v_primary_function>::instance().m_tag;
			return ret;
		}
	};

	struct st_v_array : public i_value_proto
	{
		const char* get_name(){return "v_array";}
		static st_value make_value()
		{
			st_value ret;
			ret.m_val = new array<st_value>;
			ret.m_tag = singleton<st_v_array>::instance().m_tag;
			return ret;
		}
		const char* to_string(st_value, st_vm*);
	};

	struct st_value_cmp : public std::binary_function<st_value, st_value, bool>
	{
		st_vm* m_vm;
		st_value_cmp(st_vm* vm):m_vm(vm){};
		bool operator()(const st_value& l, const st_value& r) const
		{
			if(l.m_tag == r.m_tag)
			{
				i_value_proto* pv = m_vm->get_value_proto(l.m_tag);
				return pv->compare(l, r);
			}
			else
			{	
				return l.m_tag<r.m_tag;
			}
		}
	};

	struct st_v_map : public i_value_proto
	{
		const char* get_name(){return "v_map";}
		static st_value make_value(st_vm* vm)
		{
			st_value ret;
			ret.m_val = new st_map<st_value, st_value, st_value_cmp>(st_value_cmp(vm) );
			ret.m_tag = singleton<st_v_map>::instance().m_tag;//TODO 1.需要定制st_value的比较函数, 2. 将来采用hash,
			return ret;
		}
		const char* to_string(st_value, st_vm*);
	};

}