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

template <class Map, class iterator, class Title>
void	print_map(Map & m, Title s)
{
	iterator	it = m.begin();
	std::cout << "\n\n////////	" << s << "	//////////\n";

	while (it != m.end())
	{
		std::cout << "it = " <<  it->first << " " << it->second << std::endl;
		it++;
	}

	std::cout << "size() = " << m.size() << std::endl;
	std::cout << "////////	" << s << "	//////////\n\n";
}

template <class V>
void printSize(const V & vector)
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


template <class T>
void	cmp(const T &lhs, T &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

template <class V>
void	test()
{
	 V vct;

        typename V::iterator it = vct.begin();
        typename V::const_iterator cit = vct.begin();

        typename V::reverse_iterator rit(it);
        typename V::reverse_iterator rit2;
        rit2 = rit;

        typename V::const_reverse_iterator crit(rit);
        typename V::const_reverse_iterator crit_(it);
        typename V::const_reverse_iterator crit_2(cit);

        typename V::const_reverse_iterator crit2;
        typename V::const_reverse_iterator crit2_;
        typename V::const_reverse_iterator crit2_2;

}

int main()
{
	{
		
		std::cout << "ft" << std::endl;
		//std::vector<int> v(5, 5);
		
		
		test<ft::vector<int> >();

		//std::cout <<  << std::endl;



		std::cout << "////////////////	TESTS 	////////////////\n\n";

	}

	std::cout << "\n";
 
	return (0);
}
