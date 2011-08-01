
#include "../head/exception.h"
#include "impl.h"
#include <string>

#include "../head/utility_new.h"//必须放在包含最后


namespace ns_base
{

	const char* impl_DNS::get_host_name()
	{
		static char str_ret[512];
		int iret = gethostname(str_ret, 512);
		if(iret != 0)
		{
			DWORD dwError = WSAGetLastError();
			char str_err[512];
			sprintf(str_err, "Function failed with error: %ld\n", dwError);
			RAISE_EXCEPTION(str_err);
		}
		return str_ret;
	}

	void impl_DNS::get_host_by_name(const char* name)
	{
		m_host = gethostbyname(name);
	}

	const char* impl_DNS::get_name()
	{
		if(!m_host) 
		{
			RAISE_EXCEPTION("");
			return 0;
		}
		
		return m_host->h_name;
	}

	const char* impl_DNS::alias_first()
	{
		if(!m_host) 
		{
			RAISE_EXCEPTION("");
			return 0;
		}

		m_alias_idx = 0;
		return m_host->h_aliases[m_alias_idx++];
	}

	const char* impl_DNS::alias_next()
	{
		if(!m_host) 
		{
			RAISE_EXCEPTION("");
			return 0;
		}

		return m_host->h_aliases[m_alias_idx++];
	}

	long impl_DNS::get_type()
	{
		if(!m_host) 
		{
			RAISE_EXCEPTION("");
			return 0;
		}

		if(m_host->h_addrtype == AF_INET)
		{
			return e_net_ipv4;
		}
		else if(m_host->h_addrtype == AF_INET6)
		{
			return e_net_ipv6;
		}
		else
			return e_net_other;
	}

	long impl_DNS::addr_first()
	{
		if(!m_host) 
		{
			RAISE_EXCEPTION("");
			return 0;
		}
		m_addr_idx = 0;
		char* str = m_host->h_addr_list[m_addr_idx++];
		if(!str) return 0;
		
		return *(u_long *) str;
	}

	long impl_DNS::addr_next()
	{
		if(!m_host) 
		{
			RAISE_EXCEPTION("");
			return 0;
		}


		char* str = m_host->h_addr_list[m_addr_idx++];
		if(!str) return 0;
		
		return *(u_long *) str;
	}

	const char* impl_DNS::to_ip_str(long ip_num)
	{
		struct in_addr addr;
		addr.s_addr = ip_num;
		return inet_ntoa(addr);
	}

	long impl_DNS::to_ip(const char* ip_str)
	{
		return inet_addr(ip_str);
	}


	void impl_server_block::bind(unsigned short port)
	{
		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = inet_addr("127.0.0.1");//local
		service.sin_port = htons(port);

		if (::bind(m_listen_socket,
			(SOCKADDR *) & service, sizeof (service) ) == SOCKET_ERROR)
		{
				char err[256];
				sprintf(err, "bind failed with error: %d", WSAGetLastError() );
				RAISE_EXCEPTION(err);
				return;
		}

	}

	void impl_server_block::accept()
	{
		char err[256];
		if (listen(m_listen_socket, 1) == SOCKET_ERROR)
		{
			sprintf(err, "listen failed with error: %d", WSAGetLastError() );
			RAISE_EXCEPTION(err);
		}

		m_accept_socket = ::accept(m_listen_socket, NULL, NULL);
		if (m_accept_socket == INVALID_SOCKET) {
			sprintf(err, "accept failed with error: %d", WSAGetLastError() );
			closesocket(m_listen_socket);
		}
	}

	void impl_server_block::send(char* buff, long len)
	{
		int err = 0;
		int index = 0;
		long size = len;
		while (size != 0)
		{
			if (size > 4096)
			{
				err = ::send(m_accept_socket,(char*)buff+index,4096,0);
			}
			else
			{
				err = ::send(m_accept_socket,(char*)buff+index,size,0);
			}   

			if (err == 0) 
			{
				RAISE_EXCEPTION("socket 已经断开");//TODO
				break;
			}
			if (err < 0)
			{
				char str_err[256];
				sprintf(str_err, "send failed with error: %d", WSAGetLastError() );
				RAISE_EXCEPTION(str_err);//TODO
				break;
			}
			size -= err;
			index += err;
		}
	}

