#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"

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

	template < class Key,											// map::key_type
			class T,												// map::mapped_type
			class Compare = std::less<Key>,							// map::key_compare
			class Alloc = std::allocator<ft::pair<const Key,T> >		// map::allocator_type
			>
	class map
	{
		public:
				typedef T											mapped_type;	
				typedef size_t										size_type;
				typedef Key											key_type;
				typedef pair<const key_type, mapped_type>			value_type;

				// templates typedef
				typedef Compare										key_compare;
				typedef Alloc										allocator_type;

				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				// typedef std::map::value_comp 						value_compare;
				
				typedef	typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef	typename allocator_type::difference_type	difference_type;

				// BIDIRECTIONAL ITERATOR
				typedef	bidirectional_iterator<pointer>				iterator;
				typedef	bidirectional_iterator<const_pointer>		const_iterator;

				typedef	reverse_iterator<iterator>					reverse_iterator;
				typedef	reverse_iterator<const_iterator>			const_reverse_iterator;
	};
}

#endif