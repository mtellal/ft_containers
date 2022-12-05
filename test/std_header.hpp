#ifndef STD_HEADER_HPP
#define STD_HEADER_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <cstdlib>

#include <list>
#include <vector>
#include <stack>
#include <map>

#include "containers.hpp"


template <class V>
void printSize(const V & vector)
{
	size_t	i = 0;
	std::cout << "size = " << vector.size() <<
				"\ncapacity = " << vector.capacity() <<
				"\nmax_size = " << vector.max_size() <<  std::endl;

	while (i < vector.size())
	{
		std::cout << vector[i] << std::endl;
		i++;
	}
	std::cout << "\n\n";
}

#endif