	void impl_server_block::recv(char* buff, long len)
	{
		int err;
		int index = 0;
		long size = len;
		while (size != 0)
		{
			err = ::recv(m_accept_socket,(char*)buff+index,size,0); 
			if (err == SOCKET_ERROR) break;
			if (err == 0)
			{
				RAISE_EXCEPTION("socket 已经断开");//TODO
				break;
			}
			else if(err < 0)
			{
				char str_err[256];
				sprintf(str_err, "recv failed with error: %d", WSAGetLastError() );
				RAISE_EXCEPTION(str_err);//TODO
			}

			size -= err;
			index += err;
		}
	}

	void impl_server_block::close()
	{
		closesocket(m_accept_socket);
	}

	bool impl_server_block::is_link()
	{
		//todo
		return true;
	}

	impl_server_block::impl_server_block()
	{
		m_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_listen_socket == INVALID_SOCKET)
		{
			char err[256];
			sprintf(err, "socket failed with error: %d\n", WSAGetLastError() );
			RAISE_EXCEPTION(err);
			return;
		}
	}


	void impl_client_block::connect(long addr, unsigned short port)
	{	
		sockaddr_in client_sevice;

		client_sevice.sin_family = AF_INET;
		client_sevice.sin_addr.s_addr = addr;
		client_sevice.sin_port = htons( port );

		//----------------------
		// Connect to server.
		int iResult = ::connect( m_connect_socket, (SOCKADDR*) &client_sevice, sizeof(client_sevice) );
		if ( iResult == SOCKET_ERROR)
		{
			closesocket (m_connect_socket);
			char err[256];
			sprintf(err, "Unable to connect to server: %d", WSAGetLastError() );
			RAISE_EXCEPTION(err);
		}
	}

	void impl_client_block::send(char* buff, long len)
	{
		int err = 0;
		int index = 0;
		long size = len;
		while (size != 0)
		{
			if (size > 4096)
			{
				err = ::send(m_connect_socket,(char*)buff+index,4096,0);
			}
			else
			{
				err = ::send(m_connect_socket,(char*)buff+index,size,0);
			}   

			if (err == 0) 
			{
				RAISE_EXCEPTION("socket 已经断开");//TODO
				break;
			}
			if (err < 0)
			{
				char str_err[256];
				sprintf(str_err, "send failed with error: %d", WSAGetLastError() );
				RAISE_EXCEPTION(str_err);//TODO
				break;
			}
			size -= err;
			index += err;
		}
	}

	void impl_client_block::recv(char* buff, long len)
	{
		int err;
		int index = 0;
		long size = len;
		while (size != 0)
		{
			err = ::recv(m_connect_socket,(char*)buff+index,size,0); 
			if (err == SOCKET_ERROR) break;
			if (err == 0)
			{
				RAISE_EXCEPTION("socket 已经断开");//TODO
				break;
			}
			else if(err < 0)
			{
				char str_err[256];
				sprintf(str_err, "recv failed with error: %d", WSAGetLastError() );
				RAISE_EXCEPTION(str_err);//TODO
			}

			size -= err;
			index += err;
		}
	}

	void impl_client_block::close()
	{
		closesocket(m_connect_socket);
	}

	impl_client_block::impl_client_block()
	{
		m_connect_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void impl_session::send(const char* buff, long sz)
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		
		m_send_buff.push_back(buff, sz);

		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	long impl_session::recv_buffer_size()
	{
		return m_recv_buff.size();
	}
	long impl_session::recv(char* buff, long len)
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		long sz = m_recv_buff.size();
		if(len>m_recv_buff.size() ) len = sz;
		m_recv_buff.pop_front(buff, len);
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
		return len;
	}

	void impl_session::close()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		m_status = e_close;
		m_send_buff.clear();
		m_recv_buff.clear();
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
		closesocket(m_socket);
	}

	void impl_session::run_once()//trigger event
	{	
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		//if(m_status == e_close) return;
		long sz = 0;
		if( (sz = m_send_buff.size() ) != 0)
		{
			this->s_send(sz);
		}
		if( (sz = m_recv_buff.size() ) != 0)
		{
			this->s_recv(sz);
		}
		for(size_t i = 0; i<m_exception_events.size(); ++i)
		{
			this->s_exception( m_exception_events[i] );
		}
		m_exception_events.clear();
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	impl_session::impl_session()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		m_id = m_id_count++;
		m_socket = SOCKET_ERROR;
		m_client = 0;
		m_server = 0;
		m_send_buff.clear();
		m_recv_buff.clear();
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	impl_session::~impl_session()
	{
		closesocket(m_socket);
		//从client, server中去除
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		if(m_client)
		{
			m_client->m_status = impl_client::e_close;
			m_client->m_status = 0;
		}
		else if(m_server)
		{
			std::vector<impl_session*>& sessions = m_server->m_sessions;
			std::vector<impl_session*>::iterator it = sessions.begin();
			for(; it != sessions.end(); ++it)
			{
				if (this == *it)
				{
					sessions.erase(it);
					LeaveCriticalSection(&g_select_manager.m_cs);
					return;
				}
			}
		}
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}


	void impl_server::bind(unsigned short port)
	{	
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET)
		{
			char err[256];
			sprintf(err, "socket failed with error: %d\n", WSAGetLastError() );
			/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
			RAISE_EXCEPTION(err);
			return;
		}
		//建立 无阻塞
		u_long b = 1;
		ioctlsocket(m_socket, FIONBIO, &b);

		g_select_manager.m_servers.push_back(this);

		sockaddr_in service;
		service.sin_family = AF_INET;
		service.sin_addr.s_addr = inet_addr("127.0.0.1");//local
		service.sin_port = htons(port);

		if (::bind(m_socket,
			(SOCKADDR *) & service, sizeof (service) ) == SOCKET_ERROR)
		{
			char err[256];
			sprintf(err, "bind failed with error: %d", WSAGetLastError() );
			/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
			RAISE_EXCEPTION(err);
			return;
		}
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	void impl_server::listen()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		char err[256];
		if (::listen(m_socket, 1) == SOCKET_ERROR)
		{
			sprintf(err, "listen failed with error: %d", WSAGetLastError() );
			/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
			RAISE_EXCEPTION(err);
		}
		m_status = e_listening;
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	long impl_server::get_session_sz()
	{
		return m_sessions.size();
	}
	i_session* impl_server::get_session_by_idx(long idx)
	{
		return m_sessions[idx];
	}
	i_session* impl_server::get_session_by_id(long id)
	{
		for(size_t i = 0; i<m_sessions.size(); ++i)
		{
			if(m_sessions[i]->m_id == id) return m_sessions[i];
		}
		for(size_t i = 0; i<m_new_sessions.size(); ++i)
		{
			if(m_new_sessions[i]->m_id == id) return m_new_sessions[i];
		}
		return 0;
	}

	void impl_server::close()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		//每个session结束, 然后关闭自己
		std::vector<impl_session*> copyer = m_sessions;
		for(size_t i = 0; i<copyer.size(); ++i)
		{
			impl_session* sess = copyer[i];
			sess->release();
		}
		m_sessions.clear();

		for(size_t i = 0; i<m_new_sessions.size(); ++i)
		{
			impl_session* sess = m_new_sessions[i];
			sess->release();
		}
		m_new_sessions.clear();
		m_status = e_close;
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();

		closesocket(m_socket);
		
	}

	void impl_server::run_once()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		for(size_t i = 0; i<m_sessions.size(); ++i)
		{
			m_sessions[i]->run_once();
		}
		//accept
		for(size_t i = 0; i<m_new_sessions.size(); ++i)
		{
			this->s_accept(m_new_sessions[i]->get_id() );
			this->m_sessions.push_back(m_new_sessions[i] );
		}
		this->m_new_sessions.clear();

		//exception
		for(size_t i = 0; i<m_exception_events.size(); ++i)
		{
			this->s_exception(this->m_exception_events[i]);
		}
		this->m_exception_events.clear();
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
		Sleep(1);
	}

	impl_server::impl_server()
	{
		m_status = e_close;
		m_socket = SOCKET_ERROR;
	}
	impl_server::~impl_server()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		close();
		std::vector<impl_server*>::iterator it = g_select_manager.m_servers.begin();
		for(;it != g_select_manager.m_servers.end(); ++it)
		{
			if(*it == this)
				g_select_manager.m_servers.erase(it);
		}
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}


	void impl_client::connect(long addr, unsigned short port)
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sClient == INVALID_SOCKET)
		{
			char err[256];
			sprintf(err, "socket failed with error: %d\n", WSAGetLastError() );
			/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
			RAISE_EXCEPTION(err);
			return;
		}
		//建立 无阻塞
		u_long b = 1;
		ioctlsocket(sClient, FIONBIO, &b);

		sockaddr_in client_sevice;

		client_sevice.sin_family = AF_INET;
		client_sevice.sin_addr.s_addr =  addr;
		client_sevice.sin_port = htons( port );

		//----------------------
		// Connect to server.
		long iResult = ::connect( sClient, (SOCKADDR*) &client_sevice, sizeof(client_sevice) );

		impl_session* p_session = new impl_session;
		p_session->m_socket = sClient;
		p_session->m_server = 0;
		p_session->m_client = this;
		m_status = impl_client::e_connecting;

		m_session = p_session;
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	i_session* impl_client::get_session()
	{
		return m_session;
	}
	void impl_client::close()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		if(m_session)
			m_session->release();
		m_session = 0;

		this->m_connect_events.clear();
		this->m_exception_events.clear();
		this->m_status = e_close;
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	impl_client::impl_client()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		this->m_status = e_close;
		m_session = 0;
		g_select_manager.m_clients.push_back(this);
		LeaveCriticalSection(&g_select_manager.m_cs);
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}
	impl_client::~impl_client()
	{
		close();
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		std::vector<impl_client*>::iterator it = g_select_manager.m_clients.begin();
		for(;it != g_select_manager.m_clients.end(); ++it)
		{
			if(*it == this)
				g_select_manager.m_clients.erase(it);
		}
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();

	}

	void impl_client::run_once()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		if(m_status == e_connected)
		{
			m_session->run_once();
		}

		for(size_t i = 0; i<m_connect_events.size(); ++i)
		{
			s_connect_ok();
		}
		m_connect_events.clear();

		for(size_t i = 0; i<m_exception_events.size(); ++i)
		{
			s_exception(m_exception_events[i]);
		}
		m_exception_events.clear();
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}


	static DWORD WINAPI ThreadProc(LPVOID lpThreadParam)
	{
		g_select_manager.enter_thread();
		return 0;
	}
	h_impl_net::h_impl_net()
	{
		//----------------------
		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2,2), &m_wsaData);
		if (iResult != NO_ERROR) {
			char ec[256];
			sprintf(ec, "WSAStartup failed: %d\n", iResult);
			RAISE_EXCEPTION(ec);
			return;
		}
		g_select_manager.m_thread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &g_select_manager.m_thread_id);
	}

	h_impl_net::~h_impl_net()
	{
		g_select_manager.exit_thread();
		WSACleanup();
	}

	i_DNS* h_impl_net::create_winsock_dns()
	{
		impl_DNS* ret = new impl_DNS;
		return ret;
	}

	i_server_block* h_impl_net::create_winsock_server_block()
	{
		return new impl_server_block;
	}

	i_client_block* h_impl_net::create_winsock_client_block()
	{
		return new impl_client_block;
	}

	i_server* h_impl_net::create_server_select()
	{
		return new impl_server;
	}

	i_client* h_impl_net::create_client_select()
	{
		return new impl_client;
	}

	void h_impl_net::run_once()
	{
		std::vector<impl_client*> cs = g_select_manager.m_clients;
		for(size_t i = 0; i<cs.size(); ++i)
		{
			cs[i]->run_once();
		}

		std::vector<impl_server*> ss = g_select_manager.m_servers;
		for(size_t i = 0; i<ss.size(); ++i)
		{
			ss[i]->run_once();
		}
	}

	void st_select_manager::thread_run_once()
	{
		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		SOCKADDR_IN client; 
		int iaddrSize = sizeof(client);
	
		struct timeval tm;
		tm.tv_sec = (1000 / 1000);
		tm.tv_usec = ((1000 - tm.tv_sec * 1000) * 1000);
		fd_set fdread;
		fd_set fdwrite;
		fd_set fdexception;

		FD_ZERO(&fdread);
		FD_ZERO(&fdwrite);
		FD_ZERO(&fdexception);

		//client
		for(size_t i = 0; i<m_clients.size(); ++i)
		{
			impl_client* p_client = m_clients[i];
			if(p_client->m_status == impl_client::e_connecting)
			{
				impl_session* s = static_cast<impl_session*>(p_client->get_session() );
				FD_SET(s->m_socket, &fdwrite);
				FD_SET(s->m_socket, &fdexception);
			}
			else if(p_client->m_status == impl_client::e_connected)
			{
				impl_session* s = p_client->m_session;
				FD_SET(s->m_socket, &fdread);
				FD_SET(s->m_socket, &fdwrite);
				FD_SET(s->m_socket, &fdexception);
			}
		}

		for(size_t i = 0; i<m_servers.size(); ++i)
		{
			impl_server* p_server = m_servers[i];
			if(p_server->m_status == impl_server::e_listening)
			{
				FD_SET(p_server->m_socket, &fdread);
				FD_SET(p_server->m_socket, &fdexception);
			}
			for(size_t ii = 0; ii<p_server->m_sessions.size(); ++ii )
			{
				impl_session* p_session = p_server->m_sessions[ii];
				if(p_session->m_status == impl_session::e_establish)
				{
					FD_SET(p_session->m_socket, &fdread);
					FD_SET(p_session->m_socket, &fdwrite);
					FD_SET(p_session->m_socket, &fdexception);
				}
			}
		}
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();

		int ret = ::select(1, &fdread, &fdwrite, &fdexception, &tm) ;

		/*printf("%s__", __FUNCTION__);*/g_select_manager.lock();
		if (ret == 0)  
		{  
			// Time expired  
			/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
			return;
		} 
		else if(ret == SOCKET_ERROR)
		{
			int err = WSAGetLastError();
			/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
			//TODO, log
			return;
		}

		//client
		for(size_t i = 0; i<m_clients.size(); ++i)
		{
			impl_client* p_client = m_clients[i];
			if(p_client->m_status == impl_client::e_connecting)
			{	
				impl_session* s = p_client->m_session;
				if(FD_ISSET(s->m_socket, &fdwrite) )
				{
					//连接OK
					p_client->m_status = impl_client::e_connected;
					p_client->m_session->m_status = impl_session::e_establish;
					p_client->m_connect_events.push_back(1);
				}
				if(FD_ISSET(s->m_socket, &fdexception) )
				{
					p_client->m_status = impl_client::e_exception;
					int errorVal;
					int errorValLen = sizeof (int);
					if (getsockopt					(s->m_socket, SOL_SOCKET,
						SO_ERROR, (char *) &errorVal,
						&errorValLen) != SOCKET_ERROR)
					{
						p_client->m_exception_events.push_back(errorVal);
					}
					else
					{
						p_client->m_exception_events.push_back( WSAGetLastError() );
					}
					closesocket(s->m_socket);
				}
			}
			else if(p_client->m_status == impl_client::e_connected)
			{
				impl_session* p_session = p_client->m_session;
				if(FD_ISSET(p_session->m_socket, &fdexception) )
				{
					p_client->m_status = impl_client::e_exception;
					int errorVal;
					int errorValLen = sizeof (int);
					if (getsockopt					(p_session->m_socket, SOL_SOCKET,
						SO_ERROR, (char *) &errorVal,
						&errorValLen) != SOCKET_ERROR)
					{
						p_client->m_exception_events.push_back(errorVal);
					}
					else
					{
						p_client->m_exception_events.push_back( WSAGetLastError() );
					}
					p_session->close();
				}
				else
				{
					if(FD_ISSET(p_session->m_socket, &fdread) )
					{
						//可以读了
						char buff[1024];
						memset(buff, 0, 1024);
						long ret = ::recv(p_session->m_socket, buff, 1024,0);
						if(ret <= 0)//=0, gracely closed, else close
						{
							//表示session已经断开
							p_session->m_exception_events.push_back(WSAGetLastError() );
							p_session->close();
						}
						else
						{
							p_session->m_recv_buff.push_back(buff, ret);
						}
					}
					//这时状态可能改变
					if(p_session->m_status != impl_session::e_establish)
					{
						continue;
					}
					if(FD_ISSET(p_session->m_socket, &fdwrite) )
					{
						//可以写了
						char buff[1024];
						memset(buff, 0, 1024);
						long sz = p_session->m_send_buff.size();
						if(sz>1024) sz = 1024;
						if(sz>0)
						{
							p_session->m_send_buff.pop_front(buff, sz);
							long ret = ::send(p_session->m_socket, buff, sz,0);
						}
					}
				}
			}
		}

		//servers
		for(size_t i = 0; i<m_servers.size(); ++i)
		{
			impl_server* p_server = m_servers[i];
			if(p_server->m_status == impl_server::e_listening)
			{	
				if(FD_ISSET(p_server->m_socket, &fdexception) )
				{
					p_server->m_status = impl_server::e_exception;
					int errorVal;
					int errorValLen = sizeof (int);
					if (getsockopt					(p_server->m_socket, SOL_SOCKET,
						SO_ERROR, (char *) &errorVal,
						&errorValLen) != SOCKET_ERROR)
					{
						p_server->m_exception_events.push_back(errorVal);
					}
					else
					{
						p_server->m_exception_events.push_back(WSAGetLastError() );
					}
					p_server->close();
				}
				else
				{
					if(FD_ISSET(p_server->m_socket, &fdread) )
					{
						//accepted
						SOCKET sClient = accept(p_server->m_socket, (struct sockaddr *)&client, &iaddrSize);
						impl_session* p_session = new impl_session;
						p_session->m_socket = sClient;
						p_session->m_status = impl_session::e_establish;
						p_server->m_new_sessions.push_back(p_session);
						p_session->m_server = p_server;
					}
				}
			}

			//sessions
			for(size_t ii = 0; ii<p_server->m_sessions.size(); ++ii )
			{
				impl_session* p_session = p_server->m_sessions[ii];
				if(p_session->m_status == impl_session::e_establish)
				{
					if(FD_ISSET(p_session->m_socket, &fdexception) )
					{
						p_session->m_status = impl_session::e_exception;
						int errorVal;
						int errorValLen = sizeof (int);
						if (getsockopt					(p_session->m_socket, SOL_SOCKET,
							SO_ERROR, (char *) &errorVal,
							&errorValLen) != SOCKET_ERROR)
						{
							p_session->m_exception_events.push_back(errorVal);
						}
						else
						{
							p_session->m_exception_events.push_back(WSAGetLastError() );
						}
						p_session->close();
					}
					else
					{
						if(FD_ISSET(p_session->m_socket, &fdread) )
						{
							//可以读了
							char buff[1024];
							long ret = ::recv(p_session->m_socket, buff, 1024,0);
							if(ret <= 0)//=0, gracely closed, else close
							{
								//表示session已经断开
								p_session->m_exception_events.push_back(WSAGetLastError() );
								p_session->close();
							}
							else
							{
								p_session->m_recv_buff.push_back(buff, ret);
							}
						}
						//这时状态可能改变
						if(p_session->m_status != impl_session::e_establish)
						{
							continue;
						}
						if(FD_ISSET(p_session->m_socket, &fdwrite) )
						{
							//可以写了
							char buff[1024];
							memset(buff, 0, 1024);
							long sz = p_session->m_send_buff.size();
							if(sz>1024) sz = 1024;
							if(sz>0)
							{
								p_session->m_send_buff.pop_front(buff, sz);
								long ret = ::send(p_session->m_socket, buff, sz,0);
							}
						}
					}
				}
			}
		}
		/*printf("%s__", __FUNCTION__);*/g_select_manager.unlock();
	}

	void st_select_manager::lock()
	{
		/*printf("lock\n");*/
		EnterCriticalSection(&m_cs);
	}

	void st_select_manager::unlock()
	{	
		LeaveCriticalSection(&m_cs);
		/*printf("unlock\n");*/
	}

	void st_select_manager::enter_thread()
	{
		while(m_exit)
		{
			this->thread_run_once();
			Sleep(10);
		}
	}

	void st_select_manager::exit_thread()
	{
		m_exit = false;	
	}

	st_select_manager::st_select_manager()
	{
		InitializeCriticalSection(&m_cs);
		m_exit = true;
		m_thread = 0;
		m_thread_id = 0;
	}
	
	st_select_manager::~st_select_manager()
	{
		m_exit = false;	
		WaitForSingleObject(m_thread, INFINITE);
		DeleteCriticalSection(&m_cs);
	}


	st_select_manager g_select_manager;
	long impl_session::m_id_count = 0;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	detect_memory_leaks(true);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}
#include "../head/M_interface.h"


M_IMPL(ns_base::h_net, ns_base::h_impl_net);//2. 接口实现
M_OPEN();//3. 模块建立
