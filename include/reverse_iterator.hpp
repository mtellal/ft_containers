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

        explicit reverse_iterator( iterator_type x ) : current(x) {}

        template< class U >
        reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {}

        ~reverse_iterator() {};

        template< class U >
        reverse_iterator& operator=( const reverse_iterator<U>& other ) 
        {
            current = other.base();
            return (*this);
        }

        iterator_type       base(void) const { return (current); }

        ////////////////////             ACCESS/DEFERENCE OPRATORS       ////////////////////////

        reference           operator*() const
        {
            iterator_type tmp = current;
            return (*(--tmp)); 
        }

        pointer             operator->() const { return &(operator*()); }
        
        reference           operator[]( difference_type n ) const { return (base()[-n - 1]); }

        ////////////////////             INC/DECREMENTATION OPRATORS       ////////////////////////

        reverse_iterator&   operator++() { --current; return (*this); }
        
        reverse_iterator    operator++(int) { reverse_iterator c(*this); current--; return (c); }
        
        reverse_iterator    operator--(int) { reverse_iterator c(*this); current++; return (c); }
        
        reverse_iterator&   operator--() { current++; return (*this); }

        ////////////////////             ARITHMETIC OPRATORS       ////////////////////////

        reverse_iterator    operator+(difference_type n) const { return (reverse_iterator(current - n)); }
        reverse_iterator    operator-(difference_type n) const { return (reverse_iterator(current + n)); }
        
        reverse_iterator    operator-=(difference_type n) { current += n; return (*this); }
        reverse_iterator    operator+=(difference_type n) { current -= n; return (*this); }

    protected:

        iterator_type current;
};

template< class Iterator1, class Iterator2 >
bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
    return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
    return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
    return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
    return (lhs.base() >= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
    return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs )
{
    return (lhs.base() <= rhs.base());
}

template< class Iter >
ft::reverse_iterator<Iter>
    operator+( typename ft::reverse_iterator<Iter>::difference_type n,
               const ft::reverse_iterator<Iter>& it )
{
    return (ft::reverse_iterator<Iter>(it.base() - n)); 
}

template< class Iterator1, class Iterator2 >
typename reverse_iterator<Iterator1>::difference_type
    operator-( const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs )
{
    return (rhs.base() - lhs.base());
}

#endif 