#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	// =================================
	// ==== BIDIRECTIONAL ITERATOR =====
	// =================================
	template< typename T >
	class bidirectional_iterator
	{
		private:
				// recup traits macro
				// typedef iterator_traits<T> it;
		public:
				// typedef macro	// T = PAIR
				typedef T											value_type;
				typedef T*											pointer;
				typedef T&											reference;
				typedef size_t										difference_type;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef typename value_type::pair					pair;
				typedef	pair*										pair_pointer;
		protected:
				pointer	_pointer;
				pointer	_last;
		private:
			//	node<T>		*node;	// ITERATOR IS NOW POINTING TO A PAIR HAHAAHAHAHA
		public:
				bidirectional_iterator( void ) { _pointer = NULL; }											 // default
				bidirectional_iterator( pointer Pointer, pointer Last = NULL )
				{
					_pointer	= Pointer;
					_last		= Last;
				}
				template <class Iter>
				bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _pointer(rhs.base_node()) { } // copy
				~bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pair_pointer base(void) const
				{
					return pair_pointer(&(_pointer->value));
				}
				pointer base_node(void) const
				{
					return pointer(&(this->_pointer));
				}

				// assignation
				template <class Iterator>
				bidirectional_iterator& operator= (const bidirectional_iterator<Iterator>& rhs) {
					this->_pointer = rhs.base();
					return (*this);
				}

				// *
				pair operator* () const {
					return (_pointer->value);
				}

				// ->
				pair* operator->() const {
					return &(_pointer->value);
				}

				// ++
				bidirectional_iterator&	operator++() {
					if (!_pointer)
						return *this;
					// std::cout << "coucou non const : " << _pointer->value.first << " - " <<  _pointer->value.second << std::endl;
					if (_pointer != NULL && _pointer->right != NULL)
					{
						_pointer = _pointer->right;
						while (_pointer->left != NULL)
							_pointer = _pointer->left;
					}
					else if (_pointer->parent && _pointer == _pointer->parent->left) {
						_pointer = _pointer->parent;
					}
					else
					{
						while (_pointer->parent != NULL && _pointer == _pointer->parent->right)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				bidirectional_iterator	operator++(int) {
					bidirectional_iterator	temp = *this;
					operator++();
					// std::cout << "coucou non const : " << (*temp).first << " - " << (*temp).second << std::endl;
					return temp;
				}

				// --
				bidirectional_iterator&	operator--() {
					if (_pointer == NULL)
					{
						_pointer = _last;
						return *this;
					}
					if (_pointer->left != NULL)
					{
						_pointer = _pointer->left;
						while (_pointer->right != NULL)
							_pointer = _pointer->right;
					}
					else {
						while (_pointer->parent != NULL && _pointer == _pointer->parent->left)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				bidirectional_iterator	operator--(int) {
					bidirectional_iterator	temp = *this;
					operator--();
					return temp;
				}
	};

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::bidirectional_iterator<Iterator1>& lhs,	
				const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::bidirectional_iterator<Iterator1>& lhs,
					const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	
	// =======================================
	// ==== CONST BIDIRECTIONAL ITERATOR =====
	// =======================================
	template< typename T >
	class const_bidirectional_iterator
	{
		private:
				// recup traits macro
				//typedef iterator_traits<T> it;
		public:
				// typedef macro
				typedef const T										value_type;
				typedef value_type*									pointer;
				typedef value_type&									reference;
				typedef size_t										difference_type;
				typedef std::bidirectional_iterator_tag				iterator_category;
				typedef const typename value_type::pair				pair;
				typedef	pair*										pair_pointer;
		protected:
				pointer	_pointer;
				pointer	_last;
		public:
				const_bidirectional_iterator( void ) { _pointer = NULL; }											 // default
				const_bidirectional_iterator( pointer Pointer, pointer Last = NULL )
				{
					_pointer	= Pointer;
					_last		= Last;
				}
				template <class Iter>
				const_bidirectional_iterator (const bidirectional_iterator<Iter> & rhs) : _pointer(rhs.base_node()) { } // copy
				~const_bidirectional_iterator( void ) {  }														 // destruct

				// recup le pointer de l'iterator (conversion plus simple que &(*(iterator)))
				pair_pointer base(void) const
				{
					return pair_pointer(&(_pointer->value));
				}
				pointer base_node(void) const
				{
					return pointer(&(this->_pointer));
				}

				// assignation
				template <class Iterator>
				const_bidirectional_iterator& operator= (const const_bidirectional_iterator<Iterator>& rhs) {
					this->_pointer = rhs.base();
					return (*this);
				}

				// *
				pair operator* () const {
					return (_pointer->value);
				}

				// ->
				pair* operator->() const {
					return &(_pointer->value);
				}

				// ++
				const_bidirectional_iterator&	operator++() {
					if (_pointer == NULL)
						return *this;
					// std::cout << "coucou const : " << _pointer->value.first << " - " <<  _pointer->value.second << std::endl;
					if (_pointer != NULL && _pointer->right != NULL)
					{
						_pointer = _pointer->right;
						while (_pointer != NULL && _pointer->left != NULL)
							_pointer = _pointer->left;
					}
					else if (_pointer->parent && _pointer == _pointer->parent->left) {
						_pointer = _pointer->parent;
					}
					else
					{
						while (_pointer != NULL && _pointer->parent != NULL && _pointer == _pointer->parent->right)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				const_bidirectional_iterator	operator++(int) {
					const_bidirectional_iterator	temp = *this;
					operator++();
					// std::cout << "coucou const : " << (*temp).first << " - " << (*temp).second << std::endl;
					return temp;
				}

				// --
				const_bidirectional_iterator&	operator--() {
					if (_pointer == NULL)
					{
						_pointer = _last;
						return *this;
					}
					if (_pointer->left != NULL)
					{
						_pointer = _pointer->left;
						while (_pointer->right != NULL)
							_pointer = _pointer->right;
					}
					else {
						while (_pointer->parent != NULL && _pointer == _pointer->parent->left)
							_pointer = _pointer->parent;
						_pointer = _pointer->parent;
					}
					return *this;
				}
				const_bidirectional_iterator	operator--(int) {
					const_bidirectional_iterator	temp = *this;
					operator--();
					return temp;
				}
	};

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::const_bidirectional_iterator<Iterator1>& lhs,	
				const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::bidirectional_iterator<Iterator1>& lhs,	
				const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator== (const ft::const_bidirectional_iterator<Iterator1>& lhs,	
				const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	// OPERATOR !=
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::const_bidirectional_iterator<Iterator1>& lhs,
					const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::bidirectional_iterator<Iterator1>& lhs,
					const ft::const_bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
	template <class Iterator1, class Iterator2>
	bool operator!= (const ft::const_bidirectional_iterator<Iterator1>& lhs,
					const ft::bidirectional_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}
}

#endif