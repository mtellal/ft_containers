
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"


template <class V>
void	test()
{
	const int size = 5;
	V vct(size);
	typename V::iterator it = vct.begin();
	typename V::const_iterator ite = vct.begin();

	for (int i = 0; i < size; ++i)
		it[i] = i;

	ite[1] = 42; // < -- error

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
