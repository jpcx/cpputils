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
 * @file ccutl/tests/testgroup.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides a very basic framework for unit testing.
 * @version 0.1.0
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-04
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>

namespace ccutl {
namespace tests {

/** @brief Defines a group of tests to be performed. */
class TestGroup {
 private:
  std::string ansi_red_(const std::string &text) {
    return "\033[1;31m" + text + "\033[0m";
  }
  std::string ansi_green_(const std::string &text) {
    return "\033[1;32m" + text + "\033[0m";
  }
  std::string title_;
  void init_test_(const std::string &description) {
    std::cout << description << "... ";
  }
  void test_passed_() { std::cout << ansi_green_("Passed!") << std::endl; }
  void test_failed_() {
    std::cout << ansi_red_("Failed!") << std::endl;
    throw;  // TODO: implement rest of testing
  }

 public:
  /** @brief Announces to the console that a test has begun. */
  TestGroup(const std::string &title) : title_(title) {
    std::cout << "----------- Testing " << title_ << " -----------"
              << std::endl;
  }
  ~TestGroup() {}

  template <typename T_Lambda, typename T_Value>
  /** @brief Executes a lambda function and checks for expected return. */
  void assert_value(const std::string &description, const T_Lambda &test,
                    const T_Value &value) {
    init_test_(description);
    T_Value result = test();
    if (value == result) {
      test_passed_();
    } else {
      test_failed_();
    }
  }

  template <typename T_Lambda>
  /** @brief Executes a lambda function and checks for expected return. */
  void assert_value(const std::string &description, const T_Lambda &test,
                    const char *value) {
    init_test_(description);
    const char *result = test();
    if (strncmp(result, value, strlen(value)) == 0) {
      test_passed_();
    } else {
      test_failed_();
    }
  }

  template <typename T_Lambda, typename T_Error>
  /** @brief Executes a lambda function and checks for expected throw. */
  void assert_throws(const std::string &description, const T_Lambda &test,
                     const T_Error &err) {
    init_test_(description);
    try {
      test();
      test_failed_();  // should have thrown
    } catch (const T_Error &e) {
      if (e == err) {
        test_passed_();
      } else {
        test_failed_();
      }
    }
  }

  template <typename T_Lambda>
  /** @brief Executes a lambda function and checks for expected throw. */
  void assert_throws(const std::string &description, const T_Lambda &test,
                     const char *err) {
    init_test_(description);
    try {
      test();
      test_failed_();  // should have thrown
    } catch (const char *e) {
      if (strncmp(e, err, strlen(err)) == 0) {
        test_passed_();
      } else {
        test_failed_();
      }
    }
  }

  /** @brief Ends the testing suite by drawing a closing border. */
  void end() {
    std::string border = "--------------------------------";
    for (auto it = title_.begin(); it != title_.end(); it++) {
      border.push_back('-');
    }
    std::cout << border << std::endl << std::endl;
  }
};

}  // namespace tests
}  // namespace ccutl
