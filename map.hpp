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
            if (_root->left && _root->left->left)
                std::cout << *_root->left->left << std::endl;
            if (_root->right)
                std::cout << *_root->right << std::endl;
            if (_root->right && _root->right->right)
                std::cout << *_root->right->right << std::endl;

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

        // recolor parent / grand_parent / uncle (_current_node is red)
        // case 1 : uncle red, recolor ascendants 
        
        /*      NEED RECLORIZATION RECURSIVELY      */

        node_pointer    recolor_ascendants(node_pointer z)
        {
            node_pointer    p;
            node_pointer    gp;
            node_pointer    u;

            if (z->parent && z->parent->parent)
            {
                p = z->parent;
                gp = z->parent->parent;
                if (p->l)
                    u = gp->right;
                else
                    u = gp->left;
                if (p->red == z->red)
                {
                    std::cout << "recolor_ascendants" << std::endl;
                    p->red = 0;
                    gp->red = 1;
                    if (u)
                        u->red = 0;
                }
                return (gp);
            }
            if (_root)
                _root->red = 0;
            return (z->parent);
        }

        // case 2: uncle black and triangle pattern

        node_pointer   rotate_triangle(node_pointer z)
        {
            node_pointer    p;
            node_pointer    gp;
            node_pointer    u;

            // parent in diff pos from z (parent left && z right)

            if (z->parent && z->parent->parent)
            {  
                p = z->parent;
                gp = p->parent;
                if (p->l)
                    u = gp->right;
                else
                    u = gp->left;
                if ((!u || !u->red) && p->l != z->l && p->red && z->red)
                {
                    std::cout << "rotate triangle" << std::endl;
                    if (p->l)
                    {
                        gp->left = z;
                        p->right = z->left;
                        z->left = p;
                    }
                    else
                    {
                        gp->right = z;
                        p->left = z->right;
                        z->right = p;
                    }
                    z->parent = gp;
                    p->parent = z;
                    z->l = !z->l;
                    z->r = !z->r;
                    return (p);
                }
            }
            return (z);
        }

        // NEED RECOLOR (parent / grand_parent )

        void    rotate_line(node_pointer z)
        {
            node_pointer    p;
            node_pointer    gp;
            node_pointer    u;

            // parent in diff pos from z (parent left && z right)

            if (z->parent && z->parent->parent)
            {  
                p = z->parent;
                gp = p->parent;
                if (p->l)
                    u = gp->right;
                else
                    u = gp->left;
                if ((!u || !u->red) && p->l == z->l && p->red && z->red)
                {
                    std::cout << "rotate line" << std::endl;
                    if (gp->l)
                    {
                        if (gp->parent)
                        {
                            gp->parent->left = p;
                            p->parent = gp->parent;
                        }
                        else
                        {
                            _root = p;
                            p->parent = NULL;
                            p->red = 0;
                        }
                    }
                    else
                    {
                        if (gp->parent)
                        {
                            gp->parent->right = p;
                            p->parent = gp->parent;
                        }
                        else
                        {
                            _root = p;
                            p->parent = NULL;
                            p->red = 0;
                        }
                    }
                    if (p->l)
                    {
                        gp->left = p->right;
                        p->right = gp;
                    }
                    else
                    {
                        gp->right = p->left;
                        p->left = gp;
                    }
                    gp->parent = p;
                    gp->red = 1;
                }
            }
        }


                /*      NEED RECLORIZATION RECURSIVELY      */

        void    rotate_and_recolor(node_pointer z)
        {
            z = rotate_triangle(z);
            rotate_line(z);
            z = recolor_ascendants(z);
            while (z->parent)
                z = recolor_ascendants(z);
            if (z->red && z->parent && z->parent->red)
                z->parent->red = 0;
            if (_root)
                _root->red = 0;
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
                    
                    if (_comp(k2, k1))
                    {
                        std::cout << "gauche" << std::endl;
                        // gauche
                        if (_current_node->left)
                            _current_node = _current_node->left;
                        else
                        {
                            _current_node->left = create_node(x, 1, 1);
                            _current_node->left->parent = _current_node;
                            rotate_and_recolor(_current_node->left);
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
                            _current_node->right->parent = _current_node;
                            rotate_and_recolor(_current_node->right);
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
            node_pointer    it(_root);
            
            while (it->left)
                it = it->left;
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
        _nb_construct++;
        _nb_allocate++;
    }

    size_type   size() const { return (_nb_construct); }

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
