
#pragma once

#include "interface.h"

#include "value.h"
#include "context.h"
#include "functor.h"
#include "proto_code.h"

#include "exception.h"


namespace ns_base
{
	namespace ns_c_toy
	{
		using namespace ns_core;
		using namespace ns_base;
		struct impl_context : public i_context
		{
			ns_core::i_context* m_ctx;
			impl_context(ns_core::i_context* ctx):m_ctx(ctx){}
			
			long in_size(){return m_ctx->in_size(); };

			bool to_int(long idx, int& o){return m_ctx->to_int(idx, o); };
			bool to_bool(long idx, bool& o){return m_ctx->to_bool(idx, o); };
			bool to_string(long idx, char* buff, long max_sz){return m_ctx->to_string(idx, buff, max_sz); };

			const char* to_printable_string(long idx)
			{
				return m_ctx->value_to_string(m_ctx->get_value(idx) );
			}

			void begin_push(){m_ctx->begin_push();};
			void push_bool(bool b){m_ctx->push_bool(b);};
			void push_int(int i){m_ctx->push_int(i);};
			void push_string(const char* str){m_ctx->push_string(str); };
		};

		//extern functor adaptor
		struct st_functor_template : public ns_core::i_functor
		{
			ns_base::ns_c_toy::i_functor* m_functor;
			ns_base::ns_c_toy::i_context* m_ctx;

			st_functor_template(ns_base::ns_c_toy::i_functor* functor,
				ns_base::ns_c_toy::i_context* ctx):m_functor(functor),m_ctx(ctx){}

			void on_eval(ns_core::i_context* ctx){return m_functor->on_eval(m_ctx);}
		};

		struct st_debug : public ns_core::i_debug
		{
			array<u32> m_breaks;
			u32 m_cur_idx;
			ns_core::st_context_user* m_context;
			bool m_step;

			st_debug(ns_core::st_context_user* ctx):m_context(ctx),m_cur_idx(0),m_step(false){};

			virtual bool is_step();//是否每一步设断点
			virtual u32 get_break_idx();
			virtual void next_break();
			virtual void reset();
			virtual u32 on_code(ns_core::st_vm* vm);//在断点时触发,返回断点处理状态，默认为0

			void set_step(bool is_step){m_step = is_step;}
			void set_break_on(u32 idx, bool on_off);//设置断点
			void clear_breaks();//清除断点
		};

		struct h_impl_c_toy : public h_c_toy
		{	
			ns_core::st_context_user* m_user;
			std::string m_last_error;
			std::vector<ns_core::i_functor*> m_functors;//functors
			ns_c_toy::i_context* m_ctx;//context for extern plug in
			st_debug* m_debug;
			h_impl_c_toy()
			{
				m_user = &ns_core::st_context_user::instance();
				m_ctx = new ns_c_toy::impl_context(m_user->get_vm_cons().get_i_context() );
				m_debug = new st_debug(m_user);
			}

			~h_impl_c_toy()
			{
				for(size_t i = 0; i<m_functors.size(); ++i)
				{
					delete m_functors[i];
				}
				delete m_ctx;
				delete m_debug;
			}

			//plug in
			void reg_functor(const char* reg_name, i_functor* f);

			//load script and run
			bool load_buff(const char* buff, long sz);
			bool load_string(const char* str);
			bool load_file(const char* fname);
			bool run();

			//debug
			void debug_step(bool is_step);
			void debug_set_break(long idx, bool open_close);
			void debug_clear_breaks();
			bool debug_run();
			bool debug_continue();

			const char* get_last_error();


			//vm states
			long get_local_size();
			const char* get_local_value_string(long idx);
			long get_eval_size();
			const char* get_eval_value_string(long idx);
			long get_ref_size();
			const char* get_ref_value_string(long idx);
			long get_pc();
			const char* get_current_code_string();


			//code src map
			long get_code_size();
			const char* get_code_string(long idx);
			long get_src_line_size();
			const char* get_src_line_string(long ln);
			long src_to_code(long ln, long& left);//return right
			long code_to_src(long ln);
		};

		h_c_toy* get_handler()
		{
			static h_impl_c_toy instance;
			return &instance;
		}
	}
}