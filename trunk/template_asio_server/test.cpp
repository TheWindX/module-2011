#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <iostream>
#include "../asio_net/interface.h"

struct st_tmp
{
	ns_base::i_resolver* res;
	void on_done(void)
	{
		printf("done");
		ns_base::i_endpoint* ep = res->first();
		for(;ep;)
		{
			std::cout<<ep->to_string()<<" "<<ep->get_port()<<std::endl;
			ep = res->next();
		}
		
	}

	void on_error(long ec)
	{
		printf("error: %d", ec);
	}

	void on_timeout(void)
	{
		printf("timeout");
	}
};


struct st_server_use
{	
	ns_base::i_server* m_server;
	ns_base::i_session* m_session;

	void on_recv(long sz)
	{
		char buff[1024];
		memset(buff, 0, 1024);
		m_session->recv(buff, sz);
		printf(buff);
	}
	void on_accept(long id)
	{
		printf("%d is accept\n", id);
		
		ns_base::i_session* s = m_server->get_session(id);
		assert(s != 0);
		m_session = s;
		s->send("12341531235", strlen("12341531235") );
		s->s_recv += std::make_pair(this, st_server_use::on_recv);
	}
	void on_error(long ec)
	{
		printf("error is occur: %d\n", ec);
	}
	void on_bind_error()
	{
		printf("bind error is occur");
	}

	void on_session_break(long id)
	{
		printf("session break: %d", id);
	}
};
int main(int argc, char** argv)
{
	using namespace ns_base;
	
	h_asio_net* han;
	get(han);

	//test1
	i_endpoint* ep = han->create_endpoint();
	ep->from_string("127.0.2.1", 8080);

	unsigned long ip = ep->to_ulong();

	ep->release();

	//test2
	i_resolver* res = han->create_resolver1("1234csdf", "8080");
	
	st_tmp tmp;
	tmp.res = res;
	res->s_done += std::make_pair(&tmp, &st_tmp::on_done);
	res->s_error += std::make_pair(&tmp, &st_tmp::on_error);
	res->s_timeout += std::make_pair(&tmp, &st_tmp::on_timeout);
	res->resolve(50);
	

	//test3
	i_server* ps = han->create_server();
	ps->bind(13365);
	ps->listen(true);
	st_server_use su;
	su.m_server = ps;
	ps->s_accept += std::make_pair(&su, &st_server_use::on_accept);
	ps->s_error += std::make_pair(&su, &st_server_use::on_error);
	ps->s_session_break += std::make_pair(&su, &st_server_use::on_session_break);
	for(;;)
	{
		han->run_once();
	}

	return 0;
}














