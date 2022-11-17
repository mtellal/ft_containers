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

int main()
{
	{
		ft::vector<int, Allocator<int> > pp((size_t)5, 100);
		ft::vector<int, Allocator<int> > v2;

		v2 = pp;
		(void)pp;

		int *t = v2.begin();
		size_t l;
		l = 0;
		while (l < v2.size())
		{
			std::cout << *t++ << std::endl;
			l++;
		}

	}

	std::cout << "\n";
	/* {
		std::vector<int, Allocator<int> > p(5, 100);	
		
		std::vector<int, Allocator<int> >::iterator it;
		size_t l;

		it = p.begin();
		l = 0;
		while (l < p.size())
		{
			std::cout << *it << std::endl;
			it++;
			l++;
		}

		p.push_back(10);p.push_back(10);p.push_back(10);p.push_back(10);
		p.push_back(10);p.push_back(10);p.push_back(10);p.push_back(10);
		p.push_back(10);p.push_back(10);p.push_back(10);p.push_back(10);
	} */

	//p.push_back(10);p.push_back(10);p.push_back(10);

/* 	size_t i = 0;
	while (i < p.size())
	{
		std::cout << p[i] << std::endl;
		i++;
	} */
 
	return (0);
}
