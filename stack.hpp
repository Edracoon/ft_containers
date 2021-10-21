/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:41 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 13:44:27 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <memory>
# include "iterator.hpp"
# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public:
				typedef	Container								container_type;
				typedef	typename Container::value_type			value_type;
				typedef	typename Container::size_type			size_type;
				typedef	typename Container::reference			reference;
				typedef typename Container::const_reference		const_reference;

		protected:
				container_type		c;

		public:
				explicit stack (const container_type & ctnr = container_type()) : c(ctnr) {
					ft::static_assert_ft<ft::is_same<T, typename container_type::value_type >::value>::func();	// Si la fonction existe c'est que les deux sont du meme type
				}

				// Utilisation du container sous-jacent pour toutes les fonctions
				bool empty() const {
					return (c.empty());
				}

				size_type size() const {
					return (c.size());
				}

				void push (const value_type& val) {
					c.push_back(val);
				}

				value_type& top() {
					return (c.back());
				}

				const value_type& top() const {
					return (c.back());
				}

				void pop() {
					c.pop_back();
				}

				// Utilisation de friend permet l'utilisation des variables private ou protected en dehors de la definition de la classe
				template <class Ts, class Containers>
				friend bool operator== (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

				template <class Ts, class Containers>
				friend bool operator!= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

				template <class Ts, class Containers>
				friend bool operator<  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

				template <class Ts, class Containers>
				friend bool operator<= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

				template <class Ts, class Containers>
				friend bool operator>  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);

				template <class Ts, class Containers>
				friend bool operator>= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs);
	};

	template <class Ts, class Containers>
	bool operator== (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.c == rhs.c);
	}

	template <class Ts, class Containers>
	bool operator!= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.c != rhs.c);
	}

	template <class Ts, class Containers>
	bool operator<  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.c < rhs.c);
	}

	template <class Ts, class Containers>
	bool operator<= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.c <= rhs.c);
	}

	template <class Ts, class Containers>
	bool operator>  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.c > rhs.c);
	}

	template <class Ts, class Containers>
	bool operator>= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.c >= rhs.c);
	}

}

#endif