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

        RedBlackTreeIterator & operator=(const pointer & x)
        {
            _node = x;
            return (*this);
        }

        bool    operator==(const RedBlackTreeIterator & x) { return (_node == x._node); }
        bool    operator!=(const RedBlackTreeIterator & x) { return (_node != x._node); }

        pointer    base() const { return (_node); }

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
            else if (_node->parent && !_node->right)
            {
                pointer _it(_node);

                if (_node == _node->parent->right)
                {
                    ++_node;
                    return (*this);
                }
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
            else
                ++_node;
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
                pointer _it(_node);
                pointer y;

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
            if (_node->left)
            {
                if (_node->left->right)
                    _node = max_element(_node->left->right);
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
                    _node = max_element(_node->left->right);
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
            else
                _node--;
            return (old);
        }

    private:

        pointer     _node;
        Compare     _comp;     

};

#endif
