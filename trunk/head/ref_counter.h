#pragma once
/*#include <iostream>*/

//disable virtual inherite warning
#pragma warning(disable:4250)


namespace ns_common
{
	struct i_ref_counter
	{
		virtual void add_ref() = 0;
		virtual bool release() = 0;
		virtual long get_count() = 0;
	};

	struct impl_ref_counter : public virtual i_ref_counter
	{
	public:
		impl_ref_counter()
			: m_debug_name(0), m_counter(1){}
		
		virtual ~impl_ref_counter(){}

		void add_ref() { ++m_counter;/*std::cout<<"m_counter:"<<m_counter<<std::endl;*/}
		bool release() 
		{	
			--m_counter;
			/*std::cout<<"m_counter:"<<m_counter<<std::endl;*/
			if (!m_counter)
			{
				delete this;
				return true;
			}
			return false;
		}
		
		long get_count() 
		{
			return m_counter;
		}

		const char* get_debug_name() 
		{
			return m_debug_name;
		}

	protected:
		void set_debug_name(const char* newName)
		{
			m_debug_name = newName;
		}

	private:
		const char* m_debug_name;
		long m_counter;
	};

	template <typename T> void smart_ptr_add_ref(T* t) 
	{	t->add_ref();	} 
	template <typename T> void smart_ptr_release(T* t) 
	{	t->release();	}
}