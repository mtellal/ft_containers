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
		ft::vector<p::entier> _2d((size_t)10, 200);
		ft::vector<p::entier> fv((size_t)10, 5);

		std::vector<p::entier> v2d(10, 200);
		std::vector<p::entier > v(10, 5);

		//fv[5] = 654654;
		ft::vector<p::entier>::iterator it = fv + 5;
		std::vector<p::entier>::iterator it2 = v.begin() + 5;

		display_index<std::vector<p::entier> >(v, v.size());
		v.insert(v.end(), v2d.begin(), v2d.end());
		display_index<std::vector<p::entier> >(v, v.size());

		std::cout << "////////////////////////" << std::endl;
		display_index<ft::vector<p::entier> >(fv, fv.size());
		fv.insert(fv.end(), _2d.begin(), _2d.end());
		display_index<ft::vector<p::entier> >(fv, fv.size());


		(void)it;
		(void)it2;

		/* v.clear();
		std::cout << "vector after .clear() =>" << std::endl;
		i = 0;
		while (i < v.size())
		{
			std::cout << v[i++] << std::endl;
		}
		std::cout << "v.capacity() = " << v.capacity() << std::endl; */

/* 
		ft::vIterator<p::entier> it = fv.begin();
		std::vector<p::entier>::iterator it2 = v.begin();

		(void)it;
		(void)it2;
		*(it + 3) = 2;
		it += 3;
		std::cout << *it << std::endl;
 */

		(void)fv;
		(void)v;
		

	}

	std::cout << "\n";
 
	return (0);
}
