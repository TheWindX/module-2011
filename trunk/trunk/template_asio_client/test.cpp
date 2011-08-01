#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <iostream>
#include "../asio_net/interface.h"


using namespace ns_base;
struct st_client_use
{
	
	ns_base::i_client* m_client;
	void on_timeout()
	{
		printf("connect time out!");
	}

	void on_done()
	{
		printf("connect done");

		i_session* ps = m_client->get_session();

		char buff[256];
		memset(buff, 0, 256);

		gets (buff); 
		
		ps->send(buff, strlen(buff) );
	}


};


int main(int argc, char** argv)
{
	using namespace ns_base;
	
	h_asio_net* han;
	get(han);


	st_client_use cu;


	i_endpoint* ep = han->create_endpoint();
	ep->from_string("127.0.0.1", 13365);

	i_client* pc = han->create_client();
	cu.m_client = pc;
	pc->connect(ep, 1111);
	pc->s_timeout += std::make_pair(&cu, st_client_use::on_timeout);
	pc->s_done += std::make_pair(&cu, st_client_use::on_done);

	for(;;)
	{
		han->run_once();
	}

	return 0;
}
















