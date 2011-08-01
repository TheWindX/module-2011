
#include <string>


#include "../head/exception.h"

#include "impl.h"

#include "machine_key.h"
#include "../head/system.h"
#include "../head/exception.h"
#include "../head/utility_new.h"

namespace ns_base
{
	long impl_machine_key::get_CPU_id()
	{
		long ret = 0;
		if(GetCpuId(ret) )
		{
			return ret;
		}
		else
		{
			RAISE_EXCEPTION("");
		}

	}

	void impl_machine_key::get_HDD_SN(char buff[14])
	{
		if(!GetDiskPhysicalSN(buff) )
		{
			RAISE_EXCEPTION("");
		}
	}

	st_os_version::st_os_version()
	{
		m_succ = get_info();
	}

	long impl_os_info::get_major_version()
	{
		if(!m_info.m_succ) {RAISE_EXCEPTION("");}
		return m_info.m_major_version;
	}

	long impl_os_info::get_minor_version()
	{
		if(!m_info.m_succ) {RAISE_EXCEPTION("");}
		return m_info.m_minor_version;
	}

	long impl_os_info::get_build_number()
	{
		if(!m_info.m_succ) {RAISE_EXCEPTION("");}
		return m_info.m_build_number;
	}

	bool impl_font_info::first()
	{
		static std::string ret;
		if(m_font_names.size() == 0)return false;
		m_count = 0;
		return true;
	}

	bool impl_font_info::next()
	{
		static std::string ret;
		if(++m_count == m_font_names.size() )
			return false;
		else
			return true;
	}

	const char* impl_font_info::get_name()
	{
		static std::string ret;
		ret = m_font_names[m_count];
		return ret.c_str();
	}

	long impl_font_info::get_type()
	{
		return m_font_type[m_count];
	}

	impl_font_info::impl_font_info():m_count(0)
	{	
		m_hdc = CreateDC("DISPLAY", "DISPLAY", 0 ,0 );
	}

	impl_font_info::~impl_font_info()
	{
		if(m_hdc)
			DeleteDC(m_hdc);
	}

	const char *setnames[] = {"ANSI", "All Available", "OEM", "Baltic", "Chinese Simplified", "Chinese Traditional",
		"Eastern European", "Greek", "Hangul", "Macintosh", "Russian",
		"Japanese", "Symbol", "Turkish", "Vietnamese", "Johab",
		"Arabic", "Hebrew", "Thai", 0};

	// callback for adding font names
	int CALLBACK EnumFontFamExProc( ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,
		DWORD FontType, LPARAM lParam)
	{
		impl_font_info* t = (impl_font_info*) lParam;
		t->m_font_names.push_back( std::string( (char*)lpelfe->elfFullName) );
		t->m_font_type.push_back(FontType);
		return 1;
	}

	i_machine_key* impl_h_system::create_machine_key()
	{
		impl_machine_key* p_key = new impl_machine_key;
		return p_key;
	}

	i_font_info* impl_h_system::create_font_info(long currentCharSet)
	{
		impl_font_info* ret = new impl_font_info;
		LOGFONT lf;
		lf.lfFaceName[0] = '\0';
		lf.lfCharSet = currentCharSet;
		// HRESULT hr; // no error checking(!)

		// create list of available fonts
		EnumFontFamiliesEx(ret->m_hdc , (LPLOGFONT) &lf, (FONTENUMPROC) EnumFontFamExProc, (LPARAM) ret, 0);
		{
			const char* desc = MakeAPIErrorDesc();
			RAISE_EXCEPTION(desc);
		}
		return ret;
	}

	i_os_info* impl_h_system::create_os_info()
	{
		impl_os_info* p_info = new impl_os_info;
		return p_info;
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

M_IMPL(ns_base::h_system, ns_base::impl_h_system);//2. 接口实现
M_OPEN();//3. 模块建立


