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

#define NAMESPACE ft

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
void    printSize(T_MAP const &mp, bool print_content = 1,
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


#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void    ft_erase(MAP &mp, U param)
{
        std::cout << "\t-- [" << iter++ << "] --" << std::endl;
        mp.erase(param);
        printSize(mp);
}

template <typename MAP, typename U, typename V>
void    ft_erase(MAP &mp, U param, V param2)
{
        std::cout << "\t-- [" << iter++ << "] --" << std::endl;
        mp.erase(param, param2);
        printSize(mp);
}

void            test(void)
{
        std::list<T3> lst;
        unsigned int lst_size = 10;
        for (unsigned int i = 0; i < lst_size; ++i)
                lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
        NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
        printSize(mp);

        ft_erase(mp, ++mp.begin());

        ft_erase(mp, mp.begin());

        ft_erase(mp, --mp.end());

        ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
        ft_erase(mp, --(--(--mp.end())), --mp.end());

        mp[10] = "Hello";
        mp[11] = "Hi there";
        printSize(mp);
        ft_erase(mp, --(--(--mp.end())), mp.end());

        mp[12] = "ONE";
        mp[13] = "TWO";
        mp[14] = "THREE";
        mp[15] = "FOUR";
        printSize(mp);
        ft_erase(mp, mp.begin(), mp.end());

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

		/* ft::map<int, int> map;

		map[5] = 9;
		map[6] = 9;
		map[8] = 9;
		map[65] = 19;

		std::cout << *map.end() << std::endl;
		std::cout << map.begin().base() << " " <<  (--map.end()).base()<< std::endl; */


		/* for (size_t i = 1; i < 9; i++)
		{
			std::cout << i - 1 << " = " << i * 3 << std::endl;
			map.insert(ft::make_pair(i - 1, i * 3 ));
		}
		map.print_tree();
		printSize(map); */

		/* std::list<T3> lst;
		unsigned int lst_size = 10;
		for (unsigned int i = 0; i < lst_size; ++i)
		{
			std::cout << ((i + 1) * 3) << std::endl;
			lst.push_back(T3(i + 1, (i + 1) * 3));
		}
		ft::map<T1, T2> mp(lst.begin(), lst.end());
		printSize(mp); */

		//std::cout <<  << std::endl;



		std::cout << "////////////////	TESTS 	////////////////\n\n";

	}

	std::cout << "\n";
 
	return (0);
}
