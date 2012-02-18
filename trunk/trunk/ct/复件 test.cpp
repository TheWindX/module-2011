
#include <iostream>
#include <string>

#include "exception.h"
#include "context.h"
#include "Timer.h"

#include "functor.h"
#include "proto_code.h"

struct st_f_user : public ns_core::i_functor
{
	void on_eval(ns_core::i_context* ctx)
	{
		char buff1[256], buff2[256];
		ctx->to_string(0, buff1, 256);
		ctx->to_string(1, buff2, 256);
		std::string str = buff1;
		str += buff2;
		ctx->begin_push();
		ctx->push_string(str.c_str());
		printf("%s, %s in extern user!\n",buff1, buff2);
	}
};

namespace ns_core
{
	struct st_user_debug : public i_debug
	{
		std::vector<u32> m_breaks;
		size_t m_cur_idx;
		st_context_user* m_context;

		st_user_debug()
		{
			m_cur_idx = 0;
		}

		virtual u32 get_break_idx()//获得断点位置
		{
			if(m_cur_idx<m_breaks.size() )
				return m_breaks[m_cur_idx];
			else return U32_NA;
		}

		virtual void next_break()//步进到下一个断点
		{
			m_cur_idx++;
		}

		virtual void reset()//重置debug, //重置 break indexs
		{
			m_cur_idx = 0;
		}

		virtual u32 on_code(st_vm* vm)//在断点时触发,返回断点处理状态，默认为0
		{
			printf("%d %s\n", vm->s_cur_pc(), code_to_string(vm->s_cur_code(), vm) );
			printf("%s\n\n", m_context->m_debug.code2line(vm->s_cur_pc() ).c_str() );
			if(m_cur_idx == m_breaks.size()-1) return 0;
			return -1;
		}

		void add_break(u32 idx)
		{	
			m_breaks.push_back(idx);
		}
	};
}


int main(int argc, char** argv)
{
	using namespace  ns_core;

	st_f_user f_user;
	st_context_user& user = st_context_user::instance();
	user.get_vm_cons().reg_function("user_f", &f_user);

	st_user_debug dbg;
	dbg.m_context = &user;
	user.get_vm_cons().set_debug(&dbg);
	dbg.add_break(3);
	dbg.add_break(4);
	
	try
	{	
		user.load_file("user_file.txt");
		//user.print_codes();
		u32 rc = user.run();
		while(rc != 0)
		{
			system("pause");
			rc = user.debug_continue();
		}
	}
	catch(st_compile_exception ex)
	{
		std::cout<<ex.m_desc<<std::endl;
	}

	/*try
	{
		user.load_file("user_file.txt");
		//user.print_codes();
		
		u32 sz = user.m_debug.m_src_text.get_line_size();
		for(u32 i = 0; i<sz; ++i)
		{	
			printf("%s\n", user.m_debug.m_src_text.get_line(i) );

			u32 left, right;
			right = user.m_debug.line2code_num(i, left);

			if(right == U32_NA)continue;

			for(u32 j = left; j<right; ++j)
			{
				std::string s = user.get_vm_cons().code_to_string(j);
				printf("%d %s\n", j, s.c_str() );
			}
		}
		//Timer t;
		//t.start();
		//user.run();
		//t.stop();
		//std::cout<<t.getElapsedTime()<<std::endl;
	}
	catch (st_compile_exception ex)
	{
		std::cout<<ex.m_desc<<std::endl;
	}*/
	
	return 0;
}