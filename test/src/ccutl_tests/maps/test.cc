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
 * @file ccutl_tests/maps/test.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions of ccutl::maps.
 * @version 0.3.1
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-11
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl_tests/maps/test.h"

#include <string>

#include "ccutl/maps/maps.h"
#include "ccutl/tests/testgroup.h"

namespace ccutl_tests {
namespace maps {

void one_dimensional_tests() {
  test_1D<int, int>();
  test_1D<int, const char *>();
  test_1D<int, std::string>();
  test_1D<int, std::string *>();
  test_1D<const char *, int>();
  test_1D<const char *, const char *>();
  test_1D<const char *, std::string>();
  test_1D<const char *, std::string *>();
  test_1D<std::string, int>();
  test_1D<std::string, const char *>();
  test_1D<std::string, std::string>();
  test_1D<std::string, std::string *>();
  test_1D<std::string *, int>();
  test_1D<std::string *, const char *>();
  test_1D<std::string *, std::string>();
  test_1D<std::string *, std::string *>();
}

void two_dimensional_tests() {
  test_2D<int, int, int>();
  test_2D<int, int, const char *>();
  test_2D<int, int, std::string>();
  test_2D<int, int, std::string *>();
  test_2D<int, const char *, int>();
  test_2D<int, const char *, const char *>();
  test_2D<int, const char *, std::string>();
  test_2D<int, const char *, std::string *>();
  test_2D<int, std::string, int>();
  test_2D<int, std::string, const char *>();
  test_2D<int, std::string, std::string>();
  test_2D<int, std::string, std::string *>();
  test_2D<int, std::string *, int>();
  test_2D<int, std::string *, const char *>();
  test_2D<int, std::string *, std::string>();
  test_2D<int, std::string *, std::string *>();
  test_2D<const char *, int, int>();
  test_2D<const char *, int, const char *>();
  test_2D<const char *, int, std::string>();
  test_2D<const char *, int, std::string *>();
  test_2D<const char *, const char *, int>();
  test_2D<const char *, const char *, const char *>();
  test_2D<const char *, const char *, std::string>();
  test_2D<const char *, const char *, std::string *>();
  test_2D<const char *, std::string, int>();
  test_2D<const char *, std::string, const char *>();
  test_2D<const char *, std::string, std::string>();
  test_2D<const char *, std::string, std::string *>();
  test_2D<const char *, std::string *, int>();
  test_2D<const char *, std::string *, const char *>();
  test_2D<const char *, std::string *, std::string>();
  test_2D<const char *, std::string *, std::string *>();
  test_2D<std::string, int, int>();
  test_2D<std::string, int, const char *>();
  test_2D<std::string, int, std::string>();
  test_2D<std::string, int, std::string *>();
  test_2D<std::string, const char *, int>();
  test_2D<std::string, const char *, const char *>();
  test_2D<std::string, const char *, std::string>();
  test_2D<std::string, const char *, std::string *>();
  test_2D<std::string, std::string, int>();
  test_2D<std::string, std::string, const char *>();
  test_2D<std::string, std::string, std::string>();
  test_2D<std::string, std::string, std::string *>();
  test_2D<std::string, std::string *, int>();
  test_2D<std::string, std::string *, const char *>();
  test_2D<std::string, std::string *, std::string>();
  test_2D<std::string, std::string *, std::string *>();
  test_2D<std::string *, int, int>();
  test_2D<std::string *, int, const char *>();
  test_2D<std::string *, int, std::string>();
  test_2D<std::string *, int, std::string *>();
  test_2D<std::string *, const char *, int>();
  test_2D<std::string *, const char *, const char *>();
  test_2D<std::string *, const char *, std::string>();
  test_2D<std::string *, const char *, std::string *>();
  test_2D<std::string *, std::string, int>();
  test_2D<std::string *, std::string, const char *>();
  test_2D<std::string *, std::string, std::string>();
  test_2D<std::string *, std::string, std::string *>();
  test_2D<std::string *, std::string *, int>();
  test_2D<std::string *, std::string *, const char *>();
  test_2D<std::string *, std::string *, std::string>();
  test_2D<std::string *, std::string *, std::string *>();
}

void run_tests() {
  one_dimensional_tests();
  two_dimensional_tests();
}

}  // namespace maps
}  // namespace ccutl_tests
