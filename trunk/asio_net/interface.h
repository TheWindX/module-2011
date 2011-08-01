#pragma once

#include "../head/delegate.h"
#include "../head/ref_counter.h"


namespace ns_base
{
	struct i_endpoint : public virtual ns_common::i_ref_counter
	{
		virtual bool from_string(const char* str_ip, unsigned short port) = 0;

		virtual unsigned long to_ulong() = 0;
		virtual const char* to_string() = 0;
		virtual unsigned short get_port() = 0;
	};

	struct i_resolver : public virtual ns_common::i_ref_counter
	{
		ns_delegate::Delegate<void(void)> s_timeout;
		ns_delegate::Delegate<void(void)> s_done;
		ns_delegate::Delegate<void(long)> s_error;

		virtual i_endpoint* first() = 0;
		virtual i_endpoint* next() = 0;

		virtual void resolve(unsigned long timeout) = 0;
	};

	struct i_session
	{
		ns_delegate::Delegate<void(long)> s_error;
		ns_delegate::Delegate<void(long)> s_recv;
		ns_delegate::Delegate<void(long)> s_send;

		virtual size_t get_recv_buffer_size() = 0;
		virtual size_t recv(char* buff, size_t sz) = 0;
		virtual void send(char* buff, size_t sz) = 0;

		virtual i_endpoint* get_local_endpoint() = 0;
		virtual i_endpoint* get_remote_endpoint() = 0;
		
		enum
		{
			e_exception = 0,
			e_establish,
			e_close,
		};
		virtual int statu() = 0;
		virtual void close() = 0;
	};

	struct i_client : public virtual ns_common::i_ref_counter
	{
		ns_delegate::Delegate<void(void)> s_timeout;
		ns_delegate::Delegate<void(void)> s_done;
		ns_delegate::Delegate<void(long)> s_error;
		ns_delegate::Delegate<void(void)> s_session_break;


		virtual void connect(i_endpoint* ep, size_t timeout) = 0;
		virtual i_session* get_session() = 0;
		virtual void release_session() = 0;
	};

	struct i_server : public virtual ns_common::i_ref_counter
	{
		//ns_delegate::Delegate<void(void)> s_bind_error;
		ns_delegate::Delegate<void(long)> s_accept;
		ns_delegate::Delegate<void(long)> s_error;
		ns_delegate::Delegate<void(long)> s_session_break;
		
		virtual bool bind(unsigned short port) = 0;
		virtual void listen(bool blisten) = 0;

		virtual i_session* get_session(int id) = 0;
		virtual i_session* first_session() = 0;
		virtual i_session* next_session() = 0;
		virtual void remove_session(int id) = 0;
	};


	//接口导出 
	struct h_asio_net
	{
		virtual i_resolver* create_resolver1(const char* addr, const char* protocol) = 0;
		virtual i_resolver* create_resolver2(const char* addr, unsigned short port) = 0;
		virtual i_resolver* create_resolver3(unsigned long ip, unsigned short port) = 0;

		virtual i_endpoint* create_endpoint() = 0;

		virtual i_client* create_client() = 0;
		virtual i_server* create_server() = 0;


		virtual void run_once() = 0;
	};
}

#include "../head/M_interface.h"
M_DECL(ns_base::h_asio_net, "asio_net.dll");
