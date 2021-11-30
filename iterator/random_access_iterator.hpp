#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"
# include "util.hpp"

namespace ft
{
    template <typename T>
    class random_access_iterator : ft::iterator<std::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef          T*											                             pointer;
            typedef			 T&											                             reference;

            random_access_iterator(void) : _p(nullptr) {}
			random_access_iterator(pointer p) : _p(p) {}
			random_access_iterator(const random_access_iterator& op) : _p(op._p) {}
            random_access_iterator &operator=(const random_access_iterator& op)
            {
            	if (this == &op)
		    		return (*this);
                this->_p = op._p;
                return (*this);
            }
			virtual ~random_access_iterator() {}

            pointer base() const { return (this->_p); }
            reference operator*(void) const { return (*_p); }
            pointer operator->(void) { return &(this->operator*()); }
            random_access_iterator& operator++(void) { _p++; return (*this); }
            random_access_iterator operator++(int) { random_access_iterator n(*this); operator++(); return (n); }
			random_access_iterator& operator--(void) { _p--; return (*this); }
			random_access_iterator operator--(int) { random_access_iterator n(*this); operator--(); return (n); }
            random_access_iterator operator+(difference_type n) const { return (_p + n); }
            random_access_iterator operator-(difference_type n) const { return (_p - n); }
            random_access_iterator& operator+=(difference_type n) { _p += n; return (*this); }
			random_access_iterator& operator-=(difference_type n) { _p -= n; return (*this); }
			reference operator[](difference_type n) { return (*(operator+(n))); }
			operator random_access_iterator<const T> () const { return (random_access_iterator<const T>(this->_p)); }

		private:
            pointer		_p;
    };

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    	operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() == rhs.base()); }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
        operator==(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { 
        return (lhs.base() == rhs.base()); 
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    	operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() != rhs.base()); }
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
        operator!=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { return (lhs.base() != rhs.base()); }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    	operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() < rhs.base()); }
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
        operator<(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { return (lhs.base() < rhs.base()); }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    	operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() > rhs.base()); }
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
        operator>(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { return (lhs.base() > rhs.base()); }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    	operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() <= rhs.base()); }
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
        operator<=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { return (lhs.base() <= rhs.base()); }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    	operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() >= rhs.base()); }
    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
        operator>=(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { return (lhs.base() >= rhs.base()); }

    template<typename T>
    ft::random_access_iterator<T>
		operator+( typename ft::random_access_iterator<T>::difference_type n, typename ft::random_access_iterator<T>& rai)
    { return (&(*rai) + n); }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
		operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
    { return (lhs.base() - rhs.base()); }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    	operator-(const ft::random_access_iterator<T_L> lhs, const ft::random_access_iterator<T_R> rhs)
    { return (lhs.base() - rhs.base()); }
}

#endif