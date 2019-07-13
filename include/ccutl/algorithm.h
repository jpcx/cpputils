#ifndef CPPUTILS_CCUTL_ALGORITHM_H_
#define CPPUTILS_CCUTL_ALGORITHM_H_

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
 * @file ccutl/algorithm.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various algorithmic templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-06-28
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/algorithm.h"

#include <algorithm>
#include <cassert>
#include <execution>
#include <iostream>
#include <iterator>
#include <thread>
#include <type_traits>
#include <vector>

#include "ccutl/convert.h"
#include "ccutl/type_traits.h"

namespace ccutl {

/* .--------------------------------------------------------------------------,
	/                           ccutl::transform_it                            /
 '--------------------------------------------------------------------------' */

template <bool BackInsert, typename TInputContainer, typename TOutputContainer,
					typename TUnaryOp,
					std::enable_if_t<are_const_iterable_v<TInputContainer> &&
													 are_iterable_v<TOutputContainer>> *>
auto transform_it(const TInputContainer &input, TOutputContainer *output,
									const TUnaryOp &f) {
	using std::transform;
	if constexpr (BackInsert) {
		return transform(input.cbegin(), input.cend(),
										 std::back_insert_iterator(*output), f);
	} else {
		return transform(input.cbegin(), input.cend(), output->begin(), f);
	}
}

template <bool BackInsert, typename TExecutionPolicy, typename TInputContainer,
					typename TOutputContainer, typename TUnaryOp,
					std::enable_if_t<
							std::is_execution_policy_v<decay_deep_t<TExecutionPolicy>> &&
							are_const_iterable_v<TInputContainer> &&
							are_iterable_v<TOutputContainer>> *>
auto transform_it(const TExecutionPolicy &&policy, const TInputContainer &input,
									TOutputContainer *output, const TUnaryOp &f) {
	if constexpr (BackInsert) {
		return std::transform(policy, input.cbegin(), input.cend(),
													std::back_insert_iterator(*output), f);

	} else {
		return std::transform(policy, input.cbegin(), input.cend(), output->begin(),
													f);
	}
}

template <
		bool BackInsert, typename TInputContainer1, typename TInputContainer2,
		typename TOutputContainer, typename TBinaryOp,
		std::enable_if_t<are_const_iterable_v<TInputContainer1, TInputContainer2> &&
										 are_iterable_v<TOutputContainer>> *>
auto transform_it(const TInputContainer1 &input1,
									const TInputContainer2 &input2, TOutputContainer *output,
									const TBinaryOp &f) {
	if constexpr (BackInsert) {
		return std::transform(input1.cbegin(), input1.cend(), input2.cbegin(),
													std::back_insert_iterator(*output), f);
	} else {
		return std::transform(input1.cbegin(), input1.cend(), input2.cbegin(),
													output->begin(), f);
	}
}

template <bool BackInsert, typename TExecutionPolicy, typename TInputContainer1,
					typename TInputContainer2, typename TOutputContainer,
					typename TUnaryOp,
					std::enable_if_t<
							std::is_execution_policy_v<decay_deep_t<TExecutionPolicy>> &&
							are_const_iterable_v<TInputContainer1, TInputContainer2> &&
							are_iterable_v<TOutputContainer>> *>
auto transform_it(const TExecutionPolicy &&policy,
									const TInputContainer1 &input1,
									const TInputContainer2 &input2, TOutputContainer *output,
									const TUnaryOp &f) {
	if constexpr (BackInsert) {
		return std::transform(policy, input1.cbegin(), input1.cend(),
													input2.cbegin(), std::back_insert_iterator(*output),
													f);
	} else {
		return std::transform(policy, input1.cbegin(), input1.cend(),
													input2.cbegin(), output->begin(), f);
	}
}

/* .--------------------------------------------------------------------------,
	/                            ccutl::for_each_it                            /
 '--------------------------------------------------------------------------' */

template <typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<are_const_iterable_v<TInputContainer>> *>
TUnaryOp for_each_it(const TInputContainer &input, const TUnaryOp &f) {
	return std::for_each(input.cbegin(), input.cend(), f);
}

template <typename TExecutionPolicy, typename TInputContainer, typename T,
					typename TUnaryOp,
					std::enable_if_t<
							std::is_execution_policy_v<decay_deep_t<TExecutionPolicy>> &&
							are_const_iterable_v<TInputContainer>> *>
void for_each_it(const TExecutionPolicy &&policy, const TInputContainer &input,
								 const TUnaryOp &f) {
	std::for_each(policy, input.cbegin(), input.cend(), f);
}

/* .--------------------------------------------------------------------------,
	/                            ccutl::iterate_it                             /
 '--------------------------------------------------------------------------' */

/*                                   unary                                   */

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, false, 1>> *>
void iterate_it(const TInputContainer &input, const TUnaryOp &f) {
	// Specialization: functor accepts current iterator
	//                 functor returns next iterator
	if constexpr (Reverse) {
		auto it = input.crbegin();
		do {
			it = f(it);
		} while (it != input.crend());
	} else {
		auto it = input.cbegin();
		do {
			it = f(it);
		} while (it != input.cend());
	}
}

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, false, 2>> *>
void iterate_it(const TInputContainer &input, const TUnaryOp &f) {
	// Specialization: functor accepts current and next iterators
	//                 functor returns next iterator
	if constexpr (Reverse) {
		auto it = input.crbegin();
		do {
			it = f(it, std::next(it));
		} while (it != input.crend());
	} else {
		auto it = input.cbegin();
		do {
			it = f(it, std::next(it));
		} while (it != input.cend());
	}
}

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, false, 3>> *>
void iterate_it(const TInputContainer &input, const TUnaryOp &f) {
	// Specialization: functor accepts current, next, and end iterators
	//                 functor returns next iterator
	if constexpr (Reverse) {
		auto it = input.crbegin();
		do {
			it = f(it, std::next(it), input.crend());
		} while (it != input.crend());
	} else {
		auto it = input.cbegin();
		do {
			it = f(it, std::next(it), input.cend());
		} while (it != input.cend());
	}
}

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, true, 1>> *>
void iterate_it(const TInputContainer &input, const TUnaryOp &f) {
	// Specialization: functor accepts current iterator
	//                 iterate_it iterates it
	if constexpr (Reverse) {
		auto it = input.crbegin();
		do {
			f(it);
		} while (++it != input.crend());
	} else {
		auto it = input.cbegin();
		do {
			f(it);
		} while (++it != input.cend());
	}
}

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, true, 2>> *>
void iterate_it(const TInputContainer &input, const TUnaryOp &f) {
	// Specialization: functor accepts current and next iterators
	//                 iterate_it iterates it
	if constexpr (Reverse) {
		auto it = input.crbegin();
		decltype(it) next;
		do {
			next = std::next(it);
			f(it, next);
			it = next;
		} while (it != input.crend());
	} else {
		auto it = input.cbegin();
		decltype(it) next;
		do {
			next = std::next(it);
			f(it, next);
			it = next;
		} while (it != input.cend());
	}
}

template <bool Reverse, typename TInputContainer, typename TUnaryOp,
					std::enable_if_t<internal::iterate_it_unary_should_enable_v_<
							Reverse, TInputContainer, TUnaryOp, true, 3>> *>
void iterate_it(const TInputContainer &input, const TUnaryOp &f) {
	// Specialization: functor accepts current, next, and end iterators
	//                 iterate_it iterates it
	if constexpr (Reverse) {
		auto it = input.crbegin();
		decltype(it) next;
		do {
			next = std::next(it);
			f(it, next, input.crend());
			it = next;
		} while (it != input.crend());
	} else {
		auto it = input.cbegin();
		decltype(it) next;
		do {
			next = std::next(it);
			f(it, next, input.cend());
			it = next;
		} while (it != input.cend());
	}
}

/*                                   binary                                   */

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 2>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1 and it2 iterators
	//                 functor returns next1, iterate_it iterates it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		do {
			it1 = f(it1, it2);
		} while (it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		do {
			it1 = f(it1, it2);
		} while (it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 3>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, and next1 iterators
	//                 functor returns next1, iterate_it iterates it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		do {
			it1 = f(it1, it2, std::next(it1));
		} while (it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		do {
			it1 = f(it1, it2, std::next(it1));
		} while (it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 4>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, next1, and next2 iterators
	//                 functor returns next1, iterate_it iterates it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		do {
			it1 = f(it1, it2, std::next(it1), std::next(it2));
		} while (it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		do {
			it1 = f(it1, it2, std::next(it1), std::next(it2));
		} while (it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 5>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, next1, next2, and end1 iterators
	//                 functor returns next1, iterate_it iterates it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		do {
			it1 = f(it1, it2, std::next(it1), std::next(it2), input1.crend());
		} while (it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		do {
			it1 = f(it1, it2, std::next(it1), std::next(it2), input1.cend());
		} while (it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, false, 6>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, next1, next2, end1, and end2
	//                                                               iterators
	//                 functor returns next1, iterate_it iterates it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		do {
			it1 = f(it1, it2, std::next(it1), std::next(it2), input1.crend(),
							input2.crend());
		} while (it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		do {
			it1 = f(it1, it2, std::next(it1), std::next(it2), input1.cend(),
							input2.cend());
		} while (it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 2>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1 and it2 iterators
	//                 iterate_it iterates it1 and it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		do {
			f(it1, it2);
		} while (++it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		do {
			f(it1, it2);
		} while (++it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 3>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, and next1 iterators
	//                 iterate_it iterates it1 and it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		decltype(it1) next1;
		do {
			f(it1, it2, next1);
			it1 = next1;
		} while (it1 != input1.crend() && ++it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		decltype(it1) next1;
		do {
			f(it1, it2, next1);
			it1 = next1;
		} while (it1 != input1.cend() && ++it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 4>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, next1, and next2 iterators
	//                 iterate_it iterates it1 and it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		decltype(it1) next1;
		decltype(it2) next2;
		do {
			f(it1, it2, next1, next2);
			it1 = next1;
			it2 = next2;
		} while (it1 != input1.crend() && it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		decltype(it1) next1;
		decltype(it2) next2;
		do {
			f(it1, it2, next1, next2);
			it1 = next1;
			it2 = next2;
		} while (it1 != input1.cend() && it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 5>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, next1, next2, and end1 iterators
	//                 iterate_it iterates it1 and it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		decltype(it1) next1;
		decltype(it2) next2;
		do {
			f(it1, it2, next1, next2, input1.crend());
			it1 = next1;
			it2 = next2;
		} while (it1 != input1.crend() && it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		decltype(it1) next1;
		decltype(it2) next2;
		do {
			f(it1, it2, next1, next2, input1.cend());
			it1 = next1;
			it2 = next2;
		} while (it1 != input1.cend() && it2 != input2.cend());
	}
}

template <
		bool Reverse, typename TInputContainer1, typename TInputContainer2,
		typename TBinaryOp,
		std::enable_if_t<internal::iterate_it_binary_should_enable_v_<
				Reverse, TInputContainer1, TInputContainer2, TBinaryOp, true, 6>> *>
void iterate_it(const TInputContainer1 &input1, const TInputContainer2 &input2,
								const TBinaryOp &f) {
	// Specialization: functor accepts it1, it2, next1, next2, end1, and end2
	//                                                               iterators
	//                 iterate_it iterates it1 and it2
	if constexpr (Reverse) {
		auto it1 = input1.crbegin();
		auto it2 = input2.crbegin();
		decltype(it1) next1;
		decltype(it2) next2;
		do {
			f(it1, it2, next1, next2, input1.crend(), input2.crend());
			it1 = next1;
			it2 = next2;
		} while (it1 != input1.crend() && it2 != input2.crend());
	} else {
		auto it1 = input1.cbegin();
		auto it2 = input2.cbegin();
		decltype(it1) next1;
		decltype(it2) next2;
		do {
			f(it1, it2, next1, next2, input1.cend(), input2.cend());
			it1 = next1;
			it2 = next2;
		} while (it1 != input1.cend() && it2 != input2.cend());
	}
}

/* .--------------------------------------------------------------------------,
	/                              ccutl::concat                               /
 '--------------------------------------------------------------------------' */

template <typename TContain, typename TVal,
					std::enable_if_t<are_iterable_v<TContain> &&
													 are_const_iterable_v<TContain> &&
													 !are_decay_same_v<std::string, TContain> &&
													 std::is_constructible_v<TContain, TVal>> *>
TContain concat(const TVal &value) {
	return value;
}

template <typename TContain, typename TVal, typename... TRest,
					std::enable_if_t<are_iterable_v<TContain> &&
													 are_const_iterable_v<TContain> &&
													 !are_decay_same_v<std::string, TContain> &&
													 std::is_constructible_v<TContain, TVal>> *>
TContain concat(const TVal &value, const TRest... rest) {
	using std::back_inserter;
	using std::copy;
	TContain result = value;
	TContain subresult = concat<TContain>(rest...);
	copy(subresult.cbegin(), subresult.cend(), back_inserter(result));
	return result;
}

template <typename TContain, typename TVal,
					std::enable_if_t<are_decay_same_v<std::string, TContain> &&
													 (std::is_constructible_v<std::string, TVal> ||
														are_streamable_to_v<std::ostream, TVal>)> *>
TContain concat(const TVal &value) {
	return to_string(value);
}

template <typename TContain, typename TVal, typename... TRest,
					std::enable_if_t<are_decay_same_v<std::string, TContain> &&
													 (std::is_constructible_v<std::string, TVal> ||
														are_streamable_to_v<std::ostream, TVal>)> *>
TContain concat(const TVal &value, const TRest... rest) {
	using std::back_inserter;
	using std::copy;
	std::string result = to_string(value);
	std::string subresult = concat<std::string>(rest...);
	copy(subresult.cbegin(), subresult.cend(), back_inserter(result));
	return result;
}

/* .--------------------------------------------------------------------------,
	/                               ccutl::join                                /
 '--------------------------------------------------------------------------' */

template <template <typename...> typename TContain, typename TVal,
					typename TDelim,
					std::enable_if_t<are_const_iterable_v<TContain<TVal>> &&
													 are_streamable_to_v<std::ostream, TVal, TDelim>> *>
std::string join(const TContain<TVal> &target, const TDelim &delimiter) {
	using std::for_each;
	using std::next;
	using std::string;
	const auto begin = target.cbegin();
	string result = *begin;
	for_each(next(begin), target.cend(), [&](const auto &v) {
		result += to_string(delimiter);
		result += to_string(v);
	});
	return result;
}

/* .--------------------------------------------------------------------------,
	/                             ccutl::combinate                             /
 '--------------------------------------------------------------------------' */

template <typename T, std::enable_if_t<are_const_iterable_v<T>> *>
/** @brief Finds all possible combinations of the values in a container T and
	 returns the result as a vector<T>. */
std::vector<T> combinate(const T &target, size_t sample_sz) {
	/*                            Local Typenames                            */
	using std::back_insert_iterator;
	using std::next;
	using std::prev;
	using std::transform;
	using std::vector;
	using TargetCit = typename T::const_iterator;
	using SampleRit = typename vector<TargetCit>::reverse_iterator;
	/*                                                                       */

	// check base cases / assertions
	size_t n_avail = target.size();
	if (sample_sz == n_avail) return {target};
	assert(sample_sz > 0 && sample_sz < n_avail);

	//                Result goes here
	vector<T> result;
	//                ----------------

	// current target iterator sample
	vector<TargetCit> sample(sample_sz);
	{
		// create ascending iterator sample
		TargetCit base_cit = target.cbegin();
		transform(sample.begin(), sample.end(), sample.begin(),
							[&]([[maybe_unused]] const auto &v) { return base_cit++; });
	}

	// beginning of sample iterator
	SampleRit s_rbegin = sample.rbegin();
	// end of sample iterator
	SampleRit s_rend = sample.rend();
	// current sample iterator
	SampleRit scur = s_rbegin;
	// current last position for target iterator (decreases with scur increase)
	TargetCit tlim = prev(target.cend());

	// perform logic until done
	while (true) {
		// Update result vector
		{
			// create subresult
			T subresult;
			// fill subresult with iterator endpoints
			transform(sample.begin(), sample.end(), back_insert_iterator(subresult),
								[](const auto &it) { return *it; });
			// store the subresult in the results
			result.push_back(subresult);
		}

		if (*scur != tlim) {
			++*scur;
		} else {
			while (*scur == tlim) {
				++scur;
				--tlim;
				if (scur == s_rend) {
					return result;
				}
			}

			TargetCit tnext = next(*scur);

			while (*scur != tnext) {
				*scur = tnext;
				if (scur != s_rbegin) {
					--scur;
					++tlim;
					++tnext;
				}
			}
		}
	}
}

/* .--------------------------------------------------------------------------,
	/                             ccutl::permutate                             /
 '--------------------------------------------------------------------------' */

template <typename T, std::enable_if_t<are_const_iterable_v<T>> *>
/** @brief Finds all possible permutations of the values in a container T and
	 returns the result as a vector<T>. Optionally allows for value repetition.
 */
/**
 * @brief Finds all possible permutations of the values in a container T and
 * returns the result as a vector<T>. Optionally allows for value repetition.
 *
 * @param target Target container
 * @param sample_sz Sample size to pick from (sz of 0 uses target.size())
 * @param repetition Whether or not to allow repetition (aaa, aab, etc.)
 * @return std::vector<T>
 */
std::vector<T> permutate(const T &target, size_t sample_sz, bool repetition) {
	/*                            Local Typenames                            */
	using std::back_insert_iterator;
	using std::fill;
	using std::next;
	using std::prev;
	using std::transform;
	using std::vector;
	using TargetCit = typename T::const_iterator;
	using SampleRit = typename vector<TargetCit>::reverse_iterator;
	/*                                                                       */

	// check assertions
	assert(sample_sz <= target.size());

	// handle default value
	if (sample_sz == 0) sample_sz = target.size();

	//                Result goes here
	vector<T> result;
	//                ----------------

	if (!repetition) {
		// use std::next_permutation with all combinations
		auto combinations = combinate(target, sample_sz);
		for (auto &combination : combinations) {
			do {
				result.push_back(combination);
			} while (std::next_permutation(combination.begin(), combination.end()));
		}
		return result;
	} else {
		// use counting method

		// current target iterator sample
		vector<TargetCit> sample(sample_sz);

		// beginning of sample iterator
		SampleRit s_rbegin = sample.rbegin();
		// end of sample iterator
		SampleRit s_rend = sample.rend();
		// current sample iterator
		SampleRit scur = s_rbegin;
		// current last position for target iterator (decreases with scur
		// increase)
		TargetCit tlim = prev(target.cend());
		// target beginning iterator
		TargetCit t_cbegin = target.cbegin();

		// fill with base value
		fill(s_rbegin, s_rend, t_cbegin);

		// perform logic until done
		while (true) {
			// Update result vector
			{
				// create subresult
				T subresult;
				// fill subresult with iterator endpoints
				transform(s_rbegin, s_rend, back_insert_iterator(subresult),
									[](const auto &it) { return *it; });
				// store the subresult in the results
				result.push_back(subresult);
			}

			if (*scur != tlim) {
				++*scur;
			} else {
				while (*scur == tlim) {
					++scur;
					if (scur == s_rend) {
						return result;
					}
				}

				++*scur;

				while (scur != s_rbegin) {
					--scur;
					*scur = t_cbegin;
				}
			}
		}
	}
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_ALGORITHM_H_
