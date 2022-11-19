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

    template <class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class vIterator : public std::iterator<std::random_access_iterator_tag, T, Distance, Pointer, Reference>
    {
        typedef typename std::iterator<std::random_access_iterator_tag, T>  iterator_category;
        typedef T                                                           value_type;
        typedef Distance                                                    difference_type;
        typedef Pointer                                                     pointer;
        typedef Reference                                                   reference;

        public:

            vIterator(void) : it(NULL) {};
            vIterator(const pointer & p) : it(p) {};
            vIterator(const vIterator & v) : it(v.it) {};
            ~vIterator(void) {};
            vIterator &     operator=(const vIterator & o)
            {
                if (this != &o)
                    it = o.it;
                return (*this);
            }

            ////////////////////             IN/DECREMENTATION OPRATORS       ////////////////////////

            vIterator& operator++(void) { it++; return (*this); }
            vIterator& operator--(void){ it--; return (*this); }
            vIterator operator++(int) {vIterator old(*this); it++; return (old); }
            vIterator operator--(int) {vIterator old(*this); it--; return (old); }

            ////////////////////             ACCESS/DEFERENCE OPRATORS       ////////////////////////

            reference   operator*(void) const { return (*it); }
            pointer    operator->(void) const { return (it); }

            ////////////////////             ARITHMETIC OPRATORS       ////////////////////////

           // operator+()
           vIterator     operator+(const difference_type & n) const { return (it + n); }
           vIterator     operator-(const difference_type & n) const { return (it - n); }
           vIterator &     operator+=(const difference_type & n) { it += n; return (*this); }
           vIterator &   operator-=(const difference_type & n) { it -= n; return (*this); }

            ////////////////////             LOGICAL OPRATORS       ////////////////////////

            bool    operator==(const vIterator & obj) const { return (it == obj.it); }
            bool    operator!=(const vIterator & obj) const { return (it != obj.it); }
            bool    operator<(const vIterator & obj) const { return (it < obj.it); }
            bool    operator<=(const vIterator & obj) const { return (it <= obj.it); }
            bool    operator>(const vIterator & obj) const { return (it > obj.it); }
            bool    operator>=(const vIterator & obj) const { return (it >= obj.it); }

            ////////////////////             OFFSET OPRATORS       ////////////////////////

            const reference    operator[](const difference_type n) const { return *(it + n); }
        
        private:

            pointer it;
    };




    template < class T, class Allocator = std::allocator<T> >
    class vector
    {
        typedef T                                           value_type;

        typedef Allocator                               allocator_type;
        typedef typename Allocator::reference           reference;
        typedef typename Allocator::const_reference     const_reference;
        typedef typename Allocator::pointer             pointer;
        typedef typename Allocator::const_pointer       const_pointer;

        typedef typename Allocator::difference_type    difference_type;
        typedef typename Allocator::size_type          size_type;    

        public:

            typedef typename ft::vIterator<value_type>                                          iterator;
            typedef typename std::iterator<std::random_access_iterator_tag, const value_type>   const_iterator;
            typedef typename std::reverse_iterator<iterator>                                    reverse_iterator;
            typedef typename std::reverse_iterator<const_iterator>                              const_reverse_iterator;

            explicit vector(const allocator_type& alloc = allocator_type()) :
                allocator(alloc), _begin(NULL), _end(NULL), _nb_construct(0), _nb_allocate(0)
            
            {}

            explicit vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :
                    allocator(alloc), _begin(NULL), _end(NULL), _nb_construct(n), _nb_allocate(n)

            {
                if (n > 0)
                {
                    _begin = allocator.allocate(n);
                    _construct(n, val);
                    _end = _begin + n;
                }
            }

            template <class InputIterator>
            vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
                _begin(NULL)
            {
                (void)first;
                (void)last;
                (void)alloc;
                std::cout << " vector template constructor called " << std::endl;
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
                if (_nb_allocate > 0 && _begin)
                    allocator.deallocate(_begin, _nb_allocate);
            }

            ////////////////////             ELEMENT OPRATOR       ////////////////////////

            vector<value_type, Allocator>& operator=(const vector<value_type, Allocator> & nv)
            {                
                size_type   l;

                l = 0;
                if (this != &nv)
                {
                    clear();
                    if (_nb_allocate && _begin)
                    {
                        allocator.deallocate(_begin, _nb_allocate);
                        _begin = NULL;
                    }
                    if (!_begin)
                    {
                        _begin = allocator.allocate(nv.size());
                        _end = _begin + nv.size();
                        _nb_allocate = nv.size();
                    }
                    while (l < nv.size())
                    {
                        allocator.construct(_begin + l, nv.at(l));
                        l++;
                    }
                    _nb_construct = nv.size();
                }
                return (*this);
            }

            pointer           operator+(const size_type n) const { return (_begin + n); }

            value_type&         operator[](size_type i) const { return (*(_begin + i)); }

            reference           at(size_type n)
            {
                if (_begin && _nb_construct && n < _nb_construct)
                    return (_begin[n]);
                else
                {
                    throw std::out_of_range("vector: error: out_of_range: n (wich is "
                    + std::to_string(n)
                    + ") >= this->size() (wich is "
                    + std::to_string(this->size()) + ")");
                }
            }

            const_reference     at(size_type n) const
            {
                if (_begin && _nb_construct && n < _nb_construct)
                    return (_begin[n]);
                else
                {
                    throw std::out_of_range("vector: error: out_of_range: n (wich is "
                    + std::to_string(n)
                    + ") >= this->size() (wich is "
                    + std::to_string(this->size()) + ")");
                }
            }

            reference           front(void) { return (*_begin); }
            const_reference     front(void) const { return (*_begin); }

            reference           back(void) { return (*(_end - 1)); }
            const_reference     back(void) const { return (*(_end - 1)); }
            
            pointer             data(void) noexcept { return (_begin); }
            const_pointer       data(void) const noexcept { return (_begin); }

            //////////////////////////////////////////////////////////////////////////////////////
            /////                        MEMBERS FUNCTIONS                                   /////
            //////////////////////////////////////////////////////////////////////////////////////

            ////////////////////             ITERATORS       ////////////////////////
        
            iterator begin() const { return (_begin); }

            iterator    end(void) const { return (_end); }

            ////////////////////             CAPACITY       ////////////////////////

            size_type   size(void) const { return (_nb_construct); }

            size_type   max_size(void) const { return (_nb_allocate - _nb_construct); }

            // resize ()

            void        resize(size_type n, value_type val = value_type())
            {
                (void)n;
                (void)val;
            }

            size_type   capacity(void) const { return (_nb_allocate) ;}

            bool        empty(void) const { return (_nb_construct > 0); }

            // reserve()

            //shrink_to_fit()

            ////////////////////             ITERATORS       ////////////////////////

            allocator_type      get_allocator(void) const { return (allocator); }

            template <class InputIterator>
            void        assign(InputIterator first, InputIterator last)
            {  
                (void)first;
                (void)last;

            }

            void        assign(size_type n, const value_type & val)
            {
                if (n > _nb_allocate)
                {
                    clear();
                    _begin = allocator.allocate(n);
                }
                _construct(n, val);
            }

            void    push_back(const value_type & val)
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

            void        pop_back(void)
            {
                if (_end && (_end - 1) && _nb_construct >= 1)
                {
                    allocator.destroy(_end - 1);
                    _nb_construct--;
                }
            }

            iterator    insert(iterator position, const value_type & val)
            {
                insert(position, 1, val);
                return (position);
            }

            void        insert(iterator position, size_type n, const value_type & val)
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
            void        insert(iterator position, InputIterator first, InputIterator last)
            {
                vector      _n;
                iterator    it;
                iterator    itn;
                size_type   i;
                size_type   n;

                i = 0;
                n = ft::distance(first, last);
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
                while (first != last)
                    *itn++ = *first++;
                while (_end && position != _end)
                    *itn++ = *position++;
                _n._nb_construct = size() + n;
                *this = _n;
            }

            void        clear(void)
            {
                size_type   i;

                i = 0;
                while (i < _nb_construct && _begin)
                    allocator.destroy(_begin + i++);
                _nb_construct = 0;
            }


            void    _construct(size_type n, const value_type & val)
            {
                size_type   i;

                i = 0;
                while (i < n && i < _nb_allocate && _begin)
                    allocator.construct(_begin + i++, val);
            }

        private:

            allocator_type  allocator;
            pointer         _begin;
            pointer         _end;
            size_type       _nb_construct;
            size_type       _nb_allocate;
            

    };


#endif
