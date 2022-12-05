/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:14:05 by mtellal           #+#    #+#             */
/*   Updated: 2022/12/01 13:14:26 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

template <class T>
struct Node
{ 
    typedef T       value_type;
    typedef T&      reference;
    typedef T*      pointer;
    typedef Node*   node_pointer;

    typedef typename T::first_type  first_type;
    typedef typename T::second_type second_type;

    value_type           value;     // ft::pair<X,Y>
    node_pointer         parent;    // parent node
    node_pointer         right;     // right node
    node_pointer         left;      // left node
    bool                 red;       // color (red or !red = black)

    Node (void) : value(T()), parent(NULL), right(NULL), left(NULL), red(0)
    { 
    }

    Node (const value_type & v, const node_pointer & p = 0, const node_pointer & r = 0,
        const node_pointer & l = 0, bool rd = 0):
    value(v), parent(p), right(r), left(l), red(rd)
    {
    }

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

    // debug function 

    friend std::ostream & operator<<(std::ostream & output, const Node & obj)
    {
        output << "\n////// NODE (" << &obj << ") /////\n";
        output << "key = " << obj.value.first << "\nvalue = " << obj.value.second << "\nparent = "
        << obj.parent << "\nright = " << obj.right << "\nleft = " << obj.left << "\nred = " << obj.red 
        << "\nl = " << obj.l << "\nr = " << obj.r ;
        return (output);
    }
};


template <class Pair, class Compare = std::less<Pair>, class Alloc = std::allocator<ft::Node<Pair> > >
class   RedBlackTree
{
    public:

        typedef Compare                                         key_compare;                                          
        typedef Pair                                            pair;
        typedef typename Pair::first_type                       key_type;
        typedef typename Pair::second_type                      mapped_type;

        typedef Alloc                                           allocator_type;
        typedef typename Alloc::reference                       reference;
        typedef typename Alloc::const_reference                 const_reference;
        typedef typename Alloc::pointer                         pointer;
        typedef typename Alloc::const_pointer                   const_pointer;
        typedef typename Alloc::size_type                       size_type;

        typedef ft::Node<pair>                                  node_type;
        typedef ft::Node<const pair>                            const_node_type;        
        typedef typename node_type::node_pointer                node_pointer;

        typedef typename ft::RedBlackTreeIterator<node_type, key_compare>            iterator;
        typedef typename ft::RedBlackTreeIterator<const_node_type, key_compare>     const_iterator;
        typedef typename ft::reverse_iterator<iterator>                             reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>                       const_reverse_iterator;


        RedBlackTree() : _root(0), _nb_element(0) {};

        RedBlackTree(const RedBlackTree & x) : 
        _root(0), _compare(x._compare), _allocator(x._allocator), _nb_element(0)
        {
            iterator    first;
            iterator    last;

            first = x.begin();
            last = x.end();
            while (first != last)
            {
                insert(ft::make_pair(first->first, first->second));
                first++;
            }
        }

        ~RedBlackTree()
        {
            clear();
        };

        void    print_tree()
        {
             if (_root)
                std::cout << "root" << *_root << std::endl;

            if (_root && _root->left)
                std::cout << "\n\n=> LEFT \n" << *_root->left << std::endl;

            if (_root && _root->left && _root->left->left)
                std::cout << *_root->left->left << std::endl;

            if (_root && _root->left && _root->left->right)
                std::cout << *_root->left->right << std::endl;

            if (_root && _root->right)
                std::cout << "\n\n=> RIGHT \n" <<  *_root->right << std::endl;

            if (_root && _root->right && _root->right->right)
                std::cout << *_root->right->right << std::endl;

            if (_root && _root->right && _root->right->left)
                std::cout << *_root->right->left << std::endl;

        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   ITERATORS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        iterator    begin() const
        {
            node_pointer    it(_root);

            while (it && it->left)
            {
                it = it->left;
            }
            return (it);
        }

        iterator    end() const
        {
            iterator it;

            if (!_nb_element)
                return (begin());
            it = max_element() + 1;
            return (it);
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   CAPACITY                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        size_t   size(void) const { return (_nb_element); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                              ELEMENT ACCESS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        node_pointer    root() const { return (_root); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   MODIFIERS                                /////
        //////////////////////////////////////////////////////////////////////////////////////


        node_pointer    insert(const pair & k)
        {
            node_pointer    z;
            node_pointer    y;
            node_pointer    x;

            y = NULL;
            x = _root;
            while (x)
            {
                y = x;
                if (!_compare(k.first, x->value.first) && !_compare(x->value.first, k.first))
                    return (x);
                if (_compare(k.first, x->value.first))
                    x = x->left;
                else
                    x = x->right;
            }
            z = create_node(k);
            z->parent = y;
            if (!y)
                _root = z;
            else if (_compare(k.first, y->value.first))
                y->left = z;
            else
                y->right = z;
            insert_fixup(z);
            return (z);
        }

        void    erase(iterator position)
        {
            node_pointer    p;
            
            if (!_root)
                return ;
            p = find(position->first, _root);
            if (p)
            {
                std::cout << "erase called on => [ " << p->value.first << " ]" <<  std::endl;
                _delete(p);
                p->parent = 0;
                p->right = 0;
                p->left = 0;
                _allocator.destroy(p);
                _allocator.deallocate(p, 1);
                _nb_element--;
            }
        }

        void    clear()
        {
            if (_root && _nb_element)
                destroy_tree(_root);
            if (_root && _nb_element)
                deallocate_tree(_root);
            _root = NULL;
            _nb_element = 0;
        }



        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  OPERATIONS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        node_pointer    find(key_type val, node_pointer _n)
        {
            node_pointer    tmp = NULL;

            if (_n && !_compare(_n->value.first, val) && !_compare(val, _n->value.first))
                return (_n);
            else
            {
                if (_n->left)
                {
                    tmp = find(val, _n->left);
                    if (tmp)
                        return (tmp);
                }    
                if (_n->right)
                {
                    tmp = find(val, _n->right);
                    if (tmp)
                        return (tmp);
                }
            }
            return (end().base());
        }

        size_type   count(const key_type & val, node_pointer _n) const
        {
            size_type    tmp = 0;

            if (_n && !_compare(_n->value.first, val) && !_compare(val, _n->value.first))
                return (1);
            else
            {
                if (_n->left)
                    tmp += count(val, _n->left);
                if (_n->right)
                    tmp += count(val, _n->right);
            }
            return (tmp);
        }

        // remove before push 

        void    verify_reds(node_pointer z)
        {
            if (z->left && z->red && z->left->red)
            {
                std::cout << "2 ADJACENTS RED NODES\n";
                std::cout << *z << " " << *z->left << std::endl;
                verify_reds(z->left);
            }
            if (z->right && z->red && z->right->red)
            {
                std::cout << "2 ADJACENTS RED NODES\n";
                std::cout << *z << " " << *z->right << std::endl;
                verify_reds(z->right);
            }
        }



        ////////////////////////////////////       PRIVATE         ////////////////////////////////////

    private:

        node_pointer        _root;
        key_compare         _compare;
        allocator_type      _allocator;
        size_type           _nb_element;

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                    ALGO                                    /////
        //////////////////////////////////////////////////////////////////////////////////////


        node_pointer    min_element() const
        {
            node_pointer n(_root);

            while (n && n->left)
                n = n->left;
            return (n);
        }

        node_pointer    min_element(node_pointer n) const
        {
            while (n && n->left)
                n = n->left;
            return (n);
        }

        node_pointer    max_element() const
        {
            node_pointer n(_root);

            while (n && n->right)
                n = n->right;
            return (n);
        }

        node_pointer    max_element(node_pointer n) const
        {
            while (n && n->right)
                n = n->right;
            return (n);
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                 MOFIERS                                    /////
        //////////////////////////////////////////////////////////////////////////////////////

        void    deallocate_tree(node_pointer x)
        {
            if (x->left)
                deallocate_tree(x->left);
            if (x->right)
                deallocate_tree(x->right);
            if (x)
                _allocator.deallocate(x, 1);
        }

        void    destroy_tree(node_pointer x)
        {
            if (x->left)
                destroy_tree(x->left);
            if (x->right)
                destroy_tree(x->right);
            if (x)
                _allocator.destroy(x);
        }

        node_pointer   create_node(const Pair & x)
        {
            node_pointer   _n;

            _n = _allocator.allocate(1);
            _allocator.construct(_n, x);
            _n->red = 1;
            _nb_element++;
            _n->left = NULL;
            _n->right = NULL;
            return (_n);
        }


        //////////////////////////////////////////////////////////////////////////////////////
        /////                              MOFIFIERS_UTILS                               /////
        //////////////////////////////////////////////////////////////////////////////////////

        void    insert_fixup(node_pointer z)
        {
            node_pointer    u;

            while (z->parent && z->parent->red)
            {
                if (z == z->parent->parent->left)
                {
                    u = z->parent->parent->right;
                    if (u && u->red)
                    {
                        z->parent->red = 0;
                        u->red = 0;
                        z->parent->parent->red = 1;
                        z = z->parent->parent;
                    }
                    else
                    {
                        if (z == z->parent->right)
                        {
                            z = z->parent;
                            left_rotation(z);
                        }
                        z->parent->red = 0;
                        z->parent->parent->red = 1;
                        right_rotation(z->parent->parent);
                    }
                }
                else
                {
                    u = z->parent->parent->left;
                    if (u && u->red)
                    {
                        z->parent->red = 0;
                        u->red = 0;
                        z->parent->parent->red = 1;
                        z = z->parent->parent;
                    }
                    else
                    {
                        if (z == z->parent->left)
                        {
                            z = z->parent;
                            right_rotation(z);
                        }
                        z->parent->red = 0;
                        z->parent->parent->red = 1;
                        left_rotation(z->parent->parent);
                    }
                }
                if (z == _root)
                    break ;
            }
            _root->red = 0;
        }


        /*          ROTATIONS LEFT / RIGHT          */

        void    left_rotation(node_pointer x)
        {
            node_pointer    y;

            y = x->right;
            x->right = y->left; 

            if (y->left)
                y->left->parent = x;
            y->parent = x->parent;
            if (!x->parent)
                _root = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y; 
            y->left = x;
            x->parent = y;
        }

        void right_rotation(node_pointer x)
        {
            node_pointer    y;

            y = x->left;
            x->left = y->right;
            if (y->right)
                y->right->parent = x;
            y->parent = x->parent;
            if (!x->parent)
                _root = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }


        // DELETION RBT

        void    _transplant(node_pointer p, node_pointer c)
        {
            if (!p->parent)
                _root = c;
            else if (p == p->parent->left)
                p->parent->left = c;
            else
                p->parent->right = c;
            if (c)
                c->parent = p->parent;
        }

        void    _delete(node_pointer p)
        {
            node_pointer    m;
            node_pointer    c;

            c = p;
            if (!p->right)
            {
                c = p->left;
                _transplant(p, p->left);
            }
            else if (!p->left)
            {
                c = p->right;
                _transplant(p, p->right);
            }
            else
            {
                m = min_element(p->right);
                c = m->right;
                if (m->parent != p)
                {
                    _transplant(m, m->right);
                    m->right = p->right;
                    m->right->parent = m;
                }
                _transplant(p, m);
                m->left = p->left;
                m->left->parent = m;
            }
            if (c && !c->red)
                delete_fixup(c);
        }

        void    delete_fixup(node_pointer c)
        {
            node_pointer    c2;
            node_pointer    p;

            while (c != _root && !c->red)
            {
                if (c == c->parent->left)
                {
                    p = c->parent;
                    c2 = p->right;
                    if (c2 && c2->red)
                    {
                        c2->red = 0;
                        p->red = 1;
                        left_rotation(p);
                        c2 = p->right;
                    }
                    if (c2 &&
                        c2->left && !c2->left->red &&
                        c2->right && !c2->right->red)
                    {
                        c2->red = 1;
                        c = p;
                    }
                    else
                    {
                        if (c2 && c2->right && !c2->right->red)
                        {
                            c2->left->red = 0;
                            c2->red = 1;
                            right_rotation(c2);
                            c2 = p->right;
                        }
                        c2->red = p->red;
                        p->red = 0;
                        c2->right->red = 0;
                        left_rotation(p);
                        c = _root;
                    }
                }
                else
                {
                    p = c->parent;
                    c2 = p->left;
                    if (c2 && c2->red)
                    {
                        c2->red = 0;
                        p->red = 1;
                        right_rotation(p);
                        c2 = p->left;
                    }
                    if (c2 &&
                        c2->right && !c2->right->red &&
                        c2->left && !c2->left->red)
                    {
                        c2->red = 1;
                        c = p;
                    }
                    else
                    {
                        if (c2->left && !c2->left->red)
                        {
                            c2->right->red = 0;
                            c2->red = 1;
                            left_rotation(c2);
                            c2 = p->left;
                        }
                        c2->red = p->red;
                        p->red = 0;
                        c2->left->red = 0;
                        right_rotation(p);
                        c = _root;
                    }
                }
            }
            _root->red = 0;
        }
};

#endif
