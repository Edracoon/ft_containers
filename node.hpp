/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:28:48 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/18 18:50:31 by epfennig         ###   ########.fr       */
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

				~node() { }
				
				T				value;
			
				node*			parent;
				node*			right;
				node*			left;

				node*			NIL;

				bool			color;

				node*	uncle() {
					if (this->parent != NIL && this->parent->parent != NIL && this->parent->parent->left == *this)
						return (this->parent->parent->right);
					else if (this->parent != NIL && this->parent->parent != NIL && this->parent->parent->right == *this)
						return (this->parent->parent->left);
					return (NULL); 
				}

				
	};
	// template <class type1, class type2>
	// bool operator==(const node<type1>& lhs, const node<type2>& rhs) {
	// 	return (lhs.value == rhs.value);
	// }
	// template <class type1, class type2>
	// bool operator!=(const node<type1>& lhs, const node<type2>& rhs) {
	// 	std::cout << "hello123" << std::endl;
	// 	return (lhs.value != rhs.value);
	// }
}

#endif