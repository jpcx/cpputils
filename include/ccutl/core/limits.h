#ifndef CPPUTILS_CCUTL_CORE_LIMITS_H_
#define CPPUTILS_CCUTL_CORE_LIMITS_H_

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
 * @file ccutl/core/limits.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various limit-checking functions.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <limits>
#include <type_traits>

#include "ccutl/core/type_traits.h"

namespace ccutl {

template <typename T, std::enable_if_t<are_arithmetic_v<T>>* = nullptr>
constexpr T max_v = std::numeric_limits<T>::max();

template <typename T, std::enable_if_t<are_arithmetic_v<T>>* = nullptr>
constexpr T min_v = std::numeric_limits<T>::lowest();

template <typename TLim, typename TTest,
					std::enable_if_t<are_arithmetic_v<TLim, TTest>>* = nullptr>
constexpr bool is_val_overflow(TTest value);

template <typename TLim, typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TLim, TA, TB>>* = nullptr>
bool is_add_overflow(TA a, TB b);

template <typename TLim, typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TLim, TA, TB>>* = nullptr>
bool is_sub_overflow(TA a, TB b);

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_LIMITS_H_
