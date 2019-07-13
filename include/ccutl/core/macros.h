#ifndef CPPUTILS_CCUTL_CORE_MACROS_H_
#define CPPUTILS_CCUTL_CORE_MACROS_H_

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
 * @file ccutl/core/macros.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various helper macros.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-08
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <iostream>
#include <string>

#include "ccutl/core/algorithm.h"
#include "ccutl/core/compare.h"
#include "ccutl/core/io.h"

#ifndef CPPUTILS_INTERNAL_LOG_0_
#define CPPUTILS_INTERNAL_LOG_0_(...) ([=]() { std::cout << std::endl; })()
#endif	// CPPUTILS_INTERNAL_LOG_0_

#ifndef CPPUTILS_INTERNAL_LOG_1_
#define CPPUTILS_INTERNAL_LOG_1_(x, ...)                                 \
	([=]() {                                                               \
		ccutl::log(                                                          \
				ccutl::concat<std::string>(#x, ": ", ([]() { return (x); })())); \
	})()
#endif	// CPPUTILS_INTERNAL_LOG_1_

#ifndef CPPUTILS_INTERNAL_LOG_2_
#define CPPUTILS_INTERNAL_LOG_2_(x, descr, ...)                              \
	([=]() {                                                                   \
		ccutl::log(ccutl::concat<std::string>(#x, " [", descr,                   \
																					"]: ", ([]() { return (x); })())); \
	})()
#endif	// CPPUTILS_INTERNAL_LOG_2_

#ifndef CPPUTILS_INTERNAL_LOG_3_
#define CPPUTILS_INTERNAL_LOG_3_(...) \
	static_assert(false,                \
								"CCUTL_LOG cannot be called with more than 2 arguments.");
#endif	// CPPUTILS_INTERNAL_LOG_3_

#ifndef CPPUTILS_INTERNAL_LOG_N_
#define CPPUTILS_INTERNAL_LOG_N_(_0, _1, _2, _3, n, ...) \
	CPPUTILS_INTERNAL_LOG_##n##_(_1, _2, _3)
#endif	// CPPUTILS_INTERNAL_LOG_N_

#ifndef CCUTL_LOG
/** @brief CCUTL_LOG([expr], [descr]) ---> #expr: (expr)\n || #expr [descr]:
 * (expr)\n || expr\n || \n; Logs result of expression to console. Removes
 * quotes from const char * literals (and doesn't log them twice). */
#define CCUTL_LOG(...) CPPUTILS_INTERNAL_LOG_N_(, ##__VA_ARGS__, 3, 2, 1, 0)
#endif	// CCUTL_LOG

#endif	// CPPUTILS_CCUTL_CORE_MACROS_H_
