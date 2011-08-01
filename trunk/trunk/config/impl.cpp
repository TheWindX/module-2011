
#include "../head/exception.h"

#include "impl.h"
#include "../head/utility_new.h"

namespace ns_base
{

	//数据访问
	int impl_config::get_idx_count()
	{
		return m_lua->get_idx_count();
	}

	void impl_config::root_section()//根结点
	{
		m_lua->root_section();
	}

	void impl_config::enter_section(const char* key)
	{
		if(m_lua->enter_section(key) )
		{
			return;
		}
		RAISE_EXCEPTION("");
	}

	void impl_config::enter_section_idx(int idx)
	{
		if(m_lua->enter_section_idx(idx) )
		{
			return;
		}
		RAISE_EXCEPTION("");
	}

	void impl_config::leave_section()//向上
	{
		if(m_lua->leave_section() )
		{
			return;
		}
		RAISE_EXCEPTION("");
	}

	bool impl_config::get_bool(const char* key)
	{
		bool ret = false;
		if(!m_lua->get_bool(key, ret) )
		{
			RAISE_EXCEPTION("");
		}
		return ret;
	}

	bool impl_config::get_bool_idx(int idx)
	{
		bool ret = false;
		if(!m_lua->get_bool_idx(idx, ret) )
		{
			RAISE_EXCEPTION("");
		}
		return ret;
	}

	int impl_config::get_int(const char* key)
	{
		int ret = false;
		if(!m_lua->get_int(key, ret) )
		{
			RAISE_EXCEPTION("");
		}
		return ret;
	}

	int impl_config::get_int_idx(int idx)
	{
		int ret = false;
		if(!m_lua->get_int_idx(idx, ret) )
		{
			RAISE_EXCEPTION("");
		}
		return ret;
	}

	double impl_config::get_double(const char* key)
	{
		double ret = false;
		if(!m_lua->get_double(key, ret) )
		{
			RAISE_EXCEPTION("");
		}
		return ret;
	}

	double impl_config::get_double_idx(int idx)
	{
		double ret = false;
		if(!m_lua->get_double_idx(idx, ret) )
		{
			RAISE_EXCEPTION("");
		}
		return ret;
	}

	const char* impl_config::get_string(const char* key)
	{
		const char* ret = m_lua->get_string(key);
		if(!ret) RAISE_EXCEPTION("");
		return ret;
	}

	const char* impl_config::get_string_idx(int idx)
	{
		const char* ret = m_lua->get_string_idx(idx);
		if(!ret) RAISE_EXCEPTION("");
		return ret;
	}

	i_config* impl_h_config::create_from_file(const char* path)
	{
		h_script* hs;
		get(hs);

		i_lua* p_lua = hs->create_lua_from_file(path);

		impl_config* ret = new impl_config(p_lua);
		return ret;
	}

	i_config* impl_h_config::create_from_pak(i_pak* pak, const char* path)
	{
		h_script* hs;
		get(hs);

		i_buffer* buff = pak->get_buffer(path);
		if(!buff) RAISE_EXCEPTION("");
		
		i_lua* p_lua = hs->create_lua_from_buffer(path, buff);

		impl_config* ret = new impl_config(p_lua);
		return ret;
	}

}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}


#include "../head/M_interface.h"

M_IMPL(ns_base::h_config, ns_base::impl_h_config);//2. 接口实现
M_OPEN();//3. 模块建立


