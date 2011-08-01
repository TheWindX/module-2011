#pragma once
#include "interface.h"
#include <vector>
#include <string>

#include "machine_key.h"
#include "../head/system.h"

namespace ns_base
{

	struct impl_machine_key : public i_machine_key, public virtual ns_common::impl_ref_counter
	{	
		long get_CPU_id();
		void get_HDD_SN(char buff[14]);
	};

	struct st_os_version
	{
		bool m_succ;
		long m_major_version;
		long m_minor_version;
		long m_build_number;
		bool get_info()
		{
			OSVERSIONINFOEX info;
			::ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
			info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);


			if( !(::GetVersionEx ((OSVERSIONINFO *) &info)) )
			{
				// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
				info.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
				if (!::GetVersionEx ( (OSVERSIONINFO *) &info) ) 
				{
					const char* desc = MakeAPIErrorDesc();
					RAISE_EXCEPTION(desc);
					m_succ = false;
					return false;
				}
			}
			m_major_version = info.dwMajorVersion;
			m_minor_version = info.dwMinorVersion;
			m_build_number = info.dwBuildNumber;
			return true;
		}

		st_os_version();
	};
	struct impl_os_info : public i_os_info, public virtual ns_common::impl_ref_counter
	{
		st_os_version m_info;
		long get_major_version();
		long get_minor_version();
		long get_build_number();
	};

	struct impl_font_info : public i_font_info, public virtual ns_common::impl_ref_counter
	{
		std::vector<std::string> m_font_names;
		std::vector<long> m_font_type;
		
		size_t m_count;
		HDC m_hdc;

		bool first();
		bool next();

		const char* get_name();
		long get_type();

		impl_font_info();
		~impl_font_info();
	};


	struct impl_h_system : public h_system
	{
		i_machine_key* create_machine_key();
		i_font_info* create_font_info(long char_set);
		i_os_info* create_os_info();
	};


}