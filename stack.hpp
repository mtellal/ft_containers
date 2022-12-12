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

        typedef T           value_type;
        typedef Container   container_type;
        typedef size_t      size_type;


        explicit    stack (const container_type& ctnr = container_type()) : _container(ctnr) {}
        
        stack( const stack& other ) : _container(other._container) {}



        bool        empty() const { return (_container.empty()); }



    private:

        container_type  _container;
}


#endif
