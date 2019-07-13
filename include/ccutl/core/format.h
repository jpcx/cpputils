#ifndef CPPUTILS_CCUTL_CORE_FORMAT_H_
#define CPPUTILS_CCUTL_CORE_FORMAT_H_

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
 * @file ccutl/core/format.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various text formatting templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <string>
#include <type_traits>

#include "ccutl/core/type_traits.h"

namespace ccutl {

template <typename T,
					std::enable_if_t<std::is_constructible_v<std::string, T> &&
													 are_const_iterable_v<T>>* = nullptr>
std::string trim_space(const T& text);

template <typename T,
					std::enable_if_t<std::is_constructible_v<std::string, T> &&
													 !are_const_iterable_v<T>>* = nullptr>
std::string trim_space(const T& text);

template <typename TStr = const char*, typename TNum = size_t,
					std::enable_if_t<std::is_constructible_v<std::string, TStr> &&
													 std::is_integral_v<TNum>>* = nullptr>
std::string string_repeat(TNum n_repeat, const TStr& input = " ");

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_FORMAT_H_
