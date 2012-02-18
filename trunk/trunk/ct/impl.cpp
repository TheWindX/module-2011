
#include "impl.h"

#include "context.h"
#include "proto_code.h"
#include "proto_value.h"

namespace ns_base
{
	namespace ns_c_toy
	{
		bool st_debug::is_step()//是否每一步设断点
		{
			return m_step;
		}

		u32 st_debug::get_break_idx()//获得断点位置
		{
			if(m_cur_idx<m_breaks.size() )
				return m_breaks[m_cur_idx];
			else return U32_NA;
		}

		void st_debug::next_break()//步进到下一个断点
		{
			m_cur_idx++;
		}

		void st_debug::reset()//重置debug, //重置 break indexs
		{
			m_cur_idx = 0;
		}

		u32 st_debug::on_code(st_vm* vm)//在断点时触发,返回断点处理状态，默认为0
		{
			if(m_cur_idx == m_breaks.top_idx() ) return 0;
			return -1;
		}

		void st_debug::set_break_on(u32 idx, bool on_off)
		{	
			u32 bidx = m_breaks.find(idx);
			if(bidx != U32_NA)
			{
				if(!on_off)
					m_breaks.erase(bidx);
			}
			else
			{
				if(on_off) m_breaks.push(idx);
			}
		}

		void st_debug::clear_breaks()//清除断点
		{
			m_breaks.clear();
		}

		//plug in
		void h_impl_c_toy::reg_functor(const char* reg_name, i_functor* f)
		{
			st_functor_template* fvm = new st_functor_template(f, m_ctx);
			m_functors.push_back(fvm);
			m_user->get_vm_cons().reg_function(reg_name, fvm);
		}

		//load script and run
		bool h_impl_c_toy::load_buff(const char* buff, long sz)
		{
			try{
				m_user->load_buffer(buff, sz);
				return true;
			}
			catch(st_compile_exception& ex)
			{
				m_last_error = ex.m_desc;
				return false;
			}
		}

		bool h_impl_c_toy::load_string(const char* str)
		{
			try{
				m_user->load_string(str);
				return true;
			}
			catch(st_compile_exception& ex)
			{
				m_last_error = ex.m_desc;
				return false;
			}
		}

		bool h_impl_c_toy::load_file(const char* fname)
		{
			try{
				m_user->load_file(fname);
				return true;
			}
			catch(st_compile_exception& ex)
			{
				m_last_error = ex.m_desc;
				return false;
			}
		}

		bool h_impl_c_toy::run()
		{
			m_user->get_vm_cons().set_debug(0);
			try{m_user->run(); return true;}
			catch(st_compile_exception& ex)
			{
				m_last_error = ex.m_desc;
				return false;
			}
			return true;
		}

		void h_impl_c_toy::debug_step(bool is_step)
		{
			return m_debug->set_step(is_step);
		}

		//debug
		void h_impl_c_toy::debug_set_break(long idx, bool open_close)
		{
			m_debug->set_break_on(idx, open_close);
		}

		void h_impl_c_toy::debug_clear_breaks()
		{
			m_debug->clear_breaks();
		}

		bool h_impl_c_toy::debug_run()
		{
			m_user->get_vm_cons().set_debug(m_debug);
			m_user->get_vm_cons().apply_instant();
			if(m_user->get_vm_cons().eval() == 0)
				return true;
			else
				return false;
		}

		bool h_impl_c_toy::debug_continue()
		{
			if(m_user->get_vm_cons().eval(true) == 0)
				return true;
			else
				return false;
		}

		const char* h_impl_c_toy::get_last_error()
		{
			return m_last_error.c_str();
		}

		//vm states
		long h_impl_c_toy::get_local_size()
		{
			return m_user->get_vm_cons().get_local_size();
		}

		const char* h_impl_c_toy::get_local_value_string(long idx)
		{
			ns_core::st_value& v = m_user->get_vm_cons().get_local(idx);
			return ns_core::value_to_string(v, &m_user->get_vm_cons() );
		}

		long h_impl_c_toy::get_eval_size()
		{
			return m_user->get_vm_cons().get_eval_size();
		}

		const char* h_impl_c_toy::get_eval_value_string(long idx)
		{
			ns_core::st_value& v = m_user->get_vm_cons().get_eval(idx);
			return ns_core::value_to_string(v, &m_user->get_vm_cons() );
		}

		long h_impl_c_toy::get_ref_size()
		{
			return m_user->get_vm_cons().get_ref_size();
		}

		const char* h_impl_c_toy::get_ref_value_string(long idx)
		{
			ns_core::st_value& v = m_user->get_vm_cons().get_ref(idx);
			return ns_core::value_to_string(v, &m_user->get_vm_cons() );
		}

		long h_impl_c_toy::get_pc()
		{
			return m_user->get_vm_cons().s_cur_pc();
		}

		const char* h_impl_c_toy::get_current_code_string()
		{
			ns_core::st_code c = m_user->get_vm_cons().s_cur_code();
			return ns_core::code_to_string(c, &m_user->get_vm_cons() );
		}

		//code src map
		long h_impl_c_toy::get_code_size()
		{
			return m_user->get_vm_cons().get_code_size();
		}

		const char* h_impl_c_toy::get_code_string(long idx)
		{
			static std::string str;
			str = m_user->get_vm_cons().code_to_string(idx);
			return str.c_str();
		}

		long h_impl_c_toy::get_src_line_size()
		{
			return m_user->m_debug.m_src_text.get_line_size();
		}

		const char* h_impl_c_toy::get_src_line_string(long ln)
		{
			return m_user->m_debug.m_src_text.get_line(ln);
		}

		long h_impl_c_toy::src_to_code(long ln, long& left)
		{
			u32 left_;
			u32 right = m_user->m_debug.line2code_num(ln, left_);
			left = left_;
			return right;
		}

		long h_impl_c_toy::code_to_src(long ln)
		{
			return m_user->m_debug.code2line_num(ln);
		}
	}
}

#include "../head/M_interface.h"

M_IMPL(ns_base::ns_c_toy::h_c_toy, ns_base::ns_c_toy::h_impl_c_toy);//2. 接口实现
M_OPEN();//3. 模块建立