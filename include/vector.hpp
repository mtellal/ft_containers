/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:27:29 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/15 09:28:15 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

    template < class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:

            typedef T                                           value_type;

            typedef Allocator                               allocator_type;
            typedef typename Allocator::reference           reference;
            typedef typename Allocator::const_reference     const_reference;
            typedef typename Allocator::pointer             pointer;
            typedef typename Allocator::const_pointer       const_pointer;

            typedef typename Allocator::difference_type     difference_type;
            typedef size_t                                  size_type;

            typedef  ft::random_access_iterator<value_type>         iterator;
            typedef  ft::random_access_iterator<const value_type>   const_iterator;
            typedef  ft::reverse_iterator<iterator>                 reverse_iterator;
            typedef  ft::reverse_iterator<const_iterator>           const_reverse_iterator;


            //////////////////////////////////////////////////////////////////////////////////////
            /////                         CONSTRUCTORS / DESTRUCTOR                          /////
            //////////////////////////////////////////////////////////////////////////////////////


            explicit vector(const allocator_type& alloc = allocator_type()) : allocator(alloc),
                _begin(NULL), _nb_construct(0), _nb_allocate(0)
            {}


            explicit vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :
            
            allocator(alloc), _begin(NULL), _nb_construct(n), _nb_allocate(n)

            {
                size_type   i = 0;

                if (n > 0)
                {
                    _begin = allocator.allocate(n);
                    while (i < n)
                        allocator.construct(_begin + i++, val);
                }
            }


            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0) 
                
                : allocator(alloc)
            {
                size_type       l;
                size_type       i;

                l = ft::distance(first, last);
                _begin = allocator.allocate(l);
                _nb_construct = l;
                _nb_allocate = l;
                i = 0;
                while (first != last)
                {
                    allocator.construct(_begin + i, *first++);
                    i++;
                }
            }


            vector(const vector& x) : allocator(x.allocator),
                _begin(NULL), _nb_construct(0), _nb_allocate(0)

            {
                const_iterator    first;
                iterator    it;

                if (this != &x)
                {
                    _begin = allocator.allocate(x.capacity());
                    _nb_allocate = x.capacity();
                    it = begin();
                    first = x.begin();
                    while (first != x.end())
                    {
                        allocator.construct(it++.base(), *first++);
                    }
                    _nb_construct = x.size();
                }
            }

            ~vector() 
            {
                if (_nb_construct && _begin)
                    clear();
                if (_nb_allocate && _begin)
                {
                    allocator.deallocate(_begin, _nb_allocate);
                }
            }



            //////////////////////////////////////////////////////////////////////////////////////
            /////                            MEMBERS FUNCTIONS                               /////
            //////////////////////////////////////////////////////////////////////////////////////


            vector<value_type, Allocator> & operator=(const vector<value_type, Allocator> & nv)
            {
                size_type   i;
                size_type   n;

                if (this != &nv)
                {
                    n = _nb_construct;
                    clear();
                    if (nv._nb_construct > n)
                    {
                        if (_begin)
                            allocator.deallocate(_begin, n);
                        _begin = allocator.allocate(nv._nb_allocate);
                        _nb_allocate = nv._nb_construct;
                    }
                    i = 0;
                    _nb_construct = nv._nb_construct;
                    while (_begin && i < _nb_construct)
                    {
                        allocator.construct(_begin + i, nv.at(i));
                        i++;
                    }
                }
                return (*this);
            }


            template <class InputIterator>
            void                assign(InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0)
            {
                size_type   l;
                iterator    it;

                l = ft::distance(first, last);
                clear();
                if (l > _nb_allocate)
                {
                    if (_begin)
                        allocator.deallocate(_begin, _nb_allocate);
                    _begin = allocator.allocate(l);
                    _nb_allocate = l;
                }
                _nb_construct = l;
                it = begin();
                while (first != last)
                    *it++ = *first++;
            }


            void                assign(size_type n, const value_type & val)
            {
                size_type   i;

                i = 0;
                clear();
                if (n > _nb_allocate)
                {
                    if (_begin)
                        allocator.deallocate(_begin, _nb_allocate);
                    _begin = allocator.allocate(n);
                    _nb_allocate = n;
                }
                _nb_construct = n;
                while (i < n)
                    allocator.construct(_begin + i++, val);
            }


            allocator_type      get_allocator(void) const { return (allocator); }


            //////////////////////////////////////////////////////////////////////////////////////
            /////                            ELEMENTS ACCES                                  /////
            //////////////////////////////////////////////////////////////////////////////////////

            pointer             operator+(const size_type n) const { return (_begin + n); }

            value_type&         operator[](size_type i) const { return (*(_begin + i)); }

            reference           at(size_type n)
            {
                if (_begin && _nb_construct && n < _nb_construct)
                    return (_begin[n]);
                else
                   throw std::out_of_range("vector: error: out_of_range");
            }

            const_reference     at(size_type n) const
            {
                if (_begin && _nb_construct && n < _nb_construct)
                    return (_begin[n]);
                else
                    throw std::out_of_range("vector: error: out_of_range");
            }

            reference           front() { return (*_begin); }
            const_reference     front() const { return (*_begin); }


            reference           back() { return (*(end() - 1)); }
            const_reference     back() const { return (*(end() - 1)); }
            

            pointer             data() { return (_begin); }
            const_pointer       data() const { return (_begin); }


            //////////////////////////////////////////////////////////////////////////////////////
            /////                               ITERATORS                                    /////
            //////////////////////////////////////////////////////////////////////////////////////

            iterator            begin() { return (_begin); }
            const_iterator      begin() const { return (_begin); }

            iterator            end()  { return (_begin + size()); }
            const_iterator      end() const { return (_begin + size()); }
              
            reverse_iterator    rbegin() { return (reverse_iterator(end())); }
            const_reverse_iterator  rbegin() const { return (const_reverse_iterator(end())); }

            reverse_iterator    rend() { return (reverse_iterator(begin())); }
            const_reverse_iterator  rend() const { return (const_reverse_iterator(begin())); }

            //////////////////////////////////////////////////////////////////////////////////////
            /////                               CAPACITY                                     /////
            //////////////////////////////////////////////////////////////////////////////////////

            size_type           size() const { return (_nb_construct); }

            size_type           max_size() const { return (allocator.max_size()); }

            void                resize(size_type n, value_type val = value_type())
            {
                if (n == _nb_construct)
                    return ;
                if (n < _nb_construct)
                {
                    for (size_type i = n; i < _nb_construct; i++)
                        allocator.destroy(_begin + i);
                }
                else if (n > _nb_allocate)
                {
                    vector          old(*this);
                    size_type       i = 0;

                    clear();
                    if (_begin)
                        allocator.deallocate(_begin, _nb_allocate);
                    if (!_nb_allocate && n)
                        _nb_allocate = 1;
                    while (_nb_allocate < n)
                        _nb_allocate *= 2;
                    _begin = allocator.allocate(_nb_allocate);

                    while (i < old.size())
                    {
                        allocator.construct(_begin + i, old[i]);
                        i++;
                    }
                    while (i < n)
                        allocator.construct(_begin + i++, val);
                    _nb_construct = n;
                }
                else if (n > _nb_construct)
                {
                    for (size_type i = _nb_construct; i < n; i++)
                        allocator.construct(_begin + i, val);
                }
                _nb_construct = n;
            }

            size_type           capacity() const { return (_nb_allocate) ;}

            bool                empty() const { return (!_nb_construct); }

            void                reserve(size_type n)
            {
                vector      _n;

                if (n > max_size())
                {
                    throw std::length_error("vector::reverse()");
                }
                else if (n > _nb_allocate)
                {
                    _n = *this;
                    clear();
                    if (_begin)
                        allocator.deallocate(_begin, _n._nb_allocate);
                    if (!_n._nb_allocate)
                        _n._nb_allocate = 1;
                    while (n > _n._nb_allocate)
                        _n._nb_allocate *= 2;
                    _begin = allocator.allocate(_n._nb_allocate);
                    _nb_construct = _n._nb_construct;
                    _nb_allocate = _n._nb_allocate;
                    for (size_type i = 0; i < _n._nb_construct; i++)
                        allocator.construct(_begin + i, *(_n + i));
                }
            }
           
            //////////////////////////////////////////////////////////////////////////////////////
            /////                               MODIFIERS                                    /////
            //////////////////////////////////////////////////////////////////////////////////////

            void                push_back(const value_type & val)
            {
                insert(end(), 1, val);
            }


            void                pop_back(void)
            {
                if (_nb_construct >= 1)
                {
                    allocator.destroy((--end()).base());
                    _nb_construct--;
                }
            }

            iterator            insert(iterator position, const value_type & val)
            {
                size_type i;

                i = ft::distance(begin(), position);
                insert(position, 1, val);
                return (_begin + i);
            }


            void                insert(iterator position, size_type n, const value_type & val)
            {
                vector      _new(*this);
                iterator    it;
                iterator    itnew;

                if (!n)
                    return ;
                _new.resize(_nb_construct + n);
                it = begin();
                itnew = _new.begin();

                while (_begin && it != position) 
                    allocator.construct((itnew++).base(), *it++);
                size_type   i = 0;
                while (i < n)
                {
                    allocator.construct((itnew++).base(), val);
                    i++;
                }
                while (it != end())
                    allocator.construct((itnew++).base(), *it++);
               *this = _new;
            }


            template <class InputIterator>
            void                insert(iterator position, InputIterator first, InputIterator last, 
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, int>::type = 0)
            {
                vector      _new;
                iterator    it;
                iterator    itnew;

                if (first == last)
                    return ;

                _new.resize(_nb_construct + ft::distance(first, last));

                it = begin();
                itnew = _new.begin();

                while (_begin && it != position) 
                    allocator.construct((itnew++).base(), *it++);
                while (first != last)
                    allocator.construct((itnew++).base(), *first++);
                while (it != end())
                    allocator.construct((itnew++).base(), *it++);
               *this = _new;
            }


            iterator            erase(iterator position)
            {
                return (erase(position, position + 1));
            }

            iterator            erase(iterator first, iterator last)
            {
                size_type   i;
                size_type   l;
                iterator    it;
                iterator    itnew;
                vector      _new;

                if (first >= end())
                    return (end());
                else if (last < begin())
                    return (begin());
                else if (first > last)
                    return (last);
                
                
                l = ft::distance(begin(), first);
                i = _nb_construct - ft::distance(first, last);

                _new._begin = allocator.allocate(i);
                _new._nb_construct = i;
                _new._nb_allocate = i;

                it = begin();   
                itnew = _new.begin();
                while (it != first)
                    allocator.construct((itnew++).base(), *it++);
                while (it != last)
                    it++;
                while (it != end())
                    allocator.construct((itnew++).base(), *it++);
                *this = _new;
                return (_begin + l);
            }

            void                swap(vector & x)
            {
                allocator_type  atmp;
                pointer         ptmp;
                size_type       consttmp;
                size_type       alloctmp;

                atmp = x.allocator;
                ptmp = x._begin;
                consttmp = x._nb_construct;
                alloctmp = x._nb_allocate;

                x._begin = _begin;
                x.allocator = allocator;
                x._nb_construct = _nb_construct;
                x._nb_allocate = _nb_allocate;

                _begin = ptmp;
                allocator = atmp;
                _nb_construct = consttmp;
                _nb_allocate = alloctmp;
            }

            void                clear(void)
            {
                size_type   i;

                i = 0;
                while (i < _nb_construct && _begin)
                    allocator.destroy(_begin + i++);
                _nb_construct = 0;
            }

        private:

            allocator_type  allocator;
            pointer         _begin;
            size_type       _nb_construct;
            size_type       _nb_allocate;
            
    };

template< class T, class Alloc >
bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
    return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && 
            !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
    return (!(lhs == rhs));
}

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs )
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
    return (!(rhs < lhs));
}

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
    return (rhs < lhs);
}

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs )
{
    return (!(lhs < rhs));
}

#endif
