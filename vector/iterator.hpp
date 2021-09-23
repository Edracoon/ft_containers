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
				pointer	_pointer;
		public:
				random_access_iterator( void ) { _pointer = NULL; }					// default
				random_access_iterator( pointer pointer ) { _pointer = pointer; }	// param
				template <class Iter>
				explicit random_access_iterator (const random_access_iterator<Iter> & rhs)	// copy
					: _pointer(rhs.base()) { }
				~random_access_iterator( void ) {  }								// destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pointer base(void) const
				{
					return this->_pointer;
				}

				// assignation
				template <class Iterator>
				random_access_iterator& operator= (const random_access_iterator<Iterator>& rhs) {
					this->_pointer = rhs.base();
					return (*this);
				}

				// *
				reference operator* () {
					return (*_pointer);
				}
				reference operator* () const {
					return (*_pointer);
				}

				// []
				reference operator[] (difference_type n) {
					return (*(_pointer + n));
				}
				reference operator[] (difference_type n) const {
					return (*(_pointer + n));
				}

				// ->
				pointer operator->() const {
					return &(operator*());
				}
				// +=
				random_access_iterator operator+=(difference_type n) {
					return (this->_pointer = this->_pointer + n);
				}
				// -=
				random_access_iterator operator-=(difference_type n) {
					return (this->_pointer = this->_pointer - n);
				}

				// ++
				random_access_iterator&	operator++() {
					_pointer++;
					return (*this);
				}
				random_access_iterator	operator++(int) {
					random_access_iterator temp(*this);
					_pointer++;
					return (temp);
				}

				// --
				random_access_iterator&	operator--() {
					_pointer--;
					return (*this);
				}
				random_access_iterator	operator--(int) {
					random_access_iterator temp(*this);
					_pointer--;
					return (temp);
				}

				// -
				difference_type operator-(const random_access_iterator & rhs) const {
					return (_pointer - rhs._pointer);
				}
				random_access_iterator operator-(difference_type n) const {
					return random_access_iterator(_pointer - n);
				}

				// +
				difference_type operator+(const random_access_iterator & rhs) const {
					return (_pointer + rhs._pointer);
				}
				random_access_iterator operator+(difference_type n) const {
					return random_access_iterator(_pointer + n);
				}

				// Comparison operators in class
				bool	operator!=( const random_access_iterator& rhs ) {
					return ( this->_pointer != rhs._pointer);
				}
				bool	operator==( const random_access_iterator& rhs ) {
					return ( this->_pointer == rhs._pointer);
				}

	};

	template <class Iterator>
	typename random_access_iterator<Iterator>::difference_type operator- ( random_access_iterator<Iterator>& lhs, 
											const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
	}
	template <class Iterator>
	random_access_iterator<Iterator> operator+ ( typename random_access_iterator<Iterator>::difference_type n, 
											const random_access_iterator<Iterator>& it) {
		return (it + n);
	}

	// Comparison operators out of class
	template <class Iterator1, class Iterator2>
	bool operator== (const random_access_iterator<Iterator1>& lhs,	
				const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const random_access_iterator<Iterator1>& lhs,
					const random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator>
	bool operator<  (const random_access_iterator<Iterator>& lhs,
					const random_access_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iterator>
	bool operator<= (const random_access_iterator<Iterator>& lhs,
					const random_access_iterator<Iterator>& rhs){
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator>
	bool operator>  (const random_access_iterator<Iterator>& lhs,
					const random_access_iterator<Iterator>& rhs){
		return (lhs.base() > rhs.base());
	}
	template <class Iterator>
	bool operator>= (const random_access_iterator<Iterator>& lhs,
					const random_access_iterator<Iterator>& rhs){
		return (lhs.base() >= rhs.base());
	}

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