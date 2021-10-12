/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:20 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/12 18:44:50 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include "btree.hpp"
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

				typedef size_t												size_type;
				typedef ft::pair<const key_type, mapped_type>				value_type;			// la value deviens une clé et une valeur associé dans une node

				// ALLOCATOR
				typedef typename allocator_type::reference					reference;			// value_type &
				typedef typename allocator_type::const_reference			const_reference;	// value_type & const
				typedef	typename allocator_type::pointer					pointer;			// value_type *
				typedef typename allocator_type::const_pointer				const_pointer;		// value_type * const
				typedef	typename allocator_type::difference_type			difference_type;	// usually ptrdiff_t

		protected:
				typedef	btree<value_type, key_compare, allocator_type>		btree_type;
		public:
				// BIDIRECTIONAL ITERATOR
				typedef	typename btree_type::iterator						iterator;
				typedef	typename btree_type::const_iterator					const_iterator;
				typedef	ft::reverse_iterator<iterator>					reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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
				// =============
				// == DEFAULT ==
				// =============
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(btree_type(comp))
				{
					_alloc			= alloc;
					_comp			= comp;
				}

				// =============
				// === RANGE ===
				// =============
				template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				{
					_comp			= comp;
					_alloc			= alloc;
					_tree			= btree_type(first, last, comp, alloc);
				}

				// ============
				// === COPY ===
				// ============
				map (const map& x)
				{
					_alloc	= x._alloc;
					_comp	= x._comp;
					*this	= x;
				}

				~map() {}

				// === SWAP ===
				void swap (map& x) {
					
					// Les deux methodes marchent mais les iterateurs sont invalidés
					
					// Swap the tree roots
					// btree_type	temp_tree = btree_type();
					
					// temp_tree._root = this->_tree._root;
					// this->_tree._root = x._tree._root;
					// x._tree._root = temp_tree._root;

					// Swap the elements with inserts
					ft::map<key_type, mapped_type, key_compare, allocator_type>		temp;
					
					temp.insert(this->begin(), this->end());
					
					this->clear();
					this->insert(x.begin(), x.end());

					x.clear();
					x.insert(temp.begin(), temp.end());

					// CODE SOURCE :

					/*swap(__begin_node_, __t.__begin_node_);
					swap(__pair1_.first(), __t.__pair1_.first());
					__swap_allocator(__node_alloc(), __t.__node_alloc());
					__pair3_.swap(__t.__pair3_);
					if (size() == 0)
						__begin_node() = __end_node();
					else
						__end_node()->__left_->__parent_ = static_cast<__parent_pointer>(__end_node());
					if (__t.size() == 0)
						__t.__begin_node() = __t.__end_node();
					else
					__t.__end_node()->__left_->__parent_ = static_cast<__parent_pointer>(__t.__end_node());*/
				}

				// ===================
				// === BEGIN | END ===
				// ===================
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
				
				// =============
				// === CLEAR ===
				// =============
				void clear() {
					if (this->empty() == false)
					{
						_tree.btree_clear(_tree._root);
						_tree._root = NULL;
					}
				}

				// ============
				// === SIZE ===
				// ============
				size_type size() const {
					return (_tree.size((_tree._root)));
				}

				// =============
				// === EMPTY ===
				// =============
				bool empty() const {
					return (!_tree.size((_tree._root)));
				}

				// ============
				// === FIND ===
				// ============
				iterator find (const key_type& k) {
					return iterator(_tree.btree_find_node(_tree._root, ft::make_pair(k, "oui")));
				}
				const_iterator find (const key_type& k) const {
					return const_iterator(_tree.btree_find_node(_tree._root, ft::make_pair(k, "oui")));
				}

				// =============
				// === COUNT ===
				// =============
				size_type count (const key_type& k) const {
					return (_tree.btree_find_node(_tree._root, ft::make_pair(k, "oui")) != NULL ? 1 : 0);
				}

				// ==============
				// === INSERT ===
				// ==============
				pair<iterator, bool> insert (const value_type& val) {
					
					bool		insertable	= _tree.btree_find_pair(_tree._root, val) == NULL ? true : false;
					iterator	it = _tree.btree_insert(&(_tree._root), val);
					
					return ft::make_pair(it, insertable);
				}

				iterator insert (iterator position, const value_type& val) {
					(void)position;

					this->insert(val);
					iterator	ret = iterator(_tree.btree_find_node(_tree._root, val));
					
					return (ret);
				}

				template <class InputIterator>
				void insert (InputIterator first, InputIterator last) {
					for ( ; first != last ; first++) {
						this->_tree.btree_insert(&(_tree._root), *first);
					}
				}

				// === OPERATORS === //
				mapped_type& operator[] (const key_type& k) {
					return ((this->insert( ft::make_pair(k, mapped_type()) )).first)->second;
				}

				map& operator= (const map& x)
				{
					this->clear();
					this->insert(x.begin(), x.end());
					return *this;
				}
	
				// PENSER A SUPPRIMER
				void	print_tree(void)
				{
					_tree.btree_display(_tree._root, 0);
				}
	};
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