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

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
class map
{

    public:
        
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        // std::map accept std::pair<key/const key> => segfault for me 
        typedef typename ft::pair<const key_type, mapped_type>          value_type;
        typedef Compare                                                 key_compare;                                          

        typedef Alloc                                                   allocate_type;
        typedef typename Alloc::reference                               reference;
        typedef typename Alloc::const_reference                         const_reference;
        typedef typename Alloc::pointer                                 pointer;
        typedef typename Alloc::const_pointer                           const_pointer;

        typedef typename ft::RedBlackTreeIterator<ft::Node<value_type>, key_compare>            iterator;
        typedef typename ft::RedBlackTreeIterator<ft::Node< const value_type>, key_compare>     const_iterator;
        typedef typename ft::reverse_iterator<iterator>                                         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>                                   const_reverse_iterator;

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

                value_compare(){};
                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
        };

        explicit    map(const key_compare & comp = key_compare(), const allocate_type & alloc = allocate_type()) :
            _compare(comp), _nb_construct(0), _nb_allocate(0)
        {
            (void)comp;
            (void)alloc;
            std::cout << "map default constructor called " << std::endl;
        }

        template < class InputIterator>
        map (InputIterator first, InputIterator last, const key_type & comp = key_compare(),
            const allocate_type & alloc = allocate_type()) : _nb_construct(0), _nb_allocate(0)
        {
            std::cout << "map iterator constructor called" << std::endl;
            (void)first;
            (void)last;
            (void)comp;
            (void)alloc;
        }

        map(const map & x) : _nb_construct(0), _nb_allocate(0)
        {
            (void)x;
            std::cout << "map copy constructor called" << std::endl;
        }

        ~map(void)
        {
            std::cout << "map destructor called" << std::endl;
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   ITERATORS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        /* !!!!!!!!!!!!!!!!!!!!!!  NEED MORE TESTS (CONST + REVERSE) !!!!!!!!!!!!! */

        iterator                begin() { return (_tree.begin()); }

        const_iterator          begin() const { return (_tree.begin()); }

        iterator                end() { return (_tree.end()); }

        const_iterator          end() const { return (_tree.end()); }

        reverse_iterator        rbegin() { return (reverse_iterator(_tree.end())); }
        
        const_reverse_iterator  rbegin() const { return (reverse_iterator(_tree.end())); }

        reverse_iterator        rend() { return (reverse_iterator(_tree.begin())); }

        const_reverse_iterator  rend() const { return (reverse_iterator(_tree.begin())); }
        
        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   CAPACITY                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        size_type       size() const { return (_tree.size()); }

        bool            empty() const { return (begin() == end()); }

        size_type       max_size(void) const { return (_allocator.max_size()); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                              ELEMENT ACCESS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        // std::outofrange thrown
        T &             at(const Key & key)
        {
            iterator    it;

            it = find(key);
            if (!it.base())
                throw std::out_of_range("Element does not exists");
            return (it->second);
        }

        const   T &     at(const Key & key) const
        {
            iterator    it;

            it = find(key);
            if (!it.base())
                throw std::out_of_range("Element does not exists");
            return (it->second);
        }

        mapped_type &   operator[](const key_type & k)
        {
            iterator it;

            it = insert(ft::make_pair(k, mapped_type())).first;
            return (it->second);
        }


        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   MODIFIERS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        pair<iterator, bool>    insert(const value_type & val)
        {
            iterator    it;
            size_type   n;

            n = size();
            it = _tree.insert(val);
            if (n + 1 == size())
            {
                _nb_construct++;
                _nb_allocate++;
                return (ft::pair<iterator, bool>(it, true));
            }
            else
                return (ft::pair<iterator, bool>(it, false));
        }

        // !!!!!!! need more tests !!!!!!!!

        iterator    insert(iterator position, const value_type & val)
        {
            iterator    it;

            it = _tree.insert(position, val);
            return (it);
        }

        template <class InputIterator>
        void    insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                insert(ft::make_pair(first->first, first->second));
                first++;
            }
        }


        void        erase(iterator position)
        {
            _tree.erase(position);
        }
        
        size_type   erase(const key_type & k)
        {
            iterator    it;

            it = find(k);
            if (it)
            {
               erase(it);
                return (1);
            }
            return (0);
        }

        void    erase(iterator first, iterator last)
        {
            iterator    it;

            while (first != last)
            {
                it = first;
                first++;
                erase(it);
            }
        }



        // !!!! need more tests + fixed x errors from contexts

        void    clear() { _tree.clear(); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  OBSERVERS                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        key_compare key_comp() const { return (_compare); };

        value_compare value_comp() const { return (_value_compare); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  OPERATIONS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        iterator    find(const key_type & k)
        {
            return (_tree.find(k, _tree.root()));
        }
        
        const_iterator  find(const key_type & k) const
        {
            return (_tree.find(k, _tree.root()));
        }

        size_type    count(const key_type & k)
        {
            return (_tree.count(k, _tree.root()));
        }

        /*  !!!!!!!!!!  NEED MORE TESTS (segfault with empty map) !!!!!!!!!!!!!!!!!!!*/

        iterator lower_bound (const key_type& k)
        {
            iterator    it;

            it = begin();
            while (it != end())
            {
                if (!_compare(it->first, k))
                    return (it);
                it++;
            }
            return (it);
        }

        /* const_iterator lower_bound (const key_type& k) const
        {
            (void)k;
        } */

        iterator upper_bound(const key_type& k)
        {
            iterator    it;
            
            it = begin();
            while (it != end())
            {
                if (_compare(k, it->first))
                    return (it);
                it++;
            }
            return (it);
        }

        ft::pair<iterator,iterator> equal_range(const key_type & k)
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  DEBUGGING                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        // remove before push (util debugging)
        void print_tree() { _tree.print_tree(); }

    private:

        ft::RedBlackTree<value_type, key_compare>               _tree;
        key_type                                                _key;
        value_type                                              _value;
        key_compare                                             _compare;
        value_compare                                           _value_compare;

        allocate_type                                           _allocator;
        size_type                                               _nb_construct;
        size_type                                               _nb_allocate;


};


#endif
