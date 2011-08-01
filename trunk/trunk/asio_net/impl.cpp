#include "impl.h"


namespace ns_base
{

	bool impl_endpoint::from_string(const char* str_ip, unsigned short port)
	{
		address_v4 addrv4;
		boost::system::error_code ec;
		addrv4 = addrv4.from_string(str_ip, ec);
		if(ec)
		{
			return false;
		}
		address addr(addrv4);
		m_endpoint.address(addr);
		m_endpoint.port(port);
		return true;
	}

	unsigned long impl_endpoint::to_ulong()
	{
		boost::asio::ip::address addr = m_endpoint.address();
		boost::asio::ip::address_v4 addrv4 = addr.to_v4();
		return addrv4.to_ulong();
	}

	const char* impl_endpoint::to_string()
	{
		static std::string str_ip = "";
		boost::asio::ip::address addr = m_endpoint.address();
		boost::asio::ip::address_v4 addrv4 = addr.to_v4();

		boost::system::error_code ec;
		str_ip = addrv4.to_string(ec);
		if(ec)
		{
			return "";
		}
		else
		{
			return str_ip.c_str();
		}
	}

	unsigned short impl_endpoint::get_port()
	{
		return m_endpoint.port();
	}



	i_endpoint* impl_resolver::first()
	{
		boost::asio::ip::tcp::resolver::iterator end;
		
		if(m_it != end)
		{
			m_endpoint.m_endpoint = m_it->endpoint();
			m_it++;
			return &m_endpoint;
		}
		else return 0;
	}

	i_endpoint* impl_resolver::next()
	{
		boost::asio::ip::tcp::resolver::iterator end;

		if(m_it != end)
		{
			m_endpoint.m_endpoint = m_it->endpoint();
			m_it++;
			return &m_endpoint;
		}
		else return 0;
	}

	void impl_resolver::resolve(unsigned long timeout)
	{
		boost::system::error_code ec;
		
		boost::posix_time::ptime expires_time =
			boost::posix_time::microsec_clock::universal_time() + boost::posix_time::time_duration(0,0,0,timeout*1000);
		
		m_timer.expires_at(expires_time, ec);
		//expire_from_now is OK as well

		if(!ec)
		{
			m_timer.async_wait(boost::bind(&impl_resolver::on_timeout, this, _1) );
			m_res.async_resolve(m_query, boost::bind(&impl_resolver::on_done, this, _1, _2) );
		}
		else
		{
			assert(false);
		}
	}

	void impl_resolver::on_timeout(const boost::system::error_code &ec)
	{
		if(ec)
		{
			if(ec == boost::asio::error::operation_aborted)
			{
				//be resolved then cancelled
				return;
			}
			else
			{
				assert(false);
			}
		}
		m_res.cancel();
		s_timeout();
		s_done.Clear();
		s_error.Clear();
	}

	void impl_resolver::on_done(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it)
	{
		if(ec)
		{
			if(ec == boost::asio::error::operation_aborted)
			{
				//for timeout then cancelled
				return;
			}
			m_timer.cancel();
			s_error(ec.value() );
			//s_done.Clear();
			//s_timeout.Clear();
		}
		else
		{
			m_timer.cancel();
			m_it = it;
			s_done();
			//s_error.Clear();
			//s_timeout.Clear();
		}
	}

	impl_resolver::impl_resolver(tcp::resolver::query& q, boost::asio::io_service& io):m_query(q), m_res(io),m_timer(io, boost::posix_time::seconds(0) )
	{	
	}
	
	size_t impl_session::get_recv_buffer_size()
	{
		return m_buffer.size();
	}

	size_t impl_session::recv(char* buff, size_t sz)
	{
		size_t buff_sz = m_buffer.size();
		if(buff_sz > sz)
		{
			m_buffer.pop_front(buff, sz);	
			return sz;
		}
		else
		{
			m_buffer.pop_front(buff, buff_sz);
			return buff_sz;
		}
	}

	void impl_session::send_handler(size_t id, size_t bytesTransferred, const boost::system::error_code& errorCode)
	{
		if(!errorCode)
		{
			std::string& buffer = m_send_buffers[id];
			if(bytesTransferred == buffer.size() )
			{
				//send done
				m_send_buffers.erase(id);
				this->s_send(bytesTransferred);
			}
			else
			{
				//TODO, 是否有buffer没发送完的合理情况
				assert(false);
			}
		}
		else
		{
			this->s_error(errorCode.value() );
			this->close();
			m_statu = e_exception;
		}
	}

