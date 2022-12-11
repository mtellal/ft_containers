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

#define NAMESPACE std

template <class T, bool v>
struct container_constant {
  typedef T value_type;
  typedef container_constant<T,v> type;
  static const bool value = v;
  operator T() { return v; }
};

template <class T>  struct is_map :                               container_constant<T, false> {};
template <class K, class V>         struct is_map<std::map<K, V> > :   container_constant<bool, true> {};
template <class K, class V>         struct is_map<ft::map<K, V> > :   container_constant<bool, true> {};

template <class T>  struct is_vector :                            container_constant<T, false> {};
template <class V>         struct is_vector<std::vector<V> > :   container_constant<bool, true> {};
template <class V>         struct is_vector<ft::vector<V> > :   container_constant<bool, true> {};

template <class V>
void printSize(const V & vector,
                typename ft::enable_if<is_vector<V>::value, int>::type = 0)
{
        size_t  i = 0;
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
                typedef T       value_type;

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
                value_type      getValue(void) const { return this->value; };
                void            switchVerbose(void) { this->_verbose = !(this->_verbose); };

                operator value_type(void) const {
                        return value_type(this->value);
                }
        private:
                value_type      value;
                bool            _verbose;
};

template <typename T>
std::ostream    &operator<<(std::ostream &o, foo<T> const &bar) {
        o << bar.getValue();
        return o;
}
// --- End of class foo

template <typename T>
T       inc(T it, int n)
{
        while (n-- > 0)
                ++it;
        return (it);
}

template <typename T>
T       dec(T it, int n)
{
        while (n-- > 0)
                --it;
        return (it);
}



#define _pair NAMESPACE::pair

template <typename T>
std::string     printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
        o << "key: " << iterator->first << " | value: " << iterator->second;
        if (nl)
                o << std::endl;
        return ("");
}

template <typename T_MAP>
void    printSize(T_MAP const &mp, bool print_content = 1)
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
void    printReverse(ft::map<T1, T2> &mp)
{
        typename ft::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

        std::cout << "printReverse:" << std::endl;
        while (it != ite) {
                it--;
                std::cout << "-> " << printPair(it, false) << std::endl;
        }
        std::cout << "_______________________________________________" << std::endl;
}

#define T1 char
#define T2 int
typedef _pair<const T1, T2> T3;

template <class MAP>
void	cmp(const MAP &lhs, const MAP &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void		test(void)
{
	NAMESPACE::map<T1, T2> mp1;
	NAMESPACE::map<T1, T2> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(mp1, mp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(mp2, mp1); // 3

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(mp2, mp1); // 5

	swap(mp1, mp2);

	cmp(mp1, mp2); // 6
	cmp(mp2, mp1); // 7
}

int main(int argc, char **argv)
{
	(void)argv;
	{
		if (argc == 2)
		{
			std::cout << "ft" << std::endl;
		}
		else
			std::cout << "std" << std::endl;
		//std::vector<int> v(5, 5);
		
		test();



		std::cout << "////////////////	TESTS 	////////////////\n\n";

	}

	std::cout << "\n";
 
	return (0);
}
