/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:04:34 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/19 16:04:58 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

template <class InputIterator>
size_t       distance(InputIterator first, InputIterator last)
{
    size_t   l = 0;

    while (first != last)
    {
        first++;
        l++;
    }
    return (l);
}


#endif
