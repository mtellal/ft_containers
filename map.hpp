/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:54:16 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/23 09:54:30 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

template <class T>
struct Node
{ 
    typedef T       value_type;
    typedef T*      pointer;

    value_type      value;
    pointer         parent;
    pointer         right;
    pointer         left;
    bool            red;

    Node (void) : value(T()), parent(NULL), right(NULL), left(NULL), red(0) {}

    Node (const value_type & v, const pointer & p = 0, const pointer & r = 0, const pointer & l = 0, bool rd = 0):
    value(v), parent(p), right(r), left(l), red(rd) {}

    Node (const Node & x) : value(x.value), right(x.right), left(x.left), red(x.red) {}

    Node & operator=(const Node & x)
    {
        if (this != &x)
        {
            value = x.value;
            right = x.right;
            left = x.left;
            red = x.red;
        }
        return (*this);
    }
};

//

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > > 
class map
{

    public:
        
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef typename ft::pair<const key_type, mapped_type>          value_type;
        typedef Compare                                                 key_compare;                                          

        typedef Alloc                                                   allocate_type;
        typedef typename Alloc::reference                               reference;
        typedef typename Alloc::const_reference                         const_reference;
        typedef typename Alloc::pointer                                 pointer;
        typedef typename Alloc::const_pointer                           const_pointer;

        //define bidirectional_iterator for pair<const key, T>
        typedef typename ft::random_access_iterator<value_type>         iterator;
        typedef typename ft::random_access_iterator<const value_type>   const_iterator;
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const iterator>           const_reverse_iterator;

        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef size_t                                                  size_type;


        class value_compare
        {
            friend class map;
            
            protected:
                Compare comp;
                value_compare (Compare c) : comp(c) {}
            
            public:

                typedef bool        result_type;
                typedef value_type  first_argument_type;
                typedef value_type  second_argument_type;

                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
        };

    explicit    map(const key_compare & comp = key_compare(), const allocate_type & alloc = allocate_type()) :
        _compare(comp)
    {
        (void)comp;
        (void)alloc;
        std::cout << "map default constructor called " << std::endl;
    }

    template < class InputIterator>
    map (InputIterator first, InputIterator last, const key_type & comp = key_compare(),
        const allocate_type & alloc = allocate_type())
    {
        std::cout << "iterator constructor called" << std::endl;
        (void)first;
        (void)last;
        (void)comp;
        (void)alloc;
    }

    map(const map & x)
    {
        (void)x;
        std::cout << "copy constructor called" << std::endl;
    }

    ~map(void)
    {
        std::cout << "destructor called" << std::endl;

    }

    value_compare value_comp() const { return _compare; }

    private:

        key_type        _key;
        value_type      _value;
        value_compare   _compare;

        allocate_type   _allocator;
        size_t          _nb_construct;
        size_t          _nb_allocate;



        

};


#endif
