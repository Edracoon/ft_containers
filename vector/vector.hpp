#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include <iterator>	// std::distance
# include <tgmath.h>
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
			
				typedef size_t														size_type;
			
				// typedef pour les iterators
				typedef ft::random_access_iterator<pointer>								iterator;
				typedef ft::random_access_iterator<const_pointer>						const_iterator;
				typedef ft::reverse_iterator<iterator>									reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;

				typedef	typename allocator_type::difference_type					difference_type;
				
		protected:
					pointer			_startpointer;	// first elem
					pointer			_endpointer;	// last elem + 1
					allocator_type	_allocator;		// allocateur selon son type pour utiliser ses fonctions
					size_type		_capacity;		// 
		public:
				explicit
				vector (const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_startpointer		= NULL;
					this->_endpointer		= NULL;
					this->_capacity			= 0;
				}
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
				template <class InputIterator>
				vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
							typename enable_if< !is_integral<InputIterator>::value, int>::type = 0 )
				{
					size_type dist = std::distance(first, last);
					_allocator			= alloc;
					_startpointer		= _allocator.allocate(dist);
					_endpointer			= _startpointer + dist;
					_capacity			= dist;
					this->assign(first, last);
				}
				vector (const vector& x) : _allocator(x._allocator) // copy
				{
					_startpointer		= _allocator.allocate(x.size());
					_endpointer			= _startpointer + x.size();
					_capacity			= x.size();
					*this = x;
				}
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
					// std::cout << position.base() << std::endl;
					if (position.base() == _endpointer)
						this->push_back(val);
					if (position.base() == NULL)
						return (position);
					if (this->_startpointer == NULL)
						this->reserve(1);

					std::cout << *position << std::endl;
					std::cout << "position - start = " << std::distance(begin(), position) << std::endl;

					ft::vector<value_type>	temp;
					temp.assign(this->begin(), position);
					temp.push_back(val);

					// if (position.base() == NULL)
					// {
					// 	reserve(1);
					// 	position = _startpointer;
					// }
					// if (position.base() == _endpointer)
					// {
					// 	if (_capacity == size())
					// 		this->reserve(_capacity * 2);
					// 	_endpointer++;
					// 	this->_allocator.construct(_endpointer - 1, val);
					// 	return (position);
					// }
					// this->push_back(back());
					// size_type i = 0;
					// for ( ; _endpointer - i != position.base() ; i++ )
					// {
					// 	this->_allocator.destroy(_endpointer - i );
					// 	this->_allocator.construct(_endpointer - i, *(_endpointer - i - 1));
					// }
					// this->_allocator.destroy(_endpointer - i);
					// this->_allocator.construct(_endpointer - i, val);
					return (position);
				}
				void insert (iterator position, size_type n, const value_type& val) 		// FILL
				{
					for (size_type range = 0 ; range < n ; range++ )
					{
						//this->insert(position, val);
						//position++;
						this->push_back(back());
						size_type i = 0;
						for ( ; _endpointer - i != position.base() ; i++ )
						{
							this->_allocator.destroy(_endpointer - i );
							this->_allocator.construct(_endpointer - i, *(_endpointer - i - 1));
						}
						this->_allocator.destroy(_endpointer - i + range);
						this->_allocator.construct(_endpointer - i + range, val);
					}
				}
				template <class InputIterator>
				typename enable_if< !is_integral<InputIterator>::value, void>::type insert (iterator position, InputIterator first, InputIterator last)	// RANGE
				{
					size_type n = std::distance(first, last);
					for (size_type range = 0 ; range < n ; range++ )
					{
						//this->insert(position, first[range]);
						//position++;
						this->push_back(*(_endpointer - 1));
						size_type i = 0;
						for ( ; _endpointer - i != position.base() ; i++ )
						{
							this->_allocator.destroy(_endpointer - i );
							this->_allocator.construct(_endpointer - i, *(_endpointer - i - 1));
						}
						this->_allocator.destroy(_endpointer - i + range);
						this->_allocator.construct(_endpointer - i + range, *first);
						first++;
					}
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
					this->reserve(n);
					this->insert(_startpointer, n, val);
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
		if (lhs.size() != rhs.size()) return (false);	// check size first
		return (equal(lhs.begin(), lhs.end(), rhs.begin()));
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
