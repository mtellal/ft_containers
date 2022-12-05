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

            typedef typename ft::random_access_iterator<value_type>         iterator;
            typedef typename ft::random_access_iterator<const value_type>   const_iterator;
            typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
            typedef typename ft::reverse_iterator<const iterator>           const_reverse_iterator;


            //////////////////////////////////////////////////////////////////////////////////////
            /////                         CONSTRUCTORS / DESTRUCTOR                          /////
            //////////////////////////////////////////////////////////////////////////////////////


            explicit vector(const allocator_type& alloc = allocator_type()) :

                allocator(alloc), _begin(NULL), _end(NULL), _nb_construct(0), _nb_allocate(0)
            {}


            explicit vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :
            
            allocator(alloc), _begin(NULL), _end(NULL), _nb_construct(n), _nb_allocate(n)

            {
                size_type   i = 0;

                if (n > 0)
                {
                    _begin = allocator.allocate(n);
                    _end = _begin + n;
                    while (i < n)
                        *(_begin + i++) = val;
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
                _end = _begin + l;
                _nb_construct = l;
                _nb_allocate = l;
                i = 0;
                while (first != last)
                {
                    allocator.construct(_begin + i, *first++);
                    i++;
                }
            }


            vector(const vector& x) : 

            allocator(x.allocator), _begin(NULL), _end(NULL),
            _nb_construct(x._nb_construct), _nb_allocate(x._nb_allocate)

            {
                if (this != &x)
                {
                    if (x.size() > 0)
                    {
                        _begin = allocator.allocate(x.size());
                        _end = _begin + x.size();
                        std::copy(x._begin, x._end, _begin);
                        _nb_allocate = x.size();
                        _nb_construct = _nb_allocate;
                    }
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
                iterator    it;
                size_type   i;


                if (this != &nv)
                {
                    clear();
                    i = 0;
                    if (nv._nb_construct > _nb_allocate)
                    {
                        if (_begin)
                            allocator.deallocate(_begin, _nb_allocate);
                        _begin = allocator.allocate(nv._nb_construct);
                        _end = _begin + nv._nb_construct;
                        _nb_allocate = nv._nb_construct;
                    }
                    _nb_construct = nv._nb_construct;                    
                    while (i < nv._nb_construct)
                    {
                        allocator.construct(_begin + i, nv[i]);
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
                    _end = _begin + l;
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
                    _end = _begin + n;
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
                {
                    //rewrite error message
                    throw std::out_of_range("vector: error: out_of_range: n (wich is ");
                   /*  + std::string(n)
                    + ") >= this->size() (wich is "
                    + std::string(this->size()) + ")"); */
                }
            }


            const_reference     at(size_type n) const
            {
                if (_begin && _nb_construct && n < _nb_construct)
                    return (_begin[n]);
                else
                {
                    // rewrite error message
                    throw std::out_of_range("vector: error: out_of_range: n (wich is ");
                    /* + std::string(n)
                    + ") >= this->size() (wich is "
                    + std::string(this->size()) + ")"); */
                }
            }


            reference           front(void) { return (*_begin); }
            const_reference     front(void) const { return (*_begin); }


            reference           back(void) { return (*(_end - 1)); }
            const_reference     back(void) const { return (*(_end - 1)); }
            

            pointer             data(void) { return (_begin); }
            const_pointer       data(void) const { return (_begin); }


            //////////////////////////////////////////////////////////////////////////////////////
            /////                               ITERATORS                                    /////
            //////////////////////////////////////////////////////////////////////////////////////

        
            iterator            begin() const { return (_begin); }
            iterator            end(void) const { return (_end); }
            

            /* !!!!!!!!!!!!!!!!     NEED MORE TESTS     !!!!!!!!!!!!!!!! */
            reverse_iterator    rbegin(void) { return (reverse_iterator(end() - 1)); }
            const_reverse_iterator  rbegin(void) const { return (const_reverse_iterator(end() - 1)); }

            // need more tests
            reverse_iterator    rend(void) { return (reverse_iterator(begin())); }
            const_reverse_iterator  rend(void) const { return (const_reverse_iterator(begin())); }

            //////////////////////////////////////////////////////////////////////////////////////
            /////                               CAPACITY                                     /////
            //////////////////////////////////////////////////////////////////////////////////////


            size_type           size(void) const { return (_nb_construct); }

            size_type           max_size(void) const { return (allocator.max_size()); }

            void                resize(size_type n, value_type val = value_type())
            {
                if (n == _nb_construct)
                    return ;
                if (n < _nb_construct)
                {
                    for (size_type i = 0; n + i < _nb_construct; i++)
                        allocator.destroy(_begin + n + i);
                    _nb_construct -= (_nb_construct - n);
                }
                else if (n > _nb_allocate)
                {
                    vector          _n(*this);

                    clear();
                    if (n > _nb_allocate)
                    {
                        allocator.deallocate(_begin, _nb_allocate);
                        while (_nb_allocate && _nb_allocate < n)
                            _nb_allocate *= 2;
                        _begin = allocator.allocate(_nb_allocate ? _nb_allocate : 1);
                        _end = _begin + n;
                        _nb_construct = n;
                    }
                    for (size_type i = 0; i < _n._nb_construct; i++)
                        allocator.construct(_begin + i, _n._begin[i]);
                    for (size_type i = _n.size(); i < n; i++)
                        allocator.construct(_begin + i, val);
                }
                else if (n > _nb_construct)
                {
                    for (size_type i = 0; i < (n - _nb_construct); i++)
                        allocator.construct(_begin + i, val);
                }
            }

            size_type           capacity(void) const { return (_nb_allocate) ;}

            bool                empty(void) const { return (!_nb_construct); }

            void                reserve(size_type n)
            {
                if (n > max_size())
                    throw std::length_error("vector::reverse()");
                else if (n > _nb_allocate)
                {
                    vector  _n(*this);

                    clear();
                    allocator.deallocate(_begin, _nb_allocate);
                    while (_nb_allocate && _nb_allocate < n)
                        _nb_allocate *= 2;
                    _begin = allocator.allocate(_nb_allocate);
                    _end = _begin + _n._nb_construct;
                    _nb_construct = _n._nb_construct;
                    for (size_type i = 0; i < _n._nb_construct; i++)
                        *(_begin + i) = *(_n._begin + i);
                }
            }
           
            //////////////////////////////////////////////////////////////////////////////////////
            /////                               MODIFIERS                                    /////
            //////////////////////////////////////////////////////////////////////////////////////

            void                push_back(const value_type & val)
            {
                size_type   old_nb_cons;

                old_nb_cons = _nb_construct;
                if (_nb_construct >= _nb_allocate)
                {
                    vector  old(*this);
                
                    clear();
                    allocator.deallocate(_begin, _nb_allocate);
                    _begin = allocator.allocate(_nb_construct * 2);
                    _nb_allocate = old._nb_construct * 2;
                    *this = old;
                } 
                else if (!_begin)
                {
                    _begin = allocator.allocate(1);
                    _nb_allocate = 1;
                }
                allocator.construct(_begin + old_nb_cons, val);
                _nb_construct++;
            }


            void                pop_back(void)
            {
                if (_end && (_end - 1) && _nb_construct >= 1)
                {
                    allocator.destroy(_end - 1);
                    _nb_construct--;
                }
            }


            iterator            insert(iterator position, const value_type & val)
            {
                insert(position, 1, val);
                return (position);
            }


            void                insert(iterator position, size_type n, const value_type & val)
            {
                vector      _n;
                iterator    it;
                iterator    itn;
                size_type   i;

                i = 0;
                if (_nb_construct + n > _nb_allocate)
                {
                    while (_nb_allocate && _nb_construct + n > _nb_allocate)
                        _nb_allocate *= 2;
                    _n._begin = allocator.allocate(_nb_allocate ? _nb_allocate : 1);
                    _n._nb_allocate = _nb_allocate ? _nb_allocate : 1;
                    _n._nb_construct = size();
                }
                it = _begin;
                itn = _n._begin;
                while (_begin && it != position) 
                    *itn++ = *it++; 
                for (size_type i = 0; i < n; i++)
                    *itn++ = val;
                while (_end && position != _end)
                    *itn++ = *position++;
                _n._nb_construct = size() + n;
                *this = _n;
            }


            template <class InputIterator>
            void                insert(iterator position, InputIterator first, InputIterator last)
            {
                vector      _new;
                iterator    it;
                iterator    itnew;

                if (first == last)
                    return ;

                _new._nb_construct = _nb_construct + ft::distance(first, last);
                _new._nb_allocate = _nb_allocate;

                while (_new._nb_allocate && _new._nb_construct > _new._nb_allocate)
                    _new._nb_allocate *= 2;
                _new._begin = allocator.allocate(_new._nb_allocate ? _new._nb_allocate : 1);
                _new._nb_allocate = _new._nb_allocate ? _new._nb_allocate : 1;
                _new._end = _new._begin + _new._nb_construct;

                it = begin();
                itnew = _new.begin();

                while (_begin && it != position) 
                {
                    allocator.construct((itnew++).base(), *it++);
                }
                while (first != last)
                {
                    allocator.construct((itnew++).base(), *first++);
                }
                while (_end && it.base() != _end)
                {
                    allocator.construct((itnew++).base(), *it++);
                }
               *this = _new;
            }


            iterator            erase(iterator position)
            {
                size_type   l;
                vector  _n;

                if (position >= end())
                    return (end());
                if (position < begin())
                    return (begin());
                l = ft::distance(begin(), position);
                _n._begin = allocator.allocate(l);
                _n._end = _begin + l;
                _n._nb_construct = l;
                _n._nb_allocate = l;
                std::copy(begin(), position, _n.begin());
                *this = _n;
                return (end() - 1);
            }

            iterator            erase(iterator first, iterator last)
            {
                size_type   l;
                vector      _n;
                iterator    it;
                iterator    itn;

                if (first >= end())
                    return (end());
                else if (last < begin())
                    return (begin());
                else if (first > last)
                    return (last);

                l = ft::distance(begin(), first);
                if (last != end())
                   l += ft::distance(last + 1, end());
                _n._begin = allocator.allocate(l);
                _n._end = _begin + l;
                _n._nb_construct = l;
                _n._nb_allocate = l;

                it = begin();
                itn = _n.begin();
                while (it < first)
                    *itn++ = *it++;
                while (it != last)
                    it++;
                if (last != end())
                    it++;
                while (it < end())
                    *itn++ = *it++;
                *this = _n;
                return (end() - 1);
            }

            void                swap(vector & x)
            {
                vector _n(*this);

                *this = x;
                x = _n;
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
            pointer         _end;
            size_type       _nb_construct;
            size_type       _nb_allocate;
            
    };


#endif
