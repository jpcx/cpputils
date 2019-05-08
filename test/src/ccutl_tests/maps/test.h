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
 * @file ccutl_tests/maps/test.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl::maps.
 * @version 0.3.0
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-07
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <string>
#include <type_traits>

#include "ccutl/maps/maps.h"
#include "ccutl/tests/testgroup.h"

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

/* /--------------------------------------------------------------------------/
  /--------------------- Test Group Generator Templates ---------------------/
 /--------------------------------------------------------------------------/ */

// /----------------------- Static Variable Accessors ----------------------/ //

template <typename T>
/** @brief Returns a preset static variable depending on the given type and
   variation. */
T get_test_var(u_short variation) {
  if (variation > 4) {
    throw "Bad key variation";
  }
  if constexpr (std::is_same_v<T, int>) {
    switch (variation) {
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
    switch (variation) {
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
    switch (variation) {
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
    switch (variation) {
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
  throw "Bad key type";
}

template <typename T>
/* @brief Returns a clean type name given a type. */
const char *get_test_type_name() {
  if constexpr (std::is_same_v<T, int>) {
    return "int";
  } else if constexpr (std::is_same_v<T, const char *>) {
    return "const char *";
  } else if constexpr (std::is_same_v<T, std::string>) {
    return "std::string";
  } else if constexpr (std::is_same_v<T, std::string *>) {
    return "std::string *";
  } else {
    throw "Bad key type";
  }
}

// /-------------------- One-Dimensional Type Pair Test --------------------/ //

template <typename T0, typename T1>
/** @brief Tests a pair of types for 1D ccutl::maps operations. */
void test_1D() {
  using ccutl::maps::create;
  using ccutl::maps::del;
  using ccutl::maps::get;
  using ccutl::maps::has;
  using ccutl::maps::set;
  using ccutl::tests::TestGroup;
  T0 key = get_test_var<T0>(0);
  T1 val = get_test_var<T1>(1);
  T0 bad_key = get_test_var<T0>(2);
  std::string title;
  title += "ccutl::maps | 1D | <";
  title += get_test_type_name<T0>();
  title += ", ";
  title += get_test_type_name<T1>();
  title += ">";
  auto tests = TestGroup(title);
  tests.assert_value(
      "ccutl::maps::has | returns true",
      [=]() {
        std::map<T0, T1> test = {{key, val}};
        return has(test, key);
      },
      true);
  tests.assert_value(
      "ccutl::maps::has | returns false",
      [=]() {
        std::map<T0, T1> test = {{key, val}};
        return has(test, bad_key);
      },
      false);
  tests.assert_value(
      "ccutl::maps::get | returns value",
      [=]() {
        std::map<T0, T1> test = {{key, val}};
        return get(test, key);
      },
      val);
  tests.assert_throws(
      "ccutl::maps::get | throws as expected",
      [=]() {
        std::map<T0, T1> test = {{key, val}};
        return get(test, bad_key);
      },
      "Key not found");
  tests.assert_value(
      "ccutl::maps::set | get returns set value",
      [=]() {
        std::map<T0, T1> test;
        set(&test, key, val);
        return get(test, key);
      },
      val);
  tests.assert_throws(
      "ccutl::maps::del | get throws only after del",
      [=]() {
        std::map<T0, T1> test = {{key, val}};
        try {
          get(test, key);
        } catch (...) {
          throw "Bad throw";
        }
        del(&test, key);
        return get(test, key);
      },
      "Key not found");
  tests.assert_value(
      "ccutl::maps::create | get returns created value",
      [=]() {
        auto test = create(key, val);
        return get(test, key);
      },
      val);
  tests.end();
}

// /------------------- Two-Dimensional Type Group Test --------------------/ //

template <typename T0, typename T1, typename T2>
/** @brief Test a group of types for 2D ccutl::maps operations. */
void test_2D() {
  using ccutl::maps::create;
  using ccutl::maps::del;
  using ccutl::maps::get;
  using ccutl::maps::has;
  using ccutl::maps::set;
  using ccutl::tests::TestGroup;
  T0 key_0 = get_test_var<T0>(0);
  T1 key_1 = get_test_var<T1>(1);
  T2 val = get_test_var<T2>(2);
  T0 bad_key_0 = get_test_var<T0>(3);
  T1 bad_key_1 = get_test_var<T1>(4);
  std::string title;
  title += "ccutl::maps | 2D | <";
  title += get_test_type_name<T0>();
  title += ", ";
  title += get_test_type_name<T1>();
  title += ", ";
  title += get_test_type_name<T2>();
  title += ">";
  auto tests = TestGroup(title);
  tests.assert_value(
      "ccutl::maps::has | returns true",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return has(test, key_0, key_1);
      },
      true);
  tests.assert_value(
      "ccutl::maps::has | bad parent returns false",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return has(test, bad_key_0, key_1);
      },
      false);
  tests.assert_value(
      "ccutl::maps::has | bad child returns false",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return has(test, key_0, bad_key_1);
      },
      false);
  tests.assert_value(
      "ccutl::maps::has | bad both returns false",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return has(test, bad_key_0, bad_key_1);
      },
      false);
  tests.assert_value(
      "ccutl::maps::get | returns value",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return get(test, key_0, key_1);
      },
      val);
  tests.assert_throws(
      "ccutl::maps::get | throws bad parent as expected",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return get(test, bad_key_0, key_1);
      },
      "Key not found");
  tests.assert_throws(
      "ccutl::maps::get | throws bad child as expected",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return get(test, key_0, bad_key_1);
      },
      "Key not found");
  tests.assert_throws(
      "ccutl::maps::get | throws bad both as expected",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        return get(test, bad_key_0, bad_key_1);
      },
      "Key not found");
  tests.assert_value(
      "ccutl::maps::set | get returns set value",
      [=]() {
        std::map<T0, std::map<T1, T2>> test;
        set(&test, key_0, key_1, val);
        return get(test, key_0, key_1);
      },
      val);
  tests.assert_throws(
      "ccutl::maps::del | get throws only after parent del",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        try {
          get(test, key_0, key_1);
        } catch (...) {
          throw "Bad throw";
        }
        del(&test, key_0);
        return get(test, key_0, key_1);
      },
      "Key not found");
  tests.assert_throws(
      "ccutl::maps::del | get throws only after child del",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        try {
          get(test, key_0, key_1);
        } catch (...) {
          throw "Bad throw";
        }
        del(&test, key_0, key_1);
        return get(test, key_0, key_1);
      },
      "Key not found");
  tests.assert_throws(
      "ccutl::maps::del | get throws only after both del",
      [=]() {
        std::map<T0, std::map<T1, T2>> test = {{key_0, {{key_1, val}}}};
        try {
          get(test, key_0, key_1);
        } catch (...) {
          throw "Bad throw";
        }
        del(&test, key_0, key_1);
        del(&test, key_0);
        return get(test, key_0, key_1);
      },
      "Key not found");
  tests.assert_value(
      "ccutl::maps::create | get returns created value",
      [=]() {
        auto test = create(key_0, key_1, val);
        return get(test, key_0, key_1);
      },
      val);
  tests.end();
}

/* /--------------------------------------------------------------------------/
  /-------------------------- Function Declarations -------------------------/
 /--------------------------------------------------------------------------/ */

/** @brief Tests all permutations of a set of types for all one-dimensional
 * ccutl::maps operations. */
void one_dimensional_tests();

/** @brief Tests all permutations of a set of types for all two-dimensional
 * ccutl::maps operations. */
void two_dimensional_tests();

/** @brief Launches all available tests */
void run_tests();

}  // namespace maps
}  // namespace ccutl_tests
