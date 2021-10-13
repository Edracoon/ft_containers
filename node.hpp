/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:28:48 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/13 15:38:44 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft {

	template <class T>
	class	node
	{
		public:	// faire une node sentinelle au lieu d'un last 
				node(const T& Value) : value(Value), parent(NULL), right(NULL), left(NULL) { }
				node(const node& rhs)
					: value(rhs.value), parent(rhs.parent), right(rhs.right), left(rhs.left) { }
				template <typename type>
				node(const node<type>& rhs)
					: value(rhs.value), parent(rhs.parent), right(rhs.right), left(rhs.left) { }
				T				value;
				node*			parent;
				node*			right;
				node*			left;

				node*			sentinelle; // si les fils de la sentinelle sont NULL : on est a end
				
				T&	operator*() {
					return (this->value);
				}
	};
}

#endif