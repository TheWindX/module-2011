#pragma once
//
/*
file: M_interface.h
author: xiaofeng.li
version: 0.1
time: 2011.01.01
*/


/*
usage:
<interface>.h:
	.......
	struct i_user//虚基类
	{
		virtual void foo() = 0;
	}
	.......
	#include "M_interface.h"
	M_DECL(i_user, "dll_test1.dll");//1. 接口类声明

<implement>.h
	.......
	struct i_user_impl : i_user//实现
	{
		void foo()
		{
		std::cout<<"hello, i am i_user insance"<<std::endl;
		}
	};
	.......

<implement>.cpp
	.......
	#include "M_interface.h"
	M_IMPL(i_user, i_user_impl);//2. 接口实现
	M_OPEN();//3. 模块建立


<user>.cpp
	.......
	i_user* p_user;
	ns_base::get(p_user);//4. 接口获得
	p_user->foo();
	.......

*/
#define  WIN32_LEAN_AND_MEAN
#include "windows.h"
#undef WIN32_LEAN_AND_MEAN

namespace ns_base
{
	//接口信息
	const int MAX_PATH_LEN = 256;
	struct st_info_base
	{	
		char m_lib[MAX_PATH_LEN];
		char m_name[MAX_PATH_LEN];
	};

#define M_NAME(T) T

	template<typename T>
	struct st_info : public st_info_base
	{
		T* m_ins;
		static st_info* get_info() {static st_info<T> g_instance; return &g_instance;};

		//to be user overrided
		st_info(){ strcpy(m_lib,"unknown_lib");strcpy(m_name, typeid(T).name() );}
	};

	//链表
	template<typename T>
	struct st_link
	{
		typedef st_link<T> st_node;
		typedef st_node* iterator;
		st_node* m_last;
		T* m_value;
		st_node* m_next;
		iterator m_iter;
		st_link(T* val): m_value(val),m_next(0),m_iter(0){m_last = this;}
		st_link(): m_value(0), m_next(0),m_iter(0){m_last = this;}
		~st_link<T>(){if(m_next)delete m_next;}		
		void push_back(T* val)
		{
			st_node* m_pre = m_last;
			m_last = new st_node(val);
			m_pre->m_next = m_last;
		}
		iterator first()
		{
			m_iter = this;
			return m_iter;
		}
		iterator next()
		{
			m_iter = m_iter->m_next;
			return m_iter;
		}
	};


#define M_ERR_MSG_LIB(lib_name, T_interface)\
	char str_err[1024];\
	sprintf(str_err, "加载%s in %s失败:", T_interface, lib_name);\
	MessageBox(0, str_err, "错误", MB_OK);\
	exit(0);

	//接口管理器
	struct st_manager
	{
		st_link<st_info_base> m_interfaces;

		template<typename T>
			T*	get_interface()
		{
			st_link<st_info_base>::iterator it = m_interfaces.first();
			for(; it!=0; it = m_interfaces.next() )
			{
				st_info<T>* p_info = static_cast<st_info<T>* >(it->m_value);
				if(!p_info) continue;//head
				if(0 == strcmp(p_info->m_name, st_info<T>::get_info()->m_name) )
					return p_info->m_ins;
			}
			return 0;
		}

		static st_manager* get(){static st_manager g_ins; return &g_ins;}
	};

	//接口注册
	template<typename T_interface, typename T_implement>
	struct reg
	{
		T_implement m_impl;
		reg()
		{	
			st_info<T_interface>::get_info()->m_ins = static_cast<T_interface*>(&m_impl);
			st_manager::get()->m_interfaces.push_back(st_info<T_interface>::get_info() );
		}
	};
	
	//接口实现
#define M_IMPL(T_interface, T_implement)\
	static ns_base::reg<T_interface, T_implement> g_impl;


	//接口获得
	typedef st_manager*(*p_finder_t)();
	template<typename T>
		void get(T*& out)
	{
		static T* m_ins = 0;
		if(m_ins) {m_ins = out;}

		char* m_lib_name = st_info<T>::get_info()->m_lib;
		char* m_name = st_info<T>::get_info()->m_name;
		HINSTANCE ins = ::GetModuleHandle(m_lib_name);
		if(!ins)
			ins = ::LoadLibrary(m_lib_name);

		if(!ins)
		{
			M_ERR_MSG_LIB(m_lib_name, m_name);
		}
		p_finder_t p_finder = (p_finder_t) GetProcAddress(ins, "M_open");
		if(p_finder == 0)
		{
			M_ERR_MSG_LIB(m_lib_name, "M_open");
		}
		st_manager* p_mana = (*p_finder)();
		m_ins = p_mana->get_interface<T>();
		if(m_ins == 0)
		{
			M_ERR_MSG_LIB(m_lib_name, m_name);
		}
		out = m_ins;
		return;
	}

	//dll 导出声明
#define M_OPEN()\
	extern "C" __declspec(dllexport)\
	ns_base::st_manager* M_open()\
	{\
	return ns_base::st_manager::get();\
	};




	//接口声明
#define M_DECL(T, lib_name)\
	template<> ns_base::st_info<T>::st_info()\
	{\
	m_ins = 0;\
	strcpy(m_name, #T);\
	strcpy(m_lib,lib_name);\
	}
}
