
#include "vm.h"


struct st_a
{
	int a;
};
struct st_b : public st_a
{
	int b;
};

struct st_af : public st_b
{
	void print_a();
	void print_all();
};

struct st_bf : public st_af
{
	void print_b();
};

void st_af::print_a()
{
	printf("a");
}

void st_af::print_all()
{
	print_a();
	static_cast<st_bf*>(this)->print_b();
}

void st_bf::print_b()
{
	printf("b");
}
//#include "ast.h"
//#include "ast_cons.h"
int main(int argc, char** argv)
{
	st_b b;
	b.a = 100;
	b.b = 1000;
	st_a* pa = static_cast<st_a*>(&b);
	st_b* pb = static_cast<st_b*>(pa);
	printf("%d\n", pb->b);
	printf("%d\n", pa->a);
	return 0;
}