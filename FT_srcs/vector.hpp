#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include <tgmath.h>

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
					size_type		_capacity;		// 
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
				vector (const vector& x) // copy
				{
					*this = x; // operator =
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
				// ====================
				// === BACK | FRONT ===
				// ====================
				reference back() {
					return (*(_endpointer - 1));
				}
				const_reference back() const {
					return (*(_endpointer - 1));
				}
				reference front() {
					return (*(_startpointer));
				}
				const_reference front() const {
					return (*(_startpointer));
				}

				// ==========
				// === AT ===
				// ==========
				reference at (size_type n) {
					if (n >= size() || n < 0)
						throw std::out_of_range("vector");
					return (_startpointer[n]);
				}
				const_reference at (size_type n) const {
					if (n >= size())
						throw std::out_of_range("vector");
					return (_startpointer[n]);
				}

				// ============
				// === SIZE ===
				// ============
				size_type	size() const {
					return (this->_endpointer - this->_startpointer);
				}
				// ================
				// === CAPACITY ===
				// ================
				size_type capacity() const {
					return (this->_capacity);
				}
				// ================
				// === MAX_SIZE ===
				// ================
				size_type max_size() const {
					if (sizeof(value_type) == 1)
						return (_allocator.max_size() / 2);
					return (_allocator.max_size());
				}
				// =================
				// === GET_ALLOC ===
				// =================
				allocator_type get_allocator(void) const {
					return (this->_allocator);
				}

				// ===============
				// === RESERVE ===
				// ===============
				void reserve (size_type n)
				{
					pointer	oldstart			= this->_startpointer;
					size_type oldsize			= this->size();
					size_type oldcapacity		= this->capacity();
					if (n <= this->capacity())
						return ;
					_capacity = n;
					this->_startpointer		= _allocator.allocate(n);
					this->_endmaxpointer	= _startpointer + _capacity;
					this->_endpointer		= _startpointer;
					size_type i = 0;
					// construction avec la new taille
					for ( ; i < oldsize ; i++ ) {
						_allocator.construct(_startpointer + i, oldstart[i]);
						_endpointer++;
					}
					// destruction du content precedent
					for (size_type j = 0; j != i ; j++) {
						_allocator.destroy(oldstart + j);
					}
					_allocator.deallocate(oldstart, oldcapacity);
				}

				// ==============
				// === RESIZE ===
				// ==============
				void resize (size_type n, value_type val = value_type())
				{
					pointer	oldstart			= this->_startpointer;
					size_type oldsize			= this->size();
					size_type oldcapacity		= this->capacity();
					
					if (n < (this->size()))
					{
						for ( pointer it = this->_startpointer + n ; it != this->_endpointer ; it++ )
							this->_allocator.destroy(it);
						this->_endpointer		= this->_startpointer + n;
						return ;
					}
					else if (n > (this->_capacity))
					{
						// mettre a jour la capacity
						if (n >= SIZE_MAX)
							throw std::length_error("vector");
						n < SIZE_MAX / 2 ? _capacity *= 2 : _capacity = SIZE_MAX;
						if (_capacity == 0)
							_capacity = 1;
						if (n > _capacity)
							_capacity = n;
						this->_startpointer		= _allocator.allocate(_capacity);
						this->_endpointer		= _startpointer + n;
						this->_endmaxpointer	= _startpointer + _capacity;

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
					}
					// si rentre dans aucuns if -> on modifie le endpointer
					this->_endpointer			= _startpointer + n;
					// attribution des dernieres valeurs si il en manque (n > oldsize) sans avoir a realouer si n < capacity et n > size
					for (pointer it = _startpointer + oldsize ; it != _endpointer ; it++) {
							_allocator.construct(it, val);
						}
				}

				// =================
				// === PUSH_BACK ===
				// =================
				void push_back (const value_type& val)
				{
					this->resize(this->size() + 1, val);
				}

				// =================
				// === POP_BACK ====
				// =================
				void pop_back ( void )
				{
					_allocator.destroy(_endpointer - 1);
					_endpointer--;
				}

				// =================
				// ===== ASSIGN ====
				// =================
				void assign (size_type n, const value_type& val)	// FILL VERSION
				{
					// destruct des elements deja presents
					pointer temp = _endpointer - 1;
					while (_startpointer - 1 != temp)
					{
						_allocator.destroy(temp);
						_endpointer--;
						temp--;
					}
					this->resize(n, val);
				}

				// =================
				// ===== ERASE =====
				// =================
				iterator erase (iterator position)
				{
					pointer	pos	= &(*(position));
					_allocator.destroy(pos);
					size_type	i = 0;
					for ( ; i < this->size() ; ) {
						
					}
					return ();
				}
				// =================
				// ===== CLEAR ====
				// =================
				void clear()
				{
					for ( ; _startpointer != _endpointer ; ) {
						_allocator.destroy(_endpointer - 1);
						_endpointer--;
					}
				}

				// =================
				// ===== EMPTY =====
				// =================
				bool empty() const {
					return (this->size() == 0 ? true : false);
				}
				// template <class InputIterator>				// RANGE VERSION
				// void assign (InputIterator first, InputIterator last);

				// ====================
				// ===== OPERATORS ====
				// ====================
				reference operator[] (size_type n) {
					return (_startpointer[n]);
				}

				const_reference operator[] (size_type n) const {
					return (_startpointer[n]);
				}

				vector& operator= (const vector& x)
				{
					this->_allocator.deallocate(this->_startpointer, this->_capacity);
					_startpointer = this->_allocator.allocate(x.size());
					size_type	n = 0;
					_endpointer = _startpointer;
					_endmaxpointer = _endpointer + x.size();
					_capacity = x.size();
					for (size_type i = x.size() ; i > 0 ; i--)
					{
						_allocator.construct(_endpointer, x[n]);
						_endpointer++;
						n++;
					}
					return (*this);
				 }
	};
}

#endif
