#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include "btree.hpp"

namespace ft
{
	// ============
	// === PAIR ===
	// ============
	template <class T1, class T2>
	struct pair
	{
		typedef T1		first_type;
		typedef T2		second_type;
		first_type		first;
		second_type		second;
		
		pair( void ) : first(first_type()), second(second_type()) { }

		template<class U, class V>
		pair ( const pair< U, V > & pr ) : first(pr.first), second(pr.second) { }

		pair (const first_type& a, const second_type& b) : first(a), second(b) { }

		pair& operator= (const pair& pr)
		{
			if (this != &pr)
			{
				first = pr.first;
				second = pr.second;
			}
			return (*this);
		}
	};


	// =============
	// ==== MAP ====
	// =============
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator< ft::pair<const Key,T> > >
	class map
	{
		public:
				// TEMPLATES TYPEDEFS
				typedef Key												key_type;
				typedef T												mapped_type;	
				typedef Compare											key_compare;
				typedef Alloc											allocator_type;

				typedef size_t											size_type;
				typedef pair<const key_type, mapped_type>				value_type;			// la value deviens une clé et une valeur associé dans une node

				// ALLOCATOR
				typedef typename allocator_type::reference				reference;			// value_type &
				typedef typename allocator_type::const_reference		const_reference;	// value_type & const
				typedef	typename allocator_type::pointer				pointer;			// value_type *
				typedef typename allocator_type::const_pointer			const_pointer;		// value_type * const
				typedef	typename allocator_type::difference_type		difference_type;	// usually ptrdiff_t

				// BIDIRECTIONAL ITERATOR
				typedef	ft::bidirectional_iterator<pointer>				iterator;
				typedef	ft::bidirectional_iterator<const_pointer>		const_iterator;
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
				typedef	btree<mapped_type, key_compare, allocator_type>		btree_type;
				allocator_type	_alloc;
				size_type		_capacity;
				key_compare		_comp;
				btree_type		_tree;
				
		
		public:
				// =============
				// == DEFAULT ==
				// =============
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				{
					_alloc			= alloc;
					_comp			= comp;
					_tree			= btree_type(comp, alloc);
				}
				
				// =============
				// === RANGE ===
				// =============
				template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				{
					(void)first;
					(void)last;
					_comp			= comp;
					_alloc			= alloc;
					_tree			= btree_type(comp, alloc);
				}

				// ============
				// === COPY ===
				// ============
				map (const map& x)
				{
					_alloc = x._alloc;
					*this = x;
				}

				~map() {}



				map& operator= (const map& x)
				{
					(void)x;
				}
	};
}

#endif