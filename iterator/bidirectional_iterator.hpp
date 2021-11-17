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
            typedef node*                                                                                   node_pointer;
            typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
            
            bidirectional_iterator(node_pointer Node = nullptr, node_pointer top = nullptr, const key_compare& comp = key_compare())
            : _node(Node), _top(top), _comp(comp) {}
            bidirectional_iterator(const bidirectional_iterator<value_type, Compare, node>& other)
            {
                _node = other.getNode();
                _top = other.gettop();
                _comp = other.getCompare();
            } 
            ~bidirectional_iterator() {}
            
            bidirectional_iterator& operator=(const bidirectional_iterator& other)
            {
                if (this != &other)
                {
                    _node = other._node;
                    _top = other._top;
                    _comp = other._comp;
                }
                return (*this);
            }

            node_pointer getNode() const             { return _node; }
            node_pointer getTop() const         { return _top; }
            key_compare getCompare() const      { return _comp; }
   
            reference operator*() const         { return (_node->value); }
            pointer operator->() const          { return (&_node->value); }


            bidirectional_iterator& operator++()
            {
                node_pointer previousNode = _node;
                if (_node == _lastNode)
                {
                    _node = _lastNode->right;
                    return (*this);
                }
 
            }

            // bidirectional_iterator& operator++()
            // {
            //     node_pointer previousNode = _node;
            //     if (_node == _lastNode)
            //     {
            //         _node = _lastNode->right;
            //         return (*this);
            //     }
 
            //     while (!_node && !_comp(previousNode->value.first, _node->value.first))
            //     {
            //         if (_node->right && (_node->right == _lastNode || _comp(previousNode->value.first, _node->right->value.first)))
            //         {
            //             _node = _node->right;      
            //             node* tmp = nullptr;
            //             if (!_node && (tmp = searchMinNode(_node)))
            //                 _node = tmp;
            //         }
            //         else
            //             _node = _node->parent;
            //     }
            //     return (*this);
            // }

            // bidirectional_iterator operator++(int)
            // {
            //     bidirectional_iterator res(*this);

            //     if (_node == _lastNode)
            //     {
            //         _node = _lastNode->right;
            //         return (res);
            //     }             
            //     while (_node != _lastNode && !_comp(res->first, _node->content.first))
            //     {
            //         if (_node->right && (_node->right == _lastNode || 
            //                 _comp(res->first, _node->right->content.first)))
            //         {
            //             _node = _node->right;
                        
            //             node* tmp = nullptr;
            //             if (_node != _lastNode && (tmp = searchMinNode(_node)))
            //                 _node = tmp;
            //         }
            //         else
            //             _node = _node->parent;
            //     }        
            //     return (res);
            // }

            // bidirectional_iterator& operator--()
            // {
            //     node_pointer previousNode = _node;

            //     if (_node == _lastNode)
            //     {
            //         _node = _lastNode->left;
            //         return (*this);
            //     }

            //     while (_node != _lastNode && !_comp(_node->content.first, previousNode->content.first))
            //     {
            //         if (_node->left && (_node->left == _lastNode || 
            //                 _comp(_node->left->content.first, previousNode->content.first)))
            //         {
            //             _node = _node->left;
                        
            //             node* tmp = nullptr;
            //             if (_node != _lastNode && (tmp = searchMaxNode(_node)))
            //                 _node = tmp;
            //         }
            //         else
            //             _node = _node->parent;
            //     }

            //     return (*this);
            // }

            // bidirectional_iterator operator--(int)
            // {
            //     bidirectional_iterator res(*this);

            //     if (_node == _lastNode)
            //     {
            //         _node = _lastNode->left;
            //         return (res);
            //     }
                
            //     while (_node != _lastNode && !_comp(_node->content.first, res->first))
            //     {
            //         if (_node->left && (_node->left == _lastNode || 
            //                 _comp(_node->left->content.first, res->first)))
            //         {
            //             _node = _node->left;
                        
            //             node* tmp = nullptr;
            //             if (_node != _lastNode && (tmp = searchMaxNode(_node)))
            //                 _node = tmp;
            //         }
            //         else
            //             _node = _node->parent;
            //     }
                
            //     return (res);
            // }

            bool operator==(const bidirectional_iterator& it) const   { return (it._node == _node); }
            bool operator!=(const bidirectional_iterator& it) const   { return (it._node != _node); }

        private:
        	node_pointer        _node;
            node_pointer        _top; 
            key_compare			_comp;
            
            node* searchMinNode(node* node)
            {
                if (!node->left)
                    return node;
                return minimum(node->left);
            }

            node* searchMinNode(node* node)
            {
                if (!node->right)
                    return node;
                return searchMaxNode(node->right);
            }    

    };     
}

#endif