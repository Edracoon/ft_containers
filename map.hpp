#ifndef MAP_HP
# define MAP_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"

namespace ft
{
	template < class Key,									// map::key_type
			class T,										// map::mapped_type
			class Compare = less<Key>,						// map::key_compare
			class Alloc = allocator<pair<const Key,T> >		// map::allocator_type
			>
	class map
	{
		public:
				typedef size_t										size_type;
				typedef typename key								key_type;
				typedef pair<const key_type, mapped_type>			value_type;

				// templates typedef
				typedef T											mapped_type;	
				typedef Compare										key_compare;
				typedef Alloc										allocator_type;

				typedef allocator_type::reference					reference;
				typedef allocator_type::const_reference				const_reference;
				// value_compare	Nested function class to compare elements	see value_comp
				
				typedef	allocator_type::pointer						pointer;
				typedef allocator_type::const_pointer				const_pointer;
				typedef	typename allocator_type::difference_type	difference_type;

				// BIDIRECTIONAL ITERATOR
				typedef	bidirectional_iterator<pointer>				iterator;
				typedef	bidirectional_iterator<const_pointer>		const_iterator;
				typedef	reverse_iterator<iterator>					reverse_iterator;
				typedef	reverse_iterator<const_iterator>			const_reverse_iterator;		
	};
}

#endif