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

int main()
{
	{
		typedef ft::map<int, int>::iterator	iterator;

		ft::map<int, int>	m;
		iterator			it;

		(void)it;

		std::cout << "\n\n////////////////	TESTS 	////////////////\n";


		m.insert(ft::pair<const int, int>(86, 0));
		m.insert(ft::pair<const int, int>(9, 0));
		m.insert(ft::pair<const int, int>(12, 654654));
		m.insert(ft::pair<const int, int>(90, 0));

		m[5] = 9999;

		(void)m;



		//m.print_tree();

		/* std::cout << "print tree" << std::endl;
		it = m.begin();
		std::cout << *it++.base() << std::endl;
		std::cout << *it++.base() << std::endl;
		std::cout << *it++.base() << std::endl;
		std::cout << *it++.base() << std::endl;
		std::cout << *it++.base() << std::endl;
		std::cout << *it++.base() << std::endl;
 */

		/* std::cout << ft::distance(m.begin(), m.end()) << " = distance" << std::endl;
		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(m, "M");


		//m.print_tree();

		std::cout << "\n\n";
		ft::map<int, int> map2;

		std::cout << "map2 insert////////////////////////////////////////////////////////" << std::endl;
		map2.insert(m.begin(), m.end());


		//map2.print_tree();

		std::cout << "distance = " << ft::distance(map2.begin(), map2.end()) << std::endl;
		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(map2, "MAP2");


		ft::map<int, int>	copy(map2);

		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(copy, "COPY");

		copy[13] = 6354;
		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(copy, "COPY"); */


		/* copy[11] = 6;
		copy[14] = 6354;


		//copy.print_tree();
		copy[321] = 56;

		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(copy, "COPY");


		copy.swap(map2);

		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(map2, "MAP2");
		print_map<ft::map<int, int>, ft::map<int, int>::iterator, std::string>(copy, "COPY"); */


		std::cout << "////////////////	TESTS 	////////////////\n\n";

	}

	std::cout << "\n";
 
	return (0);
}
