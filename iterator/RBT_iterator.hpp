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

    value_type           value;
    node_pointer         parent;
    node_pointer         right;
    node_pointer         left;
    bool                 red;

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



    friend std::ostream & operator<<(std::ostream & output, const Node & obj)
    {
        output << "\n////// NODE (" << &obj << ") /////\n";
        output << "key = " << obj.value.first << "\nvalue = " << obj.value.second << "\nparent = "
        << obj.parent << "\nright = " << obj.right << "\nleft = " << obj.left << "\nred = " << obj.red;
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

        RedBlackTreeIterator &  operator++()
        {
            if (_node->right)
                _node = _node->right;
            else if (_node->parent)
            {
                pointer _it(_node->parent);
                
                first_type node_key = _node->value.first; 

                while (!_comp(_it->value.first, node_key))
                {
                    if (!_it->parent)
                        return (*this);
                    else
                        _it = _it->parent;
                }
                if (_it->parent)
                    _node = _it;
            }
            return (*this);
        }

        RedBlackTreeIterator operator++(int)
        {
            //X++
            RedBlackTreeIterator old(*this);

            if (_node->right)
                _node = _node->right;
            else if (_node->parent)
            {
                pointer _it(_node->parent);
                
                first_type node_key = _node->value.first; 

                while (!_comp(_it->value.first, node_key))
                {
                    if (!_it->parent)
                        return (*this);
                    else
                        _it = _it->parent;
                }
                if (_it->parent)
                    _node = _it;
            }
            return (old);
        }

        RedBlackTreeIterator & operator--()
        {
            if (_node->left)
                _node = _node->left;
            else if (_node->parent)
            {
                pointer _it(_node->parent);
                while (!_comp(_it->value.first, _node->value.first))
                {
                    if (!_it->parent)
                        return (*this);
                    else
                        _it = _it->parent;
                }
                if (_it->parent)
                    _node = _it;
            }
        }

        RedBlackTreeIterator    operator--(int)
        {
            if (_node->left)
                _node = _node->left;
            else if (_node->parent)
            {
                pointer _it(_node->parent);
                while (!_comp(_it->value.first, _node->value.first))
                {
                    if (!_it->parent)
                        return (*this);
                    else
                        _it = _it->parent;
                }
                if (_it->parent)
                    _node = _it;
            }
        }

    private:

        pointer     _node;
        Compare     _comp;     

};

#endif
