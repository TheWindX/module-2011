
#include "vm.h"

namespace ns_core
{
	namespace ns_primary
	{
		u32 _pause(st_vm* rt);
		u32 print(st_vm* rt);

		//unit op
		u32 minus(st_vm* rt);

		//bin op
		u32 add(st_vm* rt);
		u32 sub(st_vm* rt);
		u32 mul(st_vm* rt);
		u32 div(st_vm* rt);
		u32 mod(st_vm* rt);
		u32 equal_num(st_vm* rt);
		u32 GT_num(st_vm* rt);
		u32 LT_num(st_vm* rt);

		//array
		u32 null_array(st_vm* rt);
		u32 array_push(st_vm* rt);
		u32 array_cor(st_vm* rt);

		//map
		u32 null_map(st_vm* rt);
		u32 map_insert(st_vm* rt);
		u32 insert(st_vm* rt);
		u32 index(st_vm* rt);

		u32 a_push(st_vm* rt);
		u32 a_pop(st_vm* rt);
		u32 a_size(st_vm* rt);

		u32 _type(st_vm* rt);

		u32 _include(st_vm* rt);
		u32 load(st_vm* rt);

		u32 print_symbol(st_vm* rt);

		u32 debug_step(st_vm* rt);

	}

}