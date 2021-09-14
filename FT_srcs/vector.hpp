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
					size_type		_capacity;
		public:
				explicit	// Default
				vector (const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_startpointer		= NULL;
					this->_endpointer		= NULL;
					this->_endmaxpointer	= NULL;
					this->_capacity			= 0;
				}
				explicit	// param
				vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_capacity			= n;
					this->_startpointer		= this->_allocator.allocate(_capacity);
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
				~vector ( void )
				{
					
				}

				// ===================
				// === BEGIN | END ===
				// ===================
				iterator	begin( void ) const {
					return (iterator(this->_startpointer));
				}
				iterator	end( void ) const {
					return (iterator(this->_endpointer));
				}

				// ============
				// === SIZE ===
				// ============
				size_type	size() const {
					return (this->_endpointer - this->_startpointer);
				}
				size_type capacity() const {
					return (this->_capacity);
				}

				void resize (size_type n, value_type val = value_type())
				{
					if (n < (this->size()))
					{
						for ( pointer it = this->_startpointer + n ; it != this->_endpointer ; it++ )
							this->_allocator.destroy(it);
						this->_endpointer = this->_startpointer + n;
					}
					else if (n > (this->size()))
					{
						pointer	oldstart		= this->_startpointer;
						size_type oldsize		= this->size();
						size_type oldcapacity	= this->capacity();

						this->_startpointer		= _allocator.allocate(n);
						this->_endpointer		= _startpointer + n;

						size_type i = 0;
						// construction avec la new taille
						for ( ; i < oldsize ; i++ ) {
							_allocator.construct(_startpointer + i, oldstart[i]);
						}
						// destruction du content precedent
						for (size_type j = 0; j != i ; j++) {
							_allocator.destroy(oldstart + j);
						}
						_allocator.deallocate(oldstart, oldcapacity);
						// attribution des dernieres valeurs si il en manque
						for ( ; i < this->size() ; i++) {
							_allocator.construct(_startpointer + i, val);
						}
					}
				}
				void push_back (const value_type& val)
				{
					_allocator.construct(_endpointer, (const_reference)val);
					_endpointer++;
				}
	};
}

#endif
