#ifndef	ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
				typedef T 				value_type;
				typedef Distance		difference_type;
				typedef Pointer			pointer;
				typedef Reference		reference;
				typedef Category		iterator_category;
	};

	struct random_access_iterator_tag {};

	template< typename T >
	class random_access_iterator : iterator<ft::random_access_iterator_tag, T>
	{
		protected:
				typedef T*			pointer;
				pointer				_pointer;
		public:
				random_access_iterator( void ) { _pointer = NULL; }					// default
				random_access_iterator( pointer pointer ) { _pointer = pointer; }	// param
				random_access_iterator( const T& rhs ) { *this = rhs; }				// copy
				~random_access_iterator( void ) {  }								// destruct

				random_access_iterator&		operator=( const random_access_iterator& rhs )	// assignation
				{ this->_pointer = rhs._pointer; return (*this); }

				T&	operator* () {
					return (*_pointer);
				}

				T&	operator++() {
					return (_pointer++);
				}

				random_access_iterator	operator++(int) {
					pointer temp = _pointer;
					_pointer++;
					return (temp);
				}

				bool	operator!=( const random_access_iterator& rhs )
				{ return ( this->_pointer == rhs._pointer ? false : true ); }
				bool	operator==( const T& rhs ) const
				{ return ( *this == rhs ? true : false ); }

	};

}

#endif