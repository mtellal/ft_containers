
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"

template <class V>
void	test()
{
	V vct(10);
	V vct2;
	V vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	printSize(vct2);

	vct2.resize(4);
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printSize(vct2);

	printSize(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	printSize(vct3);
}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v;

	for (size_t i = 0; i < n / 10; i++)
		v.insert(v.begin(), i);

	NAMESPACE::vector<int> v2;

	v2.insert(v2.begin(), v.size(), *v.begin());
	v2.insert(v2.begin(), v.begin(), v.end());
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

	time = (uend - ubegin);

	std::cout << time << std::endl;
}
