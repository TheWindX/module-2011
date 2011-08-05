#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../windows/interface.h"

#include "../telnet/interface.h"
#include "../asio_net/interface.h"


int main(int argc, char** argv)
{

	using namespace ns_base;


	h_telnet* ht;
	h_asio_net* han;
	get(ht);
	get(han);

	i_telnet_srcipt* its = ht->create_telnet_script();
	its->bind(12345);
	its->listen(true);


	for(;;)
	{
		han->run_once();
	}



	return 0;
}