	void impl_session::send(char* buff, size_t sz)
	{	
		m_id_count++;
		m_send_buffers[m_id_count] = std::string(buff, buff+sz);
		boost::asio::async_write(m_socket, boost::asio::buffer(m_send_buffers[m_id_count] ), boost::bind(impl_session::send_handler, this, m_id_count,
			boost::asio::placeholders::bytes_transferred,
			boost::asio::placeholders::error) );
		//m_socket.async_send(boost::asio::buffer(m_send_buffers[m_id_count] ), boost::bind(impl_session::send_handler, this, m_id_count,
		//	boost::asio::placeholders::bytes_transferred,
		//	boost::asio::placeholders::error) );
	}

	i_endpoint* impl_session::get_local_endpoint()
	{
		boost::system::error_code ec;
		m_endpoint.m_endpoint = m_socket.local_endpoint(ec);
		if(ec) return 0;
		
		return &m_endpoint;
	}

	i_endpoint* impl_session::get_remote_endpoint()
	{
		boost::system::error_code ec;
		m_endpoint.m_endpoint = m_socket.remote_endpoint(ec);
		if(ec) return 0;

		return &m_endpoint;
	}

	int impl_session::statu()
	{
		return m_statu;
	}

	void impl_session::close()
	{
		m_socket.close();
		m_statu = e_close;
		m_send_buffers.clear();
	}

	impl_session::impl_session(boost::asio::io_service& io_service)
		:m_id_count(0), 
		m_statu(impl_session::e_close ),
		m_socket(io_service),
		m_bclient_or_server(true),
		m_client(0)
	{	
	}

	impl_session::~impl_session()
	{
		this->close();
	}

	void impl_session::start()
	{
		m_buffer.clear();
		if(m_statu == e_establish)
		{
			m_socket.async_receive(boost::asio::buffer(m_read_buffer, BUFFER_SZ),
				boost::bind(&impl_session::read_handler, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred) );
		}
	}

	void impl_session::read_handler(const boost::system::error_code& ec,
		std::size_t bytes_transferred)
	{
		if(!ec)
		{
			m_buffer.push_back(m_read_buffer, bytes_transferred);
			this->s_recv(bytes_transferred);
			if(m_statu == e_establish)
			{
				m_socket.async_receive(boost::asio::buffer(m_read_buffer, BUFFER_SZ),
					boost::bind(&impl_session::read_handler, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred) );
			}
		}
		else
		{
			//TODO
			//if(ec == boost::asio::error::)
			//assert(false);
			
			//error occur
			this->close();
			this->m_statu = i_session::e_exception;

			if(m_bclient_or_server)
			{
				m_client->s_session_break();
			}
			else
			{
				m_server->s_session_break(m_server_id);
			}
		}
		
	}

	void impl_client::connect(i_endpoint* ep, size_t timeout)
	{
		delete m_session;
		
		h_asio_net* han;
		get(han);
		h_impl_asio_net* han1 = static_cast<h_impl_asio_net*>(han);

		m_session = new impl_session(han1->m_io);
		m_session->m_bclient_or_server = true;
		m_session->m_client = this;

		impl_endpoint* ep1 = static_cast<impl_endpoint*>(ep);
		m_session->m_socket.async_connect(ep1->m_endpoint, boost::bind(&impl_client::connect_handler, this, boost::asio::placeholders::error) );
		m_timer.expires_from_now(boost::posix_time::milliseconds(timeout) );
		m_timer.async_wait(boost::bind(&impl_client::timeout_handler, this, boost::asio::placeholders::error) );
	}

	i_session* impl_client::get_session()
	{
		return m_session;
	}

	void impl_client::release_session()
	{
		if(m_session)
		{
			delete m_session;//TODO, ~impl_session的流程
			m_session = 0;
		}
	}

	void impl_client::connect_handler(const boost::system::error_code& err)
	{
		if (err) 
		{ 
			release_session();
			s_error(err.value() );
		} 
		else 
		{ 
			// We need to cancel the timeout since we have connected. 
			m_timer.cancel(); // Fires the timer regardless. Because we are
			m_session->m_statu = i_session::e_establish;
			m_session->start();
			s_done();
		} 
	}

	void impl_client::timeout_handler(const boost::system::error_code& ec)
	{
		if(ec)
		{
			if(ec == boost::asio::error::operation_aborted)
			{
				//未超时
				return;
			}
			assert(false);
		}

		release_session();

		s_timeout();
	}

	impl_client::impl_client(boost::asio::io_service& io_service)//TODO
		:m_session(0),
		m_timer(io_service)
	{
	}

	impl_client::~impl_client()
	{
		release_session();
	}

