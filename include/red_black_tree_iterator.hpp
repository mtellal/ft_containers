/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree_iterator.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:51:59 by mtellal           #+#    #+#             */
/*   Updated: 2022/11/24 14:52:18 by mtellal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RedBlackTreeIterator_HPP
#define RedBlackTreeIterator_HPP

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

        typedef size_t                                              size_type;

        typedef Pair                                                pair;
        typedef Pair &                                              pair_reference;
        
        typedef Node                                                node_type;
        typedef node_type *                                         node_pointer;


        RedBlackTreeIterator() : _node(NULL), _end(NULL) {}

        RedBlackTreeIterator(const RedBlackTreeIterator & x) : _node(x._node), _end(x._end) {}

        RedBlackTreeIterator(const node_pointer & node, const node_pointer & end) :
            _node(node), _end(end) {}

        ~RedBlackTreeIterator() {}

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

        node_pointer    base() const { return (_node); }
    
        ////////////////////             EQUAL/NOT EQUAL OPRATORS       ////////////////////////

        bool            operator==(const RedBlackTreeIterator & x) { return (_node == x._node); }

        bool            operator!=(const RedBlackTreeIterator & x) { return (_node != x._node); }

        ////////////////////             DEREFERENCEMENT OPRATORS       ////////////////////////

        pair_reference  operator*() const { return (_node->value); }

        pair*           operator->() const { return &(_node->value); }

        ////////////////////             IN/DECREMENTATION OPRATORS       ////////////////////////

        RedBlackTreeIterator &  operator++()
        {
            node_pointer    tmp;

           if (_node == _end && _node->parent)
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

           if (_node == _end && _node->parent)
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

            if (_node == _end && _node->parent)
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

            if (_node == _end && _node->parent)
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

template <class P, class C, class N>
bool    operator==(const RedBlackTreeIterator<P, C, N> & lhs,
                    const RedBlackTreeIterator<P, C, N> & rhs)
{
    return (lhs.base() == rhs.base());
}

template <class P, class C, class N>
bool    operator==(const RedBlackTreeIterator<P, C, N> & lhs,
                    const RedBlackTreeIterator<const P, C, N> & rhs)
{
    return (lhs.base() == rhs.base());
} 

template <class P, class C, class N>
bool    operator!=(const RedBlackTreeIterator<P, C, N> & lhs,
                    const RedBlackTreeIterator<P, C, N> & rhs)
{
    return (lhs.base() != rhs.base());
}

template <class P, class C, class N>
bool    operator!=(const RedBlackTreeIterator<P, C, N> & lhs,
                    const RedBlackTreeIterator<const P, C, N> & rhs)
{
    return (lhs.base() != rhs.base());
}

#endif
