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
 * @file test/maps.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl/maps.h.
 * @version 0.3.1
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-11
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <map>
#include <string>
#include <type_traits>

#include "ccutl_test.h"

#include "ccutl/maps.h"

namespace ccutl_tests {
namespace maps {

/* /--------------------------------------------------------------------------/
	/------------------------ Static Testing Variables ------------------------/
 /--------------------------------------------------------------------------/ */

// /---------------------------------- int ---------------------------------/ //

static int int_0 = 42;
static int int_1 = 1337;
static int int_2 = 9001;
static int int_3 = 404;
static int int_4 = 31415;

// /----------------------------- const char * -----------------------------/ //

static const char *ccharp_0 = "foo";
static const char *ccharp_1 = "bar";
static const char *ccharp_2 = "baz";
static const char *ccharp_3 = "quz";
static const char *ccharp_4 = "quz";

// /-------------------------------- object --------------------------------/ //

static std::string obj_0 = ccharp_0;
static std::string obj_1 = ccharp_1;
static std::string obj_2 = ccharp_2;
static std::string obj_3 = ccharp_3;
static std::string obj_4 = ccharp_4;

// /-------------------------------- pointer -------------------------------/ //

static auto *ptr_0 = &obj_0;
static auto *ptr_1 = &obj_1;
static auto *ptr_2 = &obj_2;
static auto *ptr_3 = &obj_3;
static auto *ptr_4 = &obj_4;

template <typename T, u_char Variation>
/** @brief Returns a preset static variable depending on the given type and
	 variation. */
T test_var() {
	static_assert(Variation <= 4, "Bad key variation");
	if constexpr (std::is_same_v<T, int>) {
		switch (Variation) {
			case 0:
				return int_0;
				break;
			case 1:
				return int_1;
				break;
			case 2:
				return int_2;
				break;
			case 3:
				return int_3;
				break;
			case 4:
				return int_4;
				break;
		}
	} else if constexpr (std::is_same_v<T, const char *>) {
		switch (Variation) {
			case 0:
				return ccharp_0;
				break;
			case 1:
				return ccharp_1;
				break;
			case 2:
				return ccharp_2;
				break;
			case 3:
				return ccharp_3;
				break;
			case 4:
				return ccharp_4;
				break;
		}
	} else if constexpr (std::is_same_v<T, std::string>) {
		switch (Variation) {
			case 0:
				return obj_0;
				break;
			case 1:
				return obj_1;
				break;
			case 2:
				return obj_2;
				break;
			case 3:
				return obj_3;
				break;
			case 4:
				return obj_4;
				break;
		}
	} else if constexpr (std::is_same_v<T, std::string *>) {
		switch (Variation) {
			case 0:
				return ptr_0;
				break;
			case 1:
				return ptr_1;
				break;
			case 2:
				return ptr_2;
				break;
			case 3:
				return ptr_3;
				break;
			case 4:
				return ptr_4;
				break;
		}
	}
}

}	// namespace maps

#ifndef MAP_HAS_TEST_1D
#define MAP_HAS_TEST_1D(t0, t1)                     \
	{                                                 \
		t0 key = maps::test_var<t0, 0>();               \
		t1 val = maps::test_var<t1, 1>();               \
		t0 bad_key = maps::test_var<t0, 2>();           \
		std::map<t0, t1> map = {{key, val}};            \
		ASSERT_EQ(ccutl::map_has(map, key), true);      \
		ASSERT_EQ(ccutl::map_has(map, bad_key), false); \
	}
#endif

CCUTL_TEST(maps_map_has, general_1d) {
	MAP_HAS_TEST_1D(int, int);
	MAP_HAS_TEST_1D(int, const char *);
	MAP_HAS_TEST_1D(int, std::string);
	MAP_HAS_TEST_1D(int, std::string *);
	MAP_HAS_TEST_1D(const char *, int);
	MAP_HAS_TEST_1D(const char *, const char *);
	MAP_HAS_TEST_1D(const char *, std::string);
	MAP_HAS_TEST_1D(const char *, std::string *);
	MAP_HAS_TEST_1D(std::string, int);
	MAP_HAS_TEST_1D(std::string, const char *);
	MAP_HAS_TEST_1D(std::string, std::string);
	MAP_HAS_TEST_1D(std::string, std::string *);
	MAP_HAS_TEST_1D(std::string *, int);
	MAP_HAS_TEST_1D(std::string *, const char *);
	MAP_HAS_TEST_1D(std::string *, std::string);
	MAP_HAS_TEST_1D(std::string *, std::string *);
}

#undef MAP_HAS_TEST_1D

#ifndef MAP_HAS_TEST_2D
#define MAP_HAS_TEST_2D(t0, t1, t2)                                \
	{                                                                \
		t0 key_0 = maps::test_var<t0, 0>();                            \
		t1 key_1 = maps::test_var<t1, 1>();                            \
		t2 val = maps::test_var<t2, 2>();                              \
		t0 bad_key_0 = maps::test_var<t0, 3>();                        \
		t1 bad_key_1 = maps::test_var<t1, 4>();                        \
		std::map<t0, t2> map_1d = {{key_0, val}};                      \
		std::map<t1, t2> map_2d_pre = {{key_1, val}};                  \
		std::map<t0, std::map<t1, t2>> map_2d = {{key_0, map_2d_pre}}; \
		ASSERT_EQ(ccutl::map_has(map_2d, key_0), true);                \
		ASSERT_EQ(ccutl::map_has(map_2d, key_0, key_1), true);         \
		ASSERT_EQ(ccutl::map_has(map_2d, bad_key_0), false);           \
		ASSERT_EQ(ccutl::map_has(map_2d, bad_key_0, key_1), false);    \
		ASSERT_EQ(ccutl::map_has(map_2d, key_0, bad_key_1), false);    \
	}
#endif

CCUTL_TEST(maps_map_has, general_2d) {
	MAP_HAS_TEST_2D(int, int, int);
	MAP_HAS_TEST_2D(int, int, const char *);
	MAP_HAS_TEST_2D(int, int, std::string);
	MAP_HAS_TEST_2D(int, int, std::string *);
	MAP_HAS_TEST_2D(int, const char *, int);
	MAP_HAS_TEST_2D(int, const char *, const char *);
	MAP_HAS_TEST_2D(int, const char *, std::string);
	MAP_HAS_TEST_2D(int, const char *, std::string *);
	MAP_HAS_TEST_2D(int, std::string, int);
	MAP_HAS_TEST_2D(int, std::string, const char *);
	MAP_HAS_TEST_2D(int, std::string, std::string);
	MAP_HAS_TEST_2D(int, std::string, std::string *);
	MAP_HAS_TEST_2D(int, std::string *, int);
	MAP_HAS_TEST_2D(int, std::string *, const char *);
	MAP_HAS_TEST_2D(int, std::string *, std::string);
	MAP_HAS_TEST_2D(int, std::string *, std::string *);
	MAP_HAS_TEST_2D(const char *, int, int);
	MAP_HAS_TEST_2D(const char *, int, const char *);
	MAP_HAS_TEST_2D(const char *, int, std::string);
	MAP_HAS_TEST_2D(const char *, int, std::string *);
	MAP_HAS_TEST_2D(const char *, const char *, int);
	MAP_HAS_TEST_2D(const char *, const char *, const char *);
	MAP_HAS_TEST_2D(const char *, const char *, std::string);
	MAP_HAS_TEST_2D(const char *, const char *, std::string *);
	MAP_HAS_TEST_2D(const char *, std::string, int);
	MAP_HAS_TEST_2D(const char *, std::string, const char *);
	MAP_HAS_TEST_2D(const char *, std::string, std::string);
	MAP_HAS_TEST_2D(const char *, std::string, std::string *);
	MAP_HAS_TEST_2D(const char *, std::string *, int);
	MAP_HAS_TEST_2D(const char *, std::string *, const char *);
	MAP_HAS_TEST_2D(const char *, std::string *, std::string);
	MAP_HAS_TEST_2D(const char *, std::string *, std::string *);
	MAP_HAS_TEST_2D(std::string, int, int);
	MAP_HAS_TEST_2D(std::string, int, const char *);
	MAP_HAS_TEST_2D(std::string, int, std::string);
	MAP_HAS_TEST_2D(std::string, int, std::string *);
	MAP_HAS_TEST_2D(std::string, const char *, int);
	MAP_HAS_TEST_2D(std::string, const char *, const char *);
	MAP_HAS_TEST_2D(std::string, const char *, std::string);
	MAP_HAS_TEST_2D(std::string, const char *, std::string *);
	MAP_HAS_TEST_2D(std::string, std::string, int);
	MAP_HAS_TEST_2D(std::string, std::string, const char *);
	MAP_HAS_TEST_2D(std::string, std::string, std::string);
	MAP_HAS_TEST_2D(std::string, std::string, std::string *);
	MAP_HAS_TEST_2D(std::string, std::string *, int);
	MAP_HAS_TEST_2D(std::string, std::string *, const char *);
	MAP_HAS_TEST_2D(std::string, std::string *, std::string);
	MAP_HAS_TEST_2D(std::string, std::string *, std::string *);
	MAP_HAS_TEST_2D(std::string *, int, int);
	MAP_HAS_TEST_2D(std::string *, int, const char *);
	MAP_HAS_TEST_2D(std::string *, int, std::string);
	MAP_HAS_TEST_2D(std::string *, int, std::string *);
	MAP_HAS_TEST_2D(std::string *, const char *, int);
	MAP_HAS_TEST_2D(std::string *, const char *, const char *);
	MAP_HAS_TEST_2D(std::string *, const char *, std::string);
	MAP_HAS_TEST_2D(std::string *, const char *, std::string *);
	MAP_HAS_TEST_2D(std::string *, std::string, int);
	MAP_HAS_TEST_2D(std::string *, std::string, const char *);
	MAP_HAS_TEST_2D(std::string *, std::string, std::string);
	MAP_HAS_TEST_2D(std::string *, std::string, std::string *);
	MAP_HAS_TEST_2D(std::string *, std::string *, int);
	MAP_HAS_TEST_2D(std::string *, std::string *, const char *);
	MAP_HAS_TEST_2D(std::string *, std::string *, std::string);
	MAP_HAS_TEST_2D(std::string *, std::string *, std::string *);
}

#undef MAP_HAS_TEST_2D
#undef COMBINATORIAL_TEST_CALL

}	// namespace ccutl_tests
