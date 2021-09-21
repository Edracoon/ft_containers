#ifndef	ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator 
	{
		typedef iterator_traits<T> it;

		public:
				typedef typename it::value_type				value_type;
				typedef typename it::pointer				pointer;
				typedef typename it::reference				reference;
				typedef typename it::difference_type		difference_type;
				typedef typename it::iterator_category		iterator_category;
		protected:
				pointer																				_pointer;
		public:
				random_access_iterator( void ) { _pointer = NULL; }					// default
				random_access_iterator( pointer pointer ) { _pointer = pointer; }	// param
				random_access_iterator( const random_access_iterator & rhs ) { _pointer = rhs._pointer; }	// copy
				~random_access_iterator( void ) {  }								// destruct

				pointer base(void)
				{
					return this->_pointer;
				}


				random_access_iterator&		operator=( const random_access_iterator& rhs )	// assignation
				{ this->_pointer = rhs._pointer; return (*this); }

				reference operator* () {
					return (*_pointer);
				}

				reference operator* () const {
					return (*_pointer);
				}

				random_access_iterator	operator++() {
					return random_access_iterator(_pointer++);
				}

				random_access_iterator	operator++(int) {
					pointer temp = _pointer;
					_pointer++;
					return random_access_iterator(temp);
				}

				difference_type operator-(const random_access_iterator & rhs) {
					return (_pointer - rhs._pointer);
				}

				bool	operator!=( const random_access_iterator& rhs )
				{ return ( this->_pointer == rhs._pointer ? false : true ); }
				bool	operator==( const T& rhs ) const
				{ return ( *this == rhs ? true : false ); }

	};
	template< typename T >
	class reverse_iterator
	{
		protected:
				typedef T*			pointer;
				pointer				_pointer;
		public:
				reverse_iterator( void ) { _pointer = NULL; }					// default
				reverse_iterator( pointer pointer ) { _pointer = pointer; }	// param
				reverse_iterator( const T& rhs ) { *this = rhs; }				// copy
				~reverse_iterator( void ) {  }								// destruct

				reverse_iterator&		operator=( const reverse_iterator& rhs )	// assignation
				{ this->_pointer = rhs._pointer; return (*this); }

				T&	operator* () {
					return (*_pointer);
				}

				reverse_iterator	operator++() {
					return (_pointer--);
				}

				reverse_iterator	operator++(int) {
					pointer temp = _pointer;
					_pointer--;
					return (temp);
				}

				bool	operator!=( const reverse_iterator& rhs )
				{ return ( this->_pointer == rhs._pointer ? false : true ); }
				bool	operator==( const T& rhs ) const
				{ return ( *this == rhs ? true : false ); }

	};

}
#endif