/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:16:33 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 10:51:20 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include <iterator>	// std::distance
# include "utils.hpp"

namespace ft
{
	/* === VECTOR ===*/
	template< typename T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
				typedef	T															value_type;

				// Template pour le type d'allocator, par defaut = std::allocator<T> 
				typedef	Alloc														allocator_type;	// std::allocator

				typedef typename allocator_type::reference							reference;		// value_type&
				typedef typename allocator_type::const_reference					const_reference;// value_type& const 
				typedef typename allocator_type::pointer							pointer;		// value_type*
				typedef typename allocator_type::const_pointer						const_pointer;	// value_type* const
				
				typedef	typename allocator_type::difference_type					difference_type;// ptrdiff_t
			
				typedef size_t														size_type;
			
				// typedef pour les iterators
				typedef ft::random_access_iterator<pointer>							iterator;
				typedef ft::random_access_iterator<const_pointer>					const_iterator;
				typedef ft::reverse_iterator<iterator>								reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		protected:
					pointer			_startpointer;	// first elem
					pointer			_endpointer;	// last elem + 1
					allocator_type	_allocator;		// allocateur selon son type pour utiliser ses fonctions
					size_type		_capacity;		// allocated size
		public:
				// ===================
				// DEFAULT CONSTRUCTOR
				// ===================
				explicit	
				vector (const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_startpointer		= NULL;
					this->_endpointer		= NULL;
					this->_capacity			= 0;
				}

