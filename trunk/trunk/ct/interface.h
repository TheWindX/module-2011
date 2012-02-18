
#pragma once

namespace ns_base
{
	namespace ns_c_toy
	{
		struct i_context;
		struct i_functor//Ç¶Èë½Ó¿Ú, to be user override
		{
			virtual void on_eval(i_context* ctx) = 0;
		};

		struct i_context
		{
			virtual long in_size() = 0;

			virtual bool to_int(long idx, int&) = 0;
			virtual bool to_bool(long idx, bool&) = 0;
			virtual bool to_string(long idx, char* buff, long max_sz) = 0;

			virtual const char* to_printable_string(long idx) = 0;

			virtual void begin_push() = 0;
			virtual void push_bool(bool) = 0;
			virtual void push_int(int) = 0;
			virtual void push_string(const char* str) = 0;
		};

		struct h_c_toy
		{	
			//plug in
			virtual void reg_functor(const char* reg_name, i_functor* f) = 0;

			//load script and run
			virtual bool load_buff(const char* buff, long sz) = 0;
			virtual bool load_string(const char* str) = 0;
			virtual bool load_file(const char* fname) = 0;
			virtual bool run() = 0;

			//debug
			virtual void debug_step(bool is_step) = 0;
			virtual void debug_set_break(long idx, bool open_close) = 0;
			virtual void debug_clear_breaks() = 0;
			virtual bool debug_run() = 0;
			virtual bool debug_continue() = 0;

			virtual const char* get_last_error() = 0;


			//vm states
			virtual long get_local_size() = 0;
			virtual const char* get_local_value_string(long idx) = 0;
			virtual long get_eval_size() = 0;
			virtual const char* get_eval_value_string(long idx) = 0;
			virtual long get_ref_size() = 0;
			virtual const char* get_ref_value_string(long idx) = 0;
			virtual long get_pc() = 0;
			virtual const char* get_current_code_string() = 0;


			//code src map
			virtual long get_code_size() = 0;
			virtual const char* get_code_string(long idx) = 0;
			virtual long get_src_line_size() = 0;
			virtual const char* get_src_line_string(long ln) = 0;
			virtual long src_to_code(long ln, long& left) = 0;//return right
			virtual long code_to_src(long ln) = 0;
		};

		//h_c_toy* get_handler();
	}
}

#include "../head/M_interface.h"
M_DECL(ns_base::ns_c_toy::h_c_toy, "c_toy.dll");