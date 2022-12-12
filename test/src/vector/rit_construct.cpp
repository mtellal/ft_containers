
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"



template <class V>
void	test()
{
	V vct;

	typename V::iterator it = vct.begin();
	typename V::const_iterator cit = vct.begin();

	typename V::reverse_iterator rit(it);
	typename V::reverse_iterator rit2;
	rit2 = rit;

	typename V::const_reverse_iterator crit(rit);
	typename V::const_reverse_iterator crit_(it);
 	typename V::const_reverse_iterator crit_2(cit);

	typename V::const_reverse_iterator crit2;
	typename V::const_reverse_iterator crit2_;
 	typename V::const_reverse_iterator crit2_2;

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
