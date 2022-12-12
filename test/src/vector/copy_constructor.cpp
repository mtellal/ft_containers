
#include "std_header.hpp"

template <class V>
void	test()
{
	typedef typename V::iterator iterator;
	V vct(5);
	iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	V vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	V vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);
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
