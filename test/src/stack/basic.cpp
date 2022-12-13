
#include "std_header.hpp"
#include <vector>
#include "vector.hpp"


#define TESTED_TYPE foo<int>
#define t_stack_ NAMESPACE::stack
typedef t_stack_<TESTED_TYPE>::container_type container_type;


void	test()
{
	NAMESPACE::stack<TESTED_TYPE> stck;

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(41);
	stck.push(29);
	stck.push(10);
	stck.push(42);
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
