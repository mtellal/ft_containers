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


template < class T >
class  Allocator : public  std::allocator<T>
{
	private:

		typedef typename std::allocator<T> _value_type;
		typedef typename _value_type::pointer _pointer;
		typedef typename _value_type::size_type _size_type;
		typedef typename _value_type::const_reference _const_reference;

		_size_type	_nb_elements;
		_size_type	_nb_allocations;

	public:

	//Allocator() : std::allocator<T>() {std::cout << "Allocator constructor called " << std::endl;};

	/* template <class U>
	Allocator(const Allocator<U> & other) : Base(other) {} */

	template<class U>
	struct rebind
	{
		typedef typename ::Allocator<U> other;
	};

	_pointer allocate(_size_type n)
	{
		std::cout << "allocate " << n * sizeof(T) << " bytes" << std::endl;
		_nb_allocations += n;
		return _value_type::allocate(n);
	}

	void deallocate(_pointer p, _size_type s)
	{
		(void)s;
		_nb_allocations -= s;
		std::cout << "deallocating " << s * sizeof(T) << " bytes" << std::endl;
		_value_type::deallocate(p, s);
	}

	/* void	construct(_pointer p, const _value_type & re)
	{
		(void)p;
		(void)re;
	}

	void destroy(_pointer p)
	{
		std::cout << "called ?" << std::endl;
		if (p)
		{
			p->~T();
			delete p;
		}
		p = NULL;
	} */

	//~Allocator(){std::cout << "Allocator destructor called " << std::endl;};

};

template <class T>
void display_index(T tab, size_t l)
{
	size_t	i = 0;
	while (i < l)
	{
		std::cout << "[" << i << "] =	" << tab[i] << "\n";
		i++;
	}

	std::cout << "\n" << std::endl;
}

namespace p
{
	struct entier
	{
		int i;
		entier() : i(0) {}
		entier(int n) : i (n) {}

		bool operator==(const entier & obj)
		{
			return (obj.i == i);
		}

		bool operator!=(const entier & obj)
		{
			return (obj.i != i);
		}

		friend std::ostream & operator<<(std::ostream& output, const entier & obj)
		{
			output << obj.i;
			return (output);
		}
	};
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
















#define _pair ft::pair

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template <typename T1, typename T2>
void	printReverse(ft::map<T1, T2> &mp)
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
#define T2 foo<int>
typedef ft::map<T1, T2>::value_type T3;
typedef ft::map<T1, T2>::iterator ft_iterator;
typedef ft::map<T1, T2>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename MAP>
void	ft_bound(MAP &mp, const T1 &param)
{
	ft_iterator ite = mp.end(), it[2];
	ft::pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename MAP>
void	ft_const_bound(const MAP &mp, const T1 &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	ft::pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		test(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_const_bound(mp, -10);
	ft_const_bound(mp, 1);
	ft_const_bound(mp, 5);
	ft_const_bound(mp, 10);
	ft_const_bound(mp, 50);

	printSize(mp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound(mp, 5);
	ft_bound(mp, 7);

	printSize(mp);
	return (0);
}

int main()
{
	{
		
		std::cout << "ft" << std::endl;
		//std::vector<int> v(5, 5);
		
		
		test();

		//std::cout <<  << std::endl;



		std::cout << "////////////////	TESTS 	////////////////\n\n";

	}

	std::cout << "\n";
 
	return (0);
}
