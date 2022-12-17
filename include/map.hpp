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
        
        typedef Key                                                                             key_type;
        typedef T                                                                               mapped_type;
        typedef ft::pair<const Key, T>                                                          value_type;
        typedef Compare                                                                         key_compare;                                          
        typedef typename Alloc::difference_type                                                 difference_type;
        typedef typename Alloc::size_type                                                       size_type;

        typedef Alloc                                                                           allocator_type;
        typedef typename Alloc::reference                                                       reference;
        typedef typename Alloc::const_reference                                                 const_reference;
        typedef typename Alloc::pointer                                                         pointer;
        typedef typename Alloc::const_pointer                                                   const_pointer;

        typedef typename ft::RedBlackTree<value_type, key_compare,
            typename Alloc::template rebind< ft::Node<value_type> >::other >::iterator          iterator;
        typedef typename ft::RedBlackTree<value_type, key_compare,
            typename Alloc::template rebind< ft::Node<value_type> >::other >::const_iterator    const_iterator;
        typedef typename ft::reverse_iterator<iterator>                                         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>                                   const_reverse_iterator;


        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            friend class map;
            
            protected:
                Compare comp;
                value_compare (Compare c) : comp(c) {}
            
            public:

                typedef bool        result_type;
                typedef value_type  first_argument_type;
                typedef value_type  second_argument_type;

                value_compare() {}
                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
        };

        map() {}

        explicit map( const Compare& comp, const Alloc& alloc = Alloc() ) :
        _compare(comp), _allocator(alloc)
        {}

        template< class InputIt >
        map( InputIt first, InputIt last, const Compare& comp = Compare(),
                const Alloc& alloc = Alloc() ) :
        _compare(comp), _allocator(alloc)
        {
            insert(first, last);
        }

        map( const map& x) :
        _tree(x._tree), _compare(x._compare), _allocator(x._allocator)
        {}

        ~map(void)
        {
            _tree.clear();
        }

        map &   operator=(const map & x)
        {
            if (this != &x)
            {
                clear();
                insert(x.begin(), x.end());
            }
            return (*this);
        }

        allocator_type get_allocator() const { return (_allocator); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                              ELEMENT ACCESS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        T &                     at(const Key & key)
        {
            iterator    it;

            it = find(key);
            if (!it.base())
                throw std::out_of_range("Element does not exists");
            return (it->second);
        }

        const T &               at(const Key & key) const
        {
            iterator    it;

            it = find(key);
            if (!it.base())
                throw std::out_of_range("Element does not exists");
            return (it->second);
        }

        mapped_type &           operator[](const key_type & k)
        {
            pair<iterator, bool>    pair;

            pair = insert(ft::make_pair(k, mapped_type()));
            return (pair.first->second);
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   ITERATORS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        iterator                begin() { return (iterator(_tree.begin())); }

        const_iterator          begin() const { return (const_iterator(_tree.begin())); }

        iterator                end() { return (iterator(_tree.end())); }

        const_iterator          end() const { return (const_iterator(_tree.end())); }

        reverse_iterator        rbegin() { return (reverse_iterator(_tree.end())); }
        
        const_reverse_iterator  rbegin() const { return (reverse_iterator(_tree.end())); }

        reverse_iterator        rend() { return (reverse_iterator(_tree.begin())); }

        const_reverse_iterator  rend() const { return (reverse_iterator(_tree.begin())); }
        
        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   CAPACITY                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        bool                    empty() const { return (!_tree.size()); }
        
        size_type               size() const { return (_tree.size()); }

        size_type               max_size(void) const { return (_tree.max_size()); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   MODIFIERS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        void                    clear() { _tree.clear(); }

        pair<iterator, bool>    insert(const value_type & val)
        {
            iterator    it;
            size_type   n;

            n = size();
            it = _tree.insert(val);
            if (n + 1 == size())
            {
                return (ft::pair<iterator, bool>(it, true));
            }
            else
                return (ft::pair<iterator, bool>(it, false));
        }

        iterator                insert(iterator position, const value_type & val)
        {
            iterator    it;

            it = _tree.insert(position, val);
            return (it);
        }

        template <class InputIterator>
        void                    insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                insert(ft::make_pair(first->first, first->second));
                first++;
            }
        }

        void                    erase(iterator position)
        {
            _tree.erase(position);
        }
        
        size_type               erase(const key_type & k)
        {
            iterator    it;

            it = find(k);
            if (it.base() && it.base() != _tree.getend())
            {
                erase(it);
                return (1);
            }
            return (0);
        }

        void                    erase(iterator first, iterator last)
        {
            while (first != last)
            {
                _tree.erase(first++);
            }
        }

        void                    swap(map & x)
        {
            key_compare     ctmp;
            allocator_type   atmp;

            ctmp = x._compare;
            atmp = x._allocator;
            
            _tree.swap(x._tree);
            
            x._compare = _compare;
            x._allocator = _allocator;

            _compare = ctmp;
            _allocator = atmp;
            
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  OPERATIONS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        size_type               count(const key_type & k) const
        {
            return (_tree.count(k, _tree.getroot()));
        }

        iterator                find(const key_type & k)
        {
            return (_tree.find(k));
        }
        
        const_iterator          find(const key_type & k) const
        {
            return (_tree.find(k));
        }

        ft::pair<iterator,iterator> equal_range(const key_type & k)
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }

        ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }

        iterator                lower_bound (const key_type& k)
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

        const_iterator          lower_bound (const key_type& k) const
        {
            const_iterator    it;

            it = begin();
            while (it != end())
            {
                if (!_compare(it->first, k))
                    return (it);
                it++;
            }
            return (it);
        }

        iterator                upper_bound(const key_type& k)
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

        const_iterator          upper_bound(const key_type& k) const
        {
            const_iterator    it;
            
            it = begin();
            while (it != end())
            {
                if (_compare(k, it->first))
                    return (it);
                it++;
            }
            return (it);
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  OBSERVERS                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        key_compare             key_comp() const { return (Compare()); };

        value_compare           value_comp() const { return (value_compare(Compare())); }

    private:

        ft::RedBlackTree<value_type, key_compare>               _tree;
        key_compare                                             _compare;
        allocator_type                                           _allocator;


};


template< class Key, class T, class Compare, class Alloc >
bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
    return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) &&
                !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
    return (!(lhs == rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
    return (!(rhs < lhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                const ft::map<Key,T,Compare,Alloc>& rhs )
{
    return (!(lhs <= rhs));
}

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                 const ft::map<Key,T,Compare,Alloc>& rhs )
{
    return (!(lhs < rhs));
}

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key,T,Compare,Alloc>& lhs,
           ft::map<Key,T,Compare,Alloc>& rhs )
{
    lhs.swap(rhs);
}

#endif
