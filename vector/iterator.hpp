#ifndef	ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include "iterator_traits.hpp"

namespace ft
{

	// =======================================
	// ======= RANDOM_ACCESS_ITERATOR ========
	// =======================================
	template< typename T >
	class random_access_iterator
	{
		private:
				// recup traits macro
				typedef iterator_traits<T> it;
		public:
				// typedef macro
				typedef typename it::value_type				value_type;
				typedef typename it::pointer				pointer;
				typedef typename it::reference				reference;
				typedef typename it::difference_type		difference_type;
				typedef typename it::iterator_category		iterator_category;
		protected:
				pointer	_pointer;
		public:
				random_access_iterator( void ) { _pointer = NULL; }											 // default
				random_access_iterator( pointer pointer ) { _pointer = pointer; }							 // param
				template <class Iter>
				random_access_iterator (const random_access_iterator<Iter> & rhs) : _pointer(rhs.base()) { } // copy
				~random_access_iterator( void ) {  }														 // destruct

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
	};

	// OUT OF CLASS OPERATORS
	template <class Iterator>
	typename ft::random_access_iterator<Iterator>::difference_type operator- ( ft::random_access_iterator<Iterator>& lhs, 
											const ft::random_access_iterator<Iterator>& rhs) {
		return (lhs.base() - rhs.base());
	}
	template <class Iterator>
	ft::random_access_iterator<Iterator> operator+ ( typename ft::random_access_iterator<Iterator>::difference_type n, 
											const ft::random_access_iterator<Iterator>& it) {
		return (it + n);
	}

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::random_access_iterator<Iterator1>& lhs,	
				const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<  (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator<= (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs){
		return (lhs.base() <= rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>  (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs){
		return (lhs.base() > rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator>= (const ft::random_access_iterator<Iterator1>& lhs,
					const ft::random_access_iterator<Iterator2>& rhs){
		return (lhs.base() >= rhs.base());
	}
// ====================================================================================

	// =================================
	// ======= REVERSE_ITERATOR ========
	// =================================
	template< class Iterator >
	class reverse_iterator
	{
		private:
				// recup traits macro
 		public:
				// typedef macro
				typedef Iterator								iterator_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::iterator_category	iterator_category;

		protected:
				iterator_type		_current;
		public:
				reverse_iterator() { _it = NULL; }												// default
				explicit reverse_iterator (iterator_type current) : _current(current) { }					// param
				template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it._current) { }	// copy
				~reverse_iterator( void ) {  }

				pointer base() {
					return (this->_pointer);
				}

				// =
				// reverse_iterator&		operator=( const reverse_iterator& rhs ) {
				// //	this->_pointer = rhs._pointer;
				// 	return (*this);
				// }

				// *
				// pointer	operator* () {
				// 	return (*_pointer);
				// }

				// ++
				// reverse_iterator	operator++() {
				// 	return (_pointer--);
				// }
				// reverse_iterator	operator++(int) {
				// 	reverse_iterator temp(*this);
				// 	_pointer--;
				// 	return (temp);
				// }
	};


}
#endif