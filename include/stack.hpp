/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:48:53 by mtellal           #+#    #+#             */
/*   Updated: 2022/12/12 09:49:29 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "containers.hpp"

template <class T, class Container = ft::vector<T> >
class stack
{
    public:

        typedef T                                   value_type;
        typedef Container                           container_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;


        explicit    stack (const container_type & ctnr = container_type()) : c(ctnr) {}
        stack( const stack& other ) : c(other.c) {}
        ~stack() {}

        stack &     operator=(const stack & other)
        {
            if (this != &other)
                c = other.c;
            return (*this);
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                              ELEMENT ACCESS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        reference       top() { return (c.back()); }

        const_reference top() const { return (c.back()); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   CAPACITY                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        bool        empty() const { return (c.empty()); }

        size_type   size() const { return (c.size()); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   MODIFIERS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        void        push(const value_type & value) { c.push_back(value); }

        void        pop() { c.pop_back(); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                          RELATIONAL OPERATORS                              /////
        //////////////////////////////////////////////////////////////////////////////////////

        template< class U, class C >
        friend bool operator==( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

        template< class U, class C >
        friend bool operator!=( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

        template< class U, class C >
        friend bool operator<( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

        template< class U, class C >
        friend bool operator<=( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

        template< class U, class C >
        friend bool operator>( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

        template< class U, class C >
        friend bool operator>=( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

    protected:

        container_type  c;
};

template< class U, class C >
bool operator==( const ft::stack<U,C>& lhs,
                            const ft::stack<U,C>& rhs )
{
    return (lhs.c == rhs.c);
}

template< class U, class C >
bool operator!=( const ft::stack<U,C>& lhs,
                            const ft::stack<U,C>& rhs )
{
    return (lhs.c != rhs.c);
}

template< class U, class C >
bool operator<( const ft::stack<U,C>& lhs,
                            const ft::stack<U,C>& rhs )
{
    return (lhs.c < rhs.c);
}

template< class U, class C >
bool operator<=( const ft::stack<U,C>& lhs,
                            const ft::stack<U,C>& rhs )
{
    return (lhs.c <= rhs.c);
}

template< class U, class C >
bool operator>( const ft::stack<U,C>& lhs,
                            const ft::stack<U,C>& rhs )
{
    return (lhs.c > rhs.c);
}

template< class U, class C >
bool operator>=( const ft::stack<U,C>& lhs,
                            const ft::stack<U,C>& rhs )
{
    return (lhs.c >= rhs.c);
}


#endif
