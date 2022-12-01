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
    bool                 l;         // node is in left from parent path
    bool                 r;         // node is in right from parent path

    Node (void) : value(T()), parent(NULL), right(NULL), left(NULL), red(0), l(0), r(0)
    { 
    }

    Node (const value_type & v, const node_pointer & p = 0, const node_pointer & r = 0,
        const node_pointer & l = 0, bool rd = 0, bool _l = 0, bool _r = 0):
    value(v), parent(p), right(r), left(l), red(rd), l(_l), r(_r)
    {
    }

    Node (const Node & x) : value(x.value), right(x.right), left(x.left), red(x.red), l(x.l), r(x.r) {}

    Node & operator=(const Node & x)
    {
        if (this != &x)
        {
            value = x.value;
            right = x.right;
            left = x.left;
            red = x.red;
            l = x.l;
            r = x.r;
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
    public:

        typedef Pair                                            initial_type;
        typedef ft::Node<initial_type>                          node_type;
        typedef node_type *                                     node_pointer;
        typedef node_type &                                     node_reference;

        typedef ft::RedBlackTreeIterator<node_type, Compare>    iterator;

        typedef size_t                                          size_type;

        typedef Alloc                                           allocate_type;
        typedef Pair                                            pair;
        typedef pair *                                          pair_pointer;
        typedef typename Pair::first_type                       key_type;
        typedef typename Pair::second_type                      value_type;

        RedBlackTree() : _nb_construct(0), _nb_allocate(0) {};
        ~RedBlackTree()
        {
            std::cout << "///////////// DESTRUCTOR RBT  /////////////\n";
            if (_root)
                std::cout << "root" << *_root << std::endl;
           /*  if (_root->left)
                std::cout << *_root->left << std::endl;
            if (_root->right)
                std::cout << *_root->right << std::endl;
            std::cout << *search(13, _root) << std::endl;
            std::cout << *search(19, _root) << std::endl;
            std::cout << *search(23, _root) << std::endl; */

            if (_nb_construct && _root)
                destruct_himself(_root);
        };

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   ITERATORS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        iterator    begin()
        {
            node_pointer    it(_root);

            while (it && it->left)
                it = it->left;
            return (iterator(it));
        }

        iterator    end()
        {
            node_pointer    it(_root);

            while (it && it->right)
                it = it->right;
            return (iterator(it));
        }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   CAPACITY                                 /////
        //////////////////////////////////////////////////////////////////////////////////////

        size_t   size(void) const { return (_nb_construct); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                              ELEMENT ACCESS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        node_pointer    root() const { return (_root); }

        //////////////////////////////////////////////////////////////////////////////////////
        /////                                   MODIFIERS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        void    clear(void)
        {
            size_t  i = 0;
            while (i < _nb_construct)
                _allocator.destroy(_root + i);
        }

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
                    //std::cout << "recolor_ascendants" << std::endl;
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

        node_pointer   rotate_triangle(node_pointer z)
        {
            node_pointer    p;
            node_pointer    gp;
            node_pointer    u;

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
                    //std::cout << "rotate triangle" << std::endl;
                    if (p->l)
                    {
                        gp->left = z;
                        p->right = z->left;
                        if (z->left)
                            z->left->parent = p;
                        z->left = p;
                    }
                    else
                    {
                        gp->right = z;
                        p->left = z->right;
                        if (z->right)
                            z->right->parent = p;
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

        void    rotate_line(node_pointer z)
        {
            node_pointer    p;
            node_pointer    gp;
            node_pointer    u;

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
                    //std::cout << "rotate line" << std::endl;
                    if (gp->l)
                    {
                        if (gp->parent)
                        {
                            gp->parent->left = p;
                            p->parent = gp->parent;
                            p->l = 1;
                            p->r = 0;
                        }
                        else
                        {
                            _root = p;
                            p->parent = NULL;
                            p->red = 0;
                            p->r = 0;
                            p->l = 0;
                        }
                    }
                    else
                    {
                        if (gp->parent)
                        {
                            gp->parent->right = p;
                            p->parent = gp->parent;
                            p->r = 1;
                            p->l = 0;
                        }
                        else
                        {
                            _root = p;
                            p->parent = NULL;
                            p->red = 0;
                            p->r = 0;
                            p->l = 0;
                        }
                    }
                    if (p->l)
                    {
                        gp->left = p->right;
                        p->right = gp;
                        gp->r = 1;
                        gp->l = 0;
                    }
                    else
                    {
                        gp->right = p->left;
                        p->left = gp;
                        gp->l = 1;
                        gp->r = 0;
                    }
                    gp->parent = p;
                    gp->red = 1;
                }
            }
        }

        void    rotate_and_recolor(node_pointer z)
        {
            while (z != _root)
            {
                z = rotate_triangle(z);
                rotate_line(z);
                z = recolor_ascendants(z);
            }
            if (z->red && z->parent && z->parent->red)
                z->parent->red = 0;
            if (_root)
                _root->red = 0;
            verify_reds(z);
        }

        node_pointer    insert(const pair & x)
        {
            if (!_nb_construct)
            {
                _root = create_node(x);
                return (_root);
            }
            else
            {
                node_pointer   _current_node = _root;
                key_type    k2 = x.first;

                while (1)
                {
                    key_type k1 = _current_node->value.first;
                    
                    if (!_comp(x.first, k1) && !_comp(k1, x.first))
                        return (_current_node);
                    else if (_comp(k2, k1))
                    {
                        if (_current_node->left)
                            _current_node = _current_node->left;
                        else
                        {
                            _current_node->left = create_node(x, 1, 1);
                            _current_node->left->parent = _current_node;
                            rotate_and_recolor(_current_node->left);
                            return (_current_node->left);
                        }
                    }
                    else
                    {
                        if (_current_node->right)
                            _current_node = _current_node->right;
                        else
                        {
                            _current_node->right = create_node(x, 1, 0, 1);
                            _current_node->right->parent = _current_node;
                            rotate_and_recolor(_current_node->right);
                            return (_current_node->right);
                        }
                    }
                }
                return (_current_node);
            }
        }

        iterator    insert(iterator pos, const pair & x)
        {
            node_pointer   _current_node = pos->value;
            key_type    k2 = x.first;

            while (1)
            {
                key_type k1 = _current_node->value.first;
                
                if (!_comp(x.first, k1) && !_comp(k1, x.first))
                        return (_current_node);
                else if (_comp(k2, k1))
                {
                    if (_current_node->left)
                        _current_node = _current_node->left;
                    else
                    {
                        _current_node->left = create_node(x, 1, 1);
                        _current_node->left->parent = _current_node;
                        rotate_and_recolor(_current_node->left);
                        return (_current_node->left);
                    }
                }
                else
                {
                    if (_current_node->right)
                        _current_node = _current_node->right;
                    else
                    {
                        _current_node->right = create_node(x, 1, 0, 1);
                        _current_node->right->parent = _current_node;
                        rotate_and_recolor(_current_node->right);
                        return (_current_node->right);
                    }
                }
            }
            return (_current_node);
        }


        //////////////////////////////////////////////////////////////////////////////////////
        /////                                  OPERATIONS                                /////
        //////////////////////////////////////////////////////////////////////////////////////

        node_pointer    find(key_type val, node_pointer _n)
        {
            node_pointer    tmp = NULL;

            if (_n && !_comp(_n->value.first, val) && !_comp(val, _n->value.first))
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
            return (tmp);
        }

        size_type   count(const key_type & val, node_pointer _n) const
        {
            size_type    tmp = 0;

            if (_n && !_comp(_n->value.first, val) && !_comp(val, _n->value.first))
                return (1);
            else
            {
                if (_n->left)
                {
                    tmp += count(val, _n->left);
                }    
                if (_n->right)
                {
                    tmp += count(val, _n->right);
                }
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


    private:

        node_pointer        _root;
        Compare             _comp;
        allocate_type       _allocator;
        size_type           _nb_construct;
        size_type           _nb_allocate;
};

#endif
