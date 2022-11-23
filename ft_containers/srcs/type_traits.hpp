/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:39 by schuah            #+#    #+#             */
/*   Updated: 2022/11/22 14:25:50 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

/**
 * https://en.cppreference.com/w/cpp/types/enable_if
 * https://en.cppreference.com/w/cpp/types/integral_constant
 * https://en.cppreference.com/w/cpp/types/remove_cv
 * https://en.cppreference.com/w/cpp/types/is_integral
 * https://en.cppreference.com/w/cpp/types/is_same
 * https://stackoverflow.com/questions/43571962/how-is-stdis-integral-implemented
 * https://youtu.be/H-m23Vvzcug
 * https://youtu.be/W3pFxSBkeJ8
 */
namespace ft
{
	/**
	 * Used as a class template or function template parameter. Can be used as
	 * an additional function argument or as a return type as well
	 */
	template <bool B, class T = void>	struct enable_if {};
	template <class T>					struct enable_if<true, T> { typedef T type; };

	/* Wraps a static constant of specified type and a base class for type traits */
	template <class T, T v> struct integral_constant
	{
		static const bool value = v;

		operator T() const { return (value); }
		T operator()(void) const { return (value); }
	};

	/* Represents values false and true as types */
	template <bool B> struct bool_constant : public integral_constant<bool, B>	{};
	struct true_type : public bool_constant<true> 								{};
	struct false_type : public bool_constant<false> 							{};

	/* Removes the topmost const, or the topmost volatile, or both, if present */
	template <class T> struct remove_cv						{ typedef T type; };
	template <class T> struct remove_cv<const T>			{ typedef T type; };
	template <class T> struct remove_cv<volatile T>			{ typedef T type; };
	template <class T> struct remove_cv<const volatile T>	{ typedef T type; };

	/**
	 * Specializations of integral_constant. Provides the member constant value
	 * which is equal to true, if it is the type bool, char, char16_t, char32_t,
	 * wchar_t, short, int, long, or any implementation-defined extended integer
	 * types, including any signed, unsigned, and cv-qualified variants.
	 * Otherwise, value is equal to false
	 */
	template <class> struct is_integral_base				: public false_type {};
	template <> struct is_integral_base<bool> 				: public true_type {};
	template <> struct is_integral_base<char>				: public true_type {};
	template <> struct is_integral_base<unsigned char>		: public true_type {};
	template <> struct is_integral_base<char16_t>			: public true_type {};
	template <> struct is_integral_base<char32_t>			: public true_type {};
	template <> struct is_integral_base<wchar_t>			: public true_type {};
	template <> struct is_integral_base<short>				: public true_type {};
	template <> struct is_integral_base<unsigned short>		: public true_type {};
	template <> struct is_integral_base<int>				: public true_type {};
	template <> struct is_integral_base<unsigned int>		: public true_type {};
	template <> struct is_integral_base<long>				: public true_type {};
	template <> struct is_integral_base<unsigned long>		: public true_type {};
	template <class T> struct is_integral : is_integral_base<typename remove_cv<T>::type> {};

	/**
	 * Checks whether class T and class U are the same type. Provides the member
	 * constant value equal to true, otherwise value is false
	 */
	template <class T, class U>	struct is_same : public false_type {};
	template <class T>			struct is_same<T, T> : public true_type {};
}

#endif