				// ================
				// FILL CONSTRUCTOR
				// ================
				explicit
				vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) 
				{
					this->_allocator		= alloc;
					this->_capacity			= n;
					this->_startpointer		= this->_allocator.allocate(_capacity);
					this->_endpointer		= _startpointer;
					while (n)
					{
						_allocator.construct(_endpointer, (const_reference)val);
						_endpointer++;
						n--;
					}
				}

				// =================
				// RANGE CONSTRUCTOR
				// =================
				template <class InputIterator>	
				vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
							typename enable_if< !is_integral<InputIterator>::value, int>::type = 0 )
				{
					size_type dist		= std::distance(first, last);
					_allocator			= alloc;
					_startpointer		= _allocator.allocate(dist);
					_endpointer			= _startpointer + dist;
					_capacity			= dist;
					this->assign(first, last);
				}

				// ================
				// COPY CONSTRUCTOR
				// ================
				vector (const vector& x) : _allocator(x._allocator)
				{
					_startpointer		= NULL; //_allocator.allocate(x.size());
					_endpointer			= NULL; //_startpointer + x.size();
					_capacity			= 0; x.size();
					*this = x;	// assign
				}

				// ==========
				// DESTRUCTOR
				// ==========
				~vector ( void )
				{
					for ( ; _startpointer != _endpointer ; )
					{
						_allocator.destroy(_endpointer - 1);
						_endpointer--;
					}
					_allocator.deallocate(_startpointer, _capacity);
				}

				// ===================
				// === BEGIN | END ===
				// ===================
				iterator begin( void ) {
					return (iterator(this->_startpointer));
				}
				iterator	end( void ) {
					return (iterator(this->_endpointer));
				}

				// const begin - const end
				const_iterator	begin( void ) const {
					return (const_iterator(this->_startpointer));
				}
				const_iterator	end( void ) const {
					return (const_iterator(this->_endpointer));
				}

				// rbegin - rend
				reverse_iterator rbegin( void ) {
					return reverse_iterator(end());	// last elem
				}
				reverse_iterator rend( void ) {
					return reverse_iterator(begin());	// before the first elem to simulate a end()
				}

				// const rbegin - const rend
				const_reverse_iterator rbegin( void ) const {
					return const_reverse_iterator(end());	// last elem
				}
				const_reverse_iterator rend( void ) const {
					return const_reverse_iterator(begin());	// before the first elem to simulate a end()
				}

				// ====================
				// === BACK | FRONT ===
				// ====================
				reference back( void ) {
					return (*(_endpointer - 1));
				}
				const_reference back( void ) const {
					return (*(_endpointer - 1));
				}
				reference front( void ) {
					return (*(_startpointer));
				}
				const_reference front( void ) const {
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
				size_type	size( void ) const {
					return (this->_endpointer - this->_startpointer);
				}

				// ================
				// === CAPACITY ===
				// ================
				size_type capacity( void ) const {
					return (this->_capacity);
				}

				// ================
				// === MAX_SIZE ===
				// ================
				size_type max_size( void ) const {
					if (sizeof(value_type) == 1)
						return (_allocator.max_size() / 2);
					return (_allocator.max_size());
				}

				// =================
				// === GET_ALLOC ===
				// =================
				allocator_type get_allocator( void ) const {
					return (this->_allocator);
				}

				// ============
				// === SWAP ===
				// ============
				void swap(vector& x)
				{
					allocator_type	temp_alloc	= x._allocator;		// swap allocator
					x._allocator				= this->_allocator;
					this->_allocator			= temp_alloc;

					pointer			temp		= x._startpointer;	// swap start
					x._startpointer				= this->_startpointer;
					this->_startpointer			= temp;

					temp						= x._endpointer;	// swap end
					x._endpointer				= this->_endpointer;
					this->_endpointer			= temp;

					size_type temp_s			= x._capacity;		// swap capacity
					x._capacity					= this->_capacity;
					this->_capacity				= temp_s;
				}

				// ===============
				// === RESERVE ===
				// ===============
				void reserve (size_type n)
				{
					if (n <= this->capacity())
						return ;
					pointer	oldstart			= this->_startpointer;
					size_type oldsize			= this->size();
					size_type oldcapacity		= this->capacity();
					
					this->_capacity			= n;
					this->_startpointer		= _allocator.allocate(n);
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

				// ==============
				// === INSERT ===
				// ==============
				iterator insert (iterator position, const value_type& val)					// SINGLE ELEMENT
				{
					size_type	conserv = position - _startpointer;	// stockage de la position dans le cas d'une reallocation
					if (_startpointer == NULL)
						this->reserve(1);
					if (_startpointer != NULL && _capacity < size() + 1)
						this->reserve(_capacity * 2);
					if (position.base() != NULL && position.base() < _startpointer)	// Si pos inferieur a start -> pos = start
						position = _startpointer;
					else if (position.base() != NULL && position.base() > _endpointer)	// Si pos superieur a end -> pos = end
						position = _endpointer;
					else if (position.base() == NULL)	// cas ou position = NULL
					{
						reserve(1);
						push_back(val);
						return (_endpointer - 1);
					}
					else if (position.base() == _endpointer && position.base() != _startpointer)
					{
						push_back(val);
						return (_endpointer - 1);
					}

					ft::vector<value_type>		vector_temp;
					vector_temp._startpointer	= _allocator.allocate(this->_capacity);
					vector_temp._capacity		= _capacity;
					vector_temp._endpointer		= vector_temp._startpointer;

					pointer		pos = vector_temp._startpointer + conserv;	// on recup la nouvelle position en cas de reallocation

					pointer		save_start = _startpointer;	// conserver le _start pour permettre le swap a la fin

					for ( ; vector_temp._endpointer != pos ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						vector_temp._endpointer++;
						_startpointer++;
					}
					vector_temp._allocator.construct(vector_temp._endpointer, val);
					vector_temp._endpointer++;
					for ( ; _startpointer != _endpointer ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						_startpointer++;
						vector_temp._endpointer++;
					}
					_startpointer = save_start;
					this->swap(vector_temp);
					return (_startpointer + conserv);
				}
				void insert (iterator position, size_type n, const value_type& val) 		// FILL
				{
					if (n > max_size())
						throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
					size_type	conserv = position - _startpointer; // stockage de la position dans le cas d'une reallocation
					if (_startpointer == NULL)
						this->reserve(n);
					if (_startpointer != NULL && _capacity < size() + n)
					{
						this->reserve(_capacity * 2);
						if (_capacity < size() + n)
							this->reserve(size() + n);
					}
					if (position.base() == NULL)
							reserve(1);
					if (position.base() != NULL && position.base() < _startpointer)
						position = _startpointer;
					else if (position.base() != NULL && position.base() > _endpointer)
						position = _endpointer;

					// Methode du vector temporaire pour insert
					ft::vector<value_type>		vector_temp;
					vector_temp._startpointer	= _allocator.allocate(this->_capacity);
					vector_temp._capacity		= _capacity;
					vector_temp._endpointer		= vector_temp._startpointer;

					pointer		pos = vector_temp._startpointer + conserv;	// nouvelle position en cas de reallocation
					pointer		save_start = _startpointer;					// save le start pour faire le swap a la fin

					// construction dans le vector temporaire : de start à pos
					for ( ; vector_temp._endpointer != pos ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						vector_temp._endpointer++;
						_startpointer++;
					}
					// construction dans le vector temporaire : de pos à n pour les nouvelle valeurs
					for (size_type i = 0 ; i < n ; i++) {
						vector_temp._allocator.construct(vector_temp._endpointer, val);
						vector_temp._endpointer++;
					}
					// construction dans le vector temporaire des valeurs de mon ancien vector de pos à end
					for ( ; _startpointer != _endpointer ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						_startpointer++;
						vector_temp._endpointer++;
					}
					_startpointer = save_start;	// on redonne le bon start
					this->swap(vector_temp);	// swap
				}
				template <class InputIterator>
				typename enable_if< !is_integral<InputIterator>::value, void>::type insert (iterator position, InputIterator first, InputIterator last)	// RANGE
				{
					size_type	conserv = position - _startpointer; // stockage de la position dans le cas d'une reallocation
					size_type	dist	= std::distance(first, last);
					if (size() == 0)
						reserve(dist);
					if (_startpointer == NULL)
						reserve(dist);
					if (_startpointer != NULL && _capacity < size() + dist)
					{
						reserve(_capacity * 2);
						if (_capacity < size() + dist)
							this->reserve(size() + dist);
					}
					if (position.base() != NULL && position.base() < _startpointer)
						position = _startpointer;
					else if (position.base() != NULL && position.base() > _endpointer)
						position = _endpointer;

					ft::vector<value_type>		vector_temp;
					vector_temp._startpointer	= _allocator.allocate(this->_capacity);
					vector_temp._capacity		= _capacity;
					vector_temp._endpointer		= vector_temp._startpointer;

					pointer		pos = vector_temp._startpointer + conserv;	// on recup la nouvelle position en cas de reallocation

					pointer		save_start = _startpointer;	// conserver le _start pour permettre le swap a la fin

					for ( ; vector_temp._endpointer != pos ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						vector_temp._endpointer++;
						_startpointer++;
					}
					for (size_type i = 0 ; i < dist ; i++) {
						vector_temp._allocator.construct(vector_temp._endpointer, *first++);
						vector_temp._endpointer++;
					}
					for ( ; _startpointer != _endpointer ; ) {
						vector_temp._allocator.construct(vector_temp._endpointer, *_startpointer);
						_startpointer++;
						vector_temp._endpointer++;
					}
					_startpointer = save_start;
					this->swap(vector_temp);
				}

				// =================
				// === PUSH_BACK ===
				// =================
				void push_back (const value_type& val)
				{
					if (_startpointer == NULL)
						this->reserve(1);
					if (size() >= _capacity)
						this->reserve(2 * size());
					if (size() < _capacity)
					{
						_endpointer++;
						_allocator.construct(_endpointer - 1, val);
					}
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
				void assign (size_type n, const value_type& val)	// FILL OVERLOAD
				{
					this->clear();
					if (n > _capacity)
					{
						_allocator.deallocate(_startpointer, _capacity);
						_startpointer = _allocator.allocate(n);
						_capacity = n;
						_endpointer = _startpointer;
						for (size_type i = 0 ; i < n ; i++) {
							_allocator.construct(_endpointer, val);
							_endpointer++;
						}
					}
					else
					{
						for (size_type i = 0 ; i < n ; i++) {
							_allocator.construct(_endpointer, val);
							_endpointer++;
						}
					}
				}
				template <class InputIterator>
				typename enable_if< !is_integral<InputIterator>::value, void>::type assign(InputIterator first, InputIterator last)	// RANGE OVERLOAD
				{
					this->clear();
					size_type	dist = std::distance(first, last);
					if (this->_capacity >= dist)
					{
						for ( ; first != last ; first++)
							this->push_back(*first);
					}
					else
					{
						_allocator.deallocate(_startpointer, _capacity);
						_startpointer = _allocator.allocate(dist);
						_endpointer = _startpointer;
						_capacity = dist;
						for ( ; first != last ; first++) {
							_allocator.construct(_endpointer, *first);
							_endpointer++;
						}
					}
				}

				// =================
				// ===== ERASE =====
				// =================
				iterator erase(iterator position)
				{
					pointer	pos	= position.base();
					_allocator.destroy(position.base());
					size_type	i = 0;
					if (pos == _endpointer - 1)
					{
						_allocator.destroy(pos);
						_endpointer -= 1;
						return (pos);
					}
					else if (pos != _endpointer)
					{
						for ( ; position.base() + i != _endpointer ; i++ ) {
							_allocator.construct(pos + i, *(position.base() + i + 1));
							_allocator.destroy(pos + i + 1);
						}
						_endpointer -= 1;
					}
					return (pos);
				}
				iterator erase(iterator first, iterator last)
				{
					pointer	pos	= first.base();
					_allocator.destroy(first.base());
					size_type	diff = std::distance(first, last);
					if (pos == _endpointer - 1)
					{
						_allocator.destroy(pos);
						_endpointer -= 1;
						return (pos);
					}
					else if (pos != _endpointer)
					{
						for (size_type i = 0 ; pos + i + diff < _endpointer ; i++ ) {
							_allocator.construct(pos + i, *(pos + i + diff));
							_allocator.destroy(pos + i + diff);
						}
						_endpointer -= diff;
					}
					return (pos);
				}

				// =================
				// ===== CLEAR =====
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
					if ( this != &x)
						this->assign(x.begin(), x.end());
					return (*this);
				}
	};
	// ====================
	// NON MEMBER FUNCTIONS
	// ====================
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

	// ====================
	// NON MEMBER OPERATORS
	// ====================
	
	// ==
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	// !=
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	// < et >
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
	}
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( rhs < lhs );
	}

	// <= et >=
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( !(rhs < lhs) );
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ( !(lhs < rhs) );
	}
}

#endif