
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"



template <class V>
void	test()
{
	const int size = 5;
	V vct(size);
	typename V::reverse_iterator it(vct.rbegin());
	typename V::const_reverse_iterator ite(vct.rend()); 

	for (int i = 1; it != ite; ++i)
		*it++ = (i * 7);
	printSize(vct);

	it = vct.rbegin();
	ite = vct.rbegin();

	std::cout << *(++ite) << std::endl;
	std::cout << *(ite++) << std::endl;
	std::cout << *ite++ << std::endl;
	std::cout << *++ite << std::endl;

	it->m();
	ite->m();

	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it++ << std::endl;
	std::cout << *++it << std::endl;

	std::cout << *(--ite) << std::endl;
	std::cout << *(ite--) << std::endl;
	std::cout << *--ite << std::endl;
	std::cout << *ite-- << std::endl;

	(*it).m();
	(*ite).m();

	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it-- << std::endl;
	std::cout << *--it << std::endl;

}

int main()
{
	struct timeval begin;
	struct timeval end;
	double time;

	gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<foo<int> > >();       

	gettimeofday(&end, NULL);

time = ((double)(end.tv_usec - begin.tv_usec)) / 1000;	std::cout << time << std::endl;
}
