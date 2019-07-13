#ifndef CPPUTILS_CCUTL_CORE_ALGORITHM_H_
#define CPPUTILS_CCUTL_CORE_ALGORITHM_H_

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
 * @file ccutl/core/algorithm.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various algorithmic templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-06-28
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <execution>
#include <type_traits>

#include "ccutl/core/compare.h"
#include "ccutl/core/type_traits.h"

namespace ccutl {

/* .--------------------------------------------------------------------------,
	/                           ccutl::transform_it                            /
 '--------------------------------------------------------------------------' */

template <bool BackInsert = false, typename TInputContainer,
					typename TOutputContainer, typename TUnaryOp,
					std::enable_if_t<are_const_iterable_v<TInputContainer> &&
													 are_iterable_v<TOutputContainer>> * = nullptr>
auto transform_it(const TInputContainer &input, TOutputContainer *output,
									const TUnaryOp &f);

template <bool BackInsert = false, typename TExecutionPolicy,
					typename TInputContainer, typename TOutputContainer,
					typename TUnaryOp,
					std::enable_if_t<
							std::is_execution_policy_v<decay_deep_t<TExecutionPolicy>> &&
							are_const_iterable_v<TInputContainer> &&
							are_iterable_v<TOutputContainer>> * = nullptr>
auto transform_it(const TExecutionPolicy &&policy, const TInputContainer &input,
									TOutputContainer *output, const TUnaryOp &f);

template <
		bool BackInsert = false, typename TInputContainer1,
		typename TInputContainer2, typename TOutputContainer, typename TBinaryOp,
		std::enable_if_t<are_const_iterable_v<TInputContainer1, TInputContainer2> &&
										 are_iterable_v<TOutputContainer>> * = nullptr>
auto transform_it(const TInputContainer1 &input1,
									const TInputContainer2 &input2, TOutputContainer *output,
									const TBinaryOp &f);

template <bool BackInsert = false, typename TExecutionPolicy,
					typename TInputContainer1, typename TInputContainer2,
					typename TOutputContainer, typename TUnaryOp,
					std::enable_if_t<
							std::is_execution_policy_v<decay_deep_t<TExecutionPolicy>> &&
							are_const_iterable_v<TInputContainer1, TInputContainer2> &&
							are_iterable_v<TOutputContainer>> * = nullptr>
auto transform_it(const TExecutionPolicy &&policy,
									const TInputContainer1 &input1,
									const TInputContainer2 &input2, TOutputContainer *output,
									const TUnaryOp &f);

/* .--------------------------------------------------------------------------,
	/                            ccutl::for_each_it                            /
 '--------------------------------------------------------------------------' */

template <typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<are_const_iterable_v<TInputContainer>> * = nullptr>
TUnaryOp for_each_it(const TInputContainer &input, const TUnaryOp &f);

template <typename TExecutionPolicy, typename TInputContainer, typename T,
					typename TUnaryOp,
					std::enable_if_t<
							std::is_execution_policy_v<decay_deep_t<TExecutionPolicy>> &&
							are_const_iterable_v<TInputContainer>> * = nullptr>
void for_each_it(const TExecutionPolicy &&policy, const TInputContainer &input,
								 const TUnaryOp &f);

/* .--------------------------------------------------------------------------,
	/                            ccutl::iterate_it                             /
 '--------------------------------------------------------------------------' */
namespace internal {

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					bool ShouldReturnVoid, size_t NArgs,
					std::enable_if_t<constexpr_ncmp<size_t, size_t, NArgs, 4> == -1> * =
							nullptr>
constexpr bool iterate_it_unary_should_enable_v_ = ([]() constexpr->bool {
	if constexpr (Reverse ? !are_const_reverse_iterable_v<TInputContainer>
												: !are_const_iterable_v<TInputContainer>) {
		return false;
	}
	using InputItT =
			std::conditional_t<Reverse,
												 decltype(std::declval<TInputContainer>().crbegin()),
												 decltype(std::declval<TInputContainer>().cbegin())>;
	if constexpr (NArgs == 1) {
		if constexpr (std::is_invocable_v<TUnaryOp, InputItT>) {
			using FunctorReturnT = functor_return_type_t<TUnaryOp, InputItT>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputItT, FunctorReturnT>;
			}
		}
		return false;
	} else if constexpr (NArgs == 2) {
		if constexpr (std::is_invocable_v<TUnaryOp, InputItT, InputItT>) {
			using FunctorReturnT =
					functor_return_type_t<TUnaryOp, InputItT, InputItT>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputItT, FunctorReturnT>;
			}
		}
		return false;
	} else {
		if constexpr (std::is_invocable_v<TUnaryOp, InputItT, InputItT, InputItT>) {
			using FunctorReturnT =
					functor_return_type_t<TUnaryOp, InputItT, InputItT, InputItT>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputItT, FunctorReturnT>;
			}
		}
		return false;
	}
})();

