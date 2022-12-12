
#include "std_header.hpp"


#define T1 float
#define T2 foo<int>
typedef _pair<const T1, T2> T3;

void		test(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 + i, i + 1));

	NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	NAMESPACE::map<T1, T2>::iterator it(mp.begin());
	NAMESPACE::map<T1, T2>::const_iterator ite(mp.begin());
	printSize(mp);

	printPair(++ite);
	printPair(ite++);
	printPair(ite++);
	printPair(++ite);

	it->second.m();
	ite->second.m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	(*it).second.m();
	(*ite).second.m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);
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
