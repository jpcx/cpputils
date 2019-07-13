#ifndef CPPUTILS_CCUTL_COMPARE_H_
#define CPPUTILS_CCUTL_COMPARE_H_

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
 * @file ccutl/compare.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various comparison functions.
 * @version 0.2.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/compare.h"

#include <cstring>
#include <optional>
#include <type_traits>

#include "ccutl/convert.h"
#include "ccutl/limits.h"
#include "ccutl/type_traits.h"

namespace ccutl {

namespace core {

template <bool Strict, typename TA, typename TB,
					std::enable_if_t<are_pointer_v<decay_deep_t<TA>, decay_deep_t<TB>>> *>
/**
 * @brief Compares two pointers for equality. May or may not be C arrays. Uses
 * bracket notation to compare values at each iteration. Types may be
 * ccutl::decay_deep equivalent if Strict is false (default false). Otherwise
 * must be strictly equal. Both fail cases will return false. Checks for
 * '\0' if char pointer. Returns false on first difference. Returns false if
 * n_max is not set and iteration will pass size_t max.
 *
 * @param a First array.
 * @param b Second array.
 * @param n_max Optional maximum iterations to check pointers.
 * @return true if equal.
 * @return false if not equal.
 */
bool pointers_are_iteratively_equal(const TA &a, const TB &b,
																		std::optional<size_t> n_max) {
	if (a == b) return true;
	if constexpr (!are_decay_same_v<TA, TB>) return false;
	if constexpr (Strict && !are_same_v<TA, TB>) return false;
	// Handle two arrays
	if constexpr (are_array_v<TA, TB>) {
		constexpr size_t len_a = std::extent_v<TA>;
		constexpr size_t len_b = std::extent_v<TB>;
		if constexpr (len_a != len_b) return false;
		for (size_t i = 0; i < len_a; ++i) {
			if (a[i] != b[i]) return false;
		}
		return true;
	}
	// Handle one array
	else if constexpr (are_array_v<TA>) {
		constexpr size_t len_a = std::extent_v<TA>;
		// Check char[] == char*
		if constexpr (are_decay_same_v<TA, char *>) {
			for (size_t i = 0; i < len_a; ++i) {
				if (a[i] != b[i]) return false;
				if (b[i] == '\0' && i != len_a - 1) return false;
			}
			return true;
		}
		// Check [] == *
		else {
			for (size_t i = 0; i < len_a; ++i) {
				if (a[i] != b[i]) return false;
			}
			return true;
		}
	}
	// Handle one array (recurse once to swap arguments)
	else if constexpr (are_array_v<TB>) {
		return pointers_are_iteratively_equal<Strict>(b, a, n_max);
	}
	// Handle two non-extent pointers
	else {
		// Check char* == char* (up to n_max or '\0')
		if constexpr (are_decay_same_v<TA, char *>) {
			size_t i;
			for (i = 0;
					 a[i] != '\0' && b[i] != '\0' && i < n_max.value_or(max_v<size_t>);
					 ++i) {
				if (a[i] != b[i]) return false;
			}
			// Chars are null terminated at same index
			if (a[i] == '\0' && b[i] == '\0')
				return true;
			else if (n_max.has_value() && i == n_max.value())
				return a[i] == b[i];
			return false;
		}
		// Handle two pointers (may or may not be arrays)
		else {
			size_t i;
			for (i = 0; i < n_max.value_or(max_v<size_t>); ++i) {
				if (a[i] != b[i]) return false;
			}
			if (n_max.has_value() && i == n_max.value()) return a[i] == b[i];
			return false;
		}
	}
}

}	// namespace core

template <bool Strict, typename TA, typename TB>
/**
 * @brief Checks equality of two values. Allows for ccutl::decay_deep_t type
 * equivalence if Strict is false (default false). Iterates over pointer values
 * and terminates on difference, '\0' (only if char * (not char[n?])),
 * n_max_size_cmp, or size_t overflow.
 *
 * @param a First value.
 * @param b Second value.
 * @param n_max_size_cmp Optional maximum iteration for pointer checking (only
 * used for pointers).
 * @return true if equal.
 * @return false if not equal.
 */
bool are_equal(const TA &a, const TB &b, std::optional<size_t> n_max_size_cmp) {
	if constexpr (!are_decay_same_v<TA, TB>) return false;
	if constexpr (are_pointer_v<TA> || are_array_v<TA>) {
		return core::pointers_are_iteratively_equal<Strict>(a, b, n_max_size_cmp);
	}
	if constexpr (are_decay_same_v<TA, char *>) {
		return strcmp(a, b) == 0;
	} else {
		return a == b;
	}
}

template <typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TA, TB>> *>
/** @brief Returns 0 if two values are equal, -1 if lhs is less than rhs, or 1
	 if lhs is greater than rhs. Handles comparison of integers of different
	 signedness. */
signed char ncmp(TA lhs, TB rhs) {
	if constexpr ((std::is_signed_v<TA> == std::is_signed_v<TB>) ||
								(std::is_floating_point_v<TA> ||
								 std::is_floating_point_v<TB>)) {
		// signedness is equal or comparison with a floating point number
		return lhs < rhs ? -1 : lhs > rhs ? 1 : 0;
	} else if constexpr (std::is_signed_v<TA>) {
		// lhs: signed integer; rhs: unsigned integer
		if (lhs < 0) {
			return -1;
		} else {
			auto u_lhs = static_cast<std::make_unsigned_t<TA>>(lhs);
			return u_lhs < rhs ? -1 : u_lhs > rhs ? 1 : 0;
		}
	} else {
		// lhs: unsigned integer; rhs: signed integer
		if (rhs < 0) {
			return 1;
		} else {
			auto u_rhs = static_cast<std::make_unsigned_t<TB>>(rhs);
			return lhs < u_rhs ? -1 : lhs > u_rhs ? 1 : 0;
		}
	}
}

/*                        */ /* clang-format off */ /*                        */
template <
    typename TA,
    typename TB,
    std::enable_if_t<
      (
        are_decay_same_v<TA, char *>            ||
        are_decay_same_v<TA, char>              ||
        are_arithmetic_v<TA>                    ||
        std::is_constructible_v<std::string, TA>
      ) && (
        are_decay_same_v<TB, char *>            ||
        are_decay_same_v<TB, char>              ||
        are_arithmetic_v<TB>                    ||
        std::is_constructible_v<std::string, TB>
      )
    >*
>
/*                        */ /* clang-format on */ /*                         */
/**
 * @brief Checks for equivalency between string-like and arithmetic values.
 * Assumes that chars are not arithmetic. Compares pointers and terminates on
 * difference, '\0' (only if char * (not char[n?])), n_max_size_cmp, or size_t
 * overflow.
 *
 * @param a First value.
 * @param b Second value.
 * @param n_max_size_cmp If passing pointer, optional maximum number of
 * comparisons to make.
 * @return true if equivalent.
 * @return false if not.
 */
bool are_equivalent(const TA &a, const TB &b,
										std::optional<size_t> n_max_size_cmp) {
	using std::is_constructible_v;
	using std::string;
	using std::string_view;

	// Handle cases where either TA or TB are char *.
	// Char arrays may or may not be null-terminated.
	// Char pointers must be null terminated.
	// Stops on either first difference or null termination character.
	if constexpr (are_decay_same_v<TA, char *> || are_decay_same_v<TB, char *>) {
		// Handle TA==char* && TB==char*
		if constexpr (are_decay_same_v<TA, TB>) {
			return are_equal(a, b, n_max_size_cmp);
		}
		// Handle TA==char* && TB!=char*
		else if constexpr (are_decay_same_v<TA, char *>) {
			// Handle TA==char* && TB==char
			if constexpr (are_decay_same_v<TB, char>) {
				return are_equal(a, &b, n_max_size_cmp);
			}
			// Handle TA==char* && TB==string
			else if constexpr (are_decay_same_v<TB, string>) {
				return are_equal(a, b.c_str(), n_max_size_cmp);
			}
			// Handle TA==char* && TB==number or string_constructible
			else {
				return are_equal(a, to_string(b).c_str(), n_max_size_cmp);
			}
		}
		// Handle TA!=char* && TB==char*
		else if constexpr (are_decay_same_v<TB, char *>) {
			// Recurse once to swap arguments
			return are_equivalent(b, a, n_max_size_cmp);
		}
	}
	// Handle TA and TB as same (== safe) type
	else if constexpr (are_decay_same_v<TA, TB> &&
										 !are_decay_same_v<TA, TB, char *>) {
		return a == b;
	}
	// Handle TA and TB as arithmetic types
	else if constexpr (are_arithmetic_v<TA, TB> &&
										 !(are_decay_same_v<TA, char> ||
											 are_decay_same_v<TB, char>)) {
		return ncmp(a, b) == 0;
	}
	// Handle TA==string TB==string_constructible
	else if constexpr (are_decay_same_v<TA, string>) {
		return a == to_string(b);
	}
	// Handle TA==string_constructible TB==string
	else if constexpr (are_decay_same_v<TB, string>) {
		return to_string(a) == b;
	}
	// Handle TA==char TB==(string||string_constructible)
	else if constexpr (are_decay_same_v<TA, char>) {
		if constexpr (are_decay_same_v<TB, string>) {
			return b.size() == 1 && b[0] == a;
		} else {
			string v = to_string(b);
			return v.size() == 1 && v[0] == a;
		}
	} else if constexpr (are_decay_same_v<TB, char>) {
		if constexpr (are_decay_same_v<TA, string>) {
			return a.size() == 1 && a[0] == b;
		} else {
			string v = to_string(a);
			return v.size() == 1 && v[0] == b;
		}
	} else {
		// else catch-all
		return are_equal(a, b);
	}
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_COMPARE_H_