template <bool Reverse, typename TInputContainer1, typename TInputContainer2,
					typename TBinaryOp, bool ShouldReturnVoid, size_t NArgs,
					std::enable_if_t<constexpr_ncmp<size_t, size_t, NArgs, 1> == 1 &&
													 constexpr_ncmp<size_t, size_t, NArgs, 7> == -1> * =
							nullptr>
constexpr bool iterate_it_binary_should_enable_v_ = ([]() constexpr->bool {
	if constexpr (Reverse ? (!are_const_reverse_iterable_v<TInputContainer1> ||
													 !are_const_reverse_iterable_v<TInputContainer2>)
												: (!are_const_iterable_v<TInputContainer1> ||
													 !are_const_iterable_v<TInputContainer2>)) {
		return false;
	}
	using InputIt1T =
			std::conditional_t<Reverse,
												 decltype(std::declval<TInputContainer1>().crbegin()),
												 decltype(std::declval<TInputContainer1>().cbegin())>;
	using InputIt2T =
			std::conditional_t<Reverse,
												 decltype(std::declval<TInputContainer2>().crbegin()),
												 decltype(std::declval<TInputContainer2>().cbegin())>;
	if constexpr (NArgs == 2) {
		if constexpr (std::is_invocable_v<TBinaryOp, InputIt1T, InputIt2T>) {
			using FunctorReturnT =
					functor_return_type_t<TBinaryOp, InputIt1T, InputIt2T>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputIt1T, FunctorReturnT>;
			}
		}
		return false;
	} else if constexpr (NArgs == 3) {
		if constexpr (std::is_invocable_v<TBinaryOp, InputIt1T, InputIt2T,
																			InputIt1T>) {
			using FunctorReturnT =
					functor_return_type_t<TBinaryOp, InputIt1T, InputIt2T, InputIt1T>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputIt1T, FunctorReturnT>;
			}
		}
		return false;
	} else if constexpr (NArgs == 4) {
		if constexpr (std::is_invocable_v<TBinaryOp, InputIt1T, InputIt2T,
																			InputIt1T, InputIt2T>) {
			using FunctorReturnT =
					functor_return_type_t<TBinaryOp, InputIt1T, InputIt2T, InputIt1T,
																InputIt2T>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputIt1T, FunctorReturnT>;
			}
		}
		return false;
	} else if constexpr (NArgs == 5) {
		if constexpr (std::is_invocable_v<TBinaryOp, InputIt1T, InputIt2T,
																			InputIt1T, InputIt2T, InputIt1T>) {
			using FunctorReturnT =
					functor_return_type_t<TBinaryOp, InputIt1T, InputIt2T, InputIt1T,
																InputIt2T, InputIt1T>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputIt1T, FunctorReturnT>;
			}
		}
		return false;
	} else {
		if constexpr (std::is_invocable_v<TBinaryOp, InputIt1T, InputIt2T,
																			InputIt1T, InputIt2T, InputIt1T,
																			InputIt2T>) {
			using FunctorReturnT =
					functor_return_type_t<TBinaryOp, InputIt1T, InputIt2T, InputIt1T,
																InputIt2T, InputIt1T, InputIt2T>;
			if constexpr (ShouldReturnVoid) {
				return are_decay_same_v<void, FunctorReturnT>;
			} else {
				return are_decay_same_v<InputIt1T, FunctorReturnT>;
			}
		}
		return false;
	}
})();

}	// namespace internal

