
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"


template <class V>
void	is_empty(V const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

template <class V>
void	test()
{
	const int start_size = 7;
	V vct(start_size, 20);
	V vct2;
	typename V::iterator it = vct.begin();

	for (int i = 2; i < start_size; ++i)
		it[i] = (start_size - i) * 3;
	printSize(vct);

	vct.resize(10, 42);
	printSize(vct);

	vct.resize(18, 43);
	printSize(vct);
	vct.resize(10);
	printSize(vct);
	vct.resize(23, 44);
	printSize(vct);
	vct.resize(5);
	printSize(vct);
	vct.reserve(5);
	vct.reserve(3);
	printSize(vct);
	vct.resize(87);
	vct.resize(5);
	printSize(vct);

	is_empty(vct2);
	vct2 = vct;
	is_empty(vct2);
	vct.reserve(vct.capacity() + 1);
	printSize(vct);
	printSize(vct2);

	vct2.resize(0);
	is_empty(vct2);
	printSize(vct2);
}

int main()
{
	struct timeval begin;
	struct timeval end;
	double time;

	gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<int> >();       

	gettimeofday(&end, NULL);

time = ((double)(end.tv_usec - begin.tv_usec)) / 1000;	std::cout << time << std::endl;
}
