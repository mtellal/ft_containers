/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:40:07 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/20 16:40:45 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

// need specialisation random != bidirectional 

template <class Iterator>
class reverse_iterator
{
    public:

        typedef Iterator                                                     iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category    iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type           value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type      difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer              pointer;
        typedef typename ft::iterator_traits<Iterator>::reference            reference;

        reverse_iterator() {};
        explicit reverse_iterator( iterator_type x ) : it(x) {}
        reverse_iterator( const reverse_iterator & x ) : it(x.it) {}


        template< class U >
        reverse_iterator( const reverse_iterator<U>& other ) : it(other.base()) {}

        virtual ~reverse_iterator() {};

        template< class U >
        reverse_iterator& operator=( const reverse_iterator<U>& other ) 
        {
            it = other.base();
            return (*this);
        }

       /*  operator reverse_iterator<const Iterator>() const
        {
            return (ft::reverse_iterator<const Iterator>(this->it));
        } */

        iterator_type   base(void) const { return (it); }

        reference           operator*() const
        {
            iterator_type tmp = it;
            return (*(--tmp)); 
        }

        pointer             operator->() const { return &(operator*()); }
        
        reference           operator[]( difference_type n ) const { return (base()[-n - 1]); }


        reverse_iterator&   operator++() { --it; return (*this); }
        reverse_iterator&   operator--() { it++; return (*this); }

        reverse_iterator    operator++(int) { reverse_iterator c(*this); it--; return (c); }
        reverse_iterator    operator--(int) { reverse_iterator c(*this); it++; return (c); }
        
        reverse_iterator    operator+(difference_type n) const { return (reverse_iterator(it - n)); }
        reverse_iterator    operator-(difference_type n) const { return (reverse_iterator(it + n)); }
        
        reverse_iterator    operator-=(difference_type n) { it += n; return (*this); }
        reverse_iterator    operator+=(difference_type n) { it -= n; return (*this); }

    private:

        iterator_type it;
};

template< class Iterator1, class Iterator2 >
//typename reverse_iterator<Iterator1>::difference_type
long    operator-( const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs )
{
    return (rhs.base() - lhs.base());
}

template <class T>
ft::reverse_iterator<T>
    operator-(const typename ft::reverse_iterator<T>::difference_type & n,
                    const ft::reverse_iterator<T> & rhs)
{
    return (ft::reverse_iterator<T>(rhs.base() + n));
}

template <class T>
ft::reverse_iterator<T>
    operator+(const typename ft::reverse_iterator<T>::difference_type & n,
                    const ft::reverse_iterator<T> & rhs)
{
    return (ft::reverse_iterator<T>(rhs.base() - n));
}

template <class T, class CT>
long    operator+(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() - rhs.base());
} 


template <class T>
bool    operator==(const reverse_iterator<T> & lhs,
                    const reverse_iterator<T> & rhs)
{
    return (lhs.base() == rhs.base());
}

template <class T, class CT>
bool    operator==(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() == rhs.base());
} 

template <class T>
bool    operator!=(const reverse_iterator<T> & lhs,
                    const reverse_iterator<T> & rhs)
{
    return (lhs.base() != rhs.base());
}

template <class T, class CT>
bool    operator!=(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() != rhs.base());
}

template <class T>
bool    operator>(const reverse_iterator<T> & lhs,
                    const reverse_iterator<T> & rhs)
{
    return (lhs.base() < rhs.base());
}

template <class T, class CT>
bool    operator>(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() < rhs.base());
}

template <class T>
bool    operator>=(const reverse_iterator<T> & lhs,
                    const reverse_iterator<T> & rhs)
{
    return (lhs.base() <= rhs.base());
}

template <class T, class CT>
bool    operator>=(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() <= rhs.base());
}

template <class T>
bool    operator<(const reverse_iterator<T> & lhs,
                    const reverse_iterator<T> & rhs)
{
    return (lhs.base() > rhs.base());
}

template <class T, class CT>
bool    operator<(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() > rhs.base());
}

template <class T>
bool    operator<=(const reverse_iterator<T> & lhs,
                    const reverse_iterator<T> & rhs)
{
    return (lhs.base() >= rhs.base());
}

template <class T, class CT>
bool    operator<=(const reverse_iterator<T> & lhs,
                    const reverse_iterator<CT> & rhs)
{
    return (lhs.base() >= rhs.base());
}

#endif 