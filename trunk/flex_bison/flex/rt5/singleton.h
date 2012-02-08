
#pragma once

namespace ns_util
{
	template<typename T>
	struct st_singleton : public T
	{
		static T& instance()
		{
			static T ins;
			return ins;
		}
	};
}