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

//////////////////////////////////////////////////////////////////////////////////////
/////                               ::ITERATOR_TRAITS                            /////
//////////////////////////////////////////////////////////////////////////////////////

template <class Iterator>
class iterator_traits
{
  typedef Iterator                              value_type;
  typedef typename Iterator::difference_type    difference_type;
  typedef typename Iterator::pointer            pointer;
  typedef typename Iterator::reference          reference;
  typedef typename Iterator::iterator_category  iterator_category;
};

//////////////////////////////////////////////////////////////////////////////////////
/////                               ::ENABLE_IF                                  /////
//////////////////////////////////////////////////////////////////////////////////////


template <bool Cond, class T = void>  struct enable_if {};
template <class T>                    struct enable_if<true, T> { typedef T type; };


//////////////////////////////////////////////////////////////////////////////////////
/////                               ::IS_INTEGRAL                                /////
//////////////////////////////////////////////////////////////////////////////////////

template <class T, bool v>
struct integral_constant {
  typedef T value_type;
  typedef integral_constant<T,v> type;
  static constexpr bool value = v;
  constexpr operator T() { return v; }
};

template <class T>  struct is_integral :               public     ft::integral_constant<T, false> {};
template <>         struct is_integral<bool> :                    ft::integral_constant<bool, true> {};
template <>         struct is_integral<char> :                    ft::integral_constant<bool, true> {};
template <>         struct is_integral<char16_t> :                ft::integral_constant<bool, true> {};
template <>         struct is_integral<char32_t> :                ft::integral_constant<bool, true> {};
template <>         struct is_integral<wchar_t> :                 ft::integral_constant<bool, true> {};
template <>         struct is_integral<signed char> :             ft::integral_constant<bool, true> {};
template <>         struct is_integral<short int> :               ft::integral_constant<bool, true> {};
template <>         struct is_integral<int> :                     ft::integral_constant<bool, true> {};
template <>         struct is_integral<long int> :                ft::integral_constant<bool, true> {};
template <>         struct is_integral<long long int> :           ft::integral_constant<bool, true> {};
template <>         struct is_integral<unsigned char> :           ft::integral_constant<bool, true> {};
template <>         struct is_integral<unsigned short int> :      ft::integral_constant<bool, true> {};
template <>         struct is_integral<unsigned int> :            ft::integral_constant<bool, true> {};
template <>         struct is_integral<unsigned long int> :       ft::integral_constant<bool, true> {};
template <>         struct is_integral<unsigned long long int> :  ft::integral_constant<bool, true> {};


//////////////////////////////////////////////////////////////////////////////////////
/////                                 ::EQUAL                                    /////
//////////////////////////////////////////////////////////////////////////////////////

template <class InputIt1, class InputIt2>
bool  equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
  while (first1 != last1)
  {
    if (!(*first1++ == *first2++))
      return (false);
  }
  return (true);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool  equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
  while (first1 != last1)
  {
    if (!pred(first1++, first2++))
      return (false);
  }
  return (true);
}


//////////////////////////////////////////////////////////////////////////////////////
/////                        ::LEXICOGRAPHICAL_COMPARE                           /////
//////////////////////////////////////////////////////////////////////////////////////


template <class InputIterator1, class InputIterator2>
bool  lexicographical_compare (InputIterator1 first1, InputIterator1 last1, 
  InputIterator2 first2, InputIterator2 last2)
{
  while (first1 != last1)
  {
    if (first2 == last2 || *first2 < *first1) return (false);
    else if (*first1 < *first2) return (true);
      return (false);
  }
  return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool  lexicographical_compare (InputIterator1 first1, InputIterator1 last1, 
  InputIterator2 first2, InputIterator2 last2, Compare comp)
{
  while (first1 != last1)
  {
    if (first2 == last2 || !comp(first1, first2)) return (false);
    else if (comp(first1, first2)) return (true);
      return (false);
  }
  return (first2 != last2);
}

//////////////////////////////////////////////////////////////////////////////////////
/////                                 ::PAIR                                     /////
//////////////////////////////////////////////////////////////////////////////////////

template <class T1, class T2>
struct pair
{
  typedef T1  first_type;
  typedef T2  second_type;

  first_type  first;
  second_type second;

  pair() : first(), second() {}

  template <class U, class V>
  pair (const pair<U, V> & pr) { *this = pr; }

  pair (const first_type & a, const second_type & b) : first(a), second(b) {}

  pair & operator=(const pair & pr)
  {
    if (this != &pr)
    {
      first = pr.first;
      second = pr.second;
    }
    return (*this);
  }
};

template <class T1, class T2>
bool  operator==(const ft::pair<T1, T2> & lhs, const ft::pair<T1, T2> & rhs)
{
  return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template <class T1, class T2>
bool  operator!=(const ft::pair<T1, T2> & lhs, const ft::pair<T1, T2> & rhs)
{
  return (lhs.first != rhs.first && lhs.second != rhs.second);
}

template< class T1, class T2 >
bool operator<( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
{
  return (lhs.first < rhs.first || ((lhs.first == rhs.first) && lhs.second < rhs.second));
}

template< class T1, class T2 >
bool operator<=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
{
  return (lhs.first <= rhs.first && lhs.second <= rhs.second);
}

template< class T1, class T2 >
bool operator>( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
{
  return (lhs.first > rhs.first || ((lhs.first == rhs.first) && lhs.second > rhs.second));
}

template< class T1, class T2 >
bool operator>=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs )
{
  return (lhs.first >= rhs.first && lhs.second >= rhs.second);
}


//////////////////////////////////////////////////////////////////////////////////////
/////                                 ::MAKE_PAIR                                /////
//////////////////////////////////////////////////////////////////////////////////////

template <class T1, class T2>
pair<T1, T2>  make_pair(T1 x, T2 y)
{
  return (ft::pair<T1, T2>(x, y));
}


//////////////////////////////////////////////////////////////////////////////////////
/////                          OTHER FUNCTIONS FROM STD                          /////
//////////////////////////////////////////////////////////////////////////////////////

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
