
#include "std_header.hpp"


#define T1 int
#define T2 int

void		test(void)
{
	NAMESPACE::map<T1, T2> mp;
	NAMESPACE::map<T1, T2>::iterator it = mp.begin();
	NAMESPACE::map<T1, T2>::const_iterator cit = mp.begin();

	NAMESPACE::map<T1, T2>::reverse_iterator rit(it);

	NAMESPACE::map<T1, T2>::const_reverse_iterator crit(rit);
	NAMESPACE::map<T1, T2>::const_reverse_iterator crit_(it);
	NAMESPACE::map<T1, T2>::const_reverse_iterator crit_2(cit);
}

int main()
{
	struct timeval begin;
	struct timeval end;
	double time;

	gettimeofday(&begin, NULL);
	
	test();       

	gettimeofday(&end, NULL);

	time = ((double)(end.tv_usec - begin.tv_usec)) / 1000;
	std::cout << time << std::endl;	
}
