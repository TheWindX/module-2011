
#pragma once

namespace ns_base
{
	template<typename T>
	struct singleton : public T
	{
		static T& instance()
		{
			static T ins;
			return ins;
		}
	};
}