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
				// typedef ft::random_access_iterator<const T>			const_iterator;		// only iterate
				typedef ft::reverse_iterator<iterator>				reverse_iterator;	// 
				// typedef ft::const_reverse_iterator<const_iterator>	const_reverse_iterator;
				
		protected:
					pointer			_startpointer;	// first elem
					pointer			_endpointer;	// last elem
					pointer			_endmaxpointer;	// double size in case of reallocation
					allocator_type	_allocator;		// allocateur selon son type pour utiliser ses fonctions
					size_type		_capacity;		// 
		public:
				explicit	vector (const allocator_type& alloc = allocator_type())
				{
					this->_allocator		= alloc;
					this->_startpointer		= NULL;
					this->_endpointer		= NULL;
					this->_endmaxpointer	= NULL;
					this->_capacity			= 0;
				}
				explicit	vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
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
					*this = x;	// operator =
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
				reverse_iterator rbegin( void ) {
					return (_endpointer - 1);	// last elem
				}
				reverse_iterator rend( void ) {
					return (_startpointer - 1);	// before the first elem to simulate a end()
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
					allocator_type	temp_alloc	= x._allocator;	// swap allocator
					x._allocator				= this->_allocator;
					this->_allocator			= temp_alloc;

					pointer			temp		= x._startpointer;
					x._startpointer				= this->_startpointer;
					this->_startpointer			= temp;

					temp						= x._endpointer;
					x._endpointer				= this->_endpointer;
					this->_endpointer			= temp;

					temp						= x._endmaxpointer;
					x._endmaxpointer			= this->_endmaxpointer;
					this->_endmaxpointer		= temp;

					size_type temp_s			= x._capacity;
					x._capacity					= this->_capacity;
					this->_capacity				= temp_s;
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

				// ==============
				// === INSERT ===
				// ==============
				iterator insert (iterator position, const value_type& val)					// SINGLE ELEMENT
				{
					this->push_back(*(_endpointer - 1));
					size_type i = 0;
					for ( ; _endpointer - i != position ; i++ )
					{
						this->_allocator.destroy(_endpointer - i - 2);
						this->_allocator.construct(_endpointer - i - 2, *(_endpointer - i - 3));
					}
					this->_allocator.destroy(_endpointer - i - 2);
					this->_allocator.construct(_endpointer - i - 2, val);
					return (position);
				}
				void insert (iterator position, size_type n, const value_type& val) 		// FILL
				{
					(void)position; (void)n; (void)val;
				}
				template <class InputIterator>
				void insert (iterator position, InputIterator first, InputIterator last)	// RANGE
				{
					(void)position; (void)first; (void)last;
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
				template <class InputIterator>						// RANGE VERSION ENABLE_IF ?
				void assign (InputIterator first, InputIterator last)
				{
					this->clear();
					for ( ; first != last ; first++)
						this->push_back(*first);
					this->push_back(*first);
				}

				// =================
				// ===== ERASE =====
				// =================
				iterator erase(iterator position)
				{
					pointer	pos	= &(*(position));
					_allocator.destroy(&(*(position)));
					size_type	i = 0;
					if (pos == _endpointer - 1)
					{
						_allocator.destroy(pos);
						_endpointer -= 1;
						return (pos);
					}
					else if (pos != _endpointer)
					{
						for ( ; i + *position < this->size() ; i++ ) {
							_allocator.construct(pos + i, *(&(*position) + i + 1));
							_allocator.destroy(pos + i + 1);
						}
						_endpointer -= 1;
					}
					return (pos);
				}
				iterator erase(iterator first, iterator last)
				{
					pointer	pos	= &(*(first));
					_allocator.destroy(&(*(first)));
					size_type	diff = &(*(last)) - &(*(first));
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
					this->_allocator.deallocate(this->_startpointer, this->_capacity);
					_startpointer	= this->_allocator.allocate(x.size());
					size_type	n	= 0;
					_endpointer		= _startpointer;
					_endmaxpointer	= _endpointer + x.size();
					_capacity		= x.size();
					for (size_type i = x.size() ; i > 0 ; i--)
					{
						_allocator.construct(_endpointer, x[n]);
						_endpointer++;
						n++;
					}
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
	
	// == et !=
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size()) return (false);	// check size first

		typename ft::vector<T>::iterator	it		= lhs.begin();
		typename ft::vector<T>::iterator	ite		= lhs.end();
		typename ft::vector<T>::iterator	it2		= rhs.begin();
		typename ft::vector<T>::iterator	ite2	= rhs.end();

		while ( it != ite || it2 != ite2 )
		{
			if (*it != *it2) return (false);	// check every value
			it++;
			it2++;
		}
		return (true);
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));	// operator==
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return (false);
			else if (*first1 < *first2)
				return (true);
			++first1;
			++first2;
		}
		return ( first2 != last2 );
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
