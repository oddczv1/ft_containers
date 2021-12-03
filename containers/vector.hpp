#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../iterator/random_access_iterator.hpp"

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	class vector
	{
		public:
			// Member types //
			typedef T												value_type;
			typedef Allocator 										allocator_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t 									difference_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename Allocator::pointer 					pointer;
			typedef typename Allocator::const_pointer				const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			// constructors //
			vector();
			explicit vector(const Allocator &alloc);
			explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator());
			template<typename InputIt>
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr);
			vector(const vector &other);
			// destructors //
			~vector();
			// operator //
			vector &operator=(const vector &other); 
			// assign //
			void assign(size_type count, const T &value);
			template<class InputIterator>
			void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
			// get_allocator //
			allocator_type get_allocator() const;
			// element access //
			reference at(size_type pos);
			const_reference at(size_type pos) const;
			reference operator[](size_type pos);
			const_reference operator[](size_type pos) const;
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			// iterators traits //
			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;	
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			// capacity //
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			void reserve(size_type new_cap);
			size_type capacity() const;
			// modifiers //
			void clear();
			iterator insert(iterator pos, const T &value);
			void insert(iterator pos, size_type count, const T &value);
			template< class InputIterator >
			void insert(iterator pos, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr);
			iterator erase(iterator pos);
			iterator erase(iterator first, iterator last);
			void push_back(const T &value);
			void pop_back();
			void resize(size_type count, T value = T());
			void swap(vector &other);
	
		private:
			allocator_type  _alloc;
			pointer         _first;
			pointer         _last;
			pointer         _count;
			
			// error //
			void sizeError(size_type n)
			{
				if (n >= this->size())
					throw (std::out_of_range("vector::sizeError"));
			}
			void rangeError(pointer pos)
			{
				if (pos < _first || pos >_last)
					throw (std::out_of_range("vector::rangeError"));
			}

	};

	// constructors //
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector() : _alloc(allocator_type()), _first(nullptr), _last(nullptr), _count(nullptr) {}
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(const Allocator &alloc) : _alloc(alloc), _first(nullptr), _last(nullptr), _count(nullptr) {}
	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(size_type count, const T &value, const Allocator &alloc) : _alloc(alloc)
	{
		if (this->max_size() < count)
			throw (std::length_error("constructor"));
		_first = _alloc.allocate(count);
		_last = _first;
		_count = _first + count;
		for (size_type i = 0; i < count; i++)
			_alloc.construct(_last++, value);
	}

	template<typename T, typename Allocator>
	template<typename InputIt>
	vector<T, Allocator>::vector(InputIt first, InputIt last, const Allocator &alloc,
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*) : _alloc(alloc)
	{
		difference_type count = ft::distance(first, last);
		_first = _alloc.allocate(count);
		_last = _first;
		_count = _first + count;
		for (size_t i = 0; i < (size_t)count; i++)
			_alloc.construct(_last++, *first++);
	}


	template<typename T, typename Allocator>
	vector<T, Allocator>::vector(const vector &other)
	{
		size_type count = other.size();
		_alloc = other._alloc;
		_first = _alloc.allocate(count);
		_last = _first;
		_count = _first + count;
		const_iterator first = other.begin();
		for (size_type i = 0; i < count; i++)
			_alloc.construct(_last++, *first++);
	}

	// destructor //
	template<class T, class Allocator>
	vector<T, Allocator>::~vector()
	{
		this->clear();
		_alloc.deallocate(_first, this->capacity());
	}

	// operator //
	template<class T, class Allocator>
	vector<T, Allocator> &vector<T, Allocator>::operator=(const vector &other)
	{
		if (&other == this)
			return (*this);
		this->clear();
		_alloc.deallocate(_first, this->capacity());
		_alloc = other._alloc;
		size_type count = other.size();
		_first = _alloc.allocate(count);
		_last = _first;
		_count = _first + count;
		const_iterator first = other.begin();
		for (size_type i = 0; i < count; i++)
			_alloc.construct(_last++, *first++);
		return (*this);
	}

	// assign //
	template<class T, class Allocator>
	void vector<T, Allocator>::assign(size_type count, const T &value)
	{
		this->clear();
		if (count == 0)
			return ;
		if (this->max_size() < count)
			throw (std::length_error("vector::assign"));
		
		if (this->capacity() >= count)
		{
			_last = _first;
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_last++, value);
		}
		else
		{
			_alloc.deallocate(_first, this->capacity());
			_first = _alloc.allocate(count);
			_last = _first;
			_count = _first + count;
			for (size_type i = 0; i < count; i++)
				_alloc.construct(_last++, value);
		}

	}
	template<class T, class Allocator>
	template<class InputIterator>
	void vector<T, Allocator>::assign(InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
	{
		this->clear();
		difference_type count = ft::distance(first, last);
		if (this->capacity() >= (size_type)count)
		{
			_last = _first;
			for (size_type i = 0; i < (size_type)count; i++)
				_alloc.construct(_last++, *first++);
		}
		else
		{
			_alloc.deallocate(_first, this->capacity());
			_first = _alloc.allocate(count);
			_last = _first;
			_count = _first + count;
			for (long i = 0; i < count; i++)
				_alloc.construct(_last++, *first++);
		}
	}

	// allocator_type //
	template<class T, class Allocator>
	typename vector<T, Allocator>::allocator_type vector<T, Allocator>::get_allocator() const { return (allocator_type()); }


	// element access //
	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) 
	{
		if (pos >= this->size())
			throw (std::out_of_range("vector::sizeError"));
		return (*(_first + pos));
	}
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const
	{
		if (pos >= this->size())
			throw (std::out_of_range("vector::sizeError"));
		return (*(_first + pos));
	}
	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type pos) { return (*(_first + pos)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type pos) const { return (*(_first + pos)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::front() { return (*_first); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const { return (*_first); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::back() { return (*(_last - 1)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const { return (*(_last - 1)); }


	// iterators traits //
	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() { return (iterator(_first)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const { return (const_iterator(_first)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::end() { return (iterator(_last)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const { return (const_iterator(_last)); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin() { return (reverse_iterator(this->end())); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const { return (const_reverse_iterator(this->end())); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend() { return (reverse_iterator(this->begin())); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const { return (const_reverse_iterator(this->begin())); }


	// capacity //
	template<class T, class Allocator>
	bool vector<T, Allocator>::empty() const { return (this->size() == 0 ? true : false); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::size() const { return (this->_last - this->_first); }
	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::max_size() const { return allocator_type().max_size(); }
	template<class T, class Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap)
	{
		if (new_cap > this->max_size())
			throw (std::length_error("vector::reserve"));
		else if (new_cap > this->capacity())
		{
			pointer prev_start = _first;
			size_type prev_size = this->size();
			size_type prev_capacity = this->capacity();		
			_first = _alloc.allocate( new_cap );
			_count = _first + new_cap;
			_last = _first;
			for (size_type i = 0; i < prev_size; i++)
			{
				_alloc.construct(_last++, *prev_start);
				_alloc.destroy(prev_start);
				prev_start++;
			}
			_alloc.deallocate(prev_start - prev_size, prev_capacity);
		}
	}
	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::capacity() const { return (this->_count - this->_first); }


	// modifiers
	template<class T, class Allocator>
	void vector<T, Allocator>::clear()
	{
		size_type tem = this->size();
		for (size_type i = 0; i < tem; i++)
		{
			_last--;
			_alloc.destroy(_last);
		}
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const T &value)
	{
		this->rangeError(&(*pos));
		size_t _len = ft::distance(_first, &(*pos));
		if (size_type(_count - _last) >= this->size() + 1)
		{
			std::memcpy(&(*pos) + 1, &(*pos), sizeof(T) * ft::distance(pos, this->end()));
			_last++;
			_alloc.construct(&(*pos), value);
		}
		else
		{
			int tem_capacity = this->size() > 0 ? this->size() * 2 : 1; 
			this->reserve(tem_capacity);
			pointer _pos = _first + (int)_len;
			std::memcpy(&*_pos + 1, &*_pos, sizeof(T) * ft::distance(_pos, _last));
			_alloc.construct(&*_pos, value);
			_last++;
		}
		return (iterator(_first + _len));
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::insert(iterator pos, size_type count, const T &value)	
	{
		for (size_type i = 0; i < count; i++)
			pos = this->insert(pos, value);
	}

	template<class T, class Allocator>
	template< class InputIterator >
	void vector<T, Allocator>::insert(iterator pos, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
	{
		for (InputIterator i = --last; i >=first; i--)
			pos = this->insert(pos, *i);		
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator pos)
	{
		pointer _pos = &*pos;
		if ( _pos >=_last)
			throw (std::out_of_range("vector::rangeError"));
		_alloc.destroy(_pos);
		std::memcpy(_pos, _pos + 1, sizeof(T) * ft::distance(_pos + 1, _last));
		_last--;
		return (iterator(_pos));		
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last)
	{
		pointer p_first = &*first;
		if ( p_first >=_last || &*last > _last)
			throw (std::out_of_range("vector::rangeError"));
		for (iterator i = first; i != last; i++)
			first = this->erase(first);
		return (iterator(p_first));
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back(const T &value)
	{
		if (_last == _count)
		{
			int tem_count = this->size() > 0 ? this->size() * 2 : 1;
			this->reserve(tem_count);
		}
		_alloc.construct(_last, value);
		_last++;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::pop_back()
	{
		_alloc.destroy(&this->back());
		_last--;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::resize(size_type count, T value)
	{
		if (count > this->max_size())
			throw (std::length_error("vector::resize"));
		else if (count < this->size())
		{
			while (this->size() > count)
			{
				--_last;
				_alloc.destroy(_last);
			}
		}
		else
			this->insert(this->end(), count - this->size(), value);			
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::swap(vector &other)
	{
		if (&other == this)
			return;		
		pointer tem_first = other._first;
		pointer tem_last = other._last;
		pointer tem_count = other._count;
		allocator_type tem_alloc = other._alloc;
		other._first = this->_first;
		other._last = this->_last;
		other._count = this->_count;
		other._alloc = this->_alloc;
		this->_first = tem_first;
		this->_last = tem_last;
		this->_count = tem_count;
		this->_alloc = tem_alloc;
	}

	// operator //
	template< class T, class Allocator >
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) 
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));		
	}

	template< class T, class Allocator >
	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (true);
		return (!ft::equal(lhs.begin(), lhs.end(), rhs.begin()));		
	}

	template< class T, class Allocator >
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));	
	}

	template< class T, class Allocator >
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(rhs < lhs));				
	}

	template< class T, class Allocator >
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (rhs < lhs);	
	}

	template< class T, class Allocator >
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		return (!(lhs < rhs));	
	}
}

#endif