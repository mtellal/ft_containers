
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"


template <class V>
void	test()
{
	
	V foo(3, 15);
	V bar(5, 42);
	
	typename V::const_iterator it_foo = foo.begin();
	typename V::const_iterator it_bar = bar.begin();

	std::cout << "BEFORE SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	foo.swap(bar);

	std::cout << "AFTER SWAP" << std::endl;

	std::cout << "foo contains:" << std::endl;
	printSize(foo);
	std::cout << "bar contains:" << std::endl;
	printSize(bar);

	std::cout << "Iterator validity:" << std::endl;
	std::cout << (it_foo == bar.begin()) << std::endl;
	std::cout << (it_bar == foo.begin()) << std::endl;
}

int main()
{
	test<NAMESPACE::vector<int > >();	
}
