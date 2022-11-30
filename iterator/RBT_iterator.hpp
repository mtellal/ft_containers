/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:51:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/24 14:52:18 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_ITERATOR_HPP
#define RBT_ITERATOR_HPP

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

template <class Node, class Compare>
class RedBlackTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, Node>
{

    public:

        typedef ft::iterator<ft::bidirectional_iterator_tag, Node>  iterator;
        typedef typename iterator::value_type                       value_type;
        typedef typename iterator::difference_type                  difference_type;
        typedef typename iterator::pointer                          pointer;
        typedef typename iterator::reference                        reference;
        typedef typename iterator::iterator_category                iterator_category;

        typedef typename Node::value_type                           pair;
        typedef typename Node::reference                            pair_reference;
        typedef typename Node::pointer                              pair_pointer;
        typedef typename Node::first_type                           first_type;
        typedef typename Node::reference                            second_type;

        RedBlackTreeIterator() : _node(0) {}
        RedBlackTreeIterator(const RedBlackTreeIterator & x) : _node(x._node) {}
        RedBlackTreeIterator(const pointer & x) : _node(x) {}
        ~RedBlackTreeIterator() {}

        RedBlackTreeIterator & operator=(const RedBlackTreeIterator & x)
        {
             if (this != &x)
                _node = x._node;
            return (*this);
        }

        bool    operator==(const RedBlackTreeIterator & x) { return (_node->value == x._node->value); }
        bool    operator!=(const RedBlackTreeIterator & x) { return (_node->value != x._node->value); }


        pair_reference   operator*(void) { return (_node->value); }
        pair*    operator->() { return &(_node->value); }


        pointer    min_element(pointer _n)
        {
            while (_n->left)
                _n = _n->left;
            return (_n);
        }

        pointer    max_element(pointer _n)
        {
            while (_n->right)
                _n = _n->right;
            return (_n);
        }

        /*      CHANGE ITERATORS / NOT WORKING CORRECTLY */
        RedBlackTreeIterator &  operator++()
        {
            if (_node->right)
            {
                if (_node->right->left)
                    _node = min_element(_node->right->left);
                else
                    _node = _node->right;
            }
            else if (_node->parent && !_node->right)
            {
                pointer _it(_node);
                while (_it)
                {
                    if (_comp(_node->value.first, _it->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
            }
            return (*this);
        }

        RedBlackTreeIterator operator++(int)
        {
            //X++
            RedBlackTreeIterator old(*this);

            if (_node->right)
            {
                if (_node->right->left)
                    _node = min_element(_node->right->left);
                else
                    _node = _node->right;
            }
            else if (_node->parent && !_node->right)
            {
                pointer _it(_node);
                while (_it)
                {
                    if (_comp(_node->value.first, _it->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
            }
            return (old);
        }

        RedBlackTreeIterator & operator--()
        {
            if (_node->left)
            {
                if (_node->left->right)
                    _node = max_elemement(_node->left->right);
                else
                    _node = _node->left;
            }
            else if (_node->parent && !_node->left)
            {
                pointer _it(_node);
                while (_it)
                {
                    if (_comp(_node->value.first, _it->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
            }
            return (*this);
        }

        RedBlackTreeIterator    operator--(int)
        {
            RedBlackTreeIterator    old(*this);

            if (_node->left)
            {
                if (_node->left->right)
                    _node = max_elemement(_node->left->right);
                else
                    _node = _node->left;
            }
            else if (_node->parent && !_node->left)
            {
                pointer _it(_node);
                while (_it)
                {
                    if (_comp(_node->value.first, _it->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
            }
            return (old);
        }

    private:

        pointer     _node;
        Compare     _comp;     

};

#endif
