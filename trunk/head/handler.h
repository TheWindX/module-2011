#pragma once
namespace ns_common
{
	//internal, do not use
	struct i_handler_service
	{
		virtual unsigned int reg(void* p) = 0;

		virtual void* get(unsigned int id) = 0;
		virtual bool rlease(unsigned int id) = 0;

		template<typename T> static i_handler_service* instance();
	};

	template<typename T>
	struct handler
	{
		unsigned int id;
		T* get()
		{
			return (T*)(i_handler_service::instance<T>()->get(id) );
		}

		bool release()
		{
			return i_handler_service::instance<T>()->rlease(id);
		}
	};

#define IMPL_HANDLER_SEVICE(T)\
	struct T : public ns_common::i_handler_service\
	{\
		static boost::unordered_map<unsigned int, void*> m_objs_managed;\
		static unsigned int m_id_count;\
		\
		unsigned int reg(void* p)\
		{\
			m_objs_managed.insert(std::make_pair(m_id_count, p) );\
			int rid = m_id_count++;\
			return rid;\
		}\
		void* get(unsigned int id)\
		{\
			boost::unordered_map<size_t, void*>::iterator it = m_objs_managed.find(id);\
			if(it != m_objs_managed.end() )\
			{\
				return it->second;\
			}\
			return 0;\
		}\
		\
		bool rlease(unsigned int id)\
		{\
			boost::unordered_map<unsigned int, void*>::iterator it = m_objs_managed.find(id);\
			if(it != m_objs_managed.end() )\
			{\
				delete it->second;\
				m_objs_managed.erase(it);\
				return true;\
			}\
			return false;\
		}\
	};\
	boost::unordered_map<unsigned int, void*> T::m_objs_managed;\
	unsigned int T::m_id_count;\
	static T _##T;
}

/************************************************************************/
/*useage:
1. interface.h模块里定义service接口, interface.h文件
virtual i_handler_service* get_handler_service() = 0;

2. interface.h, handler特化
namespace ns_common
{
	using namespace ns_data_structure;
	template<> i_handler_service* i_handler_service::instance<i_test>()
	{
		i_data* p_data;
		ns_module::get(p_data);
		return p_data->get_handler_service();
	}
}

3. implemnet.h, service接口实现
IMPL_HANDLER_SEVICE(impl_handler_service);
i_handler_service* impl_xxx::get_handler_service()
{
	return &_impl_handler_service;
}
*/
/************************************************************************/



