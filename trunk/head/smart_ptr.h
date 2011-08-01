#pragma once


namespace ns_common
{
	template<class T> class smart_ptr
	{
	private:

		typedef smart_ptr this_type;
		void swap(smart_ptr & rhs)
		{
			T * tmp = m_ptr;
			m_ptr = rhs.m_ptr;
			rhs.m_ptr = tmp;
		}
	public:

		typedef T element_type;

		smart_ptr(): m_ptr( 0 )
		{
		}

		smart_ptr( T * p, bool add_ref = false ): m_ptr( p )
		{
			if( m_ptr != 0 && add_ref ) smart_ptr_add_ref( m_ptr );
		}

		smart_ptr(smart_ptr const & rhs): m_ptr( rhs.m_ptr )
		{
			if( m_ptr != 0 ) smart_ptr_add_ref( m_ptr );
		}

		~smart_ptr()
		{
			if( m_ptr != 0 ) smart_ptr_release( m_ptr );
		}

		smart_ptr & operator=(smart_ptr const & rhs)
		{
			this_type(rhs).swap(*this);
			return *this;
		}

		smart_ptr & operator=(T * rhs)
		{
			this_type(rhs).swap(*this);
			return *this;
		}

		void reset()
		{
			this_type().swap( *this );
		}

		void reset( T * rhs )
		{
			this_type( rhs ).swap( *this );
		}

		T * get() const
		{
			return m_ptr;
		}

		T & operator*() const
		{
			return *m_ptr;
		}

		T * operator->() const
		{	
			return m_ptr;
		}

		operator bool () const
		{
			return m_ptr != 0;
		}

		bool operator! () const
		{
			return m_ptr == 0;
		}


		T * m_ptr;
	};

	template<class T, class U> inline bool operator==(smart_ptr<T> const & a, smart_ptr<U> const & b)
	{
		return a.get() == b.get();
	}

	template<class T, class U> inline bool operator!=(smart_ptr<T> const & a, smart_ptr<U> const & b)
	{
		return a.get() != b.get();
	}

	template<class T, class U> inline bool operator==(smart_ptr<T> const & a, U * b)
	{
		return a.get() == b;
	}

	template<class T, class U> inline bool operator!=(smart_ptr<T> const & a, U * b)
	{
		return a.get() != b;
	}

	template<class T, class U> inline bool operator==(T * a, smart_ptr<U> const & b)
	{
		return a == b.get();
	}

	template<class T, class U> inline bool operator!=(T * a, smart_ptr<U> const & b)
	{
		return a != b.get();
	}


	template<class T> inline bool operator<(smart_ptr<T> const & a, smart_ptr<T> const & b)
	{
		return std::less<T *>()(a.get(), b.get());
	}

	template<class T> void swap(smart_ptr<T> & lhs, smart_ptr<T> & rhs)
	{
		lhs.swap(rhs);
	}

	template<class T> T * get_pointer(smart_ptr<T> const & p)
	{
		return p.get();
	}

	template<class T, class U> smart_ptr<T> static_pointer_cast(smart_ptr<U> const & p)
	{
		return static_cast<T *>(p.get());
	}

	template<class T, class U> smart_ptr<T> const_pointer_cast(smart_ptr<U> const & p)
	{
		return const_cast<T *>(p.get());
	}

	template<class T, class U> smart_ptr<T> dynamic_pointer_cast(smart_ptr<U> const & p)
	{
		return dynamic_cast<T *>(p.get());
	}
}