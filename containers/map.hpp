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
                ft::pair<const Key, T>  value;
                int height;
                node* left;
                node* right;
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
			typedef typename ft::bidirectional_iterator<value_type, Compare, node>						    iterator;
			typedef typename ft::bidirectional_iterator<const value_type, Compare, node>				        const_iterator;
			// typedef ft::reverse_iterator<iterator>														reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>												const_reverse_iterator;
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
			// template< class InputIt >
			// map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr);
			// map(const map& other);
			// ~map();
			map &operator=( const map &other );
			// // Element access //
			T& at(const Key& key);
			const T& at(const Key& key) const;
			T& operator[](const Key &key);
			// Iterators //
            // iterator begin()                        { return iterator(_lastNode->right, _lastNode, _comp); }
            // const_iterator begin() const            { return const_iterator(_lastNode->right, _lastNode, _comp); }
            // iterator end()                          { return iterator(_lastNode, _lastNode, _comp); }
            // const_iterator end() const              { return const_iterator(_lastNode, _lastNode, _comp); }
            // reverse_iterator rbegin()               { return reverse_iterator(_lastNode->left, _lastNode, _comp); }
            // const_reverse_iterator rbegin() const   { return const_reverse_iterator(_lastNode->left, _lastNode, _comp); }
            // reverse_iterator rend()                 { return reverse_iterator(_lastNode, _lastNode, _comp); }
            // const_reverse_iterator rend() const     { return const_reverse_iterator(_lastNode, _lastNode, _comp); }
			// Capacity //
            // bool empty() const						{ return (_size == 0); }
            size_t size() const						{ return (_size); }
            // size_t max_size() const 				{ return (_allocNode.max_size()); }
			// Modifiers //
			// void clear();
			ft::pair<iterator, bool> insert(const value_type &value);
			// iterator insert(iterator position, const value_type& value);
			// template< class InputIterator >
			// void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
            // void erase (iterator position);
            // void erase (iterator first, iterator last);
            // size_type erase (const key_type& key);
			void swap(map &other);
			// // Lookup //
			// size_type count(const Key &key);
			// iterator find(const Key &key);
			// const_iterator find(const Key &key) const;
			// ft::pair<iterator,iterator> equal_range(const Key &key);
			// ft::pair<const_iterator,const_iterator> equal_range(const Key &key) const;
			// iterator lower_bound(const Key &key);
			// const_iterator lower_bound(const Key &key) const;
			// iterator upper_bound(const Key &key);
			// const_iterator upper_bound(const Key &key) const;
			// Observers //
            // key_compare key_comp() const        { return _comp; }
            // value_compare value_comp() const    { return value_compare(_comp); }

		private:
            node*                   _top;
			node*					_tem;
			node*					_newNode;
			node*					_target;
            size_type               _size;
            allocator_type          _allocPair;
            key_compare             _comp;
            std::allocator<node>     _allocNode;

            void insertNode(node* node, const value_type& value)
            {
                _top = insert_node(node, value);
            }

            void deleteNode(const value_type& value)
			{
                _top = delete_node(_top, value);
            }

            int max(int a, int b) {
                if (a > b)
                    return a;
                return b;
            }

            int height(node* node) {
                if (node == NULL)
                    return 0;
                return node->height;
            }

            node* createNode(const value_type& value)
            {
                node* newNode = _allocNode.allocate(1);
                _allocPair.construct(&newNode->value, value);
                newNode->height = 1;
                newNode->left = nullptr;
                newNode->right = nullptr;
                return newNode;
            }

            node* insert_node(node* node, const value_type& value) {
                if (!node)
				{
					_newNode = createNode(value);
					return _newNode;
				}
                if  (node->value.first > value.first)
                    node->left = insert_node(node->left,  value);
                else if (node->value.first < value.first)
                    node->right = insert_node(node->right, value);
                node->height = max(height(node->left), height(node->right)) + 1;
                return balance(node);
            }

            int getDifference(node* node) {
                if (!node) 
					return 0;
                return (height(node->left) - height(node->right));
            }

            node* rotate_right(node* node)
            {
                _tem = node->left;
                node->left = _tem->right;
                _tem->right = node;
                node->height = max(height(node->left), height(node->right)) + 1;
                _tem->height = max(height(_tem->left), height(_tem->right)) + 1;
                return _tem;
            }

            node* rotate_left(node* node)
            {
                _tem = node->right;
                node->right = _tem->left;
                _tem->left = node;
                node->height = max(height(node->left), height(node->right)) + 1;
                _tem->height = max(height(_tem->left), height(_tem->right)) + 1;
                return _tem;
            }

            node* balance(node* node)
            {
                if (getDifference(node) > 1)   //노드 n의 왼쪽 서브트리가 높아서 불균형 발생
                {
                    if (getDifference(node->left) < 0) // 노드 n의 왼쪽 자식의 오른쪽서브트리가 높은 경우
                        node->left = rotate_left(node->left); //LR-회전
                    node = rotate_right(node); //LL-회전
                }
                else if (getDifference(node) < -1) //노드 n의 오른쪽 서브트리가 높아서 불균형 발생
                {
                    if (getDifference(node->right) > 0)  //노드 n의 오른쪽자식의 왼쪽 서브트리가 높은 경우
                        node->right = rotate_right(node->right); //RL-회전
                    node = rotate_left(node); //RR-회전
                }
                return node;
            }

            node* delete_node(node* node, const value_type& value)
            {
                if (!node)
                    return nullptr;
                if (node->value.first > value.first) // 왼쪽 자식으로 이동
                    node->left = delete_node(node->left, value.first);
                else if (node->value.first < value.first) // 오른쪽 자식으로 이동
                    node->right = delete_node(node->right, value.first);
                else  // 삭제할 노드 발견
                {
                    if (!node->right) // case 1, 0
                        return node->left;
                    if (!node->left)  // case 0 , 1
                        return node->right;
                    _target = node;    // case 1  1
                    node = minimum(_target->right); //중위 후속자를 찾아서 n이 참조하게 함
                    node->right = del_min(_target->right);
                    node->left  = _target->left;
					deallocateNode(node* _target);
                }
                node->height = max(height(node->left), height(node->right)) + 1;
                return balance(node);
            }

			//key값이 있는지 체크
            node* checkNode(node* moveNode, const key_type& key)
            {
                if (!moveNode)
                    return (nullptr);
                if (moveNode->value.first == key)
                    return (moveNode);
                if (moveNode->value.first > key && moveNode->left )
                    return checkNode(moveNode->left, key);
                else if (moveNode->value.first < key && moveNode->right )
                    return checkNode(moveNode->right, key);
                return (nullptr);
            }

            node* minimum(node* node)
            {
                if (!node->left)
                    return node;
                return minimum(node->left);
            }

            node* maximum(node* node)
            {
                if (!node->right)
                    return node;
                return minimum(node->right);
            }

            node* del_min(node* node)
            {
                if (!node->left)
                    return node->right;
                node->left = del_min(node->left);
                node->height = max(height(node->left), height(node->right)) + 1;
                return balance(node);
            }

			void deallocateNode(node* node)
			{
                _allocPair.destroy(&node->value);
                _allocNode.deallocate(node, 1);				
			}

            // void delete_min()  //최소값삭제는 다시 만들기
            // {
            //     if (!_top)
            //         return nullptr;
            //     _top = del_min(_top);
            // }

            // node* min() //최솟값 찾기
            // {
            //     if (!_top)
            //         return nullptr;
            //     return minimum(_top);
            // }

	};

    // Member functions //
    template < class Key, class T, class Compare, class Allocator>
	map<Key, T, Compare, Allocator>::map(const Compare &comp, const Allocator &alloc) : _size(0), _allocPair(alloc), _comp(comp)
    {
        _top = createNode(value_type());
    }

    // template < class Key, class T, class Compare, class Allocator>
    // template< class InputIt >
	// map<Key, T, Compare, Allocator>::map(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
    // : _size(0), _allocPair(alloc), _comp(comp)
    // {
    //     _lastNode = createNode(value_type());
    //     _top = _lastNode;
    //     _lastNode->left = _lastNode;
    //     _lastNode->right = _lastNode;
    //     for (; first != last; ++first)
    //         insert(*first);
    // }

    // template < class Key, class T, class Compare, class Allocator>
	// map<Key, T, Compare, Allocator>::map(const map& other)
	// : _size(0), _allocPair(other._allocPair), _comp(other._comp), _allocNode(other._allocNode)
    // {
    //     _lastNode = createNode(ft::pair<const key_type, mapped_type>());
    //     _top = _lastNode;
    //     _lastNode->left = _lastNode;
    //     _lastNode->right = _lastNode;
    //     for (const_iterator it = other.begin(); it != other.end(); ++it)
    //         insert(*it);
    // }

	// clear 구현해야함
    // template < class Key, class T, class Compare, class Allocator>
	// map<Key, T, Compare, Allocator>::~map(){ clear(); deallocateNode(_lastNode); }

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
            return (haveNode->value.second);
        else
            throw (std::out_of_range("map::at:  key not found"));
    }

    template < class Key, class T, class Compare, class Allocator>
    const T& map<Key, T, Compare, Allocator>::at(const Key& key) const
    {
        node* haveNode = checkNode(_top, key);
        if (haveNode)
            return (haveNode->value.second);
        else
            throw (std::out_of_range("map::at:  key not found"));
    }

    template < class Key, class T, class Compare, class Allocator>
    T& map<Key, T, Compare, Allocator>::operator[](const Key &key)
    {
        node* haveNode = checkNode(_top, key);
        if (haveNode)
            return haveNode->value.second;
        value_type value = ft::make_pair<key_type, mapped_type>(key, mapped_type());
		insertNode(_top, value);
        ++_size;
        return (_newNode->value.second);
    }

	// Modifiers //
	// template < class Key, class T, class Compare, class Allocator>
	// void map<Key, T, Compare, Allocator>::clear() { erase(begin(), end()); }
	
	template < class Key, class T, class Compare, class Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::iterator, bool> map<Key, T, Compare, Allocator>::insert(const value_type &value)
	{
		node* haveNode = checkNode(_top, value.first);
		if (haveNode)
			return (ft::pair<iterator, bool>(iterator(haveNode, _top,_comp), false));
		insertNode(_top, value);
		++_size;
		return (ft::pair<iterator, bool>(iterator(_newNode, _top,_comp), true));
	}

	// 똑같은게 있으면 안됨 없으면 추가
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::insert(iterator position, const value_type& value)
	// {
	// 	if (position->first > value.first)
	// 	{
	// 		iterator prev(position);
	// 		--prev;
	// 		while (prev != end() && prev->first >= value.first)
	// 		{
	// 			--position;
	// 			--prev;
	// 		}
	// 	}
	// 	else if (position->first < value.first)
	// 	{
	// 		iterator next(position);
	// 		++next;
	// 		while (next != end() && next->first <= value.first)
	// 		{
	// 			++position;
	// 			++next;
	// 		}
	// 	}

	// 	if (position != end() && value.first == position->first)
	// 		return (position);
	// 	++_size;

	// 	return (iterator(insertNode(position.getNode(), value), _lastNode, _comp));
	// }

	// template < class Key, class T, class Compare, class Allocator>
	// template< class InputIterator >
	// void map<Key, T, Compare, Allocator>::insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
	// {
	// 	while (first != last)
	// 		insert(*first++);
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// void map<Key, T, Compare, Allocator>::erase (iterator position)
	// {
	// 	deleteNode(position.getNode(), position->first);
	// 	--_size;
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// void map<Key, T, Compare, Allocator>::erase (iterator first, iterator last)
	// {
	// 	while (first != last)
	// 	{
	// 		iterator tmp(first);
	// 		++first;
	// 		erase(tmp);
	// 	}
	// }

	// template < class Key, class T, class Compare, class Allocator>
	// size_t map<Key, T, Compare, Allocator>::erase (const key_type& key)
	// {
	// 	size_type ret = deleteNode(_top, key);
	// 	_size -= ret;
	// 	return (ret);
	// }

	template < class Key, class T, class Compare, class Allocator>
	void map<Key, T, Compare, Allocator>::swap(map &other)
	{
		ft::swap(_top, other._top);
		ft::swap(_size, other._size);
		ft::swap(_comp, other._comp);
		ft::swap(_allocPair, other._allocPair);
		ft::swap(_allocNode, other._allocNode);
	}

	// Lookup //
	// template < class Key, class T, class Compare, class Allocator>
	// size_t map<Key, T, Compare, Allocator>::count(const Key &key)
	// {
	// 	node* tem = checkNode(_top, key);
	// 	if (tem)
	// 		return (1);
	// 	else
	// 		return (0);
	// }
	
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::map<Key, T, Compare, Allocator>::find(const Key &key)
	// {
	// 	node* tem = checkNode(_top, key);
	// 	if (tem)
	// 		return iterator(tem, _lastNode, _comp);
	// 	return end();
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::find(const Key &key) const
	// {
	// 	node* tmp = checkNode(_top, key);
	// 	if (tmp)
	// 		return iterator(tmp, _lastNode, _comp);
	// 	return end();
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// ft::pair<typename map<Key, T, Compare, Allocator>::iterator, typename map<Key, T, Compare, Allocator>::iterator>
	// 	map<Key, T, Compare, Allocator>::equal_range(const Key &key)
	// {
	// 	iterator it = upper_bound(key);
	// 	if (it != begin())
	// 	{
	// 		--it;
	// 		if (_comp(it->first, key) || _comp(key, it->first))
	// 			++it;
	// 	}
	// 	iterator next(it);
	// 	if (it != end())
	// 		++next;
	// 	return ft::make_pair<iterator, iterator>(it, next);
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// ft::pair<typename map<Key, T, Compare, Allocator>::const_iterator, typename map<Key, T, Compare, Allocator>::const_iterator>
	// 	map<Key, T, Compare, Allocator>::equal_range(const Key &key) const
	// {
	// 	const_iterator it = upper_bound(key);
	// 	if (it != begin())
	// 	{
	// 		--it;
	// 		if (_comp(it->first, key) || _comp(key, it->first))
	// 			++it;
	// 	}
	// 	const_iterator next(it);
	// 	if (it != end())
	// 		++next;
	// 	return ft::make_pair<const_iterator, const_iterator>(it, next);
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::lower_bound(const Key &key)
	// {
	// 	iterator it = begin();
	// 	for (; it != end(); ++it)
	// 		if (!_comp(it->first, key))
	// 			break;
	// 	return it;
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::lower_bound(const Key &key) const
	// {
	// 	const_iterator it = begin();

	// 	for (; it != end(); ++it)
	// 		if (!_comp(it->first, key))
	// 			break;

	// 	return it;
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::upper_bound(const Key &key)
	// {
	// 	iterator it = begin();
	// 	for (; it != end(); ++it)
	// 		if (_comp(key, it->first))
	// 			break;
	// 	return it;
	// }
	// template < class Key, class T, class Compare, class Allocator>
	// typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::upper_bound(const Key &key) const
	// {
	// 	const_iterator it = begin();
	// 	for (; it != end(); ++it)
	// 		if (_comp(key, it->first))
	// 			break;
	// 	return it;
	// }
}

#endif