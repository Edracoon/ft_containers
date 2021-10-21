/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:26:49 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 11:09:54 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"
# include "node.hpp"

namespace ft
{
	// =================================
	// ==== BIDIRECTIONAL ITERATOR =====
	// =================================
	template< typename T >
	class bidirectional_iterator
	{
		public:
				// typedef macro
				typedef T											value_type;
				typedef value_type*									pointer;
				typedef value_type&									reference;
				typedef size_t										difference_type;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef typename ft::node<T>						node;
				typedef	node*										node_ptr;
		public:
				node_ptr		_curr_node;
				node_ptr		_last;
		public:
				bidirectional_iterator( void )
					: _curr_node(NULL), _last(NULL) { }	 // default
				bidirectional_iterator( node_ptr Node, node_ptr Last = NULL )
					: _curr_node(Node), _last(Last) { }
				template <class Iter>
				bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _curr_node(rhs.base()), _last(rhs._last) { } // copy
				~bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pointer base(void) const {
					return &(_curr_node->value);
				}
				
				node_ptr base_node(void) const {
					return (_curr_node);
				}

				// assignation
				template <class Iterator>
				bidirectional_iterator& operator= (const bidirectional_iterator<Iterator>& rhs) {
					this->_curr_node = rhs.base();
					return (*this);
				}

				// *
				reference operator* () {
					return (_curr_node->value);
				}
				reference operator* () const {
					return (_curr_node->value);
				}

				// ->
				pointer operator->() const {
					return &(operator*());
				}

				// ++
				bidirectional_iterator&	operator++()
				{
					if (_curr_node == _last)
						_curr_node = _curr_node->NIL;
					else if (_curr_node != _curr_node->NIL && _curr_node->right != _curr_node->NIL)
					{
						_curr_node = _curr_node->right;
						while (_curr_node->left != _curr_node->NIL && _curr_node->left != nullptr)
							_curr_node = _curr_node->left;
					}
					else
					{
						while (_curr_node != _curr_node->NIL && _curr_node == _curr_node->parent->right)
							_curr_node = _curr_node->parent;
						_curr_node = _curr_node->parent;
					}
					return (*this);
				}
				bidirectional_iterator	operator++(int) {
					bidirectional_iterator	temp = *this;
					operator++();
					return temp;
				}

				// --
				bidirectional_iterator&	operator--() {
					if (_curr_node == _curr_node->NIL || _curr_node->NIL == NULL)
					{
						_curr_node = _last;
						return *this;
					}
					if (_curr_node->left != _curr_node->NIL)
					{
						_curr_node = _curr_node->left;
						while (_curr_node != _curr_node->NIL && _curr_node->right != _curr_node->NIL) {
							_curr_node = _curr_node->right;
						}
					}
					else
					{
						while (_curr_node->parent != _curr_node->NIL && _curr_node == _curr_node->parent->left) {
							_curr_node = _curr_node->parent;
						}
						_curr_node = _curr_node->parent;
					}
					return *this;
				}
				bidirectional_iterator	operator--(int) {
					bidirectional_iterator	temp = *this;
					operator--();
					return temp;
				}
	};

	// =======================================
	// ==== CONST BIDIRECTIONAL ITERATOR =====
	// =======================================
	template< typename T >
	class const_bidirectional_iterator
	{
		public:
				// typedef macro
				typedef const T										value_type;
				typedef value_type*									pointer;
				typedef value_type&									reference;
				typedef size_t										difference_type;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef typename ft::node<value_type>				node;
				typedef	node*										node_ptr;
		public:
				node_ptr		_curr_node;
				node_ptr		_last;
		public:
				const_bidirectional_iterator( void )
					: _curr_node(NULL), _last(NULL) { }	// default
				const_bidirectional_iterator( node_ptr Node, node_ptr Last = NULL )
					: _curr_node(Node), _last(Last) { }
				template <class Iter>
				const_bidirectional_iterator (const const_bidirectional_iterator<Iter> & rhs) : _curr_node(rhs.base()) { } // copy
				template <class Iter>
				const_bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _curr_node(reinterpret_cast<node_ptr>(rhs.base())), _last(reinterpret_cast<node_ptr>(rhs._last)) { }
				~const_bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pointer base(void) const {
					return &(_curr_node->value);
				}

				node_ptr base_node(void) const {
					return (_curr_node);
				}

				// assignation
				template <class Iterator>
				const_bidirectional_iterator& operator= (const const_bidirectional_iterator<Iterator>& rhs) {
					this->_curr_node = rhs.base();
					return (*this);
				}

				// *
				reference operator* () {
					return (_curr_node->value);
				}
				reference operator* () const {
					return (_curr_node->value);
				}

				// ->
				pointer operator->() const {
					return &(operator*());
				}

				// ++
				const_bidirectional_iterator&	operator++() {
					if (_curr_node == _last)
						_curr_node = _curr_node->NIL;
					else if (_curr_node != _curr_node->NIL && _curr_node->right != _curr_node->NIL)
					{
						_curr_node = _curr_node->right;
						while (_curr_node->left != _curr_node->NIL && _curr_node->left != nullptr)
							_curr_node = _curr_node->left;
					}
					else
					{
						while (_curr_node != _curr_node->NIL && _curr_node == _curr_node->parent->right)
							_curr_node = _curr_node->parent;
						_curr_node = _curr_node->parent;
					}
					return (*this);
				}
				const_bidirectional_iterator	operator++(int) {
					const_bidirectional_iterator	temp = *this;
					operator++();
					return temp;
				}

				// --
				const_bidirectional_iterator&	operator--() {
					if (_curr_node->NIL == NULL)
					{
						_curr_node = _last;
						return *this;
					}
					if (_curr_node->left != _curr_node->NIL)
					{
						_curr_node = _curr_node->left;
						while (_curr_node->right != _curr_node->NIL)
							_curr_node = _curr_node->right;
					}
					else
					{
						while (_curr_node->parent != _curr_node->NIL && _curr_node == _curr_node->parent->left)
							_curr_node = _curr_node->parent;
						_curr_node = _curr_node->parent;
					}
					return *this;
				}
				const_bidirectional_iterator	operator--(int) {
					const_bidirectional_iterator	temp = *this;
					operator--();
					return temp;
				}
	};

	// === OUT OF CLASS COMPARISON ===
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::const_bidirectional_iterator<Iterator1>& lhs,	
				const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::bidirectional_iterator<Iterator1>& lhs,	
				const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::const_bidirectional_iterator<Iterator1>& lhs,	
				const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	// OPERATOR !=
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::const_bidirectional_iterator<Iterator1>& lhs,
					const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::bidirectional_iterator<Iterator1>& lhs,
					const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::const_bidirectional_iterator<Iterator1>& lhs,
					const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
}

#endif