// unaryop

template <bool Reverse = false, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, false, 1>> * = nullptr>
void iterate_it(const TInputContainer &input, const TUnaryOp &f);

template <bool Reverse = false, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, false, 2>> * = nullptr>
void iterate_it(const TInputContainer &input, const TUnaryOp &f);

template <bool Reverse = false, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, false, 3>> * = nullptr>
void iterate_it(const TInputContainer &input, const TUnaryOp &f);

template <bool Reverse = false, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, true, 1>> * = nullptr>
void iterate_it(const TInputContainer &input, const TUnaryOp &f);

template <bool Reverse = false, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, true, 2>> * = nullptr>
void iterate_it(const TInputContainer &input, const TUnaryOp &f);

template <bool Reverse = false, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, true, 3>> * = nullptr>
void iterate_it(const TInputContainer &input, const TUnaryOp &f);

// binaryop

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 2>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 3>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 4>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 5>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 6>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 2>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 3>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 4>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 5>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

template <bool Reverse = false, typename TInputContainer1,
					typename TInputContainer2, typename TBinaryOp,
					std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
							Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 6>>
							* = nullptr>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f);

/* .--------------------------------------------------------------------------,
	/                              ccutl::concat                               /
 '--------------------------------------------------------------------------' */

template <typename TContain, typename TVal,
					std::enable_if_t<are_iterable_v<TContain> &&
													 are_const_iterable_v<TContain> &&
													 !are_decay_same_v<std::string, TContain> &&
													 std::is_constructible_v<TContain, TVal>> * = nullptr>
TContain concat(const TVal &value);

template <typename TContain, typename TVal, typename... TRest,
					std::enable_if_t<are_iterable_v<TContain> &&
													 are_const_iterable_v<TContain> &&
													 !are_decay_same_v<std::string, TContain> &&
													 std::is_constructible_v<TContain, TVal>> * = nullptr>
TContain concat(const TVal &value, const TRest... rest);

template <typename TContain, typename TVal,
					std::enable_if_t<are_decay_same_v<std::string, TContain> &&
													 (std::is_constructible_v<std::string, TVal> ||
														are_streamable_to_v<std::ostream, TVal>)> * = nullptr>
TContain concat(const TVal &value);

template <typename TContain, typename TVal, typename... TRest,
					std::enable_if_t<are_decay_same_v<std::string, TContain> &&
													 (std::is_constructible_v<std::string, TVal> ||
														are_streamable_to_v<std::ostream, TVal>)> * = nullptr>
TContain concat(const TVal &value, const TRest... rest);

/* .--------------------------------------------------------------------------,
	/                               ccutl::join                                /
 '--------------------------------------------------------------------------' */

template <
		template <typename...> typename TContain, typename TVal,
		typename TDelim = const char *,
		std::enable_if_t<are_const_iterable_v<TContain<TVal>> &&
										 are_streamable_to_v<std::ostream, TVal, TDelim>> * = nullptr>
std::string join(const TContain<TVal> &target, const TDelim &delimiter = "");

/* .--------------------------------------------------------------------------,
	/                             ccutl::combinate                             /
 '--------------------------------------------------------------------------' */

template <typename T, std::enable_if_t<are_const_iterable_v<T>> * = nullptr>
std::vector<T> combinate(const T &target, size_t sample_sz);

/* .--------------------------------------------------------------------------,
	/                             ccutl::permutate                             /
 '--------------------------------------------------------------------------' */

template <typename T, std::enable_if_t<are_const_iterable_v<T>> * = nullptr>
std::vector<T> permutate(const T &target, size_t sample_sz = 0,
												 bool repetition = false);

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_ALGORITHM_H_
