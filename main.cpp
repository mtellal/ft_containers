/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:03:52 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/15 16:03:55 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "containers.hpp"
#include <cstddef>


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
		if (p)
			p->~T();
		p = NULL;
	} */

	//~Allocator(){std::cout << "Allocator destructor called " << std::endl;};

};

template <class T>
void display_index(T tab, size_t l)
{
	size_t	i = 0;
	while (i < l)
		std::cout << tab[i++] << "\n";
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
		std::cout << "wdfw" << std::endl;
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
		ft::vector<p::entier> pp((size_t)10, 5);
		std::vector<p::entier > v(10, 5);

		ft::vIterator<p::entier> it = pp.begin();
		std::vector<p::entier>::iterator it2 = v.begin();

		(void)it;
		(void)it2;
		*(it + 3) = 2;
		it += 3;
		std::cout << *it << std::endl;


		(void)pp;
		(void)v;
		

	}

	std::cout << "\n";
 
	return (0);
}
