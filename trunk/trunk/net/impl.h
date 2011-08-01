#pragma once
#include "interface.h"

#include "../head/ref_counter.h"

#include "../head/thread.h"

#include "./allocator.h"
#include "./buffer.h"

#include <winsock2.h>


//#pragma comment(lib, "wininet.lib")
// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

namespace ns_base
{
	using ns_common::impl_ref_counter;

	
	struct impl_DNS : public i_DNS, public impl_ref_counter
	{
		hostent* m_host; 
		int m_alias_idx;
		int m_addr_idx;
		const char* get_host_name();
		void get_host_by_name(const char* name);
		const char* get_name();
		const char* alias_first();
		const char* alias_next();

		long get_type();
		long addr_next();
		long addr_first();
		const char* to_ip_str(long ip_num);
		long to_ip(const char* ip_str);

		impl_DNS():m_host(0),m_alias_idx(0),m_addr_idx(0){};
	};
	
	struct impl_server_block : public i_server_block, public impl_ref_counter
	{
		SOCKET m_listen_socket;
		SOCKET m_accept_socket;

		void bind(unsigned short port);
		void accept();
		void send(char* buff, long len);
		void recv(char* buff, long len);
		void close();
		bool is_link();

		impl_server_block();
	};

	struct impl_client_block : public i_client_block, public impl_ref_counter
	{
		SOCKET m_connect_socket;
		void connect(long addr, unsigned short port);
		void send(char* buff, long len);
		void recv(char* buff, long len);
		void close();

		impl_client_block();
	};

	struct impl_client;
	struct impl_server;
	struct impl_session : public i_session, public virtual impl_ref_counter
	{
		static long m_id_count;
		enum
		{
			e_close = 0,
			e_establish,
			e_exception,
		};
		long m_status;//×´Ì¬

		std::vector<long/*id*/> m_exception_events;
		
		long m_id;
		SOCKET m_socket;
		
		impl_client* m_client;
		impl_server* m_server;
		
		ns_common::st_dequeue m_send_buff;
		ns_common::st_dequeue m_recv_buff;
		
		long get_id(){return m_id;}

		void send(const char* buff, long sz);

		long recv_buffer_size();

		long recv(char* buff, long len);

		void close();

		void run_once();//trigger event;

		impl_session();

		~impl_session();
	};

	struct impl_server : public i_server, public virtual impl_ref_counter
	{
		enum
		{
			e_close = 0,
			e_listening,
			e_exception,
		};
		long m_status;//
		
		std::vector<long/* err_code */> m_exception_events;

		SOCKET m_socket;

		std::vector<impl_session*> m_sessions;
		std::vector<impl_session*> m_new_sessions;//acception

		void bind(unsigned short port);
		void listen();

		long get_session_sz();
		i_session* get_session_by_idx(long idx);
		i_session* get_session_by_id(long id);

		void close();

		void run_once();

		impl_server();
		~impl_server();
	};

	struct impl_client : public i_client, public virtual impl_ref_counter
	{
		enum
		{
			e_close = 0,
			e_connecting,
			e_connected,
			e_exception,
		};
		long m_status;//×´Ì¬

		impl_session* m_session;
		std::vector<int> m_connect_events;
		std::vector<long> m_exception_events;

		void connect(long addr, unsigned short port);

		i_session* get_session();
		void close();

		impl_client();
		~impl_client();

		void run_once();
	};

	struct st_select_manager
	{
		CRITICAL_SECTION m_cs;
		std::vector<impl_client*> m_clients;
		std::vector<impl_server*> m_servers;

		void thread_run_once();

		void lock();
		void unlock();
		
		bool m_exit;
		HANDLE m_thread;
		DWORD m_thread_id;
		void enter_thread();
		void exit_thread();

		st_select_manager();
		~st_select_manager();
	};
	
	extern st_select_manager g_select_manager;

	struct h_impl_net : public h_net
	{
		WSADATA m_wsaData;
		i_DNS* create_winsock_dns();

		i_server_block* create_winsock_server_block();
		i_client_block* create_winsock_client_block();

		i_server* create_server_select();
		i_client* create_client_select();

		void run_once();

		h_impl_net();
		~h_impl_net();
	};

}