
#pragma once

namespace ns_core
{
	struct i_context
	{
		virtual u32 in_size() = 0;

		virtual void* get_value(u32 idx) = 0;
		virtual const char* value_to_string(void*) = 0;

		virtual bool to_int(long idx, int&) = 0;
		virtual bool to_bool(long idx, bool&) = 0;
		virtual bool to_string(long idx, char* buff, long max_sz) = 0;

		virtual void begin_push() = 0;
		virtual void push_bool(bool) = 0;
		virtual void push_int(int) = 0;
		virtual void push_string(const char* str) = 0;
	};

	struct i_functor//Ç¶Èë½Ó¿Ú, to be user override
	{
		virtual void on_eval(i_context* ctx) = 0;
		virtual ~i_functor() {};
	};

	struct impl_context : public i_context
	{
		st_vm* m_vm;

		u32 in_size();

		void* get_value(u32 idx);
		const char* value_to_string(void* v);

		bool to_int(long idx, int&);
		bool to_bool(long idx, bool&);
		bool to_string(long idx, char* buff, long max_sz);

		void begin_push();
		void push_bool(bool);
		void push_int(int);
		void push_string(const char* str);
	};

}


