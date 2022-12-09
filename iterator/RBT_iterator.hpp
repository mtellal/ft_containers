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
        << obj.parent << "\nright = " << obj.right << "\nleft = " << obj.left << "\nred = " << obj.red;
        return (output);
    }
};


template < class Pair, class Compare = std::less<Pair>, class Node = ft::Node<Pair> >
class RedBlackTreeIterator : public ft::iterator<ft::bidirectional_iterator_tag, Pair >
{

    public:

        typedef ft::iterator<ft::bidirectional_iterator_tag, Pair>  iterator;
        typedef typename iterator::value_type                       value_type;
        typedef typename iterator::difference_type                  difference_type;
        typedef typename iterator::pointer                          pointer;
        typedef typename iterator::reference                        reference;
        typedef typename iterator::iterator_category                iterator_category;

        typedef Pair                                                pair;
        typedef Pair &                                              pair_reference;
        
        typedef Node                                                node_type;
        typedef node_type *                                         node_pointer;


        RedBlackTreeIterator() : _node(NULL) {}
        RedBlackTreeIterator(const RedBlackTreeIterator & x) : _node(x._node) {}
        RedBlackTreeIterator(const node_pointer & x) : _node(x) {}
        ~RedBlackTreeIterator() {}

        operator RedBlackTreeIterator<const Pair, Compare, Node >() const
        {
            return (RedBlackTreeIterator<const Pair, Compare, Node >(this->_node));
        }

        RedBlackTreeIterator & operator=(const RedBlackTreeIterator & x)
        {
             if (this != &x)
                _node = x._node;
            return (*this);
        }

        RedBlackTreeIterator & operator=(const node_pointer & x)
        {
            _node = x;
            return (*this);
        }

        node_type    operator() () { return (*_node); }

        bool    operator==(const RedBlackTreeIterator & x) { return (_node == x._node); }
        bool    operator!=(const RedBlackTreeIterator & x) { return (_node != x._node); }

        node_pointer    base() const { return (_node); }

        pair_reference   operator*(void) const { return (_node->value); }
        pair*    operator->() const { return &(_node->value); }


        node_pointer    min_element(node_pointer _n)
        {
            while (_n->left)
                _n = _n->left;
            return (_n);
        }

        node_pointer    max_element(node_pointer _n)
        {
            while (_n->right)
                _n = _n->right;
            return (_n);
        }

        /*      INCREMENT LAST ELEMNT => RETURN TO FIRST ELEMENT    */

        /*      CHANGE ITERATORS / NOT WORKING CORRECTLY */
        RedBlackTreeIterator &  operator++()
        {
             if (_node->right)
            {
                if (_node->right->left)
                    _node = min_element(_node->right);
                else
                    _node = _node->right;
            }
            else if (_node->parent && _node == _node->parent->left)
            {
                _node = _node->parent;
            }
            else if (_node->parent && _node == _node->parent->right && !_node->right)
            {
                node_pointer _it(_node);
                node_pointer y;

                while (_it)
                {
                    y = _it;
                    if (_comp(_node->value.first, _it->value.first) &&
                        !_comp(_it->value.first, _node->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
                if (!y->parent && y->right && 
                    (_comp(y->right->value.first, _node->value.first) ||
                    (!_comp(_node->value.first, y->right->value.first) && !_comp(y->right->value.first, _node->value.first))))
                {
                    _node++;            
                }
            }
            else
                _node++;
            return (*this);
        }

        RedBlackTreeIterator operator++(int)
        {
            //X++
            RedBlackTreeIterator old(*this);

            if (_node->right)
            {
                if (_node->right->left)
                    _node = min_element(_node->right);
                else
                    _node = _node->right;
            }
            else if (_node->parent && _node == _node->parent->left)
            {
                _node = _node->parent;
            }
            else if (_node->parent && _node == _node->parent->right && !_node->right)
            {
                node_pointer _it(_node);
                node_pointer y;

                while (_it)
                {
                    y = _it;
                    if (_comp(_node->value.first, _it->value.first) &&
                        !_comp(_it->value.first, _node->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
                if (!y->parent && y->right && 
                    (_comp(y->right->value.first, _node->value.first) ||
                    (!_comp(_node->value.first, y->right->value.first) && !_comp(y->right->value.first, _node->value.first))))
                {
                    _node++;            
                }
            }
            else
                _node++;
            return (old);
        }

        RedBlackTreeIterator & operator--()
        {
            std::cout << "operator--() called" << std::endl;
            std::cout << _node->parent->right << std::endl;
            if (_node->left)
            {
                if (_node->left->right)
                    _node = max_element(_node->left);
                else
                    _node = _node->left;
            }
            else if (_node->parent && _node == _node->parent->right)
            {
                _node = _node->parent;
            }
            else if (_node->parent && _node == _node->parent->left && !_node->left)
            {
                node_pointer _it(_node);
                node_pointer y;

                while (_it)
                {
                    y = _it;
                    if (_comp(_node->value.first, _it->value.first) &&
                        !_comp(_it->value.first, _node->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
                if (!y->parent && y->left && 
                    (_comp(y->left->value.first, _node->value.first) ||
                    (!_comp(_node->value.first, y->left->value.first)
                        && !_comp(y->left->value.first, _node->value.first))))
                {
                    --_node;            
                }
            }
            else
                --_node;
            return (*this);
        }

        RedBlackTreeIterator    operator--(int)
        {
            RedBlackTreeIterator    old(*this);

            if (_node->left)
            {
                if (_node->left->right)
                    _node = max_element(_node->left);
                else
                    _node = _node->left;
            }
            else if (_node->parent && _node == _node->parent->right)
            {
                _node = _node->parent;
            }
            else if (_node->parent && _node == _node->parent->left && !_node->left)
            {
                node_pointer _it(_node);
                node_pointer y;

                while (_it)
                {
                    y = _it;
                    if (_comp(_node->value.first, _it->value.first) &&
                        !_comp(_it->value.first, _node->value.first))
                    {
                        _node = _it;
                        break ;
                    }
                    _it = _it->parent;
                }
                if (!y->parent && y->left && 
                    (_comp(y->left->value.first, _node->value.first) ||
                    (!_comp(_node->value.first, y->left->value.first)
                        && !_comp(y->left->value.first, _node->value.first))))
                {
                    _node--;            
                }
            }
            else
                _node--;
            return (old);
        }

    private:

        node_pointer     _node;
        Compare     _comp;     

};


#endif
