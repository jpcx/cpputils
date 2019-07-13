#ifndef CPPUTILS_CCUTL_CORE_CONVERT_H_
#define CPPUTILS_CCUTL_CORE_CONVERT_H_

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
 * @file ccutl/core/convert.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type-conversion templates.
 * @version 0.1.1
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <limits>
#include <optional>
#include <sstream>
#include <string>

#include "ccutl/type_traits.h"

namespace ccutl {

template <typename T,
					std::enable_if_t<are_streamable_to_v<std::ostream, T>> * = nullptr>
std::string to_string(
		const T value,
		const std::optional<std::streamsize> &precision = std::nullopt);

template <typename T>
T from_string(const std::string &value,
							const std::optional<std::streamsize> &precision = std::nullopt);

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_CONVERT_H_
