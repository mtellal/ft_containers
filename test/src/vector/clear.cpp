
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"

template <class V>
void	test()
{
	V vct(1000);
	V vct2;

	vct2.clear();
	
	vct2.push_back(0);

	vct2.clear();

	for (size_t i = 0; i < 1000; i++)
		vct[i] = i;

	vct.clear();	
}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v(n);

	v.clear();
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
