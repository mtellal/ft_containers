
#include "std_header.hpp"


#define T1 char
#define T2 foo<std::string>

void		test(void)
{
	NAMESPACE::map<T1, T2> mp;

	mp['a'] = "an element";
	mp['b'] = "another element";
	mp['c'] = mp['b'];
	mp['b'] = "old element";

	printSize(mp);

	std::cout << "insert a new element via operator[]: " << mp['d'] << std::endl;

	printSize(mp);
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
