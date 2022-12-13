
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"


#define TESTED_TYPE foo<int>
#define t_stack_ NAMESPACE::stack<TESTED_TYPE>
typedef t_stack_::container_type container_type;

void		test()
{
	container_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	t_stack_		stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	printSize(stck);

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
