#ifndef CPPUTILS_CCUTL_LIMITS_H_
#define CPPUTILS_CCUTL_LIMITS_H_

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
 * @file ccutl/limits.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various limit-checking functions.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/limits.h"

#include <cmath>
#include <limits>
#include <type_traits>
#include <vector>

#include "ccutl/compare.h"
#include "ccutl/type_traits.h"

namespace ccutl {

template <typename TLim, typename TTest,
					std::enable_if_t<are_arithmetic_v<TLim, TTest>>*>
/** @brief Checks if a value is not within a given type's range. */
constexpr bool is_val_overflow(TTest value) {
	if constexpr (are_unsigned_v<TLim>) {
		if constexpr (are_unsigned_v<TTest>) {
			// unsigned min/max && unsigned value
			return value < min_v<TLim> || value > max_v<TLim>;
		} else {
			if (value < 0) {
				// unsigned min/max && signed value < 0
				return true;
			} else {
				// unsigned min/max && signed value >= 0
				auto u_value = static_cast<std::make_unsigned_t<TTest>>(value);
				return u_value > max_v<TLim>;
			}
		}
	} else {
		if constexpr (are_unsigned_v<TTest>) {
			// signed min/max && unsigned value
			auto u_max = static_cast<std::make_unsigned_t<TLim>>(max_v<TLim>);
			return value > u_max;
		} else {
			// signed min/max && signed value
			return value < min_v<TLim> && value <= max_v<TLim>;
		}
	}
}

template <typename TLim, typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TLim, TA, TB>>*>
/** @brief Checks if a and b cannot be added without breaking the limits of
	 TLim. */
bool is_add_overflow(TA a, TB b) {
	// special consideration for floats
	if constexpr (are_floating_point_v<TA> || are_floating_point_v<TB>) {
		if (std::isinf(a + b)) return true;
	}
	constexpr auto max = max_v<TLim>;
	constexpr auto min = min_v<TLim>;
	auto cmp_a_0 = ncmp(a, 0);
	auto cmp_b_0 = ncmp(b, 0);

	/*                   return a + b > max || a + b < min                   */

	// handle zero cases
	if (cmp_a_0 == 0) {
		switch (cmp_b_0) {
			case -1:
				/*                       a == 0, b < 0                       */
				/*                       return b < min                      */
				if constexpr (are_unsigned_v<TLim>) {
					return true;	// min == 0
				} else {
					return ncmp(b, min) == -1;
				}
			case 1:
				/*                       a == 0, b > 0                       */
				/*                       return b > max                      */
				return ncmp(b, max) == 1;
			default:
				/*                        a == b == 0                        */
				return false;	// min <= 0 < max
		}
	} else {
		if (cmp_b_0 == 0) {
			/*                         a != 0, b == 0                        */
			return is_val_overflow<TLim>(a);
		}
	}

	/*                             a != 0, b != 0                            */

	// handle non-zero cases
	if (cmp_a_0 == -1) {
		if (cmp_b_0 == -1) {
			/*                          a < 0, b < 0                         */
			/*                           a + b < 0                           */
			/*                       return a + b < min                      */
			switch (ncmp(a, min)) {
				case -1:
					/*                        a < min                        */
					if constexpr (are_unsigned_v<TLim>) {
						return true;	// min == 0, a + b < 0
					} else {
						// a + b < min
						// b < min - a
						// b < -(a - min)
						//       a - min > min_v<TA>
						return ncmp(b, -(a - static_cast<TA>(min))) == -1;
					}
				case 1:
					/*                        a > min                        */
					// a + b < min
					// b < min - a
					return ncmp(b, min - static_cast<TLim>(a)) == -1;
				default:
					/*                        a == min                       */
					// a + b < min
					// a + b < a
					// b < 0
					return true;	// b < 0
			}
		} else {
			/*                           a < 0 < b                           */
			/*                         a < a + b < b                         */
			/*               return a + b > max || a + b < min               */
			signed char cmp_neg_a_b;
			if (ncmp(a, min_v<TA>) == 0) {
				// -a == max_v<TA> + 1
				cmp_neg_a_b = ncmp(max_v<TA>, b - 1);
			} else {
				cmp_neg_a_b = ncmp(-a, b);
			}
			switch (cmp_neg_a_b) {
				case -1:
					/*                       -a < b                      */
					/*                     a + b > 0                     */
					/*                 return a + b > max                */
					// a + b == b - -a
					if (ncmp(a, min_v<TA>) == 0) {
						// a + b == b - max_v<TA> + 1
						// b - max_v<TA> + 1 > max
						// b - max_v<TA> > max - 1
						switch (ncmp(b, max_v<TA>)) {
							case -1:
								return false;	// b - max_v<TA> < 0
							case 1:
								// b - max_v<TA> > 0
								return ncmp(b - static_cast<TB>(max_v<TA>),
														max - static_cast<TLim>(1)) == 1;
							default:
								return false;	// b - max_v<TA> == 0, 0 <= max - 1
						}
					} else {
						return ncmp(b - static_cast<TB>(-a), max) == 1;
					}
				case 1:
					/*                       -a > b                      */
					/*                     a + b < 0                     */
					/*                 return a + b < min                */
					if constexpr (are_unsigned_v<TLim>) {
						return true;	// min == 0, a + b < 0
					} else {
						// a + b == -(-a - b)
						//          -(-a - b) < 0
						//            -a - b  > 0
						// -(-a - b) < min
						// -a - b >= -min
						//           -min == max + 1
						// -a - b >= max + 1
						//        -a - b > 0
						//        -a - b - 1 >= 0
						// -a - b - 1 >= max
						if (ncmp(a, min_v<TA>) == 0) {
							// -a == max_v<TA> + 1
							// max_v<TA> + 1 - b - 1 >= max
							// max_v<TA> - b >= max
							switch (ncmp(b, max_v<TA>)) {
								case -1:
									/*             b < max_v<TA>             */
									// max_v<TA> - b > 0
									return ncmp(max_v<TA> - static_cast<TA>(b), max) != -1;
								case 1:
									/*             b > max_v<TA>             */
									// max_v<TA> - b < 0
									return false;	// max > 0
								default:
									/*             b == max_v<TA>            */
									// max_v<TA> - b == 0
									return false;	// min <= 0 < max
							}
						} else {
							return ncmp(-a - static_cast<TA>(b) - static_cast<TA>(1), max) !=
										 -1;
						}
					}
				default:
					/*                      -a == b                      */
					/*                     a + b == 0                    */
					return false;	// min <= 0 < max
			}
		}
	} else {
		if (cmp_b_0 == -1) {
			/*                           b < 0 < a                           */
			/*                         b < a + b < a                         */
			/*               return a + b > max || a + b < min               */
			signed char cmp_neg_b_a;
			if (ncmp(b, min_v<TB>) == 0) {
				// -b == max_v<TB> + 1
				cmp_neg_b_a = ncmp(max_v<TB>, a - 1);
			} else {
				cmp_neg_b_a = ncmp(-b, a);
			}
			switch (cmp_neg_b_a) {
				case -1:
					/*                       -b < a                      */
					/*                     a + b > 0                     */
					/*                 return a + b > max                */
					// a + b == a - -b
					if (ncmp(b, min_v<TB>) == 0) {
						// a + b == a - max_v<TB> + 1
						// a - max_v<TB> + 1 > max
						// a - max_v<TB> > max - 1
						switch (ncmp(a, max_v<TB>)) {
							case -1:
								return false;	// a - max_v<TB> < 0
							case 1:
								// a - max_v<TB> > 0
								return ncmp(a - static_cast<TA>(max_v<TB>),
														max - static_cast<TLim>(1)) == 1;
							default:
								return false;	// a - max_v<TB> == 0, 0 <= max - 1
						}
					} else {
						return ncmp(a - static_cast<TA>(-b), max) == 1;
					}
				case 1:
					/*                       -b > a                      */
					/*                     a + b < 0                     */
					/*                 return a + b < min                */
					if constexpr (are_unsigned_v<TLim>) {
						return true;	// min == 0, a + b < 0
					} else {
						// a + b == -(-b - a)
						//          -(-b - a) < 0
						//            -b - a  > 0
						// -(-b - a) < min
						// -b - a >= -min
						//           -min == max + 1
						// -b - a >= max + 1
						//        -b - a > 0
						//        -b - a - 1 >= 0
						// -b - a - 1 >= max
						if (ncmp(b, min_v<TB>) == 0) {
							// -b == max_v<TB> + 1
							// max_v<TB> + 1 - a - 1 >= max
							// max_v<TB> - a >= max
							switch (ncmp(a, max_v<TB>)) {
								case -1:
									/*             a < max_v<TB>             */
									// max_v<TB> - a > 0
									return ncmp(max_v<TB> - static_cast<TB>(a), max) != -1;
								case 1:
									/*             a > max_v<TB>             */
									// max_v<TB> - a < 0
									return false;	// max > 0
								default:
									/*             a == max_v<TB>            */
									// max_v<TB> - a == 0
									return false;	// min <= 0 < max
							}
						} else {
							return ncmp(-b - static_cast<TB>(a) - static_cast<TB>(1), max) !=
										 -1;
						}
					}
				default:
					/*                      -b == a                      */
					/*                     a + b == 0                    */
					return false;	// min <= 0 < max
			}
		} else {
			/*                    a > 0, b > 0, a + b > 0                    */
			/*                       return a + b > max                      */
			switch (ncmp(a, max)) {
				case -1:
					/*                        a < max                        */
					// a + b > max
					// b > max - a
					return ncmp(b, max - static_cast<TLim>(a)) == 1;
				case 1:
					/*                        a > max                        */
					// a + b > max
					// b > max - a
					// b > -(a - max)
					//     -(a - max) < 0
					return true;	// b > 0
				default:
					/*                        a == max                       */
					// a + b > max
					// a + b > a
					// b > 0
					return true;	// b > 0
			}
		}
	}
}

template <typename TLim, typename TA, typename TB,
					std::enable_if_t<are_arithmetic_v<TLim, TA, TB>>*>
/** @brief Checks if b cannot be subtracted from a without breaking the limits
	 of TLim. */
bool is_sub_overflow(TA a, TB b) {
	// special consideration for floats
	if constexpr (are_floating_point_v<TA> || are_floating_point_v<TB>) {
		if (std::isinf(a - b)) return true;
	}
	constexpr auto max = max_v<TLim>;
	constexpr auto min = min_v<TLim>;
	auto cmp_a_0 = ncmp(a, 0);
	auto cmp_b_0 = ncmp(b, 0);
	auto cmp_a_b = ncmp(a, b);

	/*                   return a - b > max || a - b < min                   */

	// handle zero cases
	if (cmp_a_b == 0) {
		return false;	// a - b == 0, min <= 0 < max
	}
	if (cmp_a_0 == 0) {
		switch (cmp_b_0) {
			case -1:
				/*                       a == 0, b < 0                       */
				/*                      return -b > max                      */
				if (ncmp(b, min_v<TB>) == 0) {
					// -b > max
					// max_v<TB> + 1 > max
					// max_v<TB> > max - 1
					return ncmp(max_v<TB>, max - static_cast<TLim>(1)) == 1;
				} else {
					return ncmp(-b, max) == 1;
				}
			case 1:
				/*                       a == 0, b > 0                       */
				/*                      return -b < min                      */
				// -b < min
				// b >= -min
				if constexpr (are_unsigned_v<TLim>) {
					// b >= -0
					return ncmp(b, 0) != -1;
				} else {
					// b >= max + 1
					// b - 1 >= max
					return ncmp(b - static_cast<TB>(1), max) != -1;
				}
			default:
				/*                        a == b == 0                        */
				return false;	// min <= 0 < max
		}
	} else {
		if (cmp_b_0 == 0) {
			/*                         a != 0, b == 0                        */
			return is_val_overflow<TLim>(a);
		}
	}

	/*                         a != 0, b != 0, a != b                        */

	// handle non-zero cases
	if (cmp_a_0 == -1) {
		if (cmp_b_0 == -1) {
			if (cmp_a_b == -1) {
				/*                         a < b < 0                         */
				/*                     a < b < a - b < 0                     */
				/*                     return a - b < min                    */
				return ncmp(a - static_cast<TA>(b), min) == -1;
			} else {
				/*                         b < a < 0                         */
				/*                     b < a < 0 < a - b                     */
				/*                     return a - b > max                    */
				// a - b > max
				// -(b - a) > max
				// b - a <= -max
				TB diff = b - static_cast<TB>(a);
				if constexpr (std::is_signed_v<TLim>) {
					// -max == min + 1
					return ncmp(diff, min + static_cast<TLim>(1)) != 1;
				} else {
					if (b == min_v<TB>) {
						// -(b - a) == max_v<TB> + 1
						// max_v<TB> + 1 > max
						// max_v<TB> > max - 1
						return ncmp(max_v<TB>, max - static_cast<TLim>(1)) == 1;
					} else {
						return ncmp(-diff, max) == 1;
					}
				}
			}
		} else {
			/*                           a < 0 < b                           */
			/*                       a - b < a < 0 < b                       */
			/*                       return a - b < min                      */
			if constexpr (are_unsigned_v<TLim>) {
				/*                          min == 0                         */
				return true;	// a - b < 0
			} else {
				/*                          min < 0                          */
				// a - b < min
				// a - min < b
				switch (ncmp(a, min)) {
					case -1:
						/*                    a < min < 0                    */
						/*                    a - min < 0                    */
						return ncmp(a - static_cast<TA>(min), b) == -1;
					case 1:
						/*                    min < a < 0                    */
						/*                    a - min > 0                    */
						// a - min < b
						// -(min - a) < b
						// min - a >= -b
						return ncmp(min - static_cast<TLim>(a), -b) != -1;
					default:
						/*                  min == a, a < 0                  */
						/*                    a - min == 0                   */
						return true;	// b > 0
				}
			}
		}
	} else {
		if (cmp_b_0 == -1) {
			/*                           b < 0 < a                           */
			/*                       b < 0 < a < a - b                       */
			/*                       return a - b > max                      */
			// a - b > max
			// -b > max - a
			if (ncmp(b, min_v<TB>) == 0) {
				// -b == max_v<TB> + 1
				// max_v<TB> + 1 > max - a
				// max_v<TB> > max - a - 1
				if (ncmp(max, a) < 1) {
					/*                        max <= a                       */
					/*                    max - a - 1 < 0                    */
					return true;	// max_v<TB> > 0
				} else {
					/*                        max > a                        */
					/*                    max - a - 1 >= 0                   */
					return ncmp(max_v<TB>,
											max - static_cast<TLim>(a) - static_cast<TLim>(1)) == 1;
				}
			} else {
				if (ncmp(max, a) < 1) {
					/*                        max <= a                       */
					return ncmp(-b, static_cast<TA>(max) - a) == 1;
				} else {
					/*                        max > a                        */
					return ncmp(-b, max - static_cast<TLim>(a)) == 1;
				}
			}
		} else {
			if (cmp_a_b == -1) {
				/*                         0 < a < b                         */
				/*                     a - b < 0 < a < b                     */
				/*                     return a - b < min                    */
				// a - b < min
				// a < min + b
				if constexpr (std::is_signed_v<TLim>) {
					/*                        min < 0                        */
					// -min < b - a
					// -min == max + 1
					// max + 1 < b - a
					// max < b - a - 1
					return ncmp(max, b - static_cast<TB>(a) - static_cast<TB>(1)) == -1;
				} else {
					/*                        min == 0                       */
					// a < 0 + b
					// a < b
					return true;
				}
			} else {
				/*                         0 < b < a                         */
				/*                     0 < a - b < b < a                     */
				/*                     return a - b > max                    */
				return ncmp(a - static_cast<TA>(b), max) == 1;
			}
		}
	}
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_LIMITS_H_
