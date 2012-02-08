
#include "context.h"

namespace ns_core
{
	namespace ns_primary
	{
		u32 _pause(st_context* rt);
		u32 print(st_context* rt);

		//unit op
		u32 minus(st_context* rt);

		//bin op
		u32 add(st_context* rt);
		u32 sub(st_context* rt);
		u32 mul(st_context* rt);
		u32 div(st_context* rt);
		u32 mod(st_context* rt);
		u32 equal_num(st_context* rt);
		u32 GT_num(st_context* rt);
		u32 LT_num(st_context* rt);

		//array
		u32 null_array(st_context* rt);
		u32 array_push(st_context* rt);
		u32 array_cor(st_context* rt);

		//map
		u32 null_map(st_context* rt);
		u32 map_insert(st_context* rt);
		u32 insert(st_context* rt);
		u32 index(st_context* rt);

		u32 a_push(st_context* rt);
		u32 a_pop(st_context* rt);
		u32 a_size(st_context* rt);

		u32 _type(st_context* rt);

		u32 _include(st_context* rt);
		u32 load(st_context* rt);

		u32 print_symbol(st_context* rt);

		u32 debug_step(st_context* rt);

	}

}