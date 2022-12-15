
#include "std_header.hpp"


template <class V, class iterator>
void	checkErase(V const &vct, iterator const &it)
{
	(void)vct;
	(void)it;
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

template <class V>
void	test()
{
	V vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);
	printSize(vct);

	checkErase(vct, vct.erase(vct.begin() + 2)); // 0

	checkErase(vct, vct.erase(vct.begin())); // 1
	checkErase(vct, vct.erase(vct.end() - 1)); // 2

	printSize(vct);

	checkErase(vct, vct.erase(vct.begin(), vct.begin() + 3));

	checkErase(vct, vct.erase(vct.end() - 3, vct.end() - 1));

	vct.push_back("Hello");
	vct.push_back("Hi there");
	printSize(vct);


	checkErase(vct, vct.erase(vct.end() - 3, vct.end()));

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	printSize(vct);
	checkErase(vct, vct.erase(vct.begin(), vct.end()));
}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v(n);
	
	for (size_t i = 0; i < n; i++)
		v.erase(v.begin());

	NAMESPACE::vector<int> v2(n);

	v2.erase(v2.begin(), v2.end());
	
}

int main()
{
	struct timeval begin;
	struct timeval end;
	double time;

	gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<std::string> >();       
	
	test_perf(1000);

	gettimeofday(&end, NULL);

	double uend = (double)end.tv_usec / 1000;
	double ubegin = (double)begin.tv_usec / 1000;

	time = ((double)(uend - ubegin));
	
	std::cout << time << std::endl;
}
