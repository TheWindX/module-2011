
#pragma once

namespace ns_base
{
	typedef signed char		s8;
	typedef unsigned char		u8;
	typedef char			c8;

	typedef signed short		s16;
	typedef unsigned short		u16;

	typedef signed long		s32;
	typedef unsigned long		u32;
	
	typedef float				f32;
	typedef double				f64;


	typedef u32	id_t;
	typedef u32 sz_t;
	const u32 U32_NA = 0xffffffff;
	const u32 MAX_32 = U32_NA-1;
}