	bool impl_server::bind(unsigned short port)
	{
		//m_accept.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
		
		tcp::endpoint ep(tcp::v4(), port);
		m_accept.open(ep.protocol());
		m_accept.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

		boost::system::error_code ec;
		m_accept.bind(ep, ec);
		if(ec)
		{
			return false;
		}
		m_accept.listen(boost::asio::socket_base::max_connections, ec);
		if(ec)
		{
			return false;
		}
		return true;
	}

	void impl_server::listen(bool blisten)
	{
		if(blisten)
		{
			m_listen = true;
			m_id_count++;

			h_asio_net* han;get(han);
			h_impl_asio_net* han1 = static_cast<h_impl_asio_net*>(han);
			impl_session* ps = new impl_session(han1->m_io);
			m_session[m_id_count] = ps;
			ps->m_bclient_or_server = false;
			ps->m_server = this;
			ps->m_server_id = m_id_count;

			m_accept.async_accept(ps->m_socket, boost::bind(&impl_server::handle_accept, this, m_id_count, boost::asio::placeholders::error));
		}
		else
		{
			boost::system::error_code ec;
			m_accept.cancel(ec);//TODO?
			if(ec)
			{
				assert(false);
			}
			m_listen = false;
		}
	}

	void impl_server::handle_accept(size_t id, const boost::system::error_code& error)
	{
		if (!error)
		{
			impl_session* ps = m_session[id];
			assert(ps != 0);

			if(m_listen)
			{
				ps->m_statu = i_session::e_establish;
				ps->start();
				s_accept(id);
				listen(true);
			}
			else
			{
				delete ps;
				m_session.erase(id);
			}
		}
		else
		{
			impl_session* ps = m_session[id];
			delete ps;
			m_session.erase(id);
			s_error(error.value() );
		}
	}

	i_session* impl_server::get_session(int id)
	{
		if((m_it = m_session.find(id)) != m_session.end() )
		{
			return m_it->second;
		}
		return 0;
	}

	i_session* impl_server::first_session()
	{
		m_it = m_session.begin();
		if(m_it != m_session.end() )
		{
			return m_it->second;
		}
		else
		{
			return 0;
		}
		m_it++;
	}

	i_session* impl_server::next_session()
	{
		if(m_it != m_session.end() )
		{
			return m_it->second;
		}
		else
		{
			return 0;
		}
		m_it++;
	}

	void impl_server::remove_session(int id)
	{
		impl_session* sess = static_cast<impl_session*>(get_session(id) );
		delete sess;
		m_session.erase(id);
	}

	impl_server::impl_server(boost::asio::io_service& io_service)//TODO
		:m_id_count(0),
		m_listen(false),
		m_accept(io_service)
		//m_accept(io_service, tcp::endpoint(tcp::v4(), 12365))
	{	
	}

	impl_server::~impl_server()
	{
		listen(false);
		m_it = m_session.begin();
		for(;m_it != m_session.end(); ++m_it)
		{
			delete m_it->second;
		}
	}

	//接口导出
	i_resolver* h_impl_asio_net::create_resolver1(const char* addr, const char* protocol)
	{
		tcp::resolver::query query(addr, protocol);
		impl_resolver* ret = new impl_resolver(query, m_io);
		return ret;
	}

	i_resolver* h_impl_asio_net::create_resolver2(const char* addr, unsigned short port)
	{
		char buff[256];
		itoa(port, buff, 10) ;
		tcp::resolver::query query(addr, buff);
		impl_resolver* ret = new impl_resolver(query, m_io);
		return ret;
	}

	i_resolver* h_impl_asio_net::create_resolver3(unsigned long ip, unsigned short port)
	{
		char buff[256];
		itoa(port, buff, 10) ;

		boost::asio::ip::address_v4 addrv4(ip);
		boost::system::error_code ec;
		std::string str_ip = addrv4.to_string(ec);
		if(ec)
		{
			assert(false);
		}

		tcp::resolver::query query(str_ip, buff);
		impl_resolver* ret = new impl_resolver(query, m_io);
		return ret;
	}

	i_endpoint* h_impl_asio_net::create_endpoint()
	{
		return new impl_endpoint();
	}

	i_client* h_impl_asio_net::create_client()
	{
		impl_client* ret = new impl_client(m_io);
		return ret;
	}

	i_server* h_impl_asio_net::create_server()
	{
		impl_server* ret = new impl_server(m_io);
		return ret;
	}

	void h_impl_asio_net::run_once()
	{
		m_io.run_one();
	}

}


#include "../head/M_interface.h"

M_IMPL(ns_base::h_asio_net, ns_base::h_impl_asio_net);//2. 接口实现
M_OPEN();//3. 模块建立
