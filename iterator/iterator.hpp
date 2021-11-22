#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iterator>

namespace ft
{
    // iterator_traits //
    template <class Iterator> 
    struct iterator_traits
    {
        typedef typename Iterator::difference_type       difference_type;
        typedef typename Iterator::value_type            value_type;
        typedef typename Iterator::pointer               pointer;
        typedef typename Iterator::reference             reference;
        typedef typename Iterator::iterator_category     iterator_category;
    };
    template <class T> 
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
    template <class T> 
    class iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    // iterator //
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator
    {
        public:
            typedef T           value_type;
            typedef Distance    difference_type;
            typedef Pointer     pointer;
            typedef Reference   reference;
            typedef Category    iterator_category;
    };

    // reverse_iterator //
    template <class Iterator>
    class reverse_iterator
    {
        public:
            typedef			 Iterator											iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;                    
            typedef typename ft::iterator_traits<Iterator>::value_type			value_type;         
            typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;           
            typedef typename ft::iterator_traits<Iterator>::pointer				pointer;           
            typedef typename ft::iterator_traits<Iterator>::reference			reference;
            
            reverse_iterator() : _p() {}
            explicit reverse_iterator( iterator_type x ) :_p(x) {}
            template <class U>
            reverse_iterator (const reverse_iterator<U>& other ) : _p(other.base()) {}
            virtual ~reverse_iterator() {}

            template <class U>
            reverse_iterator& operator=( const reverse_iterator<U>& other ) {this->_p =  other.base(); return (*this); }

			iterator_type base() const { return (_p); }
   
            reverse_iterator& operator++() { --_p; return (*this); }
            reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return (tmp); }
            reverse_iterator& operator+=(difference_type n) { _p -= n; return (*this); }
            reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_p - n)); }
            reverse_iterator& operator--() { ++_p; return (*this); }
            reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return (tmp); }
            reverse_iterator& operator-=(difference_type n) { _p += n; return (*this); }
            reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_p + n)); }

			reference operator*() const { iterator_type tmp = _p; return (*(--tmp)); }
            pointer operator->() const { return &(operator*()); }
            reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

        private:
            iterator_type     _p;
    };

    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator_L, typename Iterator_R>
    bool operator==(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }

    template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
    template<typename Iterator_L, typename Iterator_R>
    bool operator!=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }

    template <class Iterator>
    bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
    template<typename Iterator_L, typename Iterator_R>
    bool operator< (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }

    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }
    template<typename Iterator_L, typename Iterator_R>
    bool operator<=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }

    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
    template<typename Iterator_L, typename Iterator_R>
    bool operator>(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }

    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }
    template<typename Iterator_L, typename Iterator_R>
    bool operator>=(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

    template< class Iter >
    reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) { return (it + n); }

    template<typename Iterator_L, typename Iterator_R>
    ptrdiff_t operator-(const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs) { return (rhs.base() - lhs.base()); }
}

#endif