#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>

#include "../head/delegate.h"

#include <string>
#include <iostream>
using namespace boost::asio;
using namespace boost::asio::ip;



struct st_session
{
	tcp::socket m_socket;

	ns_delegate::Delegate<void(void)> s_exception;

	ns_delegate::Delegate<void(const char*, long)> s_recv;
	

	st_session(boost::asio::io_service& io)
		:m_socket(io){}

	boost::asio::streambuf m_data;


	void on_read(const boost::system::error_code& ec, const char* delim);

	void read_until(const char* delim);
};

void st_session::on_read(const boost::system::error_code& ec, const char* delim)
{
	if (!ec)
	{
		
		std::istream is(&m_data);
		std::string str;
		char str_buff[256];
		memset(str_buff, 0, 256);
		is.getline(str_buff, 256, delim[0] );
		printf(str_buff );
		printf("\ndone\n" );
		read_until(delim);
	}
	else
	{
		s_exception();
	}
}

void st_session::read_until(const char* delim)
{	
	boost::asio::async_read_until(m_socket, m_data, delim, boost::bind(&st_session::on_read, this, _1, delim) );
}



struct st_server
{
	io_service& m_io;
	//tcp::endpoint endpoint(tcp::v4(), 10009);

	tcp::acceptor m_acc;

	std::vector<st_session*> m_sessions;

	void on_accp(const boost::system::error_code& ec, st_session* sess);

	st_server(unsigned short port, io_service& io);
	
	
};

void st_server::on_accp(const boost::system::error_code& ec, st_session* sess)
{
	if(!ec)
	{
		m_sessions.push_back(sess);
		sess->read_until("\n");
	}
}

st_server::st_server(unsigned short port, io_service& io)
:m_acc( io, tcp::endpoint(tcp::v4(), port) ),
m_io(io)
{
	st_session* m_sess = new st_session(m_io);
	m_acc.async_accept(m_sess->m_socket,
		boost::bind(&st_server::on_accp, this, _1, m_sess) );
}

int main(int argc, char** argv)
{	
	
	boost::asio::io_service io;

	st_server server(10009, io);

	while(1)
	{
		io.run_one();
	}
	
	return 0;
}


