/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:38:30 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/08 12:19:14 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <cmath>

# include "../iterator/bidirectional_iterator.hpp"

namespace ft
{
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map
    {
        private:        

            struct node
            {
                ft::pair<const Key, T>  content;
                node*                   parent;
                node*                   left;
                node*                   right;
            };

        public:

            typedef Key                                             key_type;
            typedef Compare                                         key_compare;
            typedef Alloc                                           allocator_type;
            typedef T                                               mapped_type;
            
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef long int                                        difference_type;
            typedef size_t                                          size_type;

            typedef T&                                              reference;
            typedef const T&                                        const_reference;
            typedef T*                                              pointer;
            typedef const T*                                        const_pointer;
            
			typedef typename ft::bidirectional_iterator<value_type, Compare, node>						iterator;
			typedef typename ft::bidirectional_iterator<const value_type, Compare, node>				const_iterator;
			typedef ft::reverse_iterator<iterator>														reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>												const_reverse_iterator;		

            class value_compare
            {
                friend class map;
                
                protected:
                
                    key_compare comp;
                    
                    value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object

                public:
                
                    typedef bool        result_type;
                    typedef value_type  first_argument_type;
                    typedef value_type  second_argument_type;

                    bool operator()(const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
            
        private:

            node*                   _top;          // Pointer to the first element of the tree (moveNode)
            node*                   _lastNode;      // Pointer to the last elem of the tree
            size_type               _size;          // Number of T values inside the map
            allocator_type          _allocPair;     // Copy of allocator_type object
            key_compare             _comp;          // Copy of comp key_compare predicate
            std::allocator<node>     _allocNode;     // node's allocator
            
            
        public:       
            explicit map(const key_compare& comp = key_compare(),
                        const allocator_type& alloc = allocator_type()) :
                _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastNode = createNode(ft::pair<const key_type, mapped_type>());
                _top = _lastNode;
                _lastNode->left = _lastNode;
                _lastNode->right = _lastNode;
            }

            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type(), 
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) :
                _size(0), _allocPair(alloc), _comp(comp)
            {
                _lastNode = createNode(ft::pair<const key_type, mapped_type>());
                _top = _lastNode;
                _lastNode->left = _lastNode;
                _lastNode->right = _lastNode;
                
                for (; first != last; ++first)
                    insert(*first);
            }

            map(const map& x) :
                _size(0), _allocPair(x._allocPair), _comp(x._comp), _allocNode(x._allocNode)
            {
                _lastNode = createNode(ft::pair<const key_type, mapped_type>());
                _top = _lastNode;
                _lastNode->left = _lastNode;
                _lastNode->right = _lastNode;

                for (const_iterator it = x.begin(); it != x.end(); ++it)
                    insert(*it);
            }

            ~map()
            {
                clear();
                deallocateNode(_lastNode);
            }


            map& operator=(const map& x)
            {
                map tmp(x);
                this->swap(tmp);
                
                return *this;
            }



            iterator begin()                        { return iterator(_lastNode->right, _lastNode, _comp); }
            const_iterator begin() const            { return const_iterator(_lastNode->right, _lastNode, _comp); }
            iterator end()                          { return iterator(_lastNode, _lastNode, _comp); }
            const_iterator end() const              { return const_iterator(_lastNode, _lastNode, _comp); }
            reverse_iterator rbegin()               { return reverse_iterator(_lastNode->left, _lastNode, _comp); }
            const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastNode->left, _lastNode, _comp); }
            reverse_iterator rend()                 { return reverse_iterator(_lastNode, _lastNode, _comp); }
            const_reverse_iterator rend() const     { return const_reverse_iterator(_lastNode, _lastNode, _comp); }


            /* ------------------------------------------------------------- */
            /* -------------------------- CAPACITY ------------------------- */
            bool empty() const              { return _size == 0; }
            size_type size() const          { return _size; }
            size_type       max_size() const
            {
                if (sizeof(value_type) == 1)
                    return static_cast<size_type>(pow(2.0, 64.0) / 2.0) - 1;
                return static_cast<size_type>(pow(2.0, 64.0) / static_cast<double>(sizeof(value_type))) - 1;
            }
            mapped_type& operator[](const key_type& k)
            {
                node* tmp = checkNode(_top, k);

                if (tmp)
                    return tmp->content.second;

                value_type val = make_pair<key_type, mapped_type>(k, mapped_type());
                return insertNode(_top, val)->content.second;
            }
        
            ft::pair<iterator,bool> insert (const value_type& val)
            {
                // Searches in the tree if val's key is already present and returns 
                // an iterator to the key inside the tree if it's the case
                node* elemIsPresent = checkNode(_top, val.first);
                if (elemIsPresent)
                    return ft::pair<iterator, bool>(iterator(elemIsPresent, _lastNode, _comp), false);

                // Inserts the pair in the tree and returns an iterator to its position
                ++_size;
                return ft::pair<iterator, bool>(iterator(insertNode(_top, val), _lastNode, _comp), true);
            }
        
            iterator insert (iterator position, const value_type& val)
            {   
                // If position key is higher than val, we need to decrease position 
                // until we find the closest highest key from val in the tree
                if (position->first > val.first)
                {
                    iterator prev(position);
                    --prev;
                    while (prev != end() && prev->first >= val.first)
                    {
                        --position;
                        --prev;
                    }
                }

                // Opposite case
                else if (position->first < val.first)
                {
                    iterator next(position);
                    ++next;
                    while (next != end() && next->first <= val.first)
                    {
                        ++position;
                        ++next;
                    }
                }

                // If the value already exist, and the tree isn't empty
                if (position != end() && val.first == position->first)
                    return position;

                ++_size;
                return iterator(insertNode(position.getNode(), val), _lastNode, _comp);
            }



            template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
            {
                while (first != last)
                    insert(*first++);
            }

            void erase (iterator position)
            {
                deleteNode(position.getNode(), position->first);
                --_size;
            }

            size_type erase (const key_type& k)
            {
                size_type ret = deleteNode(_top, k);
                _size -= ret;
                return ret;
            }

            void erase (iterator first, iterator last)
            {
                while (first != last)
                {
                    iterator tmp(first);
                    ++first;
                    erase(tmp);
                }
            }

            void swap (map& x)
            {
                swap(_top, x._top);
                swap(_lastNode, x._lastNode);
                swap(_size, x._size);
                swap(_comp, x._comp);
                swap(_allocPair, x._allocPair);
                swap(_allocNode, x._allocNode);
            }

            void clear()        { erase(begin(), end()); }
            key_compare key_comp() const        { return _comp; }
            value_compare value_comp() const    { return value_compare(_comp); }
            iterator find(const key_type& k)
            {
                node* tmp = checkNode(_top, k);

                if (tmp)
                    return iterator(tmp, _lastNode, _comp);
                
                // Case no match
                return end();
            }

            const_iterator find(const key_type& k) const
            {
                node* tmp = checkNode(_top, k);

                if (tmp)
                    return const_iterator(tmp, _lastNode, _comp);
                
                // Case no match
                return end();
            }

            size_type count (const key_type& k) const
            {
                node* tmp = checkNode(_top, k);
                
                return tmp ? true: false;
            }

            iterator lower_bound(const key_type& k)
            {
                iterator it = begin();

                for (; it != end(); ++it)
                    if (!_comp(it->first, k))
                        break;
                
                return it;  
            }
            
            const_iterator lower_bound(const key_type& k) const
            {
                const_iterator it = begin();

                for (; it != end(); ++it)
                    if (!_comp(it->first, k))
                        break;
                
                return it;  
            }

            iterator upper_bound(const key_type& k)
            {
                iterator it = begin();

                for (; it != end(); ++it)
                    if (_comp(k, it->first))
                        break;
                
                return it;  
            }

            const_iterator upper_bound(const key_type& k) const
            {
                const_iterator it = begin();

                for (; it != end(); ++it)
                    if (_comp(k, it->first))
                        break;
                
                return it;  
            }

            pair<iterator,iterator> equal_range(const key_type& k)
            {
                iterator it = upper_bound(k);

                if (it != begin())
                {
                    --it;

                    if (_comp(it->first, k) || _comp(k, it->first))
                        ++it;
                }

                iterator next(it);
                if (it != end())
                    ++next;
                
                return make_pair<iterator, iterator>(it, next);
            }

            pair<const_iterator,const_iterator> equal_range(const key_type& k) const
            {
                const_iterator it = upper_bound(k);

                if (it != begin())
                {
                    --it;

                    if (_comp(it->first, k) || _comp(k, it->first))
                        ++it;
                }

                const_iterator next(it);
                if (it != end())
                    ++next;
                
                return make_pair<const_iterator, const_iterator>(it, next);
            }


            /* ----------------- PRIVATE MEMBER FUNCTIONS ------------------ */
            /* ------------------------------------------------------------- */
            
        private:

            template <typename U>
            void swap(U& a, U& b)
            {
                U tmp = a;
                a = b;
                b = tmp;
            }

            template <class T1,class T2>
            pair<T1,T2> make_pair(T1 x, T2 y) const
            {
                return pair<T1,T2>(x,y);
            }


            node* createNode(const value_type& pair)
            {
                node* newNode = _allocNode.allocate(1);

                _allocPair.construct(&newNode->content, pair);
                newNode->parent = 0;
                newNode->left = 0;
                newNode->right = 0;

                return newNode;
            }

            void deallocateNode(node* del)
            {
                _allocPair.destroy(&del->content);
                _allocNode.deallocate(del, 1);
            }

            int heightTree(node *moveNode, int height)
            {
                // We reached a NULL, returning
                if (!moveNode || moveNode == _lastNode)
                    return height - 1;

                // Exploring left side of the actual node, then right side
                int leftHeight = heightTree(moveNode->left, height + 1);
                int rightHeight = heightTree(moveNode->right, height + 1);

                return leftHeight > rightHeight ? leftHeight : rightHeight;
            }

            node* checkNode(node* moveNode, key_type key) const
            {
                // We reached a leaf or tree is empty
                if (!moveNode || moveNode == _lastNode)
                    return 0;
                
                // Case we find a match
                if (!_comp(moveNode->content.first, key) && !_comp(key, moveNode->content.first))
                    return moveNode;
                
                // Recursive loop until we find key
                if (moveNode->content.first > key && moveNode->left && moveNode->left != _lastNode)
                    return checkNode(moveNode->left, key);
                else if (moveNode->content.first < key && moveNode->right && moveNode->right != _lastNode)
                    return checkNode(moveNode->right, key);

                // If we reach this step in the first checkNode func that was called
                // with moveNode (first node of the tree), then element is missing.
                return 0;
            }

            node* searchMaxNode(node *moveNode) const
            {
                // Until we meet tree's right extremity and circular link _lastNode
                if (moveNode->right && moveNode->right != _lastNode)
                    return searchMaxNode(moveNode->right);
                return moveNode;
            }

            node* searchMinNode(node *moveNode) const
            {
                // Until we meet tree's left extremity and circular link _lastNode
                if (moveNode->left && moveNode->left != _lastNode)
                    return searchMinNode(moveNode->left);
                return moveNode;
            }

            node* insertNode(node* insertPos, const value_type& pair)
            {
                // Case creating first node of the tree
                if (_top == _lastNode)
                {
                    _top = createNode(pair);
                    
                    _top->left = _lastNode;
                    _top->right = _lastNode;
                    _lastNode->left = _top;
                    _lastNode->right = _top;

                    return _top;
                }

                // Case key already exist in the tree
                if (insertPos->content.first == pair.first)
                    return 0;

                // Recursive loop until we reach a leaf or fake last node (_lastNode)
                if (insertPos->content.first > pair.first && 
                        insertPos->left && insertPos->left != _lastNode)
                    return insertNode(insertPos->left, pair);
                else if (insertPos->content.first < pair.first && 
                        insertPos->right && insertPos->right != _lastNode)
                    return insertNode(insertPos->right, pair);

                // If we reach this step, we arrived to a leaf or to the max node / min node 
                // of the tree (they're both linked to _lastNode): inserting new node to his correct position
                node *newNode = createNode(pair);

                // Case we reached a left or right leaf
                if (insertPos->content.first > newNode->content.first && !insertPos->left)
                    insertPos->left = newNode;
                else if (insertPos->content.first < newNode->content.first && !insertPos->right)
                    insertPos->right = newNode;

                // Case we reach min node or max node, inserting the node between min / max
                // and lastElem
                else if (insertPos->left && insertPos->content.first > newNode->content.first)
                {
                    newNode->left = _lastNode;
                    _lastNode->right = newNode;
                    insertPos->left = newNode;
                }
                else if (insertPos->right && insertPos->content.first < newNode->content.first)
                {
                    newNode->right = _lastNode;
                    _lastNode->left = newNode;
                    insertPos->right = newNode;
                }
                    
                newNode->parent = insertPos;

                // Equilibrating the tree from newNode to moveNode node
                balanceTheTree(&_top, newNode);

                return newNode;
            }


            bool deleteNode(node* deletePos, key_type key)
            {
                // Balance node will point to the first node impacted by the deletion (if we delete a node, 
                // it will be the parent node; if we delete moveNode, it will be one of his son). 
                // We will then call balanceTheTree function to equilibrate the AVL tree
                node* balanceNode = 0;
                
                // The node to delete, looking from deletePos node until we match key
                node* del = checkNode(deletePos, key);

                // If element isn't present, nothing to delete
                if (!del)
                    return false;
                
                /* --------------- CASE DELETING ROOT --------------- */
                // Case the node to delete is the moveNode
                if (!del->parent)
                {
                    // Root is the only node in the tree, it will be empty
                    if (del->left == _lastNode && del->right == _lastNode)
                    {
                        _top = _lastNode;
                        _lastNode->left = _lastNode;
                        _lastNode->right = _lastNode;
                    }

                    // Case only one son (left or right, need to equilibrate the tree
                    // for only moveNode)
                    else if (del->left && del->right == _lastNode)
                    {
                        balanceNode = del->parent;
                        _top = del->left;
                        del->left->parent = 0;
                        
                        // Since the tree is AVL, if _top has only one son, this son is 
                        // a leaf and has no left and right son. So the new moveNode has to be 
                        // llastElem from left and right side, but he's already 
                        // linked to inked to _it from one side (in this case, left)
                        _lastNode->left = del->left;
                        del->left->right = _lastNode;
                    }
                    else if (del->left == _lastNode && del->right)
                    {
                        balanceNode = del->parent;
                        _top = del->right;
                        del->right->parent = 0;

                        // Same explanation but with opposite side than just above
                        _lastNode->right = del->right;
                        del->right->left = _lastNode;
                    }
                    
                    // Case two sons, need to switch the key of the node to delete with the highest key
                    // in the left subtree, and to delete the node with this highest key in the left subtree
                    else
                    {
                        node* maxNode = searchMaxNode(del->left);
                        
                        // Need to destroy then construct for copying const variable)
                        _allocPair.destroy(&del->content);
                        _allocPair.construct(&del->content, maxNode->content);
                        
                        return deleteNode(del->left, maxNode->content.first);
                    }
                }


                /* --------------- CASE DELETING NODE --------------- */
                // Case the node to delete is a leaf
                else if ((!del->left || del->left == _lastNode) && (!del->right || del->right == _lastNode))
                {
                    balanceNode = del->parent;

                    // Case min node / max node, linking differs for _lastNode
                    node* linkToParent = 0;
                    if (del->left == _lastNode || del->right == _lastNode)
                    {
                        linkToParent = _lastNode;
                        del->content.first <= del->parent->content.first ?
                            _lastNode->right = del->parent : _lastNode->left = del->parent;
                    }
                        
                    del->content.first <= del->parent->content.first ?
                        del->parent->left = linkToParent : del->parent->right = linkToParent;
                }
                
                // Case only one son (only left son or only right son)
                else if ((del->left && del->left != _lastNode) && (!del->right || del->right == _lastNode))
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->left : del->parent->right = del->left;
                    del->left->parent = del->parent;

                    // Case the node to delete is max node, need to relink _lastNode
                    if (del->right == _lastNode)
                    {
                        _lastNode->left = del->left;
                        del->left->right = _lastNode;
                    }
                }
                else if ((!del->left || del->left == _lastNode) && del->right && del->right != _lastNode)
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->right : del->parent->right = del->right;
                    del->right->parent = del->parent;
                    
                    // Case the node to delete is max node, need to relink _lastNode
                    if (del->left == _lastNode)
                    {
                        _lastNode->right = del->right;
                        del->right->left = _lastNode;
                    }
                }

                // Case two sons, need to switch the key of the node to delete with the highest key
                // in the left subtree, and to delete the node with this highest key in the left subtree
                else
                {
                    node* maxNode = searchMaxNode(del->left);

                    // Need to destroy then construct for copying const variable)
                    _allocPair.destroy(&del->content);
                    _allocPair.construct(&del->content, maxNode->content);
                    
                    return deleteNode(del->left, maxNode->content.first);
                }

                // Equilibrating the tree from balanceNode to moveNode node
                balanceTheTree(&_top, balanceNode);

                deallocateNode(del);
                return true;
            }


            int balanceOfSubtrees(node* node)
            {
                if (!node)
                    return 0;
                return heightTree(node->left, 1) - heightTree(node->right, 1);
            }

            /**
            *   Does a right rotation between a node and his left child. The left child will go up
            *   and take the position of this node; and this node will become the right child of the node
            *   going up.
            *
            *   @param moveNode             First node of the tree.
            *   @param nodeGoingDown    Rotation will occured around this node.
            */
            void rotateRight(node** moveNode, node* nodeGoingDown)
            {
                //   P (nodeGoingUp) is going up and will replace Q (nodeGoingDown)
                //
                //
                //               Q                                 P              |
                //              / \     RIGHT ROTATION            / \             |
                //             P   C  ------------------->>>     A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

                node* nodeGoingUp = nodeGoingDown->left;
                
                // Left Q' son become right P' son
                nodeGoingDown->left = nodeGoingUp->right;
                
                // Case right son is NULL to prevent segfault
                if (nodeGoingUp->right)
                    nodeGoingUp->right->parent = nodeGoingDown;
                
                // rigth P' son is Q
                nodeGoingUp->right = nodeGoingDown;
                
                // Parent P = Parent Q
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                // Determinating if Q has a parent (if not, Q is moveNode) and if it's the case,
                // determinating if it's left son or right son. Then updating Q's parent with
                // his new son, P node
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;
                
                // Parent of Q is now P
                nodeGoingDown->parent = nodeGoingUp;

                // Updating moveNode node if the rotation occured on moveNode
                if (!nodeGoingUp->parent)
                    *moveNode = nodeGoingUp;
            }


            void rotateLeft(node** moveNode, node* nodeGoingDown)
            {
                //   Q (nodeGoingUp) is going up and will replace P (nodeGoingDown)
                //
                //
                //               Q                                 P              |
                //              / \          LEFT ROTATION        / \             |
                //             P   C    <<<-------------------   A   Q            |
                //            / \                                   / \           |
                //           A   B                                 B   C          |

                node* nodeGoingUp = nodeGoingDown->right;
                
                // Right P' son become left Q' son
                nodeGoingDown->right = nodeGoingUp->left;

                // Case Q left son is NULL to prevent segfault
                if (nodeGoingUp->left)
                    nodeGoingUp->left->parent = nodeGoingDown;
                
                // Left Q' son is now P
                nodeGoingUp->left = nodeGoingDown;
                
                // Parent Q = Parent P
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                // Determinating if P has a parent (if not, P is moveNode) and if it's the case,
                // determinating if it's left son or right son. Then updating P's parent with
                // his new son, Q node
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;

                // Parent of P is now Q
                nodeGoingDown->parent = nodeGoingUp;

                // Updating moveNode node if the rotation occured on moveNode
                if (!nodeGoingUp->parent)
                    *moveNode = nodeGoingUp;
            }


            void balanceTheTree(node** moveNode, node* node)
            {
                // Checking balance of subtrees every parents of this node until we 
                // reach moveNode node          
                while (node)
                {
                    int balance;
                    
                    // Right right case (right subtree is deeper, and right right subtree aswell)
                    if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
                        rotateLeft(moveNode, node);

                    // Right left case (if balance of right node == 0, no difference between right 
                    // right case and and right left case)
                    else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
                    {
                        rotateRight(moveNode, node->right);
                        rotateLeft(moveNode, node);
                    }
                    
                    // Left left case (opposite of right right case)
                    else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
                        rotateRight(moveNode, node);

                    // Left right case (opposite of right left case)
                    else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
                    {
                        rotateLeft(moveNode, node->left);
                        rotateRight(moveNode, node);
                    }
                    node = node->parent;
                }
            }
            
    };  // class map
        
} // namespace ft

#endif