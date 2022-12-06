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

#include <list>

template <class V>
void	test()
{
	V vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << " | ";
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	printSize(vct);

	V const vct_c(vct);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	try {
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
}

int main()
{
	{
		
		std::cout << "ft" << std::endl;
		// std::vector<int> v;


		test<ft::vector<int> >();




		std::cout << "////////////////	TESTS 	////////////////\n\n";

	}

	std::cout << "\n";
 
	return (0);
}
