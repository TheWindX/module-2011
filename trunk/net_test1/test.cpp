#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>


#include "../head/smart_ptr.h"
#include "../filesystem/interface.h"
#include "../image/interface.h"
#include "../head/exception.h"

#include "../net/interface.h"

using namespace ns_base;
using namespace ns_common;

i_server* ps;
void except(long id)
{
	printf("server exceptions: %d\n", id);
}

struct st_test
{
	
	i_session* sess;
	void except(long id)
	{
		printf("exceptions: %d\n", id);
	}

	void on_recv(long sz)
	{
		printf("long is %d\n", sz);
		char buff[128];
		memset(buff, 0, 128);
		long sz1 = sess->recv(buff, 128);
		assert(sz1 == sz);
		sess->send(buff, sz);
		printf("%s\n", buff);
	}
};

void count(long id)
{
	printf("%d is accept\n", id);
	st_test* test = new st_test;
	test->sess = ps->get_session_by_id(id);
	test->sess->s_exception += std::make_pair(test, &st_test::except);
	test->sess->s_recv += std::make_pair(test, &st_test::on_recv);
}


int main(int argc, char** argv)
{
	using namespace ns_base;
	using namespace ns_common;

	h_net* hn;
	get(hn);

	ps = hn->create_server_select();	
	ps->bind(10009);
	ps->listen();
	ps->s_accept += &count;
	ps->s_exception += &except;

	while(1)
	{
		Sleep(1);
		hn->run_once();
	}
	
	return 0;
}


