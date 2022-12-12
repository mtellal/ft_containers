#ifndef STD_HEADER_HPP
#define STD_HEADER_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <cstdlib>
#include <sys/time.h>

#include <list>
#include <vector>
#include <stack>
#include <map>

#include "containers.hpp"


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

#endif
