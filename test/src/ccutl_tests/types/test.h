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
 * @file ccutl_tests/types/test.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl::types.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-05-11
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <string>
#include <string_view>

#include "ccutl/tests/testgroup.h"
#include "ccutl/types/checks.h"
#include "ccutl/types/convert.h"

namespace ccutl_tests {
namespace types {

/* /--------------------------------------------------------------------------/
  /------------------ Miscelaneous Static Testing Variables -----------------/
 /--------------------------------------------------------------------------/ */

static char char_arr[4] = {'f', 'o', 'o', '\0'};

/* /--------------------------------------------------------------------------/
  /----------- to_string && from_string Testing Variable Templates ----------/
 /--------------------------------------------------------------------------/ */

template <typename T>
/** @brief iife for test variable by type */
constexpr T tf_string_val = ([=]() constexpr->T {
  using namespace ccutl::types;
  static_assert(is_bool<T> || is_char<T> || is_cst_char_p<T> || is_char_p<T> ||
                    is_s_char<T> || is_short<T> || is_int<T> || is_long<T> ||
                    is_l_long<T> || is_u_char<T> || is_u_short<T> ||
                    is_u_int<T> || is_u_long<T> || is_ul_long<T> ||
                    is_float<T> || is_double<T> || is_l_double<T>,
                "Bad type selected for ccutl_tests::types::tf_string_val");
  if constexpr (is_bool<T>) return true;
  if constexpr (is_char<T>) return 'z';
  if constexpr (is_cst_char_p<T>) return "foo";
  if constexpr (is_char_p<T>) return char_arr;
  if constexpr (is_s_char<T> || is_short<T> || is_int<T> || is_long<T> ||
                is_l_long<T> || is_u_char<T> || is_u_short<T> || is_u_int<T> ||
                is_u_long<T> || is_ul_long<T>)
    return 42;
  if constexpr (is_float<T>) return 3.14159274F;
  if constexpr (is_double<T>) return 3.1415926535897931;
  if constexpr (is_l_double<T>) return 3.141592653589793116L;
})();

template <typename T>
/** @brief iife for expected variable by type */
constexpr const char *tf_string_str = ([=]() constexpr->const char * {
  using namespace ccutl::types;
  static_assert(is_bool<T> || is_char<T> || is_cst_char_p<T> || is_char_p<T> ||
                    is_s_char<T> || is_short<T> || is_int<T> || is_long<T> ||
                    is_l_long<T> || is_u_char<T> || is_u_short<T> ||
                    is_u_int<T> || is_u_long<T> || is_ul_long<T> ||
                    is_float<T> || is_double<T> || is_l_double<T>,
                "Bad type selected for ccutl_tests::types::tf_string_str");
  if constexpr (is_bool<T>) return "1";
  if constexpr (is_char<T>) return "z";
  if constexpr (is_cst_char_p<T> || is_char_p<T>) return "foo";
  if constexpr (is_s_char<T> || is_short<T> || is_int<T> || is_long<T> ||
                is_l_long<T> || is_u_char<T> || is_u_short<T> || is_u_int<T> ||
                is_u_long<T> || is_ul_long<T>)
    return "42";
  if constexpr (is_float<T>) return "3.14159274";
  if constexpr (is_double<T>) return "3.1415926535897931";
  if constexpr (is_l_double<T>) return "3.141592653589793116";
})();

template <typename T>
/** @brief iife for test title */
constexpr const char *type_name = ([=]() constexpr->const char * {
  using namespace ccutl::types;
  static_assert(is_bool<T> || is_char<T> || is_cst_char_p<T> || is_char_p<T> ||
                    is_s_char<T> || is_short<T> || is_int<T> || is_long<T> ||
                    is_l_long<T> || is_u_char<T> || is_u_short<T> ||
                    is_u_int<T> || is_u_long<T> || is_ul_long<T> ||
                    is_float<T> || is_double<T> || is_l_double<T>,
                "Bad type selected for ccutl_tests::types::type_name");
  if constexpr (is_bool<T>) return "bool";
  if constexpr (is_char<T>) return "char";
  if constexpr (is_cst_char_p<T>) return "const char *";
  if constexpr (is_char_p<T>) return "char *";
  if constexpr (is_s_char<T>) return "signed char";
  if constexpr (is_short<T>) return "short";
  if constexpr (is_int<T>) return "int";
  if constexpr (is_long<T>) return "long";
  if constexpr (is_l_long<T>) return "long long";
  if constexpr (is_u_char<T>) return "unsigned char";
  if constexpr (is_u_short<T>) return "unsigned short";
  if constexpr (is_u_int<T>) return "unsigned int";
  if constexpr (is_u_long<T>) return "unsigned long";
  if constexpr (is_ul_long<T>) return "unsigned long long";
  if constexpr (is_float<T>) return "float";
  if constexpr (is_double<T>) return "double";
  if constexpr (is_l_double<T>) return "long double";
})();

template <typename T>
/** @brief Generates a to_string test description. */
std::string to_string_description() {
  std::string title;
  title = "ccutl::types::to_string | testing <";
  title += type_name<T>;
  title += ">";
  title += ([=]() {
    std::string buff;
    for (size_t i = 0; i < 18 - strlen(type_name<T>); i++) {
      buff += ' ';
    }
    return buff;
  })();
  title += " -> <string>";
  return title;
}

template <typename T>
/** @brief Generates a from_string test description. */
std::string from_string_description() {
  std::string title;
  title = "ccutl::types::from_string | testing <string> -> <";
  title += type_name<T>;
  title += ">";
  title += ([=]() {
    std::string buff;
    for (size_t i = 0; i < 18 - strlen(type_name<T>); i++) {
      buff += ' ';
    }
    return buff;
  })();
  return title;
}

template <typename T>
void assert_to_string(const ccutl::tests::TestGroup &tests) {
  using ccutl::types::to_string;
  tests.assert_value(
      to_string_description<T>(), [=]() { return to_string(tf_string_val<T>); },
      std::string(tf_string_str<T>));
}

template <typename T>
void assert_from_string(const ccutl::tests::TestGroup &tests) {
  using namespace ccutl::types;
  using ccutl::types::from_string;
  tests.assert_value(
      from_string_description<T>(),
      [=]() { return from_string<T>(std::string(tf_string_str<T>)); },
      tf_string_val<T>);
}

/* /--------------------------------------------------------------------------/
  /-------------------------- Function Declarations -------------------------/
 /--------------------------------------------------------------------------/ */

void to_string_tests();
void from_string_tests();
void edge_case_tests();
void run_tests();

}  // namespace types
}  // namespace ccutl_tests