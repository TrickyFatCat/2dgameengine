#ifndef UTILS_H
#define UTILS_H

#include <algorithm>

namespace utility
{
	template <typename T>
	static T approach(const T current, const T target, const T delta)
	{
		return target > current ? std::min(current + delta, target)
								: std::max(current - delta, target);
	}
} 


#endif