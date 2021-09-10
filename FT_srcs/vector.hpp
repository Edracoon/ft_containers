#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"

namespace ft
{
	/* === VECTOR ===*/
	template< typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
				// Template du type de valeur
				typedef	T											value_type;
				// Template pour le type d'allocator, par defaut set à : std::allocator<T> 
				typedef	Alloc										allocator_type;
				// Reference de l'allocateur par defaut est (value_type&)
				typedef typename allocator_type::reference			reference;
				//const Reference de l'allocateur par defaut est (const value_type&)
				typedef typename allocator_type::const_reference	const_reference;
				// Pointer de l'allocateur par defaut est (value_type*)
				typedef typename allocator_type::pointer			pointer;
				// const Pointer de l'allocateur par defaut est (const value_type*)
				typedef typename allocator_type::const_pointer		const_pointer;
				// same as ptrdiff_t
				// typedef	typename iterator_traits<ft::iterator>::difference_type	difference_type;
				// Quantité d'élement dans le container (size_t) pour le constructeur parametrique
				typedef size_t										size_type;
				// typedef pour les iterators
				typedef ft::random_access_iterator<T>				iterator;			// modify / iterate
				typedef ft::random_access_iterator<const T>			const_iterator;		// only iterate
				// typedef ft::reverse_iterator<iterator>				reverse_iterator;	// 
				// typedef ft::const_reverse_iterator<const_iterator>	const_reverse_iterator;
				
		protected:
					pointer			_startpointer;	// first elem
					pointer			_endpointer;	// last elem
					pointer			_endmaxpointer;	// double size in case of reallocation
					allocator_type	_allocator;		// allocateur selon son type pour utiliser ses fonctions
		public:
				explicit	// Default
				vector (const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_startpointer		= NULL;
					this->_endpointer		= NULL;
					this->_endmaxpointer	= NULL;
				}
				explicit	// param
				vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_startpointer		= this->_allocator.allocate(n);
					this->_endpointer		= _startpointer;
					this->_endmaxpointer	= _endpointer + n;
					while (n)
					{
						_allocator.construct(_endpointer, (const_reference)val);
						_endpointer++;
						n--;
					}
				}
				vector (const vector& x)	// copy
				{
					(void)x;
				}

				iterator	begin( void )
				{
					return (iterator(this->_startpointer));
				}
				iterator	end( void )
				{
					return (iterator(this->_endpointer));
				}

	};
}

#endif
