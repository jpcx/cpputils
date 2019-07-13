#ifndef CPPUTILS_CCUTL_CORE_IO_H_
#define CPPUTILS_CCUTL_CORE_IO_H_

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
 * @file ccutl/core/io.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various I/O related templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-08
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#include "ccutl/core/type_traits.h"

namespace ccutl {

template <bool InsertEndLine = true, typename T,
					std::enable_if_t<are_floating_point_v<T>>* = nullptr>
void log(T value,
				 const std::optional<std::streamsize>& precision = std::nullopt);

template <bool InsertEndLine = true, typename T = const char*,
					std::enable_if_t<are_streamable_to_v<std::ostream, T>>* = nullptr>
void log(const T& value = "");

template <bool InsertEndLine = true, template <typename...> typename TContain,
					typename T, typename TDelim = const char*,
					std::enable_if_t<
							!are_streamable_to_v<std::ostream, TContain<T>> &&
							are_const_iterable_v<TContain<T>> && are_floating_point_v<T> &&
							are_streamable_to_v<std::ostream, TDelim>>* = nullptr>
void log(const TContain<T>& value, const TDelim& delimiter = " ",
				 const std::optional<std::streamsize>& precision = std::nullopt);

template <
		bool InsertEndLine = true, template <typename...> typename TContain,
		typename T, typename TDelim = const char*,
		std::enable_if_t<!are_streamable_to_v<std::ostream, TContain<T>> &&
										 are_const_iterable_v<TContain<T>> &&
										 are_streamable_to_v<std::ostream, T, TDelim>>* = nullptr>
void log(const TContain<T>& value, const TDelim& delimiter = " ");

template <bool InsertEndLine = true, template <typename...> typename TRows,
					template <typename...> typename TColumns, typename T,
					typename TRowDelim = const char*, typename TColDelim = const char*,
					std::enable_if_t<are_const_iterable_v<TRows<TColumns<T>>> &&
													 are_streamable_to_v<std::ostream, T, TRowDelim,
																							 TColDelim>>* = nullptr>
void log(const TRows<TColumns<T>>& value, const TRowDelim& row_delimiter = "",
				 const TColDelim& col_delimiter = " ");

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_IO_H_
