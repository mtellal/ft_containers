
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"

template <class V>
void	test()
{
	V vct(7, 5);
	V vct_two(4);
	V vct_three;
	V vct_four;
	V vct_five(8);

	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;

	printSize(vct);
	printSize(vct_two);

	vct_two = vct;
	vct_three = vct_two;
	vct_five = vct_two;

	printSize(vct_two);
	printSize(vct_three);
	printSize(vct_five);
	
	vct_two = vct_four;
	vct = vct_two;

	printSize(vct_two);
	printSize(vct);
}

int main()
{
	struct timeval begin;
        struct timeval end;
	double time;

        gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<int> >();	
	
	gettimeofday(&end, NULL);
	
	time = ((double)(end.tv_usec - begin.tv_usec)) / 1000;
	std::cout << time << std::endl;
}
