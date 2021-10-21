/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:15:47 by epfennig          #+#    #+#             */
/*   Updated: 2021/10/21 13:44:23 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template < class T, T v >
	struct integral_constant
	{
		static const T value = v;

		typedef T						value_type;
		typedef integral_constant<T,v>	type;

		inline operator T() { return v; }
	};

	typedef	integral_constant< bool, false >	false_type;
	typedef	integral_constant< bool, true >		true_type;

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T>
	struct is_integral : false_type {} ;
	template <>
	struct is_integral<bool> : true_type {} ;
	template <>
	struct is_integral<char> : true_type {} ;
	template <>
	struct is_integral<char16_t> : true_type {} ;
	template <>
	struct is_integral<char32_t> : true_type {} ;
	template <>
	struct is_integral<wchar_t> : true_type {} ;
	template <>
	struct is_integral<short> : true_type {} ;
	template <>
	struct is_integral<int> : true_type {} ;
	template <>
	struct is_integral<long> : true_type {} ;
	template <>
	struct is_integral<long long> : true_type {} ;

	// equal
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	// lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
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

	template<typename T, typename U>
	struct is_same			// Rentre dedans si c'est un type different
	{
		static const bool value = false; 
	};
	
	template<typename T>
	struct is_same<T, T>		// Rentre dedans si c'est le même type
	{ 
		static const bool value = true; 
	};

	template<bool>
	struct static_assert_ft
	{
		
	};

	template<>
	struct static_assert_ft<true>	// Si c'est true la fonction existe et ca compile
	{
		static void func() { /* ne sert a rien */ }
	};
}

#endif