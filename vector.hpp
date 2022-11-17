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
        typedef T                                           value_type;

        typedef Allocator                               allocator_type;
        typedef typename Allocator::reference           reference;
        typedef typename Allocator::const_reference     const_reference;
        typedef typename Allocator::pointer             pointer;
        typedef typename Allocator::const_pointer       const_pointer;

        typedef typename Allocator::difference_type    difference_type;
        typedef typename Allocator::size_type          size_type;    

        public:

            typedef typename std::iterator<std::random_access_iterator_tag, value_type>         iterator;
            typedef typename std::iterator<std::random_access_iterator_tag, const value_type>   const_iterator;
            typedef typename std::reverse_iterator<iterator>                                    reverse_iterator;
            typedef typename std::reverse_iterator<const_iterator>                              const_reverse_iterator;


            explicit vector(const allocator_type& alloc = allocator_type()) :
                allocator(alloc), _begin(NULL), _end(NULL), _nb_construct(0), _nb_allocate(0)
            
            {}

            explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
                allocator(alloc), _begin(NULL), _end(NULL), _nb_construct(n), _nb_allocate(n)

            {
                size_type i;

                i = 0;
                if (n > 0)
                {
                    _begin = allocator.allocate(n);
                    while (i < n)
                        allocator.construct(_begin + i++, val);
                    _end = _begin + --i;
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
                std::cout << " Copy constructor called (FT::VECTOR) " << std::endl;
                size_type   l;

                l = 0;
                if (this != &x)
                {
                    if (x.size() > 0)
                    {
                        _begin = allocator.allocate(x.size());
                        _end = _begin + x.size() - 1;
                        while (l < x.size())
                        {
                            this->_begin[l] = x[l];
                            l++;
                        }
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
                std::cout << "= operator called" << std::endl;
                
                size_type   l;

                l = 0;
                if (this != &nv)
                {
                    if (_nb_construct > 0)
                        destroy(_begin, _nb_construct);
                    if (!_begin)
                    {
                        _begin = allocator.allocate(nv.size());
                        _end = _begin + nv.size() - 1;
                        _nb_allocate = nv.size();
                    }
                    while (l < nv.size())
                    {
                        _begin[l] = nv[l];
                        l++;
                    }
                    _nb_construct = nv.size();
                }
                return (*this);
            }

            value_type&         operator[](size_type i) const
            {
                return (*(_begin + i));
            }

            reference           at(size_type n)
            {
                if (_begin && _nb_construct && n < _nb_construct)
                {
                    std::cout << "inside" << std::endl;
                    return (_begin[n]);
                }
                else
                {
                    throw std::out_of_range("vector: error: out_of_range: n (wich is " + std::to_string(n) + 
                    ") >= this->size() (wich is " + std::to_string(this->size()) + ")");
                }
            }

            const_reference     at(size_type n) const
            {
                if (_begin && _nb_construct && n < _nb_construct)
                {
                    std::cout << "inside" << std::endl;
                    return (_begin[n]);
                }
                else
                {
                    throw std::out_of_range("vector: error: out_of_range: n (wich is " + std::to_string(n) + 
                    ") >= this->size() (wich is " + std::to_string(this->size()) + ")");
                }
            }

            reference           front(void)
            {
                return (*_begin);
            } 

            const_reference     front(void) const
            {
                return (*_begin);
            }

            reference           back(void)
            {
                return (*_end);
            } 

            const_reference     back(void) const
            {
                return (*_end);
            } 

            pointer             data(void) noexcept
            {
                return (_begin);
            }

            const_pointer       data(void) const noexcept
            {
                return (_begin);
            }

            //////////////////////////////////////////////////////////////////////////////////////
            /////                        MEMBERS FUNCTIONS                                   /////
            //////////////////////////////////////////////////////////////////////////////////////


            ////////////////////             CAPACITY       ////////////////////////

            size_type   size(void) const
            {
                return (_nb_construct);
            }

            size_type   max_size(void) const
            {
                return (_nb_allocate - _nb_construct);
            }

            // resize ()
            void        resize(size_type n, value_type val = value_type())
            {
                (void)n;
                (void)val;
            }

            size_type   capacity(void) const
            {
                return (_nb_allocate);
            }

            bool        empty(void) const
            {
                return (_nb_construct > 0 ? false : true);
            }

            // reserve()

            //shrink_to_fit()



            void    destroy(pointer p, size_type n)
            {
                size_type   i;

                i = 0;
                while (p && p[i] && i < n)
                    allocator.destroy(p + i++);
            }


            void    push_back(const value_type & val)
            {
                (void)val;
                // verifier si assez de place

                if (_nb_allocate <= _nb_construct + 1)
                {
                    ft::vector<T, Allocator> v;

                    v = *this;
                    allocator.destroy(_begin);
                    allocator.deallocate(_begin, _nb_allocate);
                    this->_begin = allocator.allocate(_nb_construct * 2);
                    *this = v;
                    
                }
                // sinon -> allouer + de place + construct
                
                //si oui -> allocator.construct(p, val)
            }
            
            pointer begin()
            {
                return _begin;
            }




        private:

            allocator_type  allocator;
            pointer         _begin;
            pointer         _end;
            size_type       _nb_construct;
            size_type       _nb_allocate;
            

    };


#endif
