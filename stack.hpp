/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:41 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/11 11:15:42 by epfennig         ###   ########.fr       */
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
				container_type		C;

		public:
				explicit stack (const container_type & ctnr = container_type()) : C(ctnr) {  }

				// Utilisation du container sous-jacent pour toutes les fonctions
				bool empty() const {
					return (C.empty());
				}

				size_type size() const {
					return (C.size());
				}

				void push (const value_type& val) {
					C.push_back(val);
				}

				value_type& top() {
					return (C.back());
				}

				const value_type& top() const {
					return (C.back());
				}

				void pop() {
					C.pop_back();
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
		return (lhs.C == rhs.C);
	}

	template <class Ts, class Containers>
	bool operator!= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.C != rhs.C);
	}

	template <class Ts, class Containers>
	bool operator<  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.C < rhs.C);
	}

	template <class Ts, class Containers>
	bool operator<= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.C <= rhs.C);
	}

	template <class Ts, class Containers>
	bool operator>  (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.C > rhs.C);
	}

	template <class Ts, class Containers>
	bool operator>= (const stack<Ts,Containers>& lhs, const stack<Ts,Containers>& rhs) {
		return (lhs.C >= rhs.C);
	}

}

#endif