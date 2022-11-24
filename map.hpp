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

template <class Pair, class Compare = std::less<Pair>, class Alloc = std::allocator<ft::Node<Pair> > >
class   RedBlackTree
{
    typedef Pair                        initial_type;
    typedef ft::Node<initial_type>      node_type;
    typedef node_type *                 node_pointer;
    typedef node_type &                 node_reference;

    typedef ft::RedBlackTreeIterator<node_type, Compare>    iterator;

    typedef Alloc                       allocate_type;
    typedef typename Pair::first_type   key_type;
    typedef typename Pair::second_type  value_type;

    public:

        RedBlackTree() : _nb_construct(0), _nb_allocate(0) {};
        ~RedBlackTree()
        {
            if (_nb_construct && _root)
            {}
            
        };

        node_pointer   create_node(const Pair & x)
        {
            node_pointer   _n;

            _n = _allocator.allocate(1);
            _allocator.construct(_n, x);
            _nb_construct++;
            _nb_allocate++;
            return (_n);
        }

        void    insert(const Pair & x)
        {
            std::cout << "RBT insert called" << std::endl;
            if (!_nb_construct)
            {
                _root = create_node(x);
                std::cout << *_root << std::endl;
            }
            else
            {
                node_pointer   _current_node = _root;
                key_type    k2 = x.first;

                // au moins 1 noeud 
                // si compare 
                while (1)
                {
                    key_type k1 = _current_node->value.first;
                    
                    //std::cout << "boucle" << std::endl;
                    //std::cout << k1 << " " << k2 << std::endl;
                    
                    if (_comp(k2, k1))
                    {
                        std::cout << "gauche" << std::endl;
                        // gauche
                        if (_current_node->left)
                            _current_node = _current_node->left;
                        else
                        {
                            _current_node->left = create_node(x);
                            _current_node->left->parent = _current_node;
                            //std::cout << *_current_node << std::endl;
                            std::cout << *(_current_node->left) << std::endl;

                            break ;
                        }
                    }
                    else
                    {
                        // droit
                        std::cout << "droite" << std::endl;
                        // gauche
                        if (_current_node->right)
                            _current_node = _current_node->right;
                        else
                        {
                            _current_node->right = create_node(x);
                            _current_node->right->parent = _current_node;
                            //std::cout << *_current_node << std::endl;
                            std::cout << *(_current_node->right) << std::endl;
                            break ;
                        }
                    }

                }

            }
        }

        void    clear(void)
        {
            size_t  i = 0;
            while (i < _nb_construct)
                _allocator.destroy(_root + i);
        }

        iterator    begin()
        {
            node_pointer    it = _root;
            while (it->left)
            {
                it = it->left;
            }
            return (it);
        }


    private:
        node_pointer        _root;
        Compare             _comp;
        allocate_type       _allocator;
        size_t              _nb_construct;
        size_t              _nb_allocate;
};

template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > > 
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
        typedef typename ft::RedBlackTreeIterator<ft::Node<value_type>, key_compare>         iterator;
        /* typedef typename ft::random_access_iterator<const value_type>   const_iterator;
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const iterator>           const_reverse_iterator; */

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
        std::cout << "map iterator constructor called" << std::endl;
        (void)first;
        (void)last;
        (void)comp;
        (void)alloc;
    }

    map(const map & x)
    {
        (void)x;
        std::cout << "map copy constructor called" << std::endl;
    }

    ~map(void)
    {
        std::cout << "map destructor called" << std::endl;
    }
    
    pair<iterator, bool>    insert(const value_type & val)
    {
        (void) val;
    }

    iterator    insert(iterator position, const value_type & val)
    {
        (void) position;
        (void)val;
    }

    template <class InputIterator>
    void    insert(InputIterator first, InputIterator last)
    {
        (void)first;
        (void)last;
    }

    void    my_insert(const value_type & val)
    {
        _tree.insert(val);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    /////                                   ITERATORS                                /////
    //////////////////////////////////////////////////////////////////////////////////////

    iterator    begin(void)
    {
       return (_tree.begin());
    }

    value_compare value_comp() const { return _compare; }

    private:

        ft::RedBlackTree<value_type, key_compare>               _tree;
        key_type                                                _key;
        value_type                                              _value;
        value_compare                                           _compare;

        allocate_type                                           _allocator;
        size_type                                               _nb_construct;
        size_type                                               _nb_allocate;



        

};


#endif
