#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include "btree.hpp"
# include "pair.hpp"

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
				typedef	ft::reverse_iterator<iterator>						reverse_iterator;
				typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;

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

				// ==============
				// === INSERT ===
				// ==============
				pair<iterator,bool> insert (const value_type& val) {
					bool		insertable	= _tree.btree_find(_tree._root, val) == NULL ? true : false;
					iterator	it;
					// std::cout << "insertable = " << insertable << std::endl;
					it = _tree.btree_insert(&(_tree._root), val);
					return ft::make_pair(it, insertable);
				}

				iterator insert (iterator position, const value_type& val) {
					this->insert(val);
					return (position);
				}

				template <class InputIterator>
				void insert (InputIterator first, InputIterator last) {
					for ( ; first != last ; first++) {
						this->_tree.btree_insert(&(_tree._root), *first.base());
					}
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
}

#endif