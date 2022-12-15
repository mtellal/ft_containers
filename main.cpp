/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cfv                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:03:52 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/15 16:03:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include <cstddef>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include <iomanip>

#include <sys/time.h>

#define NAMESPACE ft

template <class T, bool v>
struct container_constant {
  typedef T value_type;
  typedef container_constant<T,v> type;
  static const bool value = v;
  operator T() { return v; }
};

template <class T>  struct is_map :				  container_constant<T, false> {};
template <class K, class V>         struct is_map<std::map<K, V> > :   container_constant<bool, true> {};
template <class K, class V>         struct is_map<ft::map<K, V> > :   container_constant<bool, true> {};

template <class T>  struct is_vector :				  container_constant<T, false> {};
template <class V>         struct is_vector<std::vector<V> > :   container_constant<bool, true> {};
template <class V>         struct is_vector<ft::vector<V> > :   container_constant<bool, true> {};



template <class V>
void printSize(const V & vector,
		typename ft::enable_if<is_vector<V>::value, int>::type = 0)
{
	size_t	i = 0;
	std::cout << "size = " << vector.size() <<
				"\ncapacity = " << (vector.capacity() ? "OK" : "KO") <<
				"\nmax_size = " << vector.max_size() <<  std::endl;

	while (i < vector.size())
	{
		std::cout << vector[i] << std::endl;
		i++;
	}
	std::cout << "\n\n";
}


// --- Class foo
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <typename T>
T	inc(T it, int n)
{
	while (n-- > 0)
		++it;
	return (it);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

#define _pair NAMESPACE::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1,
		typename ft::enable_if<is_map<T_MAP>::value, int>::type = 0)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
		{
			std::cout << " - " << printPair(it, false) << std::endl;
		}
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(NAMESPACE::map<T1, T2> &mp)
{
	typename NAMESPACE::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

	std::cout << "printReverse:" << std::endl;
	while (it != ite) {
		it--;
		std::cout << "-> " << printPair(it, false) << std::endl;
	}
	std::cout << "_______________________________________________" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////


template <class V>
void	test()
{
	V vct(10);
	V vct2;
	V vct3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	printSize(vct2);

	vct2.resize(4);
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	printSize(vct2);

	printSize(vct);

	for (int i = 0; i < 5; ++i)
		vct3.insert(vct3.end(), i);
	vct3.insert(vct3.begin() + 1, 2, 111);
	printSize(vct3);
}

void	test_perf(size_t n)
{
	NAMESPACE::vector<int> v;

	for (size_t i = 0; i < n; i++)
		v.insert(v.begin(), i);
}

int main()
{
	struct timeval begin;
	struct timeval end;
	double time;

	gettimeofday(&begin, NULL);
	
	test<NAMESPACE::vector<int> >();      

	test_perf(1000);

	gettimeofday(&end, NULL);

	double uend = (double)end.tv_usec / 1000;
	double ubegin = (double)begin.tv_usec / 1000;

	time = (uend - ubegin);

	std::cout << time << std::endl;
}