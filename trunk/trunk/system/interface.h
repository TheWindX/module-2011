#pragma once
#include <windows.h>
#include "../head/ref_counter.h"
#include "../head/M_interface.h"
#include "../filesystem/interface.h"

namespace ns_base
{
	struct i_font_info : public virtual i_ref_counter
	{
		virtual bool first() = 0;
		virtual bool next() = 0;
		virtual const char* get_name() = 0;
/************************************************************************/
/*font type
DEVICE_FONTTYPE RASTER_FONTTYPE TRUETYPE_FONTTYPE*/
/************************************************************************/
		virtual long get_type() = 0;
	};


	struct i_os_info : public virtual i_ref_counter
	{	
		virtual long get_major_version() = 0;
		virtual long get_minor_version() = 0;
		virtual long get_build_number() = 0;
	};
	
	struct i_machine_key : public virtual i_ref_counter
	{
		virtual long get_CPU_id() = 0;
		virtual void get_HDD_SN(char buff[14]) = 0;
	};

	struct h_system
	{
		virtual i_machine_key* create_machine_key() = 0;

		virtual i_os_info* create_os_info() = 0;
/************************************************************************/
/* charset
ANSI_CHARSET, DEFAULT_CHARSET, OEM_CHARSET, BALTIC_CHARSET, GB2312_CHARSET, CHINESEBIG5_CHARSET,
EASTEUROPE_CHARSET, GREEK_CHARSET, HANGUL_CHARSET, MAC_CHARSET, RUSSIAN_CHARSET,
SHIFTJIS_CHARSET, SYMBOL_CHARSET, TURKISH_CHARSET, VIETNAMESE_CHARSET, JOHAB_CHARSET,
ARABIC_CHARSET, HEBREW_CHARSET, THAI_CHARSET,*/
/************************************************************************/
		virtual i_font_info* create_font_info(long e_charset) = 0;
		//todo cpu memory HDD monitor...
	};
}

M_DECL(ns_base::h_system, "system.dll");
