#pragma once
#include "interface.h"
#include "../head/ref_counter.h"
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "buffer.h"

using namespace boost::asio::ip;
namespace ns_base
{
	struct impl_endpoint : public i_endpoint, public virtual ns_common::impl_ref_counter
	{
		bool from_string(const char* str_ip, unsigned short port);

		unsigned long to_ulong();
		const char* to_string();
		unsigned short get_port();

		tcp::endpoint m_endpoint;
	};

	struct impl_resolver : public i_resolver, public virtual ns_common::impl_ref_counter
	{
		i_endpoint* first();
		i_endpoint* next();

		void resolve(unsigned long timeout);

		tcp::resolver_iterator m_it;
		impl_endpoint m_endpoint;

		tcp::resolver::query m_query;
		tcp::resolver m_res;
		boost::asio::deadline_timer m_timer;

		void on_timeout(const boost::system::error_code &ec);
		void on_done(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it);

		impl_resolver(tcp::resolver::query& q, boost::asio::io_service& io);
	};


	struct impl_session : public i_session
	{
		size_t get_recv_buffer_size();
		size_t recv(char* buff, size_t sz);

		size_t m_id_count;
		std::map<size_t, std::string> m_send_buffers;
		void send_handler(size_t id, size_t bytesTransferred, const boost::system::error_code& errorCode);
		void send(const char* buff, size_t sz);

		impl_endpoint m_endpoint;
		i_endpoint* get_local_endpoint();
		i_endpoint* get_remote_endpoint();

		int m_statu;
		int statu();
		void close();

		boost::asio::ip::tcp::socket m_socket;
		ns_common::st_dequeue m_buffer;//recv_buffer

		const static int BUFFER_SZ = 8092;
		char m_read_buffer[BUFFER_SZ];//for tmp use
		void read_handler(const boost::system::error_code& ec,
			std::size_t bytes_transferred);

		void start();

		impl_session(boost::asio::io_service& io_service);
		~impl_session();

		bool m_bclient_or_server;
		unsigned int m_server_id;

		union{i_client* m_client; i_server* m_server;};
	};

	struct impl_client : public i_client, public virtual ns_common::impl_ref_counter
	{
		//ns_delegate::Delegate<void(void)> s_timeout;
		//ns_delegate::Delegate<void(void)> s_done;
		//ns_delegate::Delegate<void(long)> s_error;

		void connect(i_endpoint* ep, size_t timeout);
		i_session* get_session();
		void release_session();

		impl_session* m_session;

		boost::asio::deadline_timer m_timer;
		void connect_handler(const boost::system::error_code& err);
		void timeout_handler(const boost::system::error_code& ec);

		impl_client(boost::asio::io_service& io_service);//TODO
		~impl_client();
	};


	struct impl_server : public i_server, public virtual ns_common::impl_ref_counter
	{
		//ns_delegate::Delegate<void(void)> s_bind_error;
		//ns_delegate::Delegate<void(long)> s_accept;
		//ns_delegate::Delegate<void(long)> s_error;

		bool bind(unsigned short port);
		void listen(bool blisten);

		i_session* get_session(int id);
		i_session* first_session();
		i_session* next_session();
		void remove_session(int id);

		impl_server(boost::asio::io_service& io_service);//TODO
		~impl_server();

		boost::asio::ip::tcp::acceptor m_accept;

		size_t m_id_count;
		std::map<size_t, impl_session*> m_session;
		std::map<size_t, impl_session*>::iterator m_it;


		void handle_accept(size_t id, const boost::system::error_code& error);
		bool m_listen;
	};

	//接口导出
	struct h_impl_asio_net : public h_asio_net
	{
		i_resolver* create_resolver1(const char* addr, const char* protocol);
		i_resolver* create_resolver2(const char* addr, unsigned short port);
		i_resolver* create_resolver3(unsigned long ip, unsigned short port);

		i_endpoint* create_endpoint();

		i_client* create_client();
		i_server* create_server();

		void run_once();

		boost::asio::io_service m_io;
	};
}