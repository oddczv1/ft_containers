#ifndef MAP_HPP
# define MAP_HPP

# include "../iterator/bidirectional_iterator.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
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
			// Member types //
			typedef Key 																				key_type;
			typedef	T 																					mapped_type;
			typedef typename ft::pair<const key_type, T> 												value_type;
			typedef size_t 																				size_type;
			typedef typename std::ptrdiff_t 															difference_type;
			typedef Compare 																			key_compare;
			typedef Allocator 																			allocator_type;
			typedef value_type& 																		reference;
			typedef const value_type& 																	const_reference;
			typedef typename Allocator::pointer 														pointer;
			typedef typename Allocator::const_pointer 													const_pointer;
			typedef typename ft::bidirectional_iterator<value_type, Compare, node>						iterator;
			typedef typename ft::bidirectional_iterator<const value_type, Compare, node>				const_iterator;
			typedef ft::reverse_iterator<iterator>														reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>												const_reverse_iterator;		
			// Member classes //
			class value_compare
			{
				friend class map;
				public:
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator()(const value_type& lhs, const value_type& rhs) const { return _comp(lhs.first, rhs.first); }
				protected:
					key_compare _comp;
					value_compare(key_compare comp) : _comp(comp) {}						
			};
			// Member functions //
			map(const Compare &comp = key_compare(), const Allocator &alloc = allocator_type());
			template< class InputIt >
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr);
			map(const map& other);
			~map();
			map &operator=( const map &other );
			// Element access //
			T& at(const Key& key);
			const T& at(const Key& key) const;
			T& operator[](const Key &key);
			// Iterators //
            iterator begin()                        { return iterator(_lastNode->right, _lastNode, _comp); }
            const_iterator begin() const            { return const_iterator(_lastNode->right, _lastNode, _comp); }
            iterator end()                          { return iterator(_lastNode, _lastNode, _comp); }
            const_iterator end() const              { return const_iterator(_lastNode, _lastNode, _comp); }
            reverse_iterator rbegin()               { return reverse_iterator(_lastNode->left, _lastNode, _comp); }
            const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastNode->left, _lastNode, _comp); }
            reverse_iterator rend()                 { return reverse_iterator(_lastNode, _lastNode, _comp); }
            const_reverse_iterator rend() const     { return const_reverse_iterator(_lastNode, _lastNode, _comp); }
			// Capacity //
            bool empty() const						{ return (_size == 0); }
            size_t size() const						{ return (_size); }
            size_t max_size() const 				{ return (_allocNode.max_size()); }
			// Modifiers //
			void clear();
			ft::pair<iterator, bool> insert(const value_type &value);
			iterator insert(iterator position, const value_type& value);     
			template< class InputIterator >
			void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);   
            void erase (iterator position);
            void erase (iterator first, iterator last);
            size_type erase (const key_type& key);
			void swap(map &other);
			// Lookup //
			size_type count(const Key &key);
			iterator find(const Key &key);
			const_iterator find(const Key &key) const;
			ft::pair<iterator,iterator> equal_range(const Key &key);
			ft::pair<const_iterator,const_iterator> equal_range(const Key &key) const;
			iterator lower_bound(const Key &key);
			const_iterator lower_bound(const Key &key) const;
			iterator upper_bound(const Key &key);
			const_iterator upper_bound(const Key &key) const;
			// Observers //
            key_compare key_comp() const        { return _comp; }
            value_compare value_comp() const    { return value_compare(_comp); }

		private:
            node*                   _top;
            node*                   _lastNode;
            size_type               _size;
            allocator_type          _allocPair;
            key_compare             _comp;
            std::allocator<node>     _allocNode;

			// tree function //
            node* createNode(const value_type& value)
            {
                node* newNode = _allocNode.allocate(1);

                _allocPair.construct(&newNode->content, value);
                newNode->parent = nullptr;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return newNode;
            }

            void deallocateNode(node* del)
            {
                _allocPair.destroy(&del->content);
                _allocNode.deallocate(del, 1);
            }

            int heightTree(node *moveNode, int height)
            {
                if (!moveNode || moveNode == _lastNode)
                    return height - 1;

                int leftHeight = heightTree(moveNode->left, height + 1);
                int rightHeight = heightTree(moveNode->right, height + 1);

                return (leftHeight > rightHeight ? leftHeight : rightHeight);
            }

            node* searchMaxNode(node *moveNode)
            {
                if (moveNode->right && moveNode->right != _lastNode)
                    return searchMaxNode(moveNode->right);
                return moveNode;
            }

            node* searchMinNode(node *moveNode) const
            {
                if (moveNode->left && moveNode->left != _lastNode)
                    return searchMinNode(moveNode->left);
                return moveNode;
            }

            node* checkNode(node* moveNode, const key_type& key) 
            {
                if (!moveNode || moveNode == _lastNode)
                    return (nullptr);    
                if (moveNode->content.first == key)
                    return (moveNode);             
                if (moveNode->content.first > key && moveNode->left && moveNode->left != _lastNode)
                    return checkNode(moveNode->left, key);
                else if (moveNode->content.first < key && moveNode->right && moveNode->right != _lastNode)
                    return checkNode(moveNode->right, key);
                return (nullptr);
            }

            node* insertNode(node* moveNode, const value_type& value)
            {
                if (_top == _lastNode)
                {
                    _top = createNode(value);
                    _top->left = _lastNode;
                    _top->right = _lastNode;
                    _lastNode->left = _top;
                    _lastNode->right = _top;
                    return _top;
                }
                // 넣을 자리까지 이동
                if (moveNode->content.first > value.first && moveNode->left && moveNode->left != _lastNode)
                    return insertNode(moveNode->left, value);
                else if (moveNode->content.first < value.first && moveNode->right && moveNode->right != _lastNode)
                    return insertNode(moveNode->right, value);
                // 노드 생성하고 왼쪽 넣을지 오른쪽 넣을지 확인
                node *newNode = createNode(value);
                if (moveNode->content.first > newNode->content.first && !moveNode->left)
                    moveNode->left = newNode;
                else if (moveNode->content.first < newNode->content.first && !moveNode->right)
                    moveNode->right = newNode;
                else if (moveNode->left && moveNode->content.first > newNode->content.first)
                {
                    newNode->left = _lastNode;
                    _lastNode->right = newNode;
                    moveNode->left = newNode;
                }
                else if (moveNode->right && moveNode->content.first < newNode->content.first)
                {
                    newNode->right = _lastNode;
                    _lastNode->left = newNode;
                    moveNode->right = newNode;
                }               
                newNode->parent = moveNode;
                balanceTheTree(&_top, newNode);
                return newNode;
            }

            bool deleteNode(node* deletePos, key_type key)
            {
                node* balanceNode = 0;
                node* del = checkNode(deletePos, key);

                if (!del)
                    return false;
                if (!del->parent)
                {
                    if (del->left == _lastNode && del->right == _lastNode)
                    {
                        _top = _lastNode;
                        _lastNode->left = _lastNode;
                        _lastNode->right = _lastNode;
                    }
                    else if (del->left && del->right == _lastNode)
                    {
                        balanceNode = del->parent;
                        _top = del->left;
                        del->left->parent = 0;
                        _lastNode->left = del->left;
                        del->left->right = _lastNode;
                    }
                    else if (del->left == _lastNode && del->right)
                    {
                        balanceNode = del->parent;
                        _top = del->right;
                        del->right->parent = 0;
                        _lastNode->right = del->right;
                        del->right->left = _lastNode;
                    }
                    else
                    {
                        node* maxNode = searchMaxNode(del->left);
                        _allocPair.destroy(&del->content);
                        _allocPair.construct(&del->content, maxNode->content);
                        
                        return deleteNode(del->left, maxNode->content.first);
                    }
                }
                else if ((!del->left || del->left == _lastNode) && (!del->right || del->right == _lastNode))
                {
                    balanceNode = del->parent;
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
                else if ((del->left && del->left != _lastNode) && (!del->right || del->right == _lastNode))
                {
                    balanceNode = del->parent;

                    del->content.first <= del->parent->content.first ?
                            del->parent->left = del->left : del->parent->right = del->left;
                    del->left->parent = del->parent;

                    if (del->right == _lastNode)
                    {
                        _lastNode->left = del->left;
                        del->left->right = _lastNode;
                    }
                }
                else if ((!del->left || del->left == _lastNode) && del->right && del->right != _lastNode)
                {
                    balanceNode = del->parent;
                    del->content.first <= del->parent->content.first ? del->parent->left = del->right : del->parent->right = del->right;
                    del->right->parent = del->parent;
                    
                    if (del->left == _lastNode)
                    {
                        _lastNode->right = del->right;
                        del->right->left = _lastNode;
                    }
                }
                else
                {
                    node* maxNode = searchMaxNode(del->left);
                    _allocPair.destroy(&del->content);
                    _allocPair.construct(&del->content, maxNode->content);
                    
                    return deleteNode(del->left, maxNode->content.first);
                }

                balanceTheTree(&_top, balanceNode);
                deallocateNode(del);
                return (1);
            }

            void rotateRight(node** moveNode, node* nodeGoingDown)
            {
                node* nodeGoingUp = nodeGoingDown->left;
                nodeGoingDown->left = nodeGoingUp->right;
                
                if (nodeGoingUp->right)
                    nodeGoingUp->right->parent = nodeGoingDown;
                
                nodeGoingUp->right = nodeGoingDown;
                nodeGoingUp->parent = nodeGoingDown->parent;
                
                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;
                
                nodeGoingDown->parent = nodeGoingUp;

                if (!nodeGoingUp->parent)
                    *moveNode = nodeGoingUp;
            }

            void rotateLeft(node** moveNode, node* nodeGoingDown)
            {
                node* nodeGoingUp = nodeGoingDown->right;
                nodeGoingDown->right = nodeGoingUp->left;

                if (nodeGoingUp->left)
                    nodeGoingUp->left->parent = nodeGoingDown;

                nodeGoingUp->left = nodeGoingDown;
                nodeGoingUp->parent = nodeGoingDown->parent;

                if (nodeGoingDown->parent && nodeGoingDown->parent->left == nodeGoingDown)
                    nodeGoingDown->parent->left = nodeGoingUp;
                else if (nodeGoingDown->parent)
                    nodeGoingDown->parent->right = nodeGoingUp;

                nodeGoingDown->parent = nodeGoingUp;

                if (!nodeGoingUp->parent)
                    *moveNode = nodeGoingUp;
            }

            int balanceOfSubtrees(node* node)
            {
                if (!node)
                    return 0;
                return heightTree(node->left, 1) - heightTree(node->right, 1);
            }

            void balanceTheTree(node** moveNode, node* node)
            {   
                while (node)
                {
                    int balance;
                    if ((balance = balanceOfSubtrees(node)) < -1 && balanceOfSubtrees(node->right) < 0)
                        rotateLeft(moveNode, node);
                    else if (balance < -1 && balanceOfSubtrees(node->right) >= 0)
                    {
                        rotateRight(moveNode, node->right);
                        rotateLeft(moveNode, node);
                    }              
                    else if (balance > 1 && balanceOfSubtrees(node->left) > 0)
                        rotateRight(moveNode, node);

                    else if (balance > 1 && balanceOfSubtrees(node->left) <= 0)
                    {
                        rotateLeft(moveNode, node->left);
                        rotateRight(moveNode, node);
                    }
                    node = node->parent;
                }
            }
	};

    // Member functions //
    template < class Key, class T, class Compare, class Allocator>
	map<Key, T, Compare, Allocator>::map(const Compare &comp, const Allocator &alloc) : _size(0), _allocPair(alloc), _comp(comp)
    {
        _lastNode = createNode(value_type());
        _top = _lastNode;
        _lastNode->left = _lastNode;
        _lastNode->right = _lastNode;			
    }
    template < class Key, class T, class Compare, class Allocator>
    template< class InputIt >
	map<Key, T, Compare, Allocator>::map(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    : _size(0), _allocPair(alloc), _comp(comp)
    {
        _lastNode = createNode(value_type());
        _top = _lastNode;
        _lastNode->left = _lastNode;
        _lastNode->right = _lastNode;         
        for (; first != last; ++first)
            insert(*first);
    }
    template < class Key, class T, class Compare, class Allocator>
	map<Key, T, Compare, Allocator>::map(const map& other) : _size(0), _allocPair(other._allocPair), _comp(other._comp), _allocNode(other._allocNode)
    {
        _lastNode = createNode(ft::pair<const key_type, mapped_type>());
        _top = _lastNode;
        _lastNode->left = _lastNode;
        _lastNode->right = _lastNode;           
        for (const_iterator it = other.begin(); it != other.end(); ++it)
            insert(*it);
    }
    template < class Key, class T, class Compare, class Allocator>
	map<Key, T, Compare, Allocator>::~map(){ clear(); deallocateNode(_lastNode); }
    template < class Key, class T, class Compare, class Allocator>
	map<Key, T, Compare, Allocator> &map<Key, T, Compare, Allocator>::operator=( const map &other )
    {
        map tmp(other);
        this->swap(tmp);              
        return (*this);
    }

    // Element access //
    template < class Key, class T, class Compare, class Allocator>
    T& map<Key, T, Compare, Allocator>::at(const Key& key)
    {     
        node* haveNode = checkNode(_top, key);
        if (haveNode)
            return (haveNode->content.second);
        else
            throw (std::out_of_range("map::at:  key not found"));
    }
    template < class Key, class T, class Compare, class Allocator>
    const T& map<Key, T, Compare, Allocator>::at(const Key& key) const
    {
        node* haveNode = checkNode(_top, key);
        if (haveNode)
            return (haveNode->content.second);
        else
            throw (std::out_of_range("map::at:  key not found"));
    }
    template < class Key, class T, class Compare, class Allocator>
    T& map<Key, T, Compare, Allocator>::operator[](const Key &key)
    {
        node* haveNode = checkNode(_top, key);
        if (haveNode)
            return haveNode->content.second;
        value_type value = ft::make_pair<key_type, mapped_type>(key, mapped_type());
        ++_size;
        return (insertNode(_top, value)->content.second);
    }

	// Modifiers //
	template < class Key, class T, class Compare, class Allocator>
	void map<Key, T, Compare, Allocator>::clear() { erase(begin(), end()); }
	template < class Key, class T, class Compare, class Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::iterator, bool> map<Key, T, Compare, Allocator>::insert(const value_type &value)
	{
		node* haveNode = checkNode(_top, value.first);
		if (haveNode)
			return (ft::pair<iterator, bool>(iterator(haveNode, _lastNode, _comp), false));
		++_size;
		return (ft::pair<iterator, bool>(iterator(insertNode(_top, value), _lastNode, _comp), true));
	}
	// 똑같은게 있으면 안됨 없으면 추가
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::insert(iterator position, const value_type& value)
	{   
		if (position->first > value.first)
		{
			iterator prev(position);
			--prev;
			while (prev != end() && prev->first >= value.first)
			{
				--position;
				--prev;
			}
		}
		else if (position->first < value.first)
		{
			iterator next(position);
			++next;
			while (next != end() && next->first <= value.first)
			{
				++position;
				++next;
			}
		}

		if (position != end() && value.first == position->first)
			return (position);
		++_size;

		return (iterator(insertNode(position.getNode(), value), _lastNode, _comp));
	}
	template < class Key, class T, class Compare, class Allocator>   
	template< class InputIterator >
	void map<Key, T, Compare, Allocator>::insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)		
	{
		while (first != last)
			insert(*first++);
	}
	template < class Key, class T, class Compare, class Allocator>
	void map<Key, T, Compare, Allocator>::erase (iterator position)
	{
		deleteNode(position.getNode(), position->first);
		--_size;
	}
	template < class Key, class T, class Compare, class Allocator>
	void map<Key, T, Compare, Allocator>::erase (iterator first, iterator last)
	{
		while (first != last)
		{
			iterator tmp(first);
			++first;
			erase(tmp);
		}
	}
	template < class Key, class T, class Compare, class Allocator>
	size_t map<Key, T, Compare, Allocator>::erase (const key_type& key)
	{
		size_type ret = deleteNode(_top, key);
		_size -= ret;
		return (ret);
	}
	template < class Key, class T, class Compare, class Allocator>
	void map<Key, T, Compare, Allocator>::swap(map &other)
	{
		ft::swap(_top, other._top);
		ft::swap(_lastNode, other._lastNode);
		ft::swap(_size, other._size);
		ft::swap(_comp, other._comp);
		ft::swap(_allocPair, other._allocPair);
		ft::swap(_allocNode, other._allocNode);
	}

	// Lookup //
	template < class Key, class T, class Compare, class Allocator>
	size_t map<Key, T, Compare, Allocator>::count(const Key &key)
	{
		node* tem = checkNode(_top, key);
		if (tem)
			return (1);
		else
			return (0);        
	}
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::map<Key, T, Compare, Allocator>::find(const Key &key)
	{
		node* tem = checkNode(_top, key);
		if (tem)
			return iterator(tem, _lastNode, _comp);	
		return end();
	}
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::find(const Key &key) const
	{
		node* tmp = checkNode(_top, key);
		if (tmp)
			return iterator(tmp, _lastNode, _comp);
		return end();
	}
	template < class Key, class T, class Compare, class Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::iterator, typename map<Key, T, Compare, Allocator>::iterator>
		map<Key, T, Compare, Allocator>::equal_range(const Key &key)
	{
		iterator it = upper_bound(key);
		if (it != begin())
		{
			--it;
			if (_comp(it->first, key) || _comp(key, it->first))
				++it;
		}
		iterator next(it);
		if (it != end())
			++next;		
		return ft::make_pair<iterator, iterator>(it, next);
	}
	template < class Key, class T, class Compare, class Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::const_iterator, typename map<Key, T, Compare, Allocator>::const_iterator>
		map<Key, T, Compare, Allocator>::equal_range(const Key &key) const
	{
		const_iterator it = upper_bound(key);
		if (it != begin())
		{
			--it;
			if (_comp(it->first, key) || _comp(key, it->first))
				++it;
		}
		const_iterator next(it);
		if (it != end())
			++next;      
		return ft::make_pair<const_iterator, const_iterator>(it, next);
	}
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::lower_bound(const Key &key)
	{
		iterator it = begin();
		for (; it != end(); ++it)
			if (!_comp(it->first, key))
				break;       
		return it;  
	}
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::lower_bound(const Key &key) const
	{
		const_iterator it = begin();

		for (; it != end(); ++it)
			if (!_comp(it->first, key))
				break;
		
		return it;
	}
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::upper_bound(const Key &key)
	{
		iterator it = begin();
		for (; it != end(); ++it)
			if (_comp(key, it->first))
				break;     
		return it;  
	}
	template < class Key, class T, class Compare, class Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::upper_bound(const Key &key) const
	{
		const_iterator it = begin();
		for (; it != end(); ++it)
			if (_comp(key, it->first))
				break;             
		return it;  
	}
}

#endif