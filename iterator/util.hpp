#ifndef UTIL_HPP
# define UTIL_HPP

# include <iostream>
# include <iostream>
# include <memory> //std::allocator
# include <cstddef> //std::size_t, std::ptrdiff_t
# include <functional> //std::less
# include "iterator.hpp"

namespace ft
{
	// enable_if //
    template<bool Bool, class T = void> 
	struct enable_if {};
    template<class T> 
	struct enable_if<true, T> { typedef T type; };

	// is_integral //
    template <typename T>
    struct is_integral { static const bool value = false; };
    template <>
    struct is_integral<bool> { static const bool value = true; };
    template <>
    struct is_integral<wchar_t> { static const bool value = true; };
    template <>
    struct is_integral<char> { static const bool value = true; };
    template <>
    struct is_integral<signed char> { static const bool value = true; };
    template <>
    struct is_integral<unsigned char> { static const bool value = true; };
    template <>
    struct is_integral<short> { static const bool value = true; };
    template <>
    struct is_integral<unsigned short> { static const bool value = true; };
    template <>
    struct is_integral<int> { static const bool value = true; };
    template <>
    struct is_integral<unsigned int> { static const bool value = true; };
    template <>
    struct is_integral<long> { static const bool value = true; };
    template <>
    struct is_integral<unsigned long> { static const bool value = true; };
    template <>
    struct is_integral<long long> { static const bool value = true; };
    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };

	// distance //
    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            first++;
            n++;
        }
        return (n);
    }

	// lexicographical_compare //
	template <typename InputIt1, typename InputIt2, typename Compare = std::less<typename iterator_traits<InputIt1>::value_type>>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp = Compare())
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

    // equal //
    template <typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return false;
		return true;
	}

	// pair //
    template <class T1, class T2>
    struct pair
    {
        public :
            typedef T1 first_type;
            typedef T2 second_type;

            first_type first;
            second_type second;

            pair() : first(), second() {}
			pair( const T1& x, const T2& y ) : first(x), second(y) {}
			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}

            pair& operator=(const pair& other)
            {
                if (*this == other )
                    return (*this);
                this->first = other.first;
                this->second = other.second;
                return (*this);
            }
    };
    
    template <class T1, class T2>
    bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }
    template <class T1, class T2>
    bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (lhs.first != rhs.first || lhs.second != rhs.second);
    }
    template <class T1, class T2>
    bool operator< (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (lhs.first < rhs.first || ((rhs.first == lhs.first) && lhs.second < rhs.second));
    }
    template <class T1, class T2>
    bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (!(lhs < rhs));
    } 
    template <class T1, class T2>
    bool operator> (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
        return (lhs.first > rhs.first || ((rhs.first == lhs.first) && lhs.second > rhs.second));
    }
    template <class T1, class T2>
    bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
    {
	    return (!(rhs > lhs));
    }

	//	make_pair //
    template <class T1, class T2>
    ft::pair<T1,T2> make_pair(T1 x, T2 y)
    {
        return (ft::pair<T1, T2>(x, y));
    }

    // swap //
    template <typename U>
    void swap(U& a, U& b)
    {
        U tmp = a;
        a = b;
        b = tmp;
    }
}

# endif


