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
 * @file ccutl/types/compare.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type-comparison functions.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-05-09
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <cstring>
#include <type_traits>

#include "ccutl/types/checks.h"

namespace ccutl {
namespace types {

template <typename T_A, typename T_B>
/** @brief Checks equality of two values based on type; uses strncmp if
   necessary. */
constexpr bool are_equal(const T_A a, const T_B b) {
  if constexpr (std::is_same_v<T_A, T_B>) {
    if constexpr (is_cst_char_p<T_A>) {
      auto a_len = strlen(a);
      return a_len == strlen(b) && strncmp(a, b, a_len) == 0;
    } else {
      return a == b;
    }
  } else {
    return false;
  }
}

}  // namespace types
}  // namespace ccutl
