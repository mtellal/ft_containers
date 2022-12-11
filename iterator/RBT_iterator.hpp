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


        RedBlackTreeIterator() : _node(NULL), _end(NULL) {}

        RedBlackTreeIterator(const RedBlackTreeIterator & x) : _node(x._node), _end(x._end) {}

        RedBlackTreeIterator(const node_pointer & node, const node_pointer & end) :
            _node(node), _end(end) {}

        virtual ~RedBlackTreeIterator() {}

        operator RedBlackTreeIterator<const Pair, Compare, Node >() const
        {
            return (RedBlackTreeIterator<const Pair, Compare, Node >(this->_node, this->_end));
        }

        RedBlackTreeIterator & operator=(const RedBlackTreeIterator & x)
        {
             if (this != &x)
            {
                _node = x._node;
                _end = x._end;
            }
            return (*this);
        }
    
        node_type    operator() () { return (*_node); }

        bool    operator==(const RedBlackTreeIterator & x)
        {
            return (_node == x._node);
        }
        bool    operator!=(const RedBlackTreeIterator & x)
        {
             return (_node != x._node);
        }

        node_pointer    base() const { return (_node); }

        pair_reference   operator*(void) const { return (_node->value); }
        pair*    operator->() const { return &(_node->value); }


        /*      INCREMENT LAST ELEMNT => RETURN TO FIRST ELEMENT    */

        /*      CHANGE ITERATORS / NOT WORKING CORRECTLY */
        RedBlackTreeIterator &  operator++()
        {
            node_pointer    tmp;

           if (_node == _end)
                _node = _node->parent;
            else if (_node->right)
                _node = min_element(_node->right);
            else if (_node->parent)
            {
                tmp = _node;
                if (_compare(_node->value.first, _node->parent->value.first))
                    _node = _node->parent;
                else
                {
                    while (tmp->parent && _compare(tmp->parent->value.first, _node->value.first))
                        tmp = tmp->parent;
                    if (!tmp->parent && !_compare(tmp->value.first, _node->value.first))
                        _node = _end;
                    else
                        _node = tmp->parent;
                }
            }
            return (*this);
        }

        RedBlackTreeIterator operator++(int)
        {
            RedBlackTreeIterator old(*this);
            node_pointer    tmp;

           if (_node == _end)
            {
                if (_node->parent)
                    _node = _node->parent;
            }
            else if (_node->right)
            {
                _node = min_element(_node->right);
            }
            else if (_node->parent)
            {
                tmp = _node;
                if (_compare(_node->value.first, _node->parent->value.first))
                    _node = _node->parent;
                else
                {
                    while (tmp->parent && _compare(tmp->parent->value.first, _node->value.first))
                        tmp = tmp->parent;
                    if (!tmp->parent && _compare(tmp->value.first, _node->value.first))
                        _node = _end;
                    else
                        _node = tmp->parent;
                }
            }
            return (old);
        }

        RedBlackTreeIterator & operator--()
        {            
            node_pointer    tmp;

            if (_node == _end)
                _node = _node->parent;
            else if (_node->left)
                _node = max_element(_node->left);
            else if (_node->parent)
            {
                tmp = _node;
                if (_compare(_node->parent->value.first, _node->value.first))
                    _node = _node->parent;
                else
                {
                    while (tmp->parent && _compare(_node->value.first, tmp->parent->value.first))
                        tmp = tmp->parent;
                    if (!tmp->parent && _compare(_node->value.first, tmp->parent->value.first))
                        _node = _end;
                    else
                        _node = tmp->parent;
                }
            }
            return (*this);
        }

        RedBlackTreeIterator    operator--(int)
        {
            RedBlackTreeIterator    old(*this);
            node_pointer            tmp;

            if (_node == _end)
                _node = _node->parent;
            else if (_node->left)
                _node = max_element(_node->left);
            else if (_node->parent)
            {
                tmp = _node;
                if (_compare(_node->parent->value.first, _node->value.first))
                    _node = _node->parent;
                else
                {
                    while (tmp->parent && _compare(_node->value.first, tmp->parent->value.first))
                        tmp = tmp->parent;
                    if (!tmp->parent && _compare(_node->value.first, tmp->parent->value.first))
                        _node = _end;
                    else
                        _node = tmp->parent;
                }
            }
            return (old);
        }

    private:

        node_pointer    _node;
        node_pointer    _end;
        Compare         _compare;     

         node_pointer    min_element(node_pointer _n)
        {
            while (_n->left && _n->left != _end)
                _n = _n->left;
            return (_n);
        }

        node_pointer    max_element(node_pointer _n)
        {
            while (_n->right && _n->right != _end)
                _n = _n->right;
            return (_n);
        }

};


#endif
