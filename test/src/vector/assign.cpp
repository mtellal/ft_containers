
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"

template <class V>
void	test()
{
	V vct(7);
	V vct_two(4);
	V vct_three;
	V vct_four;

	for (unsigned long int i = 0; i < vct.size(); ++i)
			vct[i] = (vct.size() - i) * 3;
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;

	printSize(vct);
	printSize(vct_two);

	vct_three.assign(vct.begin(), vct.end());
	vct.assign(vct_two.begin(), vct_two.end());
	vct_two.assign(2, 42);
	vct_four.assign(4, 21);

	std::cout << "\t### After assign(): ###" << std::endl;

	printSize(vct);
	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_four);

	vct_four.assign(6, 84);
	printSize(vct_four);

	std::cout << "\t### assign() on enough capacity and low size: ###" << std::endl;

	vct.assign(5, 53);
	vct_two.assign(vct_three.begin(), vct_three.begin() + 3);

	printSize(vct);
	printSize(vct_two);
}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v;

	for (size_t i = 0; i < n; i++)
		v.assign(i, i);
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
