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
 * @file ccutl_tests/convert.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl/convert.h.
 * @version 0.1.1
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-06-26
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <string>
#include <string_view>

#include "ccutl_test.h"

#include "ccutl/convert.h"

namespace ccutl_tests {
namespace convert {

template <typename T>
/** @brief constexpr iife for test variable by type */
constexpr T tf_string_val = ([]() constexpr->T {
	using namespace ccutl;
	if constexpr (are_decay_same_v<T, bool>) return true;
	if constexpr (are_decay_same_v<T, char>) return 'z';
	if constexpr (are_decay_same_v<T, const char *>) return "foo";
	if constexpr (are_decay_same_v<T, signed char> ||
								are_decay_same_v<T, short> || are_decay_same_v<T, int> ||
								are_decay_same_v<T, long> || are_decay_same_v<T, long long> ||
								are_decay_same_v<T, u_char> || are_decay_same_v<T, u_short> ||
								are_decay_same_v<T, u_int> || are_decay_same_v<T, u_long> ||
								are_decay_same_v<T, unsigned long long>)
		return 42;
	if constexpr (are_decay_same_v<T, float>) return 3.14159274F;
	if constexpr (are_decay_same_v<T, double>) return 3.1415926535897931;
	if constexpr (are_decay_same_v<T, long double>) return 3.141592653589793116L;
})();

template <typename T>
/** @brief constexpr iife for expected variable by type */
constexpr const char *tf_string_str = ([]() constexpr->const char * {
	using namespace ccutl;
	if constexpr (are_decay_same_v<T, bool>) return "1";
	if constexpr (are_decay_same_v<T, char>) return "z";
	if constexpr (are_decay_same_v<T, char *>) return "foo";
	if constexpr (are_decay_same_v<T, signed char> ||
								are_decay_same_v<T, short> || are_decay_same_v<T, int> ||
								are_decay_same_v<T, long> || are_decay_same_v<T, long long> ||
								are_decay_same_v<T, u_char> || are_decay_same_v<T, u_short> ||
								are_decay_same_v<T, u_int> || are_decay_same_v<T, u_long> ||
								are_decay_same_v<T, unsigned long long>)
		return "42";
	if constexpr (are_decay_same_v<T, float>) return "3.14159274";
	if constexpr (are_decay_same_v<T, double>) return "3.1415926535897931";
	if constexpr (are_decay_same_v<T, long double>) return "3.141592653589793116";
})();

}	// namespace convert

#ifndef CONVERT_TO_STRING
#define CONVERT_TO_STRING(T)                             \
	ASSERT_EQ(ccutl::to_string(convert::tf_string_val<T>), \
						std::string(convert::tf_string_str<T>))
#endif

CCUTL_TEST(convert_to_string, general) {
	CONVERT_TO_STRING(bool);
	CONVERT_TO_STRING(char);
	CONVERT_TO_STRING(const char *);
	CONVERT_TO_STRING(signed char);
	CONVERT_TO_STRING(short);
	CONVERT_TO_STRING(int);
	CONVERT_TO_STRING(long);
	CONVERT_TO_STRING(long long);
	CONVERT_TO_STRING(u_char);
	CONVERT_TO_STRING(u_short);
	CONVERT_TO_STRING(unsigned);
	CONVERT_TO_STRING(u_long);
	CONVERT_TO_STRING(unsigned long long);
	CONVERT_TO_STRING(float);
	CONVERT_TO_STRING(double);
	CONVERT_TO_STRING(long double);
}

#undef CONVERT_TO_STRING

}	// namespace ccutl_tests
