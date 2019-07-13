#ifndef CPPUTILS_CCUTL_CORE_MATH_H_
#define CPPUTILS_CCUTL_CORE_MATH_H_

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
 * @file ccutl/core/math.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various mathematical templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <type_traits>

#include "ccutl/core/type_traits.h"

namespace ccutl {

template <typename TResult, typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TResult, TA, TB>>* = nullptr>
TResult safe_add(TA a, TB b);

template <typename TOutput, typename TAddend,
					std::enable_if_t<are_arithmetic_v<remove_everything_t<TOutput>, TAddend>>* =
							nullptr>
void safe_add(TOutput* a, TAddend b);

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_MATH_H_
