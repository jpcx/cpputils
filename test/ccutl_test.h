#ifndef CPPUTILS_TEST_CCUTL_TEST_H_
#define CPPUTILS_TEST_CCUTL_TEST_H_

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
 * @file test/ccutl_test.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief gtest shim for ccutl. Ignores gtest-generated warnings.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-06-27
 * @date modified 2019-06-27
 * @copyright Copyright (c) 2019 Justin Collier
 */

#pragma once

#ifndef CCUTL_TEST
#include "gtest/gtest.h"
// clang-format off
/** @brief gtest shim; Calls GTEST_TEST without triggering clang++ warning for -Wglobal-constructors */
#define CCUTL_TEST(test_case_name, test_name)                   \
  _Pragma("clang diagnostic push")                              \
  _Pragma("clang diagnostic ignored \"-Wglobal-constructors\"") \
  GTEST_TEST(ccutl_##test_case_name, test_name)                 \
  _Pragma("clang diagnostic pop")
// clang-format on
#endif

#endif	// CPPUTILS_TEST_CCUTL_TEST_H_
