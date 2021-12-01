#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > 
	class stack
	{
		public:
			typedef 			Container					container_type;
			typedef typename	Container::value_type		value_type;
			typedef typename	Container::size_type		size_type;
			typedef typename	Container::reference		reference;
			typedef typename	Container::const_reference	const_reference;

			// Member functions//
			explicit stack (const container_type& cont  = container_type()) : _cont(cont) {}
			~stack() {}
            stack& operator=(const stack& other)
            {
				if (this == &other) 
					return(*this);
				this->~stack();
				return (*new(this) stack(other));
            }

			// Element access //
			value_type& top() { return (this->_cont.back()); }
			const value_type& top() const { return (this->_cont.back()); }

			// Capacity //
			bool empty() const { return (this->_cont.empty()); }
			size_type size() const { return (this->_cont.size()); }

			// Modifiers //
			void push (const value_type& val) { this->_cont.push_back(val); }
			void pop() { this->_cont.pop_back(); }

			// Non-member functions //
			friend bool operator==(const stack& lhs, const stack& rhs)  { return (lhs._cont == rhs._cont); }
            friend bool operator!=(const stack& lhs, const stack& rhs)  { return (lhs._cont != rhs._cont); }
            friend bool operator<(const stack& lhs, const stack& rhs)   { return (lhs._cont < rhs._cont); }
            friend bool operator<=(const stack& lhs, const stack& rhs)  { return (lhs._cont <= rhs._cont); }
            friend bool operator>(const stack& lhs, const stack& rhs)   { return (lhs._cont > rhs._cont); }
            friend bool operator>=(const stack& lhs, const stack& rhs)  { return (lhs._cont >= rhs._cont); }

		protected:
			container_type _cont;
	};
}

#endif