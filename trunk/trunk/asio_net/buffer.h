
#pragma once

#include <cstdio>
#include <cstdlib>
#include <memory.h>

#include "allocator.h"
#include "../head/thread.h"

namespace ns_common
{
	const int MAX_NODE_SZ = 1024;

	using ns_common::locker;
	struct st_node
	{
		st_node* pre;
		st_node* next;
		char buff[MAX_NODE_SZ];

		st_node():pre(0),next(0){}
	};

	struct st_dequeue
	{
		CRITICAL_SECTION m_cs;

		st_node* m_first;
		st_node* m_last;
		long m_left;
		long m_right;
		long m_sz;

		st_dequeue()
		{
			InitializeCriticalSection(&m_cs);
			m_first = new st_node;
			m_last = m_first;
			m_left = 0;
			m_right = 0;
			m_sz = 0;
		}
		~st_dequeue()
		{
			DeleteCriticalSection(&m_cs);
			
			st_node* cur = m_first;
			while(cur != m_last)
			{	
				cur = cur->next;
				delete cur->pre;
			}
			delete cur;
		}

		void push_front(char* buff, long sz)
		{
			locker lock(&m_cs);
			long sz_cur = sz;
			while(sz_cur>m_left)
			{
				sz_cur -= m_left;
				memcpy(m_first->buff, buff+sz_cur, m_left);
				st_node* pnode = new st_node;
				pnode->next = m_first;
				m_first->pre = pnode;
				m_left = MAX_NODE_SZ;
				m_first = pnode;
			}
			m_left = m_left-sz_cur;
			memcpy(m_first->buff+m_left, buff, sz_cur);
			m_sz += sz;
		}

		void push_back(const char* buff, long sz)
		{
			locker lock(&m_cs);
			char* buff_idx = const_cast<char*>(buff);
			long sz_cur = sz;
			while(sz_cur>MAX_NODE_SZ-m_right)
			{
				memcpy(m_last->buff+m_right, buff_idx, MAX_NODE_SZ-m_right);
				sz_cur -= MAX_NODE_SZ-m_right;
				buff_idx += MAX_NODE_SZ-m_right;

				st_node* pnode = new st_node;
				pnode->pre = m_last;
				m_last->next = pnode;
				m_right = 0;
				m_last = pnode;
			}
			memcpy(m_last->buff+m_right, buff_idx, sz_cur);
			m_right += sz_cur;
			m_sz += sz;
		}

		bool pop_front(char* buff, long sz)
		{
			locker lock(&m_cs);
			if(sz>size() )
				return false;

			char* buff_idx = buff;
			long sz_cur = sz;

			while(sz_cur>MAX_NODE_SZ-m_left)
			{
				memcpy(buff_idx, m_first->buff, MAX_NODE_SZ-m_left);
				buff_idx += MAX_NODE_SZ-m_left;
				sz_cur -= MAX_NODE_SZ-m_left;
				m_first = m_first->next;
				delete m_first->pre;
				m_first->pre = 0;
				m_left = 0;
			}

			memcpy(buff_idx, m_first->buff+m_left, sz_cur);
			m_left += sz_cur;
			m_sz -= sz;
			return true;
		}

		bool pop_back(char* buff, long sz)
		{
			locker lock(&m_cs);
			if(sz>size() )
				return false;

			long sz_cur = sz;

			while(sz_cur>m_right)
			{
				sz_cur -= m_right;
				memcpy(buff+sz_cur, m_last->buff, m_right);
				m_last = m_last->pre;
				delete m_last->next;
				m_last->next = 0;
				m_right = MAX_NODE_SZ;
			}

			memcpy(buff, m_last->buff+m_right-sz_cur, sz_cur);
			m_right -= sz_cur;
			m_sz -= sz;
			return true;
		}


		long size()
		{
			return m_sz;
		}

		void clear()
		{
			locker lock(&m_cs);
			if(m_sz>0)
			{
				st_node* it = this->m_first;
				while(it != m_last)
				{
					st_node* next = it->next;
					delete it;
				}
			}
			
			m_first = m_last;
			m_left = 0;
			m_right = 0;
			m_sz = 0;
		}
	};
}
