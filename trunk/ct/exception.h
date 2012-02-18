
#pragma once


struct st_compile_exception
{
	enum {e_comile_err=0, e_runtime_err};
	int m_type;
	std::string m_desc;
};
