#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>

#include <string>

#include "../head/exception.h"
#include "../head/smart_ptr.h"
#include "../filesystem/interface.h"
#include "../image/interface.h"


using namespace ns_base;
using namespace ns_common;

void translate_image(const char* path, const char* to_path, float scale)
{
	h_image* hi;get(hi);
	smart_ptr<i_image> pi = hi->create_from_file(path, e_bmp);
	
	long x = 256;
	long y = 256;

	pi->size(x, y);
	pi->thumbnail(x*scale, y*scale);

	printf("%s\n到%s\n请稍候...\n\n", path, to_path);
	pi->to_file(to_path, e_jpg);
}


void iter_path(std::string path, std::string path_to, std::string ext, float scale)
{
	h_filesystem* hf;get(hf);
	i_path* cur_fold = hf->create_path(path.c_str() );
	i_path* p_to = hf->create_path(path_to.c_str() );
	

	for(const char* path_iter = cur_fold->first();path_iter != 0; path_iter = cur_fold->next() )
	{
		i_path* path_cur = hf->create_path(path_iter);
		i_path* file_name = hf->create_path(path_cur->stem() );
		i_path* file_ext = hf->create_path(path_cur->extension() );
		
		if(std::string("") == file_name->c_str() )
		{	
			continue;
		}
		else if(path_cur->is_directory() )
		{
			if(std::string(p_to->stem() ) == path_cur->stem() )
			{
				continue;
			}
			i_path* new_fold = p_to->clone();
			new_fold->append(file_name->c_str() );
			hf->make_directories(new_fold->c_str() );
			iter_path(path_cur->c_str(), new_fold->c_str(), ext, scale);
		}
		else
		{
			if(std::string(ext) == file_ext->c_str() )
			{
				//图片
				i_path* p_file_to = hf->create_path(path_to.c_str() );
				p_file_to->append( (std::string(file_name->c_str() )+".jpg").c_str() );
				translate_image(path_iter, p_file_to->c_str(), scale);
			}
		}
	}
	
}

//usage:
/************************************************************************/
/* 

.exe <ext> <缩放倍数> <输出目录> 


*/
/************************************************************************/
int main(int argc, char** argv)
{
	try
	{
		if(argc != 4)
		{
			printf("usage: <exe> <ext> <缩放倍数> <输出目录>   \nfor example: .exe .bmp 0.3 ../输出");
			Sleep(1000);
			system("pause");
			return 0;
		}

		h_image* hi;
		h_filesystem* hf;
		get(hi);
		get(hf);

		i_path* input = hf->create_work_directory();
		i_path* output = input->clone();
		output->append(argv[3]);
		output->normalize();
		hf->make_directories(output->c_str() );
		
		iter_path(input->c_str(), output->c_str(), argv[1], atof(argv[2]) );
	}
	catch(st_exception& e)
	{
		printf("出错: %s", e.what() );
	}

	return 0;
}


