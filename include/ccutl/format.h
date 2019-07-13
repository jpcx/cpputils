#ifndef CPPUTILS_CCUTL_FORMAT_H_
#define CPPUTILS_CCUTL_FORMAT_H_

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
 * @file ccutl/format.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various text formatting templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-05
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/format.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <type_traits>
#include <vector>

#include "ccutl/algorithm.h"
#include "ccutl/type_traits.h"

namespace ccutl {

template <typename T,
					std::enable_if_t<std::is_constructible_v<std::string, T> &&
													 are_const_iterable_v<T>>*>
std::string trim_space(const T& text) {
	using std::string;
	string result;
	bool found_text = false;
	bool proc_space = true;
	string buffer;
	for_each_it(text, [&](const auto& v) {
		if (found_text) {
			if (proc_space) {
				if (isspace(v)) {
					buffer += v;
				} else {
					proc_space = false;
					result += buffer;
					result += v;
					buffer = "";
				}
			} else {
				if (isspace(v)) {
					proc_space = true;
					buffer += v;
				} else {
					result += v;
				}
			}
		} else if (!isspace(v)) {
			found_text = true;
			proc_space = false;
			result += v;
		}
	});
	return result;
}

template <typename T,
					std::enable_if_t<std::is_constructible_v<std::string, T> &&
													 !are_const_iterable_v<T>>*>
std::string trim_space(const T& text) {
	return trim_space(std::string(text));
}

template <typename TStr, typename TNum,
					std::enable_if_t<std::is_constructible_v<std::string, TStr> &&
													 std::is_integral_v<TNum>>*>
std::string string_repeat(TNum n_repeat, const TStr& input) {
	std::string output = "";
	for (size_t i = 0; i < n_repeat; ++i) {
		output += input;
	}
	return output;
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_FORMAT_H_
