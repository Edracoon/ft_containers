/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:20 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 14:46:18 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include "map_RBtree.hpp"
# include "pair.hpp"
# include "utils.hpp"

namespace ft
{
	// =============
	// ==== MAP ====
	// =============
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:
				// TEMPLATES TYPEDEFS
				typedef Key													key_type;
				typedef T													mapped_type;	
				typedef Compare												key_compare;
				typedef Alloc												allocator_type;

				typedef size_t													size_type;
				typedef ft::pair<const key_type, mapped_type>					value_type;			// la value deviens une clé et une valeur associé dans une node

				// ALLOCATOR
				typedef typename allocator_type::reference						reference;			// value_type &
				typedef typename allocator_type::const_reference				const_reference;	// value_type & const
				typedef	typename allocator_type::pointer						pointer;			// value_type *
				typedef typename allocator_type::const_pointer					const_pointer;		// value_type * const
				typedef	typename allocator_type::difference_type				difference_type;	// usually ptrdiff_t

		protected:
				typedef	map_rbtree<value_type, key_compare, allocator_type>		btree_type;
		public:
				// BIDIRECTIONAL ITERATOR
				typedef	typename btree_type::iterator							iterator;
				typedef	typename btree_type::const_iterator						const_iterator;
				typedef	ft::reverse_iterator<iterator>							reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		public:
				// Nested class VALUE_COMPARE
				class value_compare : std::binary_function< value_type, value_type, bool >	// Herite de binary_function
				{
					private:
							friend class map;

					protected:
 							Compare		comp;
							value_compare (Compare c) : comp(c) { }	// construit avec la fonction de comparaison de map (passée en template)

					public:
							typedef	bool			result_type;
							typedef	value_type		first_argument_type;
							typedef	value_type		second_argument_type;

							bool operator() (const value_type& x, const value_type& y) const
							{
								return comp(x.first, y.first);	// on va utiliser std::less ou une autre fonction de comparaison templaté ;
							}
				};

		protected:
				allocator_type	_alloc;
				size_type		_capacity;
				key_compare		_comp;
				btree_type		_tree;


		public:
				// == DEFAULT ==
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree()
				{
					_alloc			= alloc;
					_comp			= comp;
				}

				// === RANGE ===
				template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				{
					_comp			= comp;
					_alloc			= alloc;
					this->insert(first, last);
				}

				// === COPY ===
				map (const map& x)
				{
					_alloc	= x._alloc;
					_comp	= x._comp;
					*this	= x;
				}

				~map() {
					_tree._alloc.destroy(_tree.NIL);
					_tree._alloc.deallocate(_tree.NIL, 1);
				}

				// === SWAP ===
				void swap (map& x) {
					_tree.btree_swap(x._tree);
				}

				// === BEGIN | END ===
				iterator begin() {
					return iterator(_tree.begin());
				}
				const_iterator begin() const {
					return const_iterator(_tree.begin());
				}

				iterator end() {
					return iterator(_tree.end());
				}
				const_iterator end() const {
					return const_iterator(_tree.end());
				}

				reverse_iterator rbegin() {
					return reverse_iterator(_tree.end());
				}
				const_reverse_iterator rbegin() const {
					return const_reverse_iterator(_tree.end());
				}
				reverse_iterator rend() {
					return reverse_iterator(_tree.begin());
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
				iterator find (const key_type& k) {
					return iterator(_tree.btree_find_node(_tree._root, k));
				}
				const_iterator find (const key_type& k) const {
					return const_iterator(reinterpret_cast<typename btree_type::const_node_ptr>(_tree.btree_find_node(_tree._root, k)));
				}

				// === COUNT ===
				size_type count (const key_type& k) const {
					return (_tree.btree_find_node(_tree._root, k) != _tree.NIL ? 1 : 0);
				}

				// === INSERT 1 ===
				pair<iterator, bool> insert (const value_type& val) {
					
					bool		insertable	= _tree.btree_find_pair(_tree._root, val.first) == NULL ? true : false;
					iterator	it = _tree.btree_insert(&(_tree._root), val);
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
					for ( ; first != last ; first++) {
						this->_tree.btree_insert(&(_tree._root), *first);
					}
				}

				// === ERASE 1 ===
				void erase (iterator position) {
					this->erase(position->first);
				}

				// === ERASE 2 ===
				size_type erase (const key_type& k) {
					value_type*		verif	= _tree.btree_find_pair(_tree._root, k);
					size_type		ret		= (verif == NULL ? 0 : 1);
					if (verif != NULL) {
						_tree._root = _tree.delete_node_tree(k);
					}
					return (ret);
				}

				// === ERASE 3 ===
				void erase (iterator first, iterator last) {
					for ( ; first != last ; ) {
						this->erase((first++)->first);
					}
				}

				// === LOWER_BOUND ===
				iterator lower_bound (const key_type& k) {
					iterator	it	= this->begin();
					iterator	ite	= this->end();
					for ( ; it != ite ; it++) {
						if (_comp(it->first, k) == false)
							break ;
					}
					return (it);
				}
				const_iterator lower_bound (const key_type& k) const {
					const_iterator	it	= this->begin();
					const_iterator	ite	= this->end();
					for ( ; it != ite ; it++) {
						if (_comp(it->first, k) == false)
							break ;
					}
					return (it);
				}

				// === UPPER_BOUND ===
				iterator upper_bound (const key_type& k) {
					iterator	it	= this->begin();
					iterator	ite	= this->end();
					for ( ; it != ite ; it++) {
						if (_comp(k, it->first) == true)
							break ;
					}
					return (it);
				}
				const_iterator upper_bound (const key_type& k) const {
					const_iterator	it	= this->begin();
					const_iterator	ite	= this->end();
					for ( ; it != ite ; it++) {
						if (_comp(k, it->first) == true)
							break ;
					}
					return (it);
				}

				// === EQUAL_RANGE ===
				pair<iterator,iterator>				equal_range (const key_type& k) {
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}
				pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
					return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
				}

				// === EQUAL_RANGE ===
				allocator_type get_allocator() const {
					return (_alloc);
				}

				// === OPERATORS ===
				mapped_type& operator[] (const key_type& k) {
					return ((this->insert( ft::make_pair(k, mapped_type()) )).first)->second;
				}

				map& operator= (const map& x)
				{
					if (this != &x)
					{
						this->clear();
						this->insert(x.begin(), x.end());
					}
					return *this;
				}
	};
	// === NON MEMBER SWAP ===
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs,
						const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs,
						const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const ft::map<Key, T, Compare, Alloc>& lhs,
						const ft::map<Key, T, Compare, Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs,
						const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs,
						const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs,
						const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(lhs < rhs);
	}
}


#endif