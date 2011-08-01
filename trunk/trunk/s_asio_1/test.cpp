
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/thread/thread.hpp>


void print(const boost::system::error_code& /*e*/)
{
	std::cout << "Hello, world!\n";
}


int test1(int argc, char** argv)
{
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	t.wait();
	std::cout << "Hello, world!\n";


	return 0;	
}


int test2(int argc, char** argv)
{
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	t.async_wait(print);


	while(1)
	{
		io.run_one();
	}
	
	return 0;	
}


void print2(const boost::system::error_code&, boost::asio::deadline_timer* t, int* count)
{
	if(*count<5)
	{
		printf("on time!\n");
		t->expires_at(t->expires_at()+boost::posix_time::seconds(1) );
		(*count)++;
		t->async_wait(boost::bind(print2,
			_1, t, count));
	}
	else
	{
		printf("on time the last time!\n");
	}
}

int test3(int argc, char** argv)
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5) );

	int count = 0;
	t.async_wait(boost::bind(print2, _1, &t, &count) );


	while(1)
	{
		io.run_one();
	}

	return 0;	
}




struct st_test1 
{
	boost::asio::strand m_strand;
	boost::asio::deadline_timer m_t1;

	int count;
	st_test1(boost::asio::io_service& io):
	m_strand(io), m_t1(io, boost::posix_time::seconds(2) ),count(0)
	{

	}

	void print(const boost::system::error_code& ec)
	{
		if(count < 5)
		{
			printf("on_time\n");
			m_t1.expires_at( m_t1.expires_at()+boost::posix_time::milliseconds(500) );
			m_t1.async_wait( m_strand.wrap(boost::bind(print, this, _1) ) );
			count++;
		}
	}
};


int test4()
{
	boost::asio::io_service io;
	st_test1 test(io);

	test.m_t1.async_wait(test.m_strand.wrap(boost::bind(&st_test1::print, &test, _1) ) );

	boost::thread t( boost::bind(boost::asio::io_service::run, &io) );

	t.join();
	return 0;
}


struct resolve_handler
{
		void handler(
		const boost::system::error_code& ec,
		boost::asio::ip::tcp::resolver::iterator iterator)
	{
		if (!ec)
		{
			for(;iterator != boost::asio::ip::tcp::resolver::iterator(); ++iterator)
			{
				std::cout<<iterator->endpoint()<<std::endl;
			}
			
			
		}
	}

};

int test5()
{
	using namespace boost::asio::ip;

	try
	{

		boost::asio::io_service io_service;

		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query("www.google.com", "80");

		resolve_handler rh;
		resolver.async_resolve(query,boost::bind(&resolve_handler::handler, &rh, _1, _2) );
		tcp::resolver::iterator end;

		// Try each endpoint until we successfully establish a connection.
		while(1)
		{
			io_service.run_one();
		}

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.

	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;

}


int test6()
{
	using namespace boost::asio;

	ip::address_v4 addr;
	addr = addr.from_string("127.0.0.1");
	unsigned long uaddr = addr.to_ulong();
	
	return 0;

}



int main(int argc, char** argv)
{
	return test6();
}


