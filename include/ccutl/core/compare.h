#ifndef CPPUTILS_CCUTL_CORE_COMPARE_H_
#define CPPUTILS_CCUTL_CORE_COMPARE_H_

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
 * @file ccutl/core/compare.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various comparison functions.
 * @version 0.2.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <optional>
#include <string>

#include "ccutl/core/limits.h"
#include "ccutl/core/type_traits.h"

namespace ccutl {

namespace core {

template <bool Strict = false, typename TA, typename TB,
					std::enable_if_t<are_pointer_v<decay_deep_t<TA>, decay_deep_t<TB>>>
							* = nullptr>
bool pointers_are_iteratively_equal(const TA &a, const TB &b,
																		std::optional<size_t> n_max = std::nullopt);

}	// namespace core

template <bool Strict = false, typename TA, typename TB>
bool are_equal(const TA &a, const TB &b,
							 std::optional<size_t> n_max_size_cmp = std::nullopt);

template <typename TA, typename TB, TA Lhs, TB Rhs,
					std::enable_if_t<are_arithmetic_v<TA, TB>> * = nullptr>
constexpr signed char constexpr_ncmp = ([]() constexpr->signed char {
	if constexpr ((std::is_signed_v<TA> == std::is_signed_v<TB>) ||
								(std::is_floating_point_v<TA> ||
								 std::is_floating_point_v<TB>)) {
		// signedness is equal or comparison with a floating point number
		return Lhs < Rhs ? -1 : Lhs > Rhs ? 1 : 0;
	} else if constexpr (std::is_signed_v<TA>) {
		// Lhs: signed integer; Rhs: unsigned integer
		if (Lhs < 0) {
			return -1;
		} else {
			auto u_Lhs = static_cast<std::make_unsigned_t<TA>>(Lhs);
			return u_Lhs < Rhs ? -1 : u_Lhs > Rhs ? 1 : 0;
		}
	} else {
		// Lhs: unsigned integer; Rhs: signed integer
		if (Rhs < 0) {
			return 1;
		} else {
			auto u_Rhs = static_cast<std::make_unsigned_t<TB>>(Rhs);
			return Lhs < u_Rhs ? -1 : Lhs > u_Rhs ? 1 : 0;
		}
	}
})();

template <typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TA, TB>> * = nullptr>
signed char ncmp(TA lhs, TB rhs);

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
    >* = nullptr
>
/*                        */ /* clang-format on */ /*                         */
bool are_equivalent(const TA &a, const TB &b,
										std::optional<size_t> n_max_size_cmp = std::nullopt);

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_COMPARE_H_
