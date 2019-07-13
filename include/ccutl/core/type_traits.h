#ifndef CPPUTILS_CCUTL_CORE_TYPE_TRAITS_H_
#define CPPUTILS_CCUTL_CORE_TYPE_TRAITS_H_

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
 * @file ccutl/core/type_traits.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type traits utilities.
 * @version 0.1.1
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <iostream>
#include <type_traits>

namespace ccutl {

namespace core {

/*                        ccutl::core::remove_function                        */

template <typename T>
struct remove_function;

template <typename T, typename... Ts>
struct remove_function<T(Ts...)>;

/*                       ccutl::core::remove_everything                       */

template <typename T>
struct remove_everything;

template <typename T>
struct remove_everything<T const>;

template <typename T>
struct remove_everything<T volatile>;

template <typename T>
struct remove_everything<T volatile const>;

template <typename T>
struct remove_everything<T*>;

template <typename T>
struct remove_everything<T&>;

template <typename T>
struct remove_everything<T&&>;

template <typename T, typename... Ts>
struct remove_everything<T(Ts...)>;

template <typename T, std::size_t Tsz>
struct remove_everything<T[Tsz]>;

template <typename T, std::size_t Tsz>
struct remove_everything<T const[Tsz]>;

template <typename T, std::size_t Tsz>
struct remove_everything<T volatile[Tsz]>;

template <typename T, std::size_t Tsz>
struct remove_everything<T volatile const[Tsz]>;

template <typename T>
struct remove_everything<T[]>;

template <typename T>
struct remove_everything<T const[]>;

template <typename T>
struct remove_everything<T volatile[]>;

template <typename T>
struct remove_everything<T volatile const[]>;

namespace internal {

/*                   ccutl::core::internal::apply_pointers_                   */

template <typename T, typename TPtrs>
struct apply_pointers_;

template <typename T, typename TPtrs>
struct apply_pointers_<T, TPtrs*>;

/*                  ccutl::core::internal::apply_pointers_t_                  */

template <typename T, typename TPtrs>
using apply_pointers_t_ = typename apply_pointers_<T, TPtrs>::type;

/*              ccutl::core::internal::apply_function_signature_              */

template <typename T, typename TFn, typename... Ts>
struct apply_function_signature_;

template <typename T, typename TFn, typename... Ts>
struct apply_function_signature_<T, TFn(Ts...)>;

/*             ccutl::core::internal::apply_function_signature_t_             */

template <typename T, typename TFn>
using apply_function_signature_t_ =
		typename apply_function_signature_<T, TFn>::type;

}	// namespace internal

/*                          ccutl::core::decay_deep                          */

template <typename T, typename TPtrs = void, typename TFSig = void>
struct decay_deep;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T const, TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile, TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile const, TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T*, TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T&, TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T&&, TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig, typename... Ts>
struct decay_deep<T(Ts...), TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T[Tsz], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T const[Tsz], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T volatile[Tsz], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig, std::size_t Tsz>
struct decay_deep<T volatile const[Tsz], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T[], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T const[], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile[], TPtrs, TFSig>;

template <typename T, typename TPtrs, typename TFSig>
struct decay_deep<T volatile const[], TPtrs, TFSig>;

/*                     ccutl::core::function_return_type                     */

template <typename Tf, typename... TArgs>
struct function_return_type;

template <typename Tf, typename... TArgs>
struct function_return_type<Tf(TArgs...)>;

/*                       ccutl::core::n_function_params                       */

template <typename Tf, size_t NParams = 0>
struct n_function_params;

template <typename Tf, typename T, size_t NParams>
struct n_function_params<Tf(T), NParams>;

template <typename Tf, typename T, size_t NParams, typename... Ts>
struct n_function_params<Tf(T, Ts...), NParams>;

/*                           ccutl::core::are_true                           */

template <typename...>
struct are_true;

template <typename T>
struct are_true<T>;

template <typename T, typename... Ts>
struct are_true<T, Ts...>;

/*                          ccutl::core::is_iterable                          */

template <typename T, typename = void>
struct is_iterable;

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
																	decltype(std::declval<T>().end())>>;

/*                      ccutl::core::is_reverse_iterable                      */

template <typename T, typename = void>
struct is_reverse_iterable;

template <typename T>
struct is_reverse_iterable<T, std::void_t<decltype(std::declval<T>().rbegin()),
																					decltype(std::declval<T>().rend())>>;

/*                       ccutl::core::is_const_iterable                       */

template <typename T, typename = void>
struct is_const_iterable;

template <typename T>
struct is_const_iterable<T, std::void_t<decltype(std::declval<T>().cbegin()),
																				decltype(std::declval<T>().cend())>>;

/*                   ccutl::core::is_const_reverse_iterable                   */

template <typename T, typename = void>
struct is_const_reverse_iterable;

template <typename T>
struct is_const_reverse_iterable<
		T, std::void_t<decltype(std::declval<T>().crbegin()),
									 decltype(std::declval<T>().crend())>>;

/*                       ccutl::core::is_streamable_to                        */

template <typename TStream, typename T, typename = void>
struct is_streamable_to;

template <typename TStream, typename T>
struct is_streamable_to<
		TStream, T,
		std::void_t<decltype(std::declval<TStream>() << std::declval<T>())>>;

}	// namespace core

/*                             ccutl::are_true_v */

template <typename... Ts>
constexpr bool are_true_v = core::are_true<Ts...>::value;

/*                           ccutl::are_iterable_v                           */

template <typename... Ts>
constexpr bool are_iterable_v =
		are_true_v<std::integral_constant<bool, core::is_iterable<Ts>::value>...>;

/*                       ccutl::are_reverse_iterable_v                       */

template <typename... Ts>
constexpr bool are_reverse_iterable_v = are_true_v<
		std::integral_constant<bool, core::is_reverse_iterable<Ts>::value>...>;

/*                        ccutl::are_const_iterable_v                        */

template <typename... Ts>
constexpr bool are_const_iterable_v = are_true_v<
		std::integral_constant<bool, core::is_const_iterable<Ts>::value>...>;

/*                    ccutl::are_const_reverse_iterable_v                    */

template <typename... Ts>
constexpr bool are_const_reverse_iterable_v = are_true_v<std::integral_constant<
		bool, core::is_const_reverse_iterable<Ts>::value>...>;

/*                       ccutl::core::are_streamable_to                       */

template <typename TStream, typename... Ts>
constexpr bool are_streamable_to_v = are_true_v<std::integral_constant<
		bool, core::is_streamable_to<TStream, Ts>::value>...>;

/*                          ccutl::are_arithmetic_v                          */

template <typename... Ts>
constexpr bool are_arithmetic_v =
		are_true_v<std::integral_constant<bool, std::is_arithmetic_v<Ts>>...>;

/*                           ccutl::are_integral_v                           */

template <typename... Ts>
constexpr bool are_integral_v =
		are_true_v<std::integral_constant<bool, std::is_integral_v<Ts>>...>;

/*                        ccutl::are_floating_point_v                        */

template <typename... Ts>
constexpr bool are_floating_point_v =
		are_true_v<std::integral_constant<bool, std::is_floating_point_v<Ts>>...>;

/*                           ccutl::are_unsigned_v                           */

template <typename... Ts>
constexpr bool are_unsigned_v =
		are_true_v<std::integral_constant<bool, std::is_unsigned_v<Ts>>...>;

/*                            ccutl::are_signed_v                            */

template <typename... Ts>
constexpr bool are_signed_v =
		are_true_v<std::integral_constant<bool, std::is_signed_v<Ts>>...>;

/*                            ccutl::are_pointer_v                            */

template <typename... Ts>
constexpr bool are_pointer_v =
		are_true_v<std::integral_constant<bool, std::is_pointer_v<Ts>>...>;

/*                             ccutl::are_const_v                             */

template <typename... Ts>
constexpr bool are_const_v =
		are_true_v<std::integral_constant<bool, std::is_const_v<Ts>>...>;

/*                           ccutl::are_volatile_v                           */

template <typename... Ts>
constexpr bool are_volatile_v =
		are_true_v<std::integral_constant<bool, std::is_volatile_v<Ts>>...>;

/*                              ccutl::are_cv_v                              */

template <typename... Ts>
constexpr bool are_cv_v =
		are_true_v<std::integral_constant<bool, std::is_const_v<Ts> ||
																								std::is_volatile_v<Ts>>...>;

/*                           ccutl::are_function_v                           */

template <typename... Ts>
constexpr bool are_function_v =
		are_true_v<std::integral_constant<bool, std::is_function_v<Ts>>...>;

/*                             ccutl::are_array_v                             */

template <typename... Ts>
constexpr bool are_array_v =
		are_true_v<std::integral_constant<bool, std::is_array_v<Ts>>...>;

/*                          ccutl::remove_function_t                          */

template <typename T>
using remove_function_t = typename core::remove_function<T>::type;

/*                         ccutl::remove_everything_t                         */

template <typename T>
using remove_everything_t = typename core::remove_everything<T>::type;

/*                            ccutl::decay_deep_t                            */

template <typename T>
using decay_deep_t = typename core::decay_deep<T>::type;

/*                             ccutl::are_same_v                             */

template <typename T, typename... Ts>
constexpr bool are_same_v =
		are_true_v<std::integral_constant<bool, std::is_same_v<T, Ts>>...>;

/*                          ccutl::are_decay_same_v                          */

template <typename T, typename... Ts>
constexpr bool are_decay_same_v = are_true_v<std::integral_constant<
		bool, std::is_same_v<decay_deep_t<T>, decay_deep_t<Ts>>>...>;

/*                       ccutl::function_return_type_t                       */

template <typename Tf, std::enable_if_t<are_function_v<Tf>>* = nullptr>
using function_return_type_t = typename core::function_return_type<Tf>::type;

/*                        ccutl::functor_return_type_t                        */

template <typename Tf, typename... TArgs>
using functor_return_type_t =
		decltype((std::declval<Tf>())(std::declval<TArgs>()...));

/*                         ccutl::n_function_params_v                         */

template <typename T, std::enable_if_t<are_function_v<T>>* = nullptr>
constexpr size_t n_function_params_v = core::n_function_params<T>::value;

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_TYPE_TRAITS_H_
