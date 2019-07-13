#ifndef CPPUTILS_CCUTL_IO_H_
#define CPPUTILS_CCUTL_IO_H_

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
 * @file ccutl/io.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various I/O related templates.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-07-08
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/io.h"

#include <iostream>
#include <string>
#include <type_traits>

#include "ccutl/algorithm.h"
#include "ccutl/compare.h"
#include "ccutl/format.h"
#include "ccutl/type_traits.h"

namespace ccutl {

template <bool InsertEndLine, typename T,
					std::enable_if_t<are_floating_point_v<T>>*>
void log(T value, const std::optional<std::streamsize>& precision) {
	using std::cout;
	using std::endl;
	if (precision.has_value()) {
		auto prec_bak = cout.precision();
		cout.precision(precision.value());
		if constexpr (InsertEndLine) {
			cout << value << endl;
		} else {
			cout << value;
		}
		cout.precision(prec_bak);
	} else {
		if constexpr (InsertEndLine) {
			cout << value << endl;
		} else {
			cout << value;
		}
	}
}

template <bool InsertEndLine, typename T,
					std::enable_if_t<are_streamable_to_v<std::ostream, T>>*>
void log(const T& value) {
	if constexpr (InsertEndLine) {
		std::cout << value << std::endl;
	} else {
		std::cout << value;
	}
}

template <bool InsertEndLine, template <typename...> typename TContain,
					typename T, typename TDelim,
					std::enable_if_t<!are_streamable_to_v<std::ostream, TContain<T>> &&
													 are_const_iterable_v<TContain<T>> &&
													 are_floating_point_v<T> &&
													 are_streamable_to_v<std::ostream, TDelim>>*>
void log(const TContain<T>& value, const TDelim& delimiter,
				 const std::optional<std::streamsize>& precision) {
	iterate_it(value, [=](const auto& it, const auto& next, const auto& end) {
		log<false>(*it, precision);
		if (next != end)
			log<false>(delimiter);
		else if constexpr (InsertEndLine)
			log();
	});
}

template <bool InsertEndLine, template <typename...> typename TContain,
					typename T, typename TDelim,
					std::enable_if_t<!are_streamable_to_v<std::ostream, TContain<T>> &&
													 are_const_iterable_v<TContain<T>> &&
													 are_streamable_to_v<std::ostream, T, TDelim>>*>
void log(const TContain<T>& value, const TDelim& delimiter) {
	iterate_it(value, [=](const auto& it, const auto& next, const auto& end) {
		log<false>(*it);
		if (next != end)
			log<false>(delimiter);
		else if constexpr (InsertEndLine)
			log();
	});
}

template <bool InsertEndLine, template <typename...> typename TRows,
					template <typename...> typename TColumns, typename T,
					typename TRowDelim, typename TColDelim,
					std::enable_if_t<
							are_const_iterable_v<TRows<TColumns<T>>> &&
							are_streamable_to_v<std::ostream, T, TRowDelim, TColDelim>>*>
void log(const TRows<TColumns<T>>& value, const TRowDelim& row_delimiter,
				 const TColDelim& col_delimiter) {
	iterate_it(value, [=](const auto& row_it, const auto& row_next,
												const auto& row_end) {
		iterate_it(*row_it, [=](const auto& col_it, const auto& col_next,
														const auto& col_end) {
			log<false>(*col_it);
			if (col_next != col_end)
				log<false>(col_delimiter);
			else if constexpr (InsertEndLine)
				log();
		});
		if (row_next != row_end) log<false>(row_delimiter);
	});
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_IO_H_
