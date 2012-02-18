
#include <cassert>
#include <string>

#include "vm.h"
#include "proto_value.h"


namespace ns_core
{
	const char* value_to_string(st_value v, st_vm* rt)
	{
		if(rt->m_proto_values.size()>v.m_tag)
		{
			i_value_proto* p = rt->m_proto_values[v.m_tag];
			return p->to_string(v, rt);
		}
		else
		{
			return "(NA)";
		}
	}
	
	const char* code_to_string(st_code c, st_vm* rt)
	{
		if(rt->m_proto_codes.size()>c.m_tag)
		{
			i_code_proto* p = rt->m_proto_codes[c.m_tag];
			return p->to_string(c);
		}
		else
		{
			return "(NA)";
		}
	}
	
	const char* st_v_null::to_string(st_value v, st_vm* rt)
	{
		return "null";
	}

	const char* st_v_bool::to_string(st_value v, st_vm* rt)
	{
		if(v.get<bool>() == true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}

	const char* st_v_int::to_string(st_value v, st_vm* rt)
	{
		static char buff[256];
		itoa(v.get<s32>(), buff, 10);
		return buff;
	}

	const char* st_v_string::to_string(st_value v, st_vm* rt)
	{
		return v.get<char*>();
	}

	bool st_v_string::compare(st_value v1, st_value v2)
	{	
		return strcmp(v1.get<char*>(), v2.get<char*>() ) < 0;
	}

	const char* st_v_array::to_string(st_value v, st_vm* rt)
	{
		static std::string sret;
		std::string ret;
		ret = "";

		array<st_value>* vs = v.get<array<st_value>*>();
		assert(vs);
		ret += "[";
		if(vs->size() != 0)
		{
			ret += value_to_string(vs->at(0), rt);
		}
		for(u32 i = 1; i<vs->size(); ++i)
		{
			ret += ", ";
			ret += value_to_string(vs->at(i), rt);
		}
		ret += "]";
		sret = ret;
		return sret.c_str();
	}

	const char* st_v_map::to_string(st_value v, st_vm* rt)
	{
		static std::string sret;
		std::string ret = "m{";
		st_map<st_value, st_value, st_value_cmp>* m = v.get<st_map<st_value, st_value, st_value_cmp>* >();

		bool b = m->first();
		if(b)
		{
			st_value& vk = const_cast<st_value&>(m->get_key() );
			st_value& vv = m->get_val();
			ret += value_to_string(vk, rt);
			ret += ":";
			ret += value_to_string(vv, rt);
		}
		for(b = m->next(); b; b = m->next() )
		{
			ret += ", ";
			st_value& vk = const_cast<st_value&>(m->get_key() );
			st_value& vv = m->get_val();
			ret += value_to_string(vk, rt);
			ret += ":";
			ret += value_to_string(vv, rt);
		}
		ret += "}";
		sret = ret;
		return sret.c_str();
	}

}