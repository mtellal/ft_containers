
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"

template <class V>
void	test()
{
	V vct(7);
	V vct2;
	V vct3;


	for (size_t i = 0; i < 100; i++)
		vct3.push_back(i);

	vct.reserve(0);
	vct.reserve(7);
	vct.reserve(10);
	vct.reserve(1000);

	vct2.reserve(0);
	vct2.reserve(10);
	
	vct2.reserve(vct3.size());

	vct2.reserve(100);
	vct2.reserve(1000);

}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v;

	for (size_t i = 0; i < n; i++)
		v.reserve(i);
}

int main()
{
	struct timeval begin;
        struct timeval end;
	double time;

        gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<int> >();	
	
	test_perf(1000);

	gettimeofday(&end, NULL);

	double uend = (double)end.tv_usec / 1000;
	double ubegin = (double)begin.tv_usec / 1000;

	time = ((double)(uend - ubegin));

	std::cout << time << std::endl;
}
