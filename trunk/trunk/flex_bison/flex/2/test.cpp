

#include "bison_user.h"

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	FILE* fin = fopen("test.txt", "rb");
	std::string str = "";
	fseek(fin, 0, SEEK_END);
	long sz = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	str.resize(sz);
	fread(&str[0], 1, sz, fin);
	fclose(fin);


	g_bison_use.reset_buffer(str.c_str(), str.size() );
	g_bison_use.parse();
	return 0;
}