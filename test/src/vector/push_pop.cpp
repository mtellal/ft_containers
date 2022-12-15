
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"


template <class V>
void	test()
{
	
	V vct(8);
	V vct2;
	typename V::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	std::cout << "push_back():\n" << std::endl;

	vct.push_back("One long string");
	vct2.push_back("Another long string");

	printSize(vct);
	printSize(vct2);

	vct.pop_back();
	vct2.pop_back();

	printSize(vct);
	printSize(vct2);

}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v;

	for (size_t i = 0; i < n; i++)
		v.push_back(i);
	
	for (size_t i = 0; i < n; i++)
		v.pop_back();
}

int main()
{
	struct timeval begin;
	struct timeval end;
	double time;

	gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<std::string> >();       

	test_perf(10000);

	gettimeofday(&end, NULL);

	double uend = (double)end.tv_usec / 1000;
	double ubegin = (double)begin.tv_usec / 1000;

	time = ((double)(uend - ubegin));
	
	std::cout << time << std::endl;
}
