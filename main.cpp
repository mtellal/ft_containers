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

int main()
{
	{
		ft::map<int, int> m;
		ft::map<int, int>::iterator	itm;

		std::map<int, int> std_m;
		std::map<int, int>::iterator std_itm;

		std_m.insert(std::pair<int, int>(86, 0));
		std_m.insert(std::pair<int, int>(9, 0));
		std_m.insert(std::pair<int, int>(12, 0));
		std_m.insert(std::pair<int, int>(90, 0));

		std::cout << "////////////////	TESTS 	////////////////\n";

		std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator > spair;

		spair = std_m.equal_range(8);

		std::cout << "std equal range = " << spair.first->first << " " << spair.second->first << std::endl;


		m.insert(ft::pair<const int, int>(86, 0));
		m.insert(ft::pair<const int, int>(9, 0));
		m.insert(ft::pair<const int, int>(12, 654654));
		m.insert(ft::pair<const int, int>(90, 0));

		std::cout << (m[5] = 6546) << std::endl;
		m[5] = 9999;
		std::cout << m[5] << std::endl;

		std::cout << "m.clear() called" << std::endl;
		m.clear();


		std::cout << "////////////////	TESTS 	////////////////n\n\n";


		/* m.my_insert(ft::pair<const int, int>(5, 0));
		m.my_insert(ft::pair<const int, int>(15, 0));
		m.my_insert(ft::pair<const int, int>(12, 0));
		m.my_insert(ft::pair<const int, int>(19, 0));
		m.my_insert(ft::pair<const int, int>(9, 0));
		m.my_insert(ft::pair<const int, int>(23, 0));
		m.my_insert(ft::pair<const int, int>(13, 0));
		m.my_insert(ft::pair<const int, int>(10, 0));
		m.my_insert(ft::pair<const int, int>(40, 0));
		m.my_insert(ft::pair<const int, int>(1, 0));
		m.my_insert(ft::pair<const int, int>(96845, 0)); */


		/* ft::map<int, int>::iterator it = m.begin();
		
		std::cout << "\n////////// PRINT MAP ///////////\n";

		for (size_t i = 0; i < m.size(); i++)
			std::cout << *it++ << std::endl; */
		//(void)vc;

	}

	std::cout << "\n";
 
	return (0);
}
