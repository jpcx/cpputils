#ifndef CPPUTILS_CCUTL_MATH_H_
#define CPPUTILS_CCUTL_MATH_H_

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
 * @file ccutl/math.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various mathematical templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/math.h"

#include <type_traits>

#include "ccutl/compare.h"
#include "ccutl/limits.h"
#include "ccutl/type_traits.h"

namespace ccutl {

template <typename TResult, typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TResult, TA, TB>>*>
/** @brief Checks if a and b cannot be added without breaking the limits of
	 TResult. If not, returns the sum. If so, throws const char * "EOverflow".
 */
TResult safe_add(TA a, TB b) {
	if (is_add_overflow<TResult>(a, b))
		throw "EOverflow";
	else {
		// Handle all floating_point or all unsigned
		if constexpr (are_floating_point_v<TResult, TA, TB> ||
									are_unsigned_v<TResult, TA, TB>) {
			return static_cast<TResult>(a) + static_cast<TResult>(b);
		}
		// Handle all floating_point / unsigned / signed mix
		else {
			auto cmp_a_0 = ncmp(a, 0);
			auto cmp_b_0 = ncmp(b, 0);
			// Handle 0 + 0
			if (cmp_a_0 == 0 && cmp_b_0 == 0) {
				return static_cast<TResult>(0);
			}
			// Handle 0 + (+/-)b
			else if (cmp_a_0 == 0) {
				return static_cast<TResult>(b);
			}
			// Handle (+/-)a + 0
			else if (cmp_b_0 == 0) {
				return static_cast<TResult>(a);
			}
			// Handle (a < 0 && b < 0) || (a > 0 && b > 0)
			else if (cmp_a_0 == cmp_b_0) {
				return static_cast<TResult>(a) + static_cast<TResult>(b);
			}
			// Handle (a > 0 && b < 0)
			else if (cmp_a_0 == 1) {
				// Handle floating point b
				if constexpr (are_floating_point_v<TB>) {
					TB inv_b = -b;
					switch (ncmp(a, inv_b)) {
						// Handle (+)a < (+)-b
						case -1: {
							return static_cast<TResult>(-(inv_b - static_cast<TB>(a)));
						}
						// Handle (+)a > (+)-b
						case 1: {
							return static_cast<TResult>(a - static_cast<TA>(inv_b));
						}
						// Handle (+)a == (+)-b
						default: {
							return static_cast<TResult>(0);
						}
					}
				}
				// Handle signed integral b
				else {
					// Handle b <= min_v<TB>
					if (ncmp(b, min_v<TB>) <= 0) {
						// -b == max_v<TB> + 1
						// ncmp(a, -b) == ncmp(a - 1, max_v<TB>)
						switch (ncmp(a - 1, max_v<TB>)) {
							// Handle (+)a < (+)-b
							//        (+)(a - 1) < (+)(max_v<TB>)
							case -1: {
								return static_cast<TResult>(
										-(max_v<TB> - static_cast<TB>(a - static_cast<TA>(1))));
							}
							// Handle (+)a > (+)-b
							//        (+)(a - 1) > max_v<TB>
							case 1: {
								return static_cast<TResult>((a - static_cast<TA>(1)) -
																						static_cast<TA>(max_v<TB>));
							}
							// Handle (+)a == (+)-b
							default: {
								return static_cast<TResult>(0);
							}
						}
					}
					// Handle b > min_v<TB>
					else {
						TB inv_b = -b;
						switch (ncmp(a, inv_b)) {
							// Handle (+)a > (+)-b
							case -1: {
								return static_cast<TResult>(a - static_cast<TA>(inv_b));
							}
							// Handle (+)a < (+)-b
							case 1: {
								return static_cast<TResult>(-(inv_b - static_cast<TB>(a)));
							}
							// Handle (+)a == (+)-b
							default: {
								return static_cast<TResult>(0);
							}
						}
					}
				}
			}
			// Handle (a < 0 && b > 0)
			else if (cmp_b_0 == 1) {
				// Handle floating point a
				if constexpr (are_floating_point_v<TA>) {
					TA inv_a = -a;
					switch (ncmp(b, inv_a)) {
						// Handle (+)b < (+)-a
						case -1: {
							return static_cast<TResult>(-(inv_a - static_cast<TA>(b)));
						}
						// Handle (+)b > (+)-a
						case 1: {
							return static_cast<TResult>(b - static_cast<TB>(inv_a));
						}
						// Handle (+)b == (+)-a
						default: {
							return static_cast<TResult>(0);
						}
					}
				}
				// Handle signed integral a
				else {
					// Handle a <= min_v<TA>
					if (ncmp(a, min_v<TA>) <= 0) {
						// -a == max_v<TA> + 1
						// ncmp(b, -a) == ncmp(b - 1, max_v<TA>)
						switch (ncmp(b - 1, max_v<TA>)) {
							// Handle (+)b < (+)-a
							//        (+)(b - 1) < (+)(max_v<TA>)
							case -1: {
								return static_cast<TResult>(
										-(max_v<TA> - static_cast<TA>(b - static_cast<TB>(1))));
							}
							// Handle (+)b > (+)-a
							//        (+)(b - 1) > max_v<TA>
							case 1: {
								return static_cast<TResult>((b - static_cast<TB>(1)) -
																						static_cast<TB>(max_v<TA>));
							}
							// Handle (+)b == (+)-a
							default: {
								return static_cast<TResult>(0);
							}
						}
					}
					// Handle a > min_v<TA>
					else {
						TA inv_a = -a;
						switch (ncmp(b, inv_a)) {
							// Handle (+)b > (+)-a
							case -1: {
								return static_cast<TResult>(b - static_cast<TB>(inv_a));
							}
							// Handle (+)b < (+)-a
							case 1: {
								return static_cast<TResult>(-(inv_a - static_cast<TA>(b)));
							}
							// Handle (+)b == (+)-a
							default: {
								return static_cast<TResult>(0);
							}
						}
					}
				}
			}
		}
	}
}

template <
		typename TOutput, typename TAddend,
		std::enable_if_t<are_arithmetic_v<remove_everything_t<TOutput>, TAddend>>*>
/** @brief Adds b to the value of a and updates a's value. Throws "EOverflow" if
	 addition would result in an overflow. */
void safe_add(TOutput* a, TAddend b) {
	*a = safe_add<std::remove_pointer_t<TOutput>>(*a, b);
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_MATH_H_
