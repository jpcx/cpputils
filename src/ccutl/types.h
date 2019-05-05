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
 * @file ccutl/types/types.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type-related templates.
 * @version 0.1.0
 * @since cpputils 0.3.0
 * @date created 2019-05-05
 * @date modified 2019-05-05
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <type_traits>

namespace ccutl {
namespace types {

template <typename T>
/** @brief Either const T& if T is an object or const T if T is a pointer or
   fundamental value. */
using const_ref_or_v = typename std::conditional_t<
    !std::is_fundamental_v<T> && !std::is_pointer_v<T>, const T &, const T>;

}  // namespace types
}  // namespace ccutl
