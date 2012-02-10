

#include "context.h"

int main(int argc, char** argv)
{
	using namespace  ns_core;
	st_context_user& user = st_context_user::instance();
	user.load_string("g.x = 100;");
	user.load_file("user_file.txt");
	user.print_codes();
	user.run();
	return 0;
}