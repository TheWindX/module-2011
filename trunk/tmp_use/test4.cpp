#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <vector>
#include <string>
#include <sstream>

#include "../filesystem/interface.h"

using namespace ns_common;
using namespace ns_base;

void path_iter(i_path_iter* it)
{
	const char* p = it->get_path();
	while(p)
	{
		printf("path: %s\n", p);

		if(it->is_directory() )
		{
			h_filesystem* hf; get(hf);
			i_path_iter* it1 = hf->create_path_iter(p);
			path_iter(it1);
		}
		it->next();
		p = it->get_path();
	}
	
	it->release();
	

}

int main(int argc, char** argv)
{
	h_filesystem* hf;
	get(hf);
	i_path_iter* pp = hf->create_path_iter("..");

	path_iter(pp);

	system("pause");
	hf->release();

	
	return 0;
}