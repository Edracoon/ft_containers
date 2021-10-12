/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_map_reverse_iterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:35:09 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/12 14:36:02 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MAP_REVERSE_ITERATOR_HPP
# define MAP_REVERSE_ITERATOR_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft
{

	// ================================
	// ===== MAP_REVERSE_ITERATOR =====
	// ================================
	template< class Iterator >
	class map_reverse_iterator
	{
 		public:
				// typedef macro
				typedef Iterator								iterator_type;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::iterator_category	iterator_category;
		private:
				typedef	typename Iterator::pair					pair;

		protected:
				iterator_type		_base_it;
		public:
				map_reverse_iterator() { _base_it = NULL; }													// default
				explicit map_reverse_iterator (iterator_type it) : _base_it(it) { }							// param
				template <class Iter>
				map_reverse_iterator (const map_reverse_iterator<Iter>& rev_it) : _base_it(rev_it.base()) { }	// copy
				~map_reverse_iterator( void ) {  }

				iterator_type base() const {
					return (this->_base_it);
				}

				pair& operator*() const {
					iterator_type	cpy = _base_it;
					return (*(--cpy));
				}
				pair* operator->() const {
					return &(operator*());
				}

				// ++ et --
				map_reverse_iterator& operator++() {
					--_base_it;
					return (*this);
				}
				map_reverse_iterator operator++(int) {
					map_reverse_iterator temp = *this;
					++(*this);
					return temp;
				}
				map_reverse_iterator& operator--() {
					++_base_it;
					return (*this);
				} 
				map_reverse_iterator operator--(int) {
					map_reverse_iterator temp = *this;
					--(*this);
					return temp;
				}

				// + et -
				map_reverse_iterator operator+ (difference_type n) const {
					return map_reverse_iterator(_base_it - n);
				}
				map_reverse_iterator operator- (difference_type n) const {
					return map_reverse_iterator(_base_it + n);
				}

				// -= et +=
				map_reverse_iterator& operator-= (difference_type n) {
					this->_base_it += n;
					return (*this);
				}
				map_reverse_iterator& operator+= (difference_type n) {
					this->_base_it -= n;
					return (*this);
				}

				// []
				reference operator[] (difference_type n) const {
					return (base()[-n-1]);
				}
	};

	// OUT OF CLASS OPERATORS
	template <class Iterator>
	map_reverse_iterator<Iterator> operator+ ( typename map_reverse_iterator<Iterator>::difference_type n,
												const map_reverse_iterator<Iterator>& rev_it) {
		return (rev_it + n);
	}
	template <class Iterator1, class Iterator2>
	typename map_reverse_iterator<Iterator1>::difference_type operator- (
					const map_reverse_iterator<Iterator1>& lhs,
						const map_reverse_iterator<Iterator2>& rhs) {
		return (rhs.base() - lhs.base());
	}

	// OUT OF CLASS COMPARISON
	template <class Iterator1, class Iterator2>
	bool operator== (const map_reverse_iterator<Iterator1>& lhs,
						const map_reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!= (const map_reverse_iterator<Iterator1>& lhs,
						const map_reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<  (const map_reverse_iterator<Iterator1>& lhs,
 						const map_reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>  (const map_reverse_iterator<Iterator1>& lhs,
						const map_reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<= (const map_reverse_iterator<Iterator1>& lhs,
						const map_reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>= (const map_reverse_iterator<Iterator1>& lhs,
						const map_reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	}
}

#endif