#pragma once

#include <cassert>

#include <queue>
#include <stack>

#include <windows.h>


namespace ns_common
{
	//线程锁
	class locker
	{
	public:
		CRITICAL_SECTION* m_p_CS;
		bool m_bLocked;
		locker(CRITICAL_SECTION* p,bool bLock = true)
		{
			assert(p);
			m_p_CS = p;
			m_bLocked = false;
			if (bLock)
			{
				lock();
			}
		};
		locker()
		{
			m_p_CS = 0;
			m_bLocked = false;
		}
		void lock(CRITICAL_SECTION* p)
		{
			m_p_CS = p;
			lock();
		}
		virtual ~locker()
		{
			unlock();
		}
		void lock()
		{
			if (m_p_CS)
			{
				EnterCriticalSection(m_p_CS);		
				m_bLocked = true;
			}
		}
		void unlock()
		{
			if (m_bLocked)
			{
				if (m_p_CS)
					LeaveCriticalSection(m_p_CS);	
				m_p_CS = 0;
				m_bLocked = false;
			}
		}
	};

	//线程安全队列
	template<typename T>
	class safe_queue
	{
	public:
		CRITICAL_SECTION m_cs;
		safe_queue() {InitializeCriticalSection(&m_cs);} 
		~safe_queue(){DeleteCriticalSection(&m_cs);}

		void push(T p) {locker lock(&m_cs);
		m_queue.push(p);};
		bool pop(T& p) {		
			locker lock(&m_cs);
			if (!front(p))
				return false;
			m_queue.pop();
			return true;};

			bool front(T& p) {	if (m_queue.empty())
				return false;
			p = m_queue.front();
			return true;}

			bool front(T* p) {	if (m_queue.empty())
				return false;
			p = &(m_queue.front() );
			return true;}

			void pop(){locker lock(&m_cs);m_queue.pop();}
			size_t size(){return m_queue.size();}

			std::queue<T> m_queue;
	};

	//线程安全堆栈
	template<typename T>
	class safe_stack
	{
	public:
		CRITICAL_SECTION m_cs;
		safe_stack() {InitializeCriticalSection(&m_cs);} 
		~safe_stack(){DeleteCriticalSection(&m_cs);}

		virtual void push(T p) {locker lock(&m_cs);
		m_stack.push_back(p);
		};

		virtual  bool pop(T& p) {		
			locker lock(&m_cs);
			if (m_stack.empty())
				return false;
			p = m_stack.back();
			m_stack.pop_back();
			return true;
		};
		void clear(){m_stack.clear();}
		bool empty(){return m_stack.empty();}

		std::deque<T> m_stack;
	};


}


