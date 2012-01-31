#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../filesystem/interface.h"
#include "../compress/interface.h"

#include <complex>

#include "math.h"
#include "stdlib.h"

using namespace ns_common;
using namespace ns_base;




int main(int argc, char** argv)
{
	h_compress* hc;
	get(hc);
	std::string str = "lasjdfljasdlfkjlksdfjlkasdjfoiwefjlawefjoiljfdjlasj18734987928w47923749812734klasjdfjasdlfjlka8912734987123947";
	i_buffer* buff = hc->compress(ns_base::e_zlib, str.c_str(), str.length(), 512);
	assert(buff != 0);

	i_buffer* buff1  = hc->uncompress(ns_base::e_zlib, (char*)buff->ptr(), buff->size(), 2048);

	assert(buff1 != 0);
	char* p = (char*)buff->ptr();
	char* p1 = (char*)buff1->ptr();
	for(size_t i=0; i<buff->size(); ++i)
	{
		assert(*(p++)==*(p1++) );
	}


	return 0;
}