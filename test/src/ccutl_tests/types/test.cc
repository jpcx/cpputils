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
 * @file ccutl_tests/types/test.cc
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

#include "ccutl_tests/types/test.h"

#include "ccutl/tests/testgroup.h"
#include "ccutl/types/convert.h"

namespace ccutl_tests {
namespace types {

void to_string_tests() {
  using ccutl::tests::TestGroup;
  using ccutl::types::to_string;
  auto tests = TestGroup("ccutl::types | to_string");
  assert_to_string<bool>(tests);
  assert_to_string<char>(tests);
  assert_to_string<const char *>(tests);
  assert_to_string<char *>(tests);
  assert_to_string<signed char>(tests);
  assert_to_string<short>(tests);
  assert_to_string<int>(tests);
  assert_to_string<long>(tests);
  assert_to_string<long long>(tests);
  assert_to_string<u_char>(tests);
  assert_to_string<u_short>(tests);
  assert_to_string<unsigned>(tests);
  assert_to_string<u_long>(tests);
  assert_to_string<unsigned long long>(tests);
  assert_to_string<float>(tests);
  assert_to_string<double>(tests);
  assert_to_string<long double>(tests);
  tests.end();
}

void from_string_tests() {
  using ccutl::tests::TestGroup;
  using ccutl::types::from_string;
  auto tests = TestGroup("ccutl::types | from_string");
  assert_from_string<bool>(tests);
  assert_from_string<char>(tests);
  assert_from_string<const char *>(tests);
  assert_from_string<signed char>(tests);
  assert_from_string<short>(tests);
  assert_from_string<int>(tests);
  assert_from_string<long>(tests);
  assert_from_string<long long>(tests);
  assert_from_string<u_char>(tests);
  assert_from_string<u_short>(tests);
  assert_from_string<unsigned>(tests);
  assert_from_string<u_long>(tests);
  assert_from_string<unsigned long long>(tests);
  assert_from_string<float>(tests);
  assert_from_string<double>(tests);
  assert_from_string<long double>(tests);
  tests.end();
}

void edge_case_tests() {
  using ccutl::tests::TestGroup;
  using ccutl::types::from_string;
  using ccutl::types::to_string;
  auto tests =
      TestGroup("ccutl::types | to_string && from_string | edge cases");
  const std::string edge_str_test_v = "foobar";
  tests.assert_value(
      "ccutl::types::to_string | testing <string> -> <string>",
      [=]() { return to_string(edge_str_test_v); }, edge_str_test_v);
  tests.assert_value(
      "ccutl::types::from_string | testing <string> -> <string>",
      [=]() { return from_string<std::string>(edge_str_test_v); },
      edge_str_test_v);
  tests.end();
}

void run_tests() {
  to_string_tests();
  from_string_tests();
  edge_case_tests();
}

}  // namespace types
}  // namespace ccutl_tests