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
 * @file ccutl_tests/limits.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl/limits.h.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-06-08
 * @date modified 2019-06-26
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <limits>
#include <string>

#include "ccutl_test.h"

#include "ccutl/limits.h"

namespace ccutl_tests {

namespace limits {
static constexpr int int_max = ccutl::max_v<int>;
static constexpr uint uint_max = ccutl::max_v<uint>;
static constexpr float float_max = ccutl::max_v<float>;
static constexpr int int_min = ccutl::min_v<int>;
static constexpr float float_min = ccutl::min_v<float>;
}	// namespace limits

CCUTL_TEST(limits_max_v, general) {
	// signed value should equal std::numeric_limits
	ASSERT_EQ(ccutl::max_v<int>, std::numeric_limits<int>::max());
	// unsigned value should equal std::numeric_limits
	ASSERT_EQ(ccutl::max_v<u_int>, std::numeric_limits<u_int>::max());
}

CCUTL_TEST(limits_min_v, general) {
	// signed value should equal std::numeric_limits
	ASSERT_EQ(ccutl::min_v<int>, std::numeric_limits<int>::lowest());
	// unsigned value should equal std::numeric_limits
	ASSERT_EQ(ccutl::min_v<u_int>, std::numeric_limits<u_int>::lowest());
}

CCUTL_TEST(limits_is_val_overflow, general) {
	// should detect uint_max -> int overflow
	ASSERT_EQ(ccutl::is_val_overflow<int>(limits::uint_max), true);
	// should detect int_max -> no int overflow
	ASSERT_EQ(ccutl::is_val_overflow<int>(limits::int_max), false);
	// should detect int_min -> uint overflow
	ASSERT_EQ(ccutl::is_val_overflow<uint>(limits::int_min), true);
	// should detect int_min -> no int overflow
	ASSERT_EQ(ccutl::is_val_overflow<int>(limits::int_min), false);
}

#ifndef LIMITS_IS_ADD_OVERFLOW
#define LIMITS_IS_ADD_OVERFLOW(a, b, type, expected)         \
	{                                                          \
		ASSERT_EQ(ccutl::is_add_overflow<type>(a, b), expected); \
		ASSERT_EQ(ccutl::is_add_overflow<type>(b, a), expected); \
	}
#endif

CCUTL_TEST(limits_is_add_overflow, signed_edge_cases) {
	LIMITS_IS_ADD_OVERFLOW(0, 0, int, false);
	LIMITS_IS_ADD_OVERFLOW(0, -1, int, false);
	LIMITS_IS_ADD_OVERFLOW(0, 1, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_max, 1, int, true);
	LIMITS_IS_ADD_OVERFLOW(limits::int_max, 0, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_max, -1, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_max, limits::int_min, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_min, 1, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_min, 0, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_min, -1, int, true);
}

CCUTL_TEST(limits_is_add_overflow, signed_general_cases) {
	LIMITS_IS_ADD_OVERFLOW(limits::int_max / 2, limits::int_max / 2, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_min / 2, limits::int_min / 2, int, false);
	LIMITS_IS_ADD_OVERFLOW(limits::int_max / 2, limits::int_max, int, true);
	LIMITS_IS_ADD_OVERFLOW(limits::int_min / 2, limits::int_min, int, true);
}

CCUTL_TEST(limits_is_add_overflow, unsigned_limits) {
	LIMITS_IS_ADD_OVERFLOW(0, 0, u_int, false);
	LIMITS_IS_ADD_OVERFLOW(0, -1, u_int, true);
	LIMITS_IS_ADD_OVERFLOW(0, 1, u_int, false);
	LIMITS_IS_ADD_OVERFLOW(0U, -1, u_int, true);
	LIMITS_IS_ADD_OVERFLOW(0U, 1, u_int, false);
	LIMITS_IS_ADD_OVERFLOW(0U, 1U, u_int, false);
}

CCUTL_TEST(limits_is_add_overflow, unsigned_arguments) {
	LIMITS_IS_ADD_OVERFLOW(0U, -1, int, false);
	LIMITS_IS_ADD_OVERFLOW(0U, 1, int, false);
	LIMITS_IS_ADD_OVERFLOW(0U, 1U, int, false);
}

CCUTL_TEST(limits_is_add_overflow, float_edge_cases) {
	LIMITS_IS_ADD_OVERFLOW(0, 0, float, false);
	LIMITS_IS_ADD_OVERFLOW(limits::float_max, limits::float_max, float, true);
	LIMITS_IS_ADD_OVERFLOW(limits::float_min, limits::float_min, float, true);
	LIMITS_IS_ADD_OVERFLOW(limits::float_max, limits::float_min, float, false);
}

CCUTL_TEST(limits_is_add_overflow, float_general_cases) {
	LIMITS_IS_ADD_OVERFLOW(limits::float_max / 2, limits::float_max / 2, float,
												 false);
	LIMITS_IS_ADD_OVERFLOW(limits::float_min / 2, limits::float_min / 2, float,
												 false);
	LIMITS_IS_ADD_OVERFLOW(limits::float_max / 2, limits::float_max, float, true);
	LIMITS_IS_ADD_OVERFLOW(limits::float_min / 2, limits::float_min, float, true);
}

#undef LIMITS_IS_ADD_OVERFLOW

#ifndef LIMITS_SUB_OVERFLOW
#define LIMITS_SUB_OVERFLOW(a, b, type, expected) \
	ASSERT_EQ(ccutl::is_sub_overflow<type>(a, b), expected)
#endif

CCUTL_TEST(limits_is_sub_overflow, signed_edge_cases) {
	LIMITS_SUB_OVERFLOW(0, 0, int, false);
	LIMITS_SUB_OVERFLOW(0, -1, int, false);
	LIMITS_SUB_OVERFLOW(0, 1, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_max, 1, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_max, 0, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_max, -1, int, true);
	LIMITS_SUB_OVERFLOW(limits::int_max, limits::int_max, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_min, limits::int_min, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_min, 1, int, true);
	LIMITS_SUB_OVERFLOW(limits::int_min, 0, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_min, -1, int, false);
}

CCUTL_TEST(limits_is_sub_overflow, signed_general_cases) {
	LIMITS_SUB_OVERFLOW(limits::int_max / 2, limits::int_max / 2, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_min / 2, limits::int_min / 2, int, false);
	LIMITS_SUB_OVERFLOW(limits::int_max / 2, limits::int_min, int, true);
	LIMITS_SUB_OVERFLOW(limits::int_min / 2, limits::int_max, int, true);
}

CCUTL_TEST(limits_is_sub_overflow, unsigned_limits) {
	LIMITS_SUB_OVERFLOW(0, 0, u_int, false);
	LIMITS_SUB_OVERFLOW(0, -1, u_int, false);
	LIMITS_SUB_OVERFLOW(0, 1, u_int, true);
	LIMITS_SUB_OVERFLOW(0U, -1, u_int, false);
	LIMITS_SUB_OVERFLOW(0U, 1, u_int, true);
	LIMITS_SUB_OVERFLOW(0U, 1U, u_int, true);
}

CCUTL_TEST(limits_is_sub_overflow, unsigned_arguments) {
	LIMITS_SUB_OVERFLOW(0U, -1, int, false);
	LIMITS_SUB_OVERFLOW(0U, 1, int, false);
	LIMITS_SUB_OVERFLOW(0U, 1U, int, false);
}

CCUTL_TEST(limits_is_sub_overflow, float_edge_cases) {
	LIMITS_SUB_OVERFLOW(0, 0, float, false);
	LIMITS_SUB_OVERFLOW(limits::float_max, limits::float_max, float, false);
	LIMITS_SUB_OVERFLOW(limits::float_min, limits::float_min, float, false);
	LIMITS_SUB_OVERFLOW(limits::float_max, limits::float_min, float, true);
}

CCUTL_TEST(limits_is_sub_overflow, float_general_cases) {
	LIMITS_SUB_OVERFLOW(limits::float_max / 2, limits::float_max / 2, float,
											false);
	LIMITS_SUB_OVERFLOW(limits::float_min / 2, limits::float_min / 2, float,
											false);
	LIMITS_SUB_OVERFLOW(limits::float_max / 2, limits::float_min, float, true);
	LIMITS_SUB_OVERFLOW(limits::float_min / 2, limits::float_max, float, true);
}

#undef LIMITS_SUB_OVERFLOW

}	// namespace ccutl_tests
