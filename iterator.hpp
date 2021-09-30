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
	template <class Iterator1, class Iterator2>
	typename ft::random_access_iterator<Iterator1>::difference_type operator- ( const ft::random_access_iterator<Iterator1>& lhs, 
											const ft::random_access_iterator<Iterator2>& rhs) {
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


	// =================================
	// ==== BIDIRECTIONAL ITERATOR =====
	// =================================
	template< typename T >
	class bidirectional_iterator
	{
		private:
				// recup traits macro
				typedef iterator_traits<T> it;
		public:
				// typedef macro
				typedef typename it::value_type							value_type;
				typedef typename it::pointer							pointer;
				typedef typename it::reference							reference;
				typedef typename it::difference_type					difference_type;
				typedef typename std::bidirectional_iterator_tag		iterator_category;
		protected:
				pointer	_pointer;
		public:
				bidirectional_iterator( void ) { _pointer = NULL; }											 // default
				bidirectional_iterator( pointer pointer ) { _pointer = pointer; }							 // param
				template <class Iter>
				bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _pointer(rhs.base()) { } // copy
				~bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pointer base(void) const
				{
					return this->_pointer;
				}

				// assignation
				template <class Iterator>
				bidirectional_iterator& operator= (const bidirectional_iterator<Iterator>& rhs) {
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

				// ->
				pointer operator->() const {
					return &(operator*());
				}

				// ++
				bidirectional_iterator&	operator++() {
					_pointer++;
					return (*this);
				}
				bidirectional_iterator	operator++(int) {
					bidirectional_iterator temp(*this);
					_pointer++;
					return (temp);
				}

				// --
				bidirectional_iterator&	operator--() {
					_pointer--;
					return (*this);
				}
				bidirectional_iterator	operator--(int) {
					bidirectional_iterator temp(*this);
					_pointer--;
					return (temp);
				}
	};

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::bidirectional_iterator<Iterator1>& lhs,	
				const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::bidirectional_iterator<Iterator1>& lhs,
					const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	// =================================
	// ======= REVERSE_ITERATOR ========
	// =================================
	template< class Iterator >
	class reverse_iterator
	{
 		public:
				// typedef macro
				typedef Iterator								iterator_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::iterator_category	iterator_category;

		protected:
				iterator_type		_base_it;
		public:
				reverse_iterator() { _base_it = NULL; }													// default
				explicit reverse_iterator (iterator_type it) : _base_it(it) { }				// param
				template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base_it(rev_it.base()) { }	// copy
				~reverse_iterator( void ) {  }

				iterator_type base() const {
					return (this->_base_it);
				}

				reference operator*() const {
					iterator_type	cpy = _base_it;
					return (*(--cpy));
				}
				pointer operator->() const {
					return &(operator*());
				}

				// ++ et --
				reverse_iterator& operator++() {
					--_base_it;
					return (*this);
				}
				reverse_iterator operator++(int) {
					reverse_iterator temp = *this;
					++(*this);
					return temp;
				}
				reverse_iterator& operator--() {
					++_base_it;
					return (*this);
				}
				reverse_iterator operator--(int) {
					reverse_iterator temp = *this;
					--(*this);
					return temp;
				}

				// + et -
				reverse_iterator operator+ (difference_type n) const {
					return reverse_iterator(_base_it - n);
				}
				reverse_iterator operator- (difference_type n) const {
					return reverse_iterator(_base_it + n);
				}

				// -= et +=
				reverse_iterator& operator-= (difference_type n) {
					this->_base_it += n;
					return (*this);
				}
				reverse_iterator& operator+= (difference_type n) {
					this->_base_it -= n;
					return (*this);
				}

				// []
				reference operator[] (difference_type n) const {
					return (base()[-n-1]);
				}
	};

	// OUT OF CLASS OPERATORS
	template <class Iterator>
	reverse_iterator<Iterator> operator+ ( typename reverse_iterator<Iterator>::difference_type n,
												const reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n);
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator- (
					const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
	}

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<  (const reverse_iterator<Iterator1>& lhs,
 						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>  (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const reverse_iterator<Iterator1>& lhs,
						const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	}
}

#endif