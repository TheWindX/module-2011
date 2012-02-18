
#include "vm.h"

#include "proto_value.h"


namespace ns_core
{
	u32 st_vm_plugs::reg_proto_code(i_code_proto* code)
	{
		u32 new_id = m_proto_codes.size();
		m_proto_codes.push(code);
		code->m_tag = new_id;
		return new_id;
	}

	u32 st_vm_plugs::reg_proto_value(i_value_proto* value)
	{
		u32 new_id = m_proto_values.size();
		m_proto_values.push(value);
		value->m_tag = new_id;
		return new_id;
	}

	i_code_proto* st_vm_plugs::get_code_proto(u32 tag_id)
	{
		return m_proto_codes[tag_id];
	}

	i_value_proto* st_vm_plugs::get_value_proto(u32 tag_id)
	{
		return m_proto_values[tag_id];
	}

	u32 st_vm_plugs::reg_function(const char* func_name, f_proto func)
	{
		ns_core::st_sym_var* var = m_symbols.reg_global_name(func_name);
		u32 id = var->g.path->get_id();
		if(m_globals.size() <= id) m_globals.resize(id+1);

		st_value& v = get_global(id );
		v = st_v_primary_function::make_value(func);
		return id;
	}

	u32 st_vm_plugs::reg_function(const char* func_name, i_functor* f)//TODO
	{
		ns_core::st_sym_var* var = m_symbols.reg_global_name(func_name);
		u32 id = var->g.path->get_id();
		if(m_globals.size() <= id) m_globals.resize(id+1);

		st_value& v = get_global(id );
		v = st_v_extern_function::make_value(f);
		return id;
	}

	ns_core::st_sym_var* st_vm_plugs::reg_global(const char* func_name)
	{
		ns_core::st_sym_var* v = m_symbols.reg_global_name(func_name);
		u32 id = v->g.path->get_id();
		if(m_globals.size() <= id) m_globals.resize(id+1);
		return v;
	}
}