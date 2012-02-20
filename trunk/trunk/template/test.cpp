#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <ctime>
#include <cassert>


class ca
{
protected:
	void fa(){printf("fa\n");}
};

class cb : public ca
{
protected:
	void fb(){printf("using fa\n"); fa();}
};

class cc : public cb
{
public:
	void fc(){fa(); fb();}
};

int main(int argc, char** argv)
{
	cc c;
	c.fc();
	return 0;
}


