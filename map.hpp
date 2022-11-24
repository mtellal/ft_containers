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

/*
    RULES RED-BLACK-TREES
    1) if empty => root node black 
    2) if not empty => new leaf node in red 
    3) if parent of new node is black => exit
    4) if parent new node is red => check parents sibling 
        a) if parents sibling null or black => rotate and recolor 
        b) if parents sibling red recolor in black &&  check if parent newnode != root => recolor parent 

    https://www.youtube.com/watch?v=qA02XWRTBdw
*/


template <class Pair, class Compare = std::less<Pair>, class Alloc = std::allocator<ft::Node<Pair> > >
class   RedBlackTree
{
    typedef Pair                                            initial_type;
    typedef ft::Node<initial_type>                          node_type;
    typedef node_type *                                     node_pointer;
    typedef node_type &                                     node_reference;

    typedef ft::RedBlackTreeIterator<node_type, Compare>    iterator;

    typedef Alloc                                           allocate_type;
    typedef typename Pair::first_type                       key_type;
    typedef typename Pair::second_type                      value_type;

    public:

        RedBlackTree() : _nb_construct(0), _nb_allocate(0) {};
        ~RedBlackTree()
        {
            if (_root)
                std::cout << "root" << *_root << std::endl;
            if (_root->left)
                std::cout << *_root->left << std::endl;
            if (_root->left->left)
                std::cout << *_root->left->left << std::endl;
            if (_root->right)
                std::cout << *_root->right << std::endl;

            if (_nb_construct && _root)
                destruct_himself(_root);
        };

        void    destruct_himself(node_pointer x)
        {
            if (x->left)
                destruct_himself(x->left);
            if (x->right)
                destruct_himself(x->right);
            if (x)
                _allocator.deallocate(x, 1);
        }

        node_pointer   create_node(const Pair & x, bool red = 0, bool l = 0, bool r = 0)
        {
            node_pointer   _n;

            _n = _allocator.allocate(1);
            _allocator.construct(_n, x);
            if (red)
                _n->red = 1;
            if (l)
                _n->l = 1;
            if (r)
                _n->r = 1;
            _nb_construct++;
            _nb_allocate++;
            return (_n);
        }


        node_pointer    max_elemement(node_pointer _node)
        {
            node_pointer    max(_node);

            while (max->right)
                max = max->right;
            return (max);
        }

        node_pointer    min_element(node_pointer _node)
        {
            node_pointer    min(_node);

            while (min->right)
                min = min->right;
            return (min);
        }

        // painter(void) => recolor needed ??

        void    insert(const Pair & x)
        {
            if (!_nb_construct)
                _root = create_node(x);
            else
            {
                node_pointer   _current_node = _root;
                key_type    k2 = x.first;

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
                            _current_node->left = create_node(x, 1, 1);

                            if (_current_node->red && _current_node->parent)
                            {

                                // au moins 3 noeuds 

                                // is parent in left side and sibling in right side ( is red )

                                ///////////////         RULE 4.B    //////////////
                                if (_current_node->l
                                    && _current_node->parent->right && _current_node->parent->right->red)
                                {
                                    _current_node->parent->right->red = 0;
                                    if (_current_node->parent->l || _current_node->parent->r)
                                        _current_node->parent->red = 1;
                                    std::cout << "recolor sibling and parent node + parent's parent (!= root) " << std::endl;
                                }

                                if (_current_node->r
                                    && _current_node->parent->left && _current_node->parent->left->red)
                                {
                                    _current_node->parent->left->red = 0;
                                    if (_current_node->parent->l || _current_node->parent->r)
                                        _current_node->parent->red = 1;
                                    std::cout << "recolor sibling and parent node + parent's parent (!= root) " << std::endl;
                                }
                                ///////////////////////////////////////////////////////////////

                                // parent left side from parent's parent + check if null or black sibling
                                if (_current_node->l
                                    && (!_current_node->parent->right || !_current_node->parent->right->red))
                                {
                                    node_pointer parent(_current_node->parent);

                                    std::cout << "first rotation launched" << std::endl;
                                        node_pointer m = max_elemement(_current_node);
                                        if (m)
                                            m->right = parent;
                                        else
                                            _current_node->right =  parent;
                                        parent->left = NULL;

                                        if (parent->parent)
                                        {
                                            _current_node->parent = parent->parent;
                                            parent->parent = _current_node;
                                        }
                                        else 
                                        {
                                            _root = _current_node;
                                            _current_node->red = 0;
                                            _current_node->l = 0;
                                            _current_node->r = 0;
                                            parent->parent = _current_node;
                                            _current_node->parent = NULL;
                                        }
                                }

                                // check if parent's sibling if black or null => rotate and recolor 
                                else if (!_current_node->parent->right
                                    || (_current_node->parent->right != _current_node && !_current_node->parent->right->red))
                                {
                                    node_pointer tmp;

                                    (void)tmp;

                                    std::cout << "rotation needed for => \n" << *_current_node->left << std::endl; 

                                }
                                else if (_current_node->parent)
                                {

                                }
                            }
                            _current_node->left->parent = _current_node;
                            break ;
                        }
                    }
                    else
                    {
                        std::cout << "droite" << std::endl;
                        if (_current_node->right)
                            _current_node = _current_node->right;
                        else
                        {
                            _current_node->right = create_node(x, 1, 0, 1);

                             // check if parent's sibling if black or null => rotate and recolor 
                            if (_current_node->parent && (!_current_node->parent->left
                                || (_current_node->parent->left != _current_node && !_current_node->parent->left->red)
                                || !_current_node->parent->right
                                || (_current_node->parent->right != _current_node && !_current_node->parent->right->red)))
                            {
                                std::cout << "rotation needed for => \n" << *_current_node->right << std::endl; 
                            }

                            _current_node->right->parent = _current_node;
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
