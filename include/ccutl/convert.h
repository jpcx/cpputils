#ifndef CPPUTILS_CCUTL_CONVERT_H_
#define CPPUTILS_CCUTL_CONVERT_H_

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
 * @file ccutl/convert.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type-conversion templates.
 * @version 0.1.1
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/convert.h"

#include <cassert>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

#include "ccutl/compare.h"
#include "ccutl/type_traits.h"

namespace ccutl {

template <typename T, std::enable_if_t<are_streamable_to_v<std::ostream, T>> *>
/**
 * @brief Converts a value to an std::string using std::ostringstream or another
 * available method. T must either be arithmetic or string constructible.
 * @param value value to convert.
 * @param precision optional std::istringstream precision (for floating point
 * defaults to std::numeric_limits<T>::max_digits10; no default for other
 * types).
 * @return std::string converted value.
 */
std::string to_string(const T value,
											const std::optional<std::streamsize> &precision) {
	static_assert(
			std::is_arithmetic_v<T> || std::is_constructible_v<std::string, T>,
			"Bad type selected for ccutl::to_string");
	if constexpr (std::is_constructible_v<std::string, T>) {
		return value;
	} else if constexpr (are_decay_same_v<T, char>) {
		return {value};
	} else if constexpr (are_decay_same_v<T, bool>) {
		return value ? "1" : "0";
	} else if constexpr (are_decay_same_v<T, signed char>) {
		return to_string(static_cast<short>(value), precision);
	} else if constexpr (are_decay_same_v<T, u_char>) {
		return to_string(static_cast<u_short>(value), precision);
	} else {
		std::ostringstream buff;
		if constexpr (std::is_floating_point_v<T>) {
			buff.precision(precision.value_or(std::numeric_limits<T>::max_digits10));
		} else if (precision.has_value()) {
			buff.precision(precision.value());
		}
		buff << value;
		return buff.str();
	}
}

template <typename T>
/**
 * @brief Converts a std::string to a value using std::istringstream or
 * another available method. T must either be arithmetic or string
 * constructible and must not be a pointer type.
 * @param value value to convert.
 * @param precision optional std::istringstream precision (for floating point
 * defaults to std::numeric_limits<T>::max_digits10; no default for other
 * types).
 * @return T converted value.
 */
T from_string(const std::string &value,
							const std::optional<std::streamsize> &precision) {
	static_assert(
			std::is_arithmetic_v<T> || std::is_constructible_v<std::string, T>,
			"Bad type selected for ccutl::from_string");
	if constexpr (std::is_constructible_v<T, std::string>) {
		return value;
	} else if constexpr (are_decay_same_v<T, const char *>) {
		return value.c_str();
	} else if constexpr (are_decay_same_v<T, char>) {
		assert(value.size() == 1);
		return value[0];
	} else if constexpr (are_decay_same_v<T, bool>) {
		assert(value == "1" || value == "0");
		if (value == "1") return true;
		return false;
	} else if constexpr (are_decay_same_v<T, short> || are_decay_same_v<T, int>) {
		return std::stoi(value);
	} else if constexpr (are_decay_same_v<T, long>) {
		return std::stol(value);
	} else if constexpr (are_decay_same_v<T, u_long>) {
		return std::stoul(value);
	} else if constexpr (are_decay_same_v<T, long long>) {
		return std::stoll(value);
	} else if constexpr (are_decay_same_v<T, unsigned long long>) {
		return std::stoull(value);
	} else if constexpr (are_decay_same_v<T, u_short> ||
											 are_decay_same_v<T, u_int>) {
		std::istringstream buff;
		buff.str(value);
		T result;
		buff >> result;
		return result;
	} else if constexpr (are_decay_same_v<T, signed char>) {
		return static_cast<signed char>(from_string<short>((value), precision));
	} else if constexpr (are_decay_same_v<T, unsigned char>) {
		return static_cast<u_char>(from_string<u_short>((value), precision));
	} else {
		std::istringstream buff;
		if constexpr (are_decay_same_v<T, float> || are_decay_same_v<T, double> ||
									are_decay_same_v<T, long double>) {
			buff.precision(precision.value_or(std::numeric_limits<T>::max_digits10));
		} else if (precision.has_value()) {
			buff.precision(precision.value());
		}
		buff.str(value);
		T result;
		buff >> result;
		return result;
	}
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CONVERT_H_
