/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:53:59 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 15:16:29 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include "set_RBtree.hpp"
# include "pair.hpp"
# include "utils.hpp"

namespace ft 
{
	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public:
				typedef T													key_type;				// The first template parameter (T)	
				typedef	T													value_type; 			// The first template parameter (T)	
				typedef	Compare												key_compare;			// The second template parameter (Compare)	defaults to: less<key_type>
				typedef	Alloc												allocator_type;			// The third template parameter (Alloc)	defaults to: allocator<value_type>
				typedef	typename allocator_type::reference					reference;				// value_type&
				typedef typename allocator_type::const_reference			const_reference;		// const value_type&
				typedef	typename allocator_type::pointer					pointer;				// value_type*
				typedef	typename allocator_type::const_pointer				const_pointer;			// const value_type*
				typedef	typename allocator_type::difference_type			difference_type;
				typedef	size_t												size_type;
	
		protected:
				typedef	set_rbtree<value_type, key_compare, allocator_type>		btree_type;
		public:
				// BIDIRECTIONAL ITERATOR
				typedef	typename btree_type::iterator						iterator;
				typedef	typename btree_type::iterator						const_iterator;
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef	ft::reverse_iterator<iterator>				const_reverse_iterator;
		
		public:
				// Nested class VALUE_COMPARE
				class value_compare : std::binary_function< value_type, value_type, bool >	// Herite de binary_function
				{
					private:
							friend class set;

					protected:
 							Compare		comp;
							value_compare (Compare c) : comp(c) { }	// construit avec la fonction de comparaison de set (passée en template)

					public:
							typedef	bool			result_type;
							typedef	value_type		first_argument_type;
							typedef	value_type		second_argument_type;

							bool operator() (const value_type& x, const value_type& y) const
							{
								return comp(x, y);	// on va utiliser std::less ou une autre fonction de comparaison templaté ;
							}
				};

		protected:
				allocator_type	_alloc;
				size_type		_capacity;
				key_compare		_comp;
				btree_type		_tree;
		
		public:
				// == DEFAULT ==
				explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree()
				{
					_alloc			= alloc;
					_comp			= comp;
				}

				// === RANGE ===
				template <class InputIterator>
				set (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				{
					_comp			= comp;
					_alloc			= alloc;
					this->insert(first, last);
					// _tree			= btree_type(first, last, comp, alloc);
				}

				// === COPY ===
				set (const set& x)
				{
					_alloc	= x._alloc;
					_comp	= x._comp;
					*this	= x;
				}

				~set() {
					_tree._alloc.destroy(_tree.NIL);
					_tree._alloc.deallocate(_tree.NIL, 1);
				}

				// === SWAP ===
				void swap (set& x) {
					_tree.btree_swap(x._tree);
				}

				// === BEGIN | END ===
				iterator begin() {
					return iterator(_tree.begin());
				}
				const_iterator begin() const {
					return iterator(_tree.begin());
				}

				iterator end() {
					return iterator(_tree.end());
				}
				const_iterator end() const {
					return iterator(_tree.end());
				}
				
				reverse_iterator rbegin() {
					return const_reverse_iterator(_tree.end());
				}
				const_reverse_iterator rbegin() const {
					return const_reverse_iterator(_tree.end());
				}
				
				reverse_iterator rend() {
					return const_reverse_iterator(_tree.begin());
				}
				const_reverse_iterator rend() const {
					return const_reverse_iterator(_tree.begin());
				}

				// === KEY_COMPARE ===
				key_compare key_comp() const {
					return _comp;
				}
				// === VALUE_COMP ===
				value_compare value_comp() const {
					return value_compare(_comp);
				}
				
				// === CLEAR ===
				void clear() {
					_tree.btree_clear(_tree._root);
				}

				// === SIZE ===
				size_type size() const {
					return (_tree._size);
				}

				// === EMPTY ===
				bool empty() const {
					return (!_tree._size);
				}

				// === MAX_SIZE ===
				size_type max_size( void ) const {
					return (_tree.max_size());
				}

				// === FIND ===
				iterator find (const key_type& k) const {
					return iterator(reinterpret_cast<typename btree_type::const_node_ptr>(_tree.btree_find_node(_tree._root, k)));
				}

				// === COUNT ===
				size_type count (const key_type& k) const {
					return (_tree.btree_find_node(_tree._root, k) != _tree.NIL ? 1 : 0);
				}

				// === INSERT 1 ===
				pair<iterator, bool> insert (const value_type& val) {
					
					bool		insertable	= _tree.btree_find_node(_tree._root, val) == _tree.NIL ? true : false;
					iterator	it			= _tree.btree_insert(&(_tree._root), val);
					return ft::make_pair(it, insertable);
				}

				// === INSERT 2 ===
				iterator insert (iterator position, const value_type& val) {
					(void)position;
					
					pair<iterator, bool> ret = this->insert(val);					
					return (ret.first);
				}

				// === INSERT 3 ===
				template <class InputIterator>
				void insert (InputIterator first, InputIterator last) {
					for ( ; first != last ; first++)
					{
						this->_tree.btree_insert(&(_tree._root), *first);
					}
				}

				// === ERASE 1 ===
				void erase (iterator position) {
					this->erase(*position);
				}

				// === ERASE 2 ===
				size_type erase (const key_type& k) {
					typename btree_type::node_ptr	verif	= _tree.btree_find_node(_tree._root, k);
					size_type						ret		= (verif == _tree.NIL ? 0 : 1);
					if (verif != _tree.NIL) {
						_tree._root = _tree.delete_node_tree(k);
					}
					return (ret);
				}

				// === ERASE 3 ===
				void erase (iterator first, iterator last) {
					for ( ; first != last ; ) {
						this->erase(*(first++));
					}
				}

				// === LOWER_BOUND ===
				iterator lower_bound (const key_type& k) const {
					iterator	it	= this->begin();
					iterator	ite	= this->end();
					for ( ; it != ite ; it++) {
						if (_comp(*it, k) == false)
							break ;
					}
					return (it);
				}

				// === UPPER_BOUND ===
				iterator upper_bound (const key_type& k) const {
					iterator	it	= this->begin();
					iterator	ite	= this->end();
					for ( ; it != ite ; it++) {
						if (_comp(k, *it) == true)
							break ;
					}
					return (it);
				}

				// === EQUAL_RANGE ===
				pair<iterator,iterator> equal_range (const key_type& k) const {
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}

				// === GET_ALLOCATOR ===
				allocator_type get_allocator() const {
					return (_alloc);
				}

				// === OPERATORS === //
				set& operator= (const set& x)
				{
					if (this != &x)
					{
						this->clear();
						this->insert(x.begin(), x.end());
					}
					return *this;
				}
	};

	template <class T, class Compare, class Alloc>
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y) {
		x.swap(y);
	}

	template <class T, class Compare, class Alloc>
	bool operator== ( const set<T,Compare,Alloc>& lhs,
					const set<T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!= ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator<  ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <class T, class Compare, class Alloc>
	bool operator<= ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	}
	
	template <class T, class Compare, class Alloc>
	bool operator>  ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	}
	
	template <class T, class Compare, class Alloc>
	bool operator>= ( const set<T,Compare,Alloc>& lhs,
						const set<T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

}

#endif