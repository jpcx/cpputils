#pragma once

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
 * @file ccutl/types/convert.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type-conversion templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-05-10
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <cassert>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

#include "ccutl/types/checks.h"
#include "ccutl/types/compare.h"

namespace ccutl {
namespace types {

template <typename T>
/**
 * @brief Converts a value to an std::string std::ostringstream or another
 * available method.
 * T must be one of: bool, char, char *, const char *, signed
 * char, short, int, long, long long, unsigned char, unsigned short, unsigned
 * int, unsigned long, unsigned long long, float, double, long double, or
 * string. Signed, unsigned, and wide chars are treated as numbers.
 * @param value value to convert.
 * @param precision optional std::istringstream precision (for floating point
 * defaults to std::numeric_limits<T>::max_digits10; no default for other
 * types).
 * @return std::string converted value.
 */
std::string to_string(
    const T value,
    const std::optional<std::streamsize> &precision = std::nullopt) {
  static_assert(is_bool<T> || is_char<T> || is_char_p<T> || is_cst_char_p<T> ||
                    is_s_char<T> || is_short<T> || is_int<T> || is_long<T> ||
                    is_l_long<T> || is_u_char<T> || is_u_short<T> ||
                    is_u_int<T> || is_u_long<T> || is_ul_long<T> ||
                    is_float<T> || is_double<T> || is_l_double<T> ||
                    is_string<T>,
                "Bad type selected for ccutl::types::to_string");
  if constexpr (is_char_p<T> || is_cst_char_p<T> || is_string<T>) {
    return value;
  } else if constexpr (is_char<T>) {
    return {value};
  } else if constexpr (is_bool<T>) {
    return value ? "1" : "0";
  } else if constexpr (is_s_char<T>) {
    return to_string((short)(value), precision);
  } else if constexpr (is_u_char<T>) {
    return to_string((u_short)(value), precision);
  } else {
    std::ostringstream buff;
    if constexpr (is_float<T> || is_double<T> || is_l_double<T>) {
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
 * another available method. T must be one of: bool, char, const char *, signed
 * char, short, int, long, long long, unsigned char, unsigned short, unsigned
 * int, unsigned long, unsigned long long, float, double, long double, or
 * string. Signed, unsigned, and wide chars are treated as numbers.
 * @param value value to convert.
 * @param precision optional std::istringstream precision (for floating point
 * defaults to std::numeric_limits<T>::max_digits10; no default for other
 * types).
 * @return T converted value.
 */
T from_string(const std::string &value,
              const std::optional<std::streamsize> &precision = std::nullopt) {
  static_assert(is_bool<T> || is_char<T> || is_cst_char_p<T> || is_s_char<T> ||
                    is_short<T> || is_int<T> || is_long<T> || is_l_long<T> ||
                    is_u_char<T> || is_u_short<T> || is_u_int<T> ||
                    is_u_long<T> || is_ul_long<T> || is_float<T> ||
                    is_double<T> || is_l_double<T> || is_string<T>,
                "Bad type selected for ccutl::types::from_string");
  if constexpr (is_string<T>) {
    return value;
  } else if constexpr (is_cst_char_p<T>) {
    return value.c_str();
  } else if constexpr (is_char<T>) {
    assert(value.size() == 1);
    return value[0];
  } else if constexpr (is_bool<T>) {
    assert(value == "1" || value == "0");
    if (value == "1") return true;
    return false;
  } else if constexpr (is_short<T> || is_int<T>) {
    return std::stoi(value);
  } else if constexpr (is_long<T>) {
    return std::stol(value);
  } else if constexpr (is_u_long<T>) {
    return std::stoul(value);
  } else if constexpr (is_l_long<T>) {
    return std::stoll(value);
  } else if constexpr (is_ul_long<T>) {
    return std::stoull(value);
  } else if constexpr (is_u_short<T> || is_u_int<T>) {
    std::istringstream buff;
    buff.str(value);
    T result;
    buff >> result;
    return result;
  } else if constexpr (is_s_char<T>) {
    return (signed char)(from_string<short>((value), precision));
  } else if constexpr (is_u_char<T>) {
    return (u_char)(from_string<u_short>((value), precision));
  } else {
    std::istringstream buff;
    if constexpr (is_float<T> || is_double<T> || is_l_double<T>) {
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

}  // namespace types
}  // namespace ccutl
