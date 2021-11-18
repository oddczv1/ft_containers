#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator.hpp"
# include "util.hpp"

namespace ft
{
    template <typename value_type, typename Compare, typename node>
    class bidirectional_iterator
    {
        public:
            typedef Compare                                                                                 key_compare;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
            
            bidirectional_iterator(node* Node = nullptr, const key_compare& comp = key_compare())
            : _node(Node), _comp(comp) {}

            bidirectional_iterator(const bidirectional_iterator<value_type, Compare, node>& other)
            {
                _node = other.getNode();
                _comp = other.getCompare();
            } 

            ~bidirectional_iterator() {}
            
            bidirectional_iterator& operator=(const bidirectional_iterator& other)
            {
                if (this != &other)
                {
                    _node = other._node;
                    _comp = other._comp;
                }
                return (*this);
            }

            node* getNode() const        { return _node; }
            key_compare getCompare() const      { return _comp; }
            reference operator*() const         { return (_node->value); }
            pointer operator->() const          { return (&_node->value); }

            bidirectional_iterator& operator++()
            {
                if (_node->right)
                {
                    _node = _node->right;
                    while (_node->left)
                        _node = _node->left;
                }
                else
                {
                    node* tmp;
                    do
                    {
                        tmp = _node;
                        _node = _node->parent;
                    } while (_node && tmp == _node->right);
                }
                return *this;
            }
        
            bidirectional_iterator operator++(int)
            {
                bidirectional_iterator tem(*this);
                operator++();
                return tem;
            }

            bidirectional_iterator& operator--()
            {
                if (_node->left)
                {
                    _node = _node->left;
                    while (_node && _node->right)
                        _node = _node->right;
                }
                else
                {
                    node* tmp;
                    do
                    {
                        tmp = _node;
                        _node = _node->parent;
                    } while (_node && tmp == _node->left);
                }
                return *this;
            }

            bidirectional_iterator operator--(int)
            {
      			bidirectional_iterator tem(*this);
                operator--();
                return tem;
            }

            bool operator==(const bidirectional_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const bidirectional_iterator& it) const   { return (it._node != _node); }

        private:
        	node*       _node;
            key_compare _comp;
            
    };     
}

#endif