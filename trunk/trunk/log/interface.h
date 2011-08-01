#pragma once
#include "../head/ref_counter.h"
#include "../head/delegate.h"
#include "../head/handler.h"
#include "../head/M_interface.h"

namespace ns_base
{	
	enum
	{
		e_info = 0,
		e_warning,
		e_error,
		e_fatal,
	};

	//请在h_driver中使用;
	//default using as %time, %text, %name, %level
	struct h_logger
	{
		enum
		{
			stage_level = 0x05,
		};
		//set up for console out
		virtual void console_on(const char* name, bool on = true) = 0;
		virtual bool is_console_on(const char* name) = 0;

		virtual void set_console_lv(const char* name, int lv) = 0;
		virtual int get_console_lv(const char* name) = 0;

		virtual void set_console_color_for_name(const char* name, int fc, int bc) = 0;
		virtual void get_console_color_for_name(const char* name, int& fc, int& bc) = 0;

		//virtual void set_console_color_for_lv(int lv, int fc, int bc) = 0;
		//virtual void get_console_color_for_lv(int lv, int& fc, int& bc) = 0;
		//todo, toggle color setup between for name or for lv

		virtual void set_console_format(const char* name, const char* format) = 0;
		virtual const char* get_console_format(const char* name) = 0;

		
		

		//set up for file out
		virtual void file_on(const char* name, bool on = true) = 0;
		virtual bool is_file_on(const char* name) = 0;

		virtual void set_file_lv(const char* name, int lv) = 0;
		virtual int get_file_lv(const char* name) = 0;

		virtual void set_file_format(const char* name, const char* format) = 0;
		virtual const char* get_file_format(const char* name) = 0;

		//write
		virtual void write(const char* name, int lv, const char* cont) = 0;

		//app退出前的清理
		virtual void release() = 0;
	};
}


#include "../head/M_interface.h"
M_DECL(ns_base::h_logger, "logger.dll");
