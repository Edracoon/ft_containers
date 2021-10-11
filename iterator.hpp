/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:04 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/11 11:15:06 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>
# include "reverse_iterator.hpp"
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
				//typedef iterator_traits<T> it;
		public:
				// typedef macro
				typedef T											value_type;
				typedef T*											pointer;
				typedef T&											reference;
				typedef size_t										difference_type;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef typename value_type::pair					pair;
				typedef	pair*										pair_pointer;
		protected:
				pointer	_pointer;
				pointer	_last;
		public:
				bidirectional_iterator( void ) { _pointer = NULL; }											 // default
				bidirectional_iterator( pointer Pointer, pointer Last = NULL )
				{
					_pointer	= Pointer;
					_last		= Last;
				}
				template <class Iter>
				bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _pointer(rhs.base_node()) { } // copy
				~bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pair_pointer base(void) const
				{
					return pair_pointer(&(_pointer->value));
				}
				pointer base_node(void) const
				{
					return pointer(&(this->_pointer));
				}

				// assignation
				template <class Iterator>
				bidirectional_iterator& operator= (const bidirectional_iterator<Iterator>& rhs) {
					this->_pointer = rhs.base();
					return (*this);
				}

				// *
				pair operator* () const {
					return (_pointer->value);
				}

				// ->
				pair* operator->() const {
					return &(_pointer->value);
				}

				// ++
				bidirectional_iterator&	operator++() {
					// if (!_pointer)
					// 	return *this;
					// std::cout << "coucou non const : " << _pointer->value.first << " - " <<  _pointer->value.second << std::endl;
					if (_pointer->right != NULL)
					{
						_pointer = _pointer->right;
						while (_pointer->left != NULL)
							_pointer = _pointer->left;
					}
					else {
						while (_pointer->parent != NULL && _pointer == _pointer->parent->right)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				bidirectional_iterator	operator++(int) {
					bidirectional_iterator	temp = *this;
					operator++();
					// std::cout << "coucou non const : " << (*temp).first << " - " << (*temp).second << std::endl;
					return temp;
				}

				// --
				bidirectional_iterator&	operator--() {
					if (_pointer == NULL)
					{
						_pointer = _last;
						return *this;
					}
					if (_pointer->left != NULL)
					{
						_pointer = _pointer->left;
						while (_pointer->right != NULL)
							_pointer = _pointer->right;
					}
					else {
						while (_pointer->parent != NULL && _pointer == _pointer->parent->left)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				bidirectional_iterator	operator--(int) {
					bidirectional_iterator	temp = *this;
					operator--();
					return temp;
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
	
	// =======================================
	// ==== CONST BIDIRECTIONAL ITERATOR =====
	// =======================================
	template< typename T >
	class const_bidirectional_iterator
	{
		private:
				// recup traits macro
				//typedef iterator_traits<T> it;
		public:
				// typedef macro
				typedef const T										value_type;
				typedef value_type*									pointer;
				typedef value_type&									reference;
				typedef size_t										difference_type;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef const typename value_type::pair				pair;
				typedef	pair*										pair_pointer;
		protected:
				pointer	_pointer;
				pointer	_last;
		public:
				const_bidirectional_iterator( void ) { _pointer = NULL; }											 // default
				const_bidirectional_iterator( pointer Pointer, pointer Last = NULL )
				{
					_pointer	= Pointer;
					_last		= Last;
				}
				template <class Iter>
				const_bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _pointer(rhs.base_node()) { } // copy
				~const_bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pair_pointer base(void) const
				{
					return pair_pointer(&(_pointer->value));
				}
				pointer base_node(void) const
				{
					return pointer(&(this->_pointer));
				}

				// assignation
				template <class Iterator>
				const_bidirectional_iterator& operator= (const const_bidirectional_iterator<Iterator>& rhs) {
					this->_pointer = rhs.base();
					return (*this);
				}

				// *
				pair operator* () const {
					return (_pointer->value);
				}

				// ->
				pair* operator->() const {
					return &(_pointer->value);
				}

				// ++
				const_bidirectional_iterator&	operator++() {
					if (!_pointer)
						return *this;
					// std::cout << "coucou const : " << _pointer->value.first << " - " <<  _pointer->value.second << std::endl;
					if (_pointer->right != NULL)
					{
						_pointer = _pointer->right;
						while (_pointer->left != NULL)
							_pointer = _pointer->left;
					}
					else {
						while (_pointer->parent != NULL && _pointer == _pointer->parent->right)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				const_bidirectional_iterator	operator++(int) {
					const_bidirectional_iterator	temp = *this;
					operator++();
					// std::cout << "coucou const : " << (*temp).first << " - " << (*temp).second << std::endl;
					return temp;
				}

				// --
				const_bidirectional_iterator&	operator--() {
					if (_pointer == NULL)
					{
						_pointer = _last;
						return *this;
					}
					if (_pointer->left != NULL)
					{
						_pointer = _pointer->left;
						while (_pointer->right != NULL)
							_pointer = _pointer->right;
					}
					else {
						while (_pointer->parent != NULL && _pointer == _pointer->parent->left)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				const_bidirectional_iterator	operator--(int) {
					const_bidirectional_iterator	temp = *this;
					operator--();
					return temp;
				}
	};

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::const_bidirectional_iterator<Iterator1>& lhs,	
				const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::const_bidirectional_iterator<Iterator1>& lhs,
					const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
}

#endif