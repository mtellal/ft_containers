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

        typedef Iterator                                iterator_type;
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;

        reverse_iterator() : it() {}

        explicit reverse_iterator(iterator_type x) : it(x) {}

        template<class U>
        reverse_iterator (const reverse_iterator<U> & other) : it(other.base()) {}

        iterator_type   base(void) const { return (it); }

        reference           operator*(void) const { return (*(it - 1)); }
        reverse_iterator    operator+(difference_type n) const { return (reverse_iterator(it - n)); }
        reverse_iterator    operator-(difference_type n) const { return reverse_iterator(it + n); }


        reverse_iterator    operator++(void) { return (--it); }
        reverse_iterator    operator++(int) { reverse_iterator _n(*this); it -= 1; return (_n); }
        reverse_iterator    operator+=(difference_type n) { return (it + n); }

        reverse_iterator    operator--(void) { return (++it); }
        reverse_iterator    operator--(int) { reverse_iterator _n(*this); it += 1; return (_n); }
        reverse_iterator    operator-=(difference_type n) { return (it - n); }

        pointer             operator->(void) const { return (*it); }
        iterator_type       operator[](difference_type n) { return (it - n); }

    private:

        Iterator it;
};

template <class Iterator>
bool    operator==(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
    return (lhs.base == rhs.base);
} 

template <class Iterator>
bool    operator!=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
    return (lhs.base != rhs.base);
}

template <class Iterator>
bool    operator>(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
    return (lhs.base > rhs.base);
}

template <class Iterator>
bool    operator>=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
    return (lhs.base >= rhs.base);
}

template <class Iterator>
bool    operator<(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
    return (lhs.base == rhs.base);
}

template <class Iterator>
bool    operator<=(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
{
    return (lhs.base == rhs.base);
}

#endif 