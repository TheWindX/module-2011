#pragma once
#include "../head/ref_counter.h"
#include "../head/delegate.h"
#include "../head/handler.h"
#include "../head/M_interface.h"

namespace ns_base
{
	using ns_common::i_ref_counter;
	enum
	{	
		e_net_ipv4 = 0,
		e_net_ipv6,
		e_net_other,
	};

	struct i_DNS : public virtual i_ref_counter
	{
		virtual const char* get_host_name() = 0;
		virtual void get_host_by_name(const char* name) = 0;
		virtual const char* get_name() = 0;
		virtual const char* alias_first() = 0;
		virtual const char* alias_next() = 0;
		
		virtual long get_type() = 0;
		virtual long addr_next() = 0;
		virtual long addr_first() = 0;
		virtual const char* to_ip_str(long ip_num) = 0;
		virtual long to_ip(const char* ip_str) = 0;
	};

	struct i_server_block : public virtual i_ref_counter
	{
		virtual void bind(unsigned short port) = 0;
		virtual void accept() = 0;
		virtual void send(char* buff, long len) = 0;
		virtual void recv(char* buff, long len) = 0;
		virtual void close() = 0;
		virtual bool is_link() = 0;
	};

	struct i_client_block : public virtual i_ref_counter
	{
		virtual void connect(long addr, unsigned short port) = 0;
		virtual void send(char* buff, long len) = 0;
		virtual void recv(char* buff, long len) = 0;
		virtual void close() = 0;
	};



	struct i_session : public virtual i_ref_counter
	{
		ns_delegate::Delegate<void(long /* errcode */)> s_exception;
		ns_delegate::Delegate<void(long /* sz */)> s_recv;
		ns_delegate::Delegate<void(long /* sz */)> s_send;

		virtual long get_id() = 0;
		virtual void send(const char* buff, long sz) = 0;
		virtual long recv_buffer_size() = 0;
		virtual long recv(char* buff, long len) = 0;

		virtual void close() = 0;
	};

	struct i_client: public virtual i_ref_counter
	{
		ns_delegate::Delegate<void(long/* errcode */)> s_exception;
		ns_delegate::Delegate<void(void)> s_connect_ok;

		virtual void connect(long addr, unsigned short port) = 0;
		virtual i_session* get_session() = 0;
		virtual void close() = 0;
	};


	struct i_server : public virtual i_ref_counter
	{
		ns_delegate::Delegate<void(long/* errcode */)> s_exception;
		ns_delegate::Delegate<void(long/* id */)> s_accept;

		virtual void bind(unsigned short port) = 0;
		virtual void listen() = 0;

		virtual long get_session_sz() = 0;
		virtual i_session* get_session_by_idx(long idx) = 0;
		virtual i_session* get_session_by_id(long id) = 0;
		virtual void close() = 0;
	};

	struct h_net
	{
		virtual i_DNS* create_winsock_dns() = 0;

		virtual i_server_block* create_winsock_server_block() = 0;
		virtual i_client_block* create_winsock_client_block() = 0;

		virtual i_server* create_server_select() = 0;
		virtual i_client* create_client_select() = 0;

		virtual void run_once() = 0;
	};
}



M_DECL(ns_base::h_net, "net.dll");
