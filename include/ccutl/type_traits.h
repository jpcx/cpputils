#ifndef CPPUTILS_CCUTL_TYPE_TRAITS_H_
#define CPPUTILS_CCUTL_TYPE_TRAITS_H_

/*
	Copyright (c) 2019 Justin Collier
	This program is free software: you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free Software
	foundation, either version 3 of the License, or (at your option) any later
	version.
	This program is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
	details.
	You should have received a copy of the GNU General Public License along with
	this program. If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file ccutl/type_traits.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type traits utilities.
 * @version 0.1.1
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/type_traits.h"

#include <iterator>
#include <type_traits>

namespace ccutl {

namespace core {

/*                        ccutl::core::remove_function                        */

template <typename T>
struct remove_function {
	typedef T type;
};

template <typename T, typename... Ts>
struct remove_function<T(Ts...)> {
	typedef T type;
};

/*                       ccutl::core::remove_everything                       */

template <typename T>
struct remove_everything {
	typedef T type;
};

template <typename T>
struct remove_everything<T const> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T volatile> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T volatile const> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T*> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T&> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T&&> {
	typedef typename remove_everything<T>::type type;
};

template <typename T, typename... Ts>
struct remove_everything<T(Ts...)> {
	typedef typename remove_everything<T>::type type;
};

template <typename T, std::size_t Tsz>
struct remove_everything<T[Tsz]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T, std::size_t Tsz>
struct remove_everything<T const[Tsz]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T, std::size_t Tsz>
struct remove_everything<T volatile[Tsz]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T, std::size_t Tsz>
struct remove_everything<T volatile const[Tsz]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T[]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T const[]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T volatile[]> {
	typedef typename remove_everything<T>::type type;
};

template <typename T>
struct remove_everything<T volatile const[]> {
	typedef typename remove_everything<T>::type type;
};

namespace internal {

/*                   ccutl::core::internal::apply_pointers_                   */

template <typename T, typename TPtrs>
struct apply_pointers_ {
	typedef T type;
};

template <typename T, typename TPtrs>
struct apply_pointers_<T, TPtrs*> {
	typedef typename apply_pointers_<T*, TPtrs>::type type;
};

/*              ccutl::core::internal::apply_function_signature_              */

template <typename T, typename TFn, typename... Ts>
struct apply_function_signature_ {
	typedef T type;
};

template <typename T, typename TFn, typename... Ts>
struct apply_function_signature_<T, TFn(Ts...)> {
	typedef typename apply_function_signature_<T(Ts...), TFn>::type type;
};

}	// namespace internal

/*                          ccutl::core::decay_deep                          */

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep {
	typedef internal::apply_function_signature_t_<
			internal::apply_pointers_t_<T, TPtrs>, TFSig>* type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T const, TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile, TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile const, TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T*, TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs*, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T&, TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T&&, TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig, typename... Ts>
struct decay_deep<T(Ts...), TPtrs, TFSig> {
	typedef typename decay_deep<T, TPtrs, TFSig(Ts...)>::type type;
};

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T[Tsz], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T const[Tsz], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T volatile[Tsz], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T volatile const[Tsz], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T[], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T const[], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile[], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile const[], TPtrs, TFSig> {
	typedef typename decay_deep<T*, TPtrs, TFSig>::type type;
};

/*                     ccutl::core::function_return_type                     */

template <typename Tf, typename... TArgs>
struct function_return_type {
	typedef void type;
};

template <typename Tf, typename... TArgs>
struct function_return_type<Tf(TArgs...)> {
	typedef Tf type;
};

/*                       ccutl::core::n_function_params                       */

template <typename Tf, size_t NParams>
struct n_function_params {
	constexpr static size_t value = NParams;
};

template <typename Tf, typename T, size_t NParams>
struct n_function_params<Tf(T), NParams> {
	constexpr static size_t value = n_function_params<Tf, NParams + 1>::value;
};

template <typename Tf, typename T, size_t NParams, typename... Ts>
struct n_function_params<Tf(T, Ts...), NParams> {
	constexpr static size_t value =
			n_function_params<Tf(Ts...), NParams + 1>::value;
};

/*                           ccutl::core::are_true */

template <typename T>
struct are_true<T> : std::integral_constant<bool, T::value> {};

template <typename T, typename... Ts>
struct are_true<T, Ts...>
		: std::integral_constant<bool, T::value && are_true<Ts...>::value> {};

/*                          ccutl::core::is_iterable                          */

template <typename T, typename>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
																	decltype(std::declval<T>().end())>>
		: std::true_type {};

/*                      ccutl::core::is_reverse_iterable                      */

template <typename T, typename>
struct is_reverse_iterable : std::false_type {};

/*                       ccutl::core::is_const_iterable                       */

template <typename T, typename>
struct is_const_iterable : std::false_type {};

template <typename T>
struct is_const_iterable<T, std::void_t<decltype(std::declval<T>().cbegin()),
																				decltype(std::declval<T>().cend())>>
		: std::true_type {};

/*                   ccutl::core::is_const_reverse_iterable                   */

template <typename T, typename>
struct is_const_reverse_iterable : std::false_type {};

template <typename T>
struct is_const_reverse_iterable<
		T, std::void_t<decltype(std::declval<T>().crbegin()),
									 decltype(std::declval<T>().crend())>> : std::true_type {};

/*                        ccutl::core::is_streamable_to                       */

template <typename TStream, typename T, typename>
struct is_streamable_to : std::false_type {};

template <typename TStream, typename T>
struct is_streamable_to<
		TStream, T,
		std::void_t<decltype(std::declval<TStream>() << std::declval<T>())>>
		: std::true_type {};

}	// namespace core

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_TYPE_TRAITS_H_
