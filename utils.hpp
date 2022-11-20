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

template <class Iterator>
class iterator_traits
{
  typedef Iterator                              value_type;
  typedef typename Iterator::difference_type    difference_type;
  typedef typename Iterator::pointer            pointer;
  typedef typename Iterator::reference          reference;
  typedef typename Iterator::iterator_category  iterator_category;
};

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

template<class Iterator>
Iterator copy(Iterator first, Iterator last, Iterator result)
{
  while (first!=last)
  {
    *result = *first;
    ++result; ++first;
  }
  return result;
}

#endif
