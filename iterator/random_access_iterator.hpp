/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:19:31 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/23 09:20:01 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

    template <class T>
    class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:

            typedef typename ft::iterator<ft::random_access_iterator_tag, T>    iterator;
            typedef typename iterator::iterator_category                        iterator_category;
            typedef typename iterator::value_type                               value_type;
            typedef typename iterator::difference_type                          difference_type;
            typedef typename iterator::pointer                                  pointer;
            typedef typename iterator::reference                                reference;

            random_access_iterator(void) : it(NULL) {};
            random_access_iterator(const pointer & p) : it(p) {};
            random_access_iterator(const random_access_iterator & v) : it(v.it) {};
            ~random_access_iterator(void) {};

            random_access_iterator &     operator=(const random_access_iterator & o)
            {
                if (this != &o)
                    it = o.it;
                return (*this);
            }

            pointer         base(void) const { return (it); }        

            ////////////////////             IN/DECREMENTATION OPRATORS       ////////////////////////

            random_access_iterator&      operator++(void) { it++; return (*this); }
            random_access_iterator       operator++(int) {random_access_iterator old(*this); it++; return (old); }
            random_access_iterator&      operator--(void){ it--; return (*this); }
            random_access_iterator       operator--(int) {random_access_iterator old(*this); it--; return (old); }

            ////////////////////             ACCESS/DEFERENCE OPRATORS       ////////////////////////

            reference       operator*(void) const { return (*it); }
            pointer         operator->(void) const { return (it); }

            ////////////////////             ARITHMETIC OPRATORS       ////////////////////////

           // operator+()
           random_access_iterator        operator+(const difference_type & n) const { return (it + n); }
           random_access_iterator        operator-(const difference_type & n) const { return (it - n); }
           random_access_iterator &      operator+=(const difference_type & n) { it += n; return (*this); }
           random_access_iterator &      operator-=(const difference_type & n) { it -= n; return (*this); }

            ////////////////////             OFFSET OPRATORS       ////////////////////////

            const reference operator[](const difference_type n) const { return *(it + n); }
        
        private:

            pointer it;
    };

template <class T>
bool    operator==(const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
{
    return (lhs.base() == rhs.base());
} 

template <class T>
bool    operator!=(const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
{
    return (lhs.base() != rhs.base());
}

template <class T>
bool    operator>(const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
{
    return (lhs.base() > rhs.base());
}

template <class T>
bool    operator>=(const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
{
    return (lhs.base() >= rhs.base());
}

template <class T>
bool    operator<(const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
{
    return (lhs.base() == rhs.base());
}

template <class T>
bool    operator<=(const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
{
    return (lhs.base() == rhs.base());
}
#endif