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
 * @file ccutl_tests/main.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Triggers cpputils library testing functions.
 * @version 0.1.1
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-11
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl_tests/maps/test.h"
#include "ccutl_tests/types/test.h"

int main() {
  ccutl_tests::types::run_tests();
  ccutl_tests::maps::run_tests();
  std::cout << "\033[1;32mAll tests completed successfully!\033[0m"
            << std::endl;
}