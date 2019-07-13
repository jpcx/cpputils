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
 * @file ccutl_tests/compare.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl/compare.h.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-21
 * @date modified 2019-06-26
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <iostream>

#include "ccutl_test.h"

#include "ccutl/compare.h"

namespace ccutl_tests {

CCUTL_TEST(compare_are_equal, general) {
	EXPECT_EQ(ccutl::are_equal("foo", "foo"), true);
	EXPECT_EQ(ccutl::are_equal("foo", "bar"), false);
	EXPECT_EQ(ccutl::are_equal(std::string("foo"), std::string("foo")), true);
	EXPECT_EQ(ccutl::are_equal(std::string("foo"), std::string("bar")), false);
	EXPECT_EQ(ccutl::are_equal(42, 42), true);
	EXPECT_EQ(ccutl::are_equal(42, 24), false);
}

#ifndef COMPARE_NCMP
#define COMPARE_NCMP(a, b, a_type, b_type, desired)                      \
	EXPECT_EQ(ccutl::ncmp(static_cast<a_type>(a), static_cast<b_type>(b)), \
						desired)
#endif
#ifndef COMPARE_NCMP_GEN
#define COMPARE_NCMP_GEN(n_a, n_b)                       \
	{                                                      \
		constexpr auto n_greater = n_a > n_b ? n_a : n_b;    \
		constexpr auto n_lesser = n_a > n_b ? n_b : n_a;     \
		COMPARE_NCMP(n_lesser, n_greater, int, int, -1);     \
		COMPARE_NCMP(n_lesser, n_greater, int, float, -1);   \
		COMPARE_NCMP(n_lesser, n_greater, float, int, -1);   \
		COMPARE_NCMP(n_lesser, n_greater, float, float, -1); \
		COMPARE_NCMP(n_greater, n_lesser, int, int, 1);      \
		COMPARE_NCMP(n_greater, n_lesser, int, float, 1);    \
		COMPARE_NCMP(n_greater, n_lesser, float, int, 1);    \
		COMPARE_NCMP(n_greater, n_lesser, float, float, 1);  \
		COMPARE_NCMP(n_lesser, n_lesser, int, int, 0);       \
		COMPARE_NCMP(n_greater, n_greater, int, int, 0);     \
		if constexpr (n_greater >= 0) {                      \
			COMPARE_NCMP(n_lesser, n_greater, int, uint, -1);  \
			COMPARE_NCMP(n_greater, n_lesser, uint, int, 1);   \
			COMPARE_NCMP(n_greater, n_greater, uint, uint, 0); \
			COMPARE_NCMP(n_greater, n_greater, int, uint, 0);  \
			COMPARE_NCMP(n_greater, n_greater, uint, int, 0);  \
		}                                                    \
		if constexpr (n_lesser >= 0) {                       \
			COMPARE_NCMP(n_lesser, n_greater, uint, int, -1);  \
			COMPARE_NCMP(n_greater, n_lesser, int, uint, 1);   \
			COMPARE_NCMP(n_lesser, n_lesser, uint, uint, 0);   \
			COMPARE_NCMP(n_lesser, n_lesser, int, uint, 0);    \
			COMPARE_NCMP(n_lesser, n_lesser, uint, int, 0);    \
		}                                                    \
		if constexpr (n_greater >= 0 && n_lesser >= 0) {     \
			COMPARE_NCMP(n_lesser, n_greater, uint, uint, -1); \
			COMPARE_NCMP(n_greater, n_lesser, uint, uint, 1);  \
			COMPARE_NCMP(n_lesser, n_lesser, uint, uint, 0);   \
			COMPARE_NCMP(n_greater, n_greater, uint, uint, 0); \
		}                                                    \
	}

#endif

CCUTL_TEST(compare_ncmp, general) {
	COMPARE_NCMP_GEN(4321, 1234);
	COMPARE_NCMP_GEN(4321, -1234);
	COMPARE_NCMP_GEN(-1234, -4321);
}

#undef COMPARE_NCMP
#undef COMPARE_NCMP_GEN

}	// namespace ccutl_tests
