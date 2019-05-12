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
 * @file ccutl/types/checks.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides various type-checking shortcuts.
 * @version 0.1.0
 * @since cpputils 0.5.0
 * @date created 2019-05-09
 * @date modified 2019-05-11
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <string>
#include <string_view>
#include <type_traits>

namespace ccutl {
namespace types {

/* /--------------------------------------------------------------------------/
  /-------------------- Fundamental Type Check Shortcuts --------------------/
 /--------------------------------------------------------------------------/ */

template <typename T>
/** @brief True if type is char. */
constexpr bool is_char = std::is_same_v<T, char>;

template <typename T>
/** @brief True if type is const char. */
constexpr bool is_cst_char = std::is_same_v<T, const char>;

template <typename T>
/** @brief True if type is char *. */
constexpr bool is_char_p = std::is_same_v<T, char *>;

template <typename T>
/** @brief True if type is char &. */
constexpr bool is_char_r = std::is_same_v<T, char &>;

template <typename T>
/** @brief True if type is const char *. */
constexpr bool is_cst_char_p = std::is_same_v<T, const char *>;

template <typename T>
/** @brief True if type is const char &. */
constexpr bool is_cst_char_r = std::is_same_v<T, const char &>;

template <typename T>
/** @brief True if type is char16_t. */
constexpr bool is_char16 = std::is_same_v<T, char16_t>;

template <typename T>
/** @brief True if type is const char16_t. */
constexpr bool is_cst_cchar16 = std::is_same_v<T, const char16_t>;

template <typename T>
/** @brief True if type is char16_t *. */
constexpr bool is_char16_p = std::is_same_v<T, char16_t *>;

template <typename T>
/** @brief True if type is char16_t &. */
constexpr bool is_char16_r = std::is_same_v<T, char16_t &>;

template <typename T>
/** @brief True if type is const char16_t *. */
constexpr bool is_cst_char16_p = std::is_same_v<T, const char16_t *>;

template <typename T>
/** @brief True if type is const char16_t &. */
constexpr bool is_cst_char16_r = std::is_same_v<T, const char16_t &>;

template <typename T>
/** @brief True if type is char32_t. */
constexpr bool is_char32 = std::is_same_v<T, char32_t>;

template <typename T>
/** @brief True if type is const char32_t. */
constexpr bool is_cst_char32 = std::is_same_v<T, const char32_t>;

template <typename T>
/** @brief True if type is char32_t *. */
constexpr bool is_char32_p = std::is_same_v<T, char32_t *>;

template <typename T>
/** @brief True if type is char32_t &. */
constexpr bool is_char32_r = std::is_same_v<T, char32_t &>;

template <typename T>
/** @brief True if type is const char32_t *. */
constexpr bool is_cst_char32_p = std::is_same_v<T, const char32_t *>;

template <typename T>
/** @brief True if type is const char32_t &. */
constexpr bool is_cst_char32_r = std::is_same_v<T, const char32_t &>;

template <typename T>
/** @brief True if type is wchar_t. */
constexpr bool is_wchar = std::is_same_v<T, wchar_t>;

template <typename T>
/** @brief True if type is const wchar_t. */
constexpr bool is_cst_wchar = std::is_same_v<T, const wchar_t>;

template <typename T>
/** @brief True if type is wchar_t *. */
constexpr bool is_wchar_p = std::is_same_v<T, wchar_t *>;

template <typename T>
/** @brief True if type is wchar_t &. */
constexpr bool is_wchar_r = std::is_same_v<T, wchar_t &>;

template <typename T>
/** @brief True if type is const wchar_t *. */
constexpr bool is_cst_wchar_p = std::is_same_v<T, const wchar_t *>;

template <typename T>
/** @brief True if type is const wchar_t &. */
constexpr bool is_cst_wchar_r = std::is_same_v<T, const wchar_t &>;

template <typename T>
/** @brief True if type is signed char. */
constexpr bool is_s_char = std::is_same_v<T, signed char>;

template <typename T>
/** @brief True if type is const signed char. */
constexpr bool is_cst_s_char = std::is_same_v<T, const signed char>;

template <typename T>
/** @brief True if type is signed char *. */
constexpr bool is_s_char_p = std::is_same_v<T, signed char *>;

template <typename T>
/** @brief True if type is signed char &. */
constexpr bool is_s_char_r = std::is_same_v<T, signed char &>;

template <typename T>
/** @brief True if type is const signed char *. */
constexpr bool is_cst_s_char_p = std::is_same_v<T, const signed char *>;

template <typename T>
/** @brief True if type is const signed char &. */
constexpr bool is_cst_s_char_r = std::is_same_v<T, const signed char &>;

template <typename T>
/** @brief True if type is short. */
constexpr bool is_short = std::is_same_v<T, short>;

template <typename T>
/** @brief True if type is const short. */
constexpr bool is_cst_short = std::is_same_v<T, const short>;

template <typename T>
/** @brief True if type is short *. */
constexpr bool is_short_p = std::is_same_v<T, short *>;

template <typename T>
/** @brief True if type is short &. */
constexpr bool is_short_r = std::is_same_v<T, short &>;

template <typename T>
/** @brief True if type is const short *. */
constexpr bool is_cst_short_p = std::is_same_v<T, const short *>;

template <typename T>
/** @brief True if type is const short &. */
constexpr bool is_cst_short_r = std::is_same_v<T, const short &>;

template <typename T>
/** @brief True if type is int. */
constexpr bool is_int = std::is_same_v<T, int>;

template <typename T>
/** @brief True if type is const int. */
constexpr bool is_cst_int = std::is_same_v<T, const int>;

template <typename T>
/** @brief True if type is int *. */
constexpr bool is_int_p = std::is_same_v<T, int *>;

template <typename T>
/** @brief True if type is int &. */
constexpr bool is_int_r = std::is_same_v<T, int &>;

template <typename T>
/** @brief True if type is const int *. */
constexpr bool is_cst_int_p = std::is_same_v<T, const int *>;

template <typename T>
/** @brief True if type is const int &. */
constexpr bool is_cst_int_r = std::is_same_v<T, const int &>;

template <typename T>
/** @brief True if type is long. */
constexpr bool is_long = std::is_same_v<T, long>;

template <typename T>
/** @brief True if type is const long. */
constexpr bool is_cst_long = std::is_same_v<T, const long>;

template <typename T>
/** @brief True if type is long *. */
constexpr bool is_long_p = std::is_same_v<T, long *>;

template <typename T>
/** @brief True if type is long &. */
constexpr bool is_long_r = std::is_same_v<T, long &>;

template <typename T>
/** @brief True if type is const long *. */
constexpr bool is_cst_long_p = std::is_same_v<T, const long *>;

template <typename T>
/** @brief True if type is const long &. */
constexpr bool is_cst_long_r = std::is_same_v<T, const long &>;

template <typename T>
/** @brief True if type is long long. */
constexpr bool is_l_long = std::is_same_v<T, long long>;

template <typename T>
/** @brief True if type is const long long. */
constexpr bool is_cst_l_long = std::is_same_v<T, const long long>;

template <typename T>
/** @brief True if type is long long *. */
constexpr bool is_l_long_p = std::is_same_v<T, long long *>;

template <typename T>
/** @brief True if type is long long &. */
constexpr bool is_l_long_r = std::is_same_v<T, long long &>;

template <typename T>
/** @brief True if type is const long long *. */
constexpr bool is_cst_l_long_p = std::is_same_v<T, const long long *>;

template <typename T>
/** @brief True if type is const long long &. */
constexpr bool is_cst_l_long_r = std::is_same_v<T, const long long &>;

template <typename T>
/** @brief True if type is unsigned char. */
constexpr bool is_u_char = std::is_same_v<T, u_char>;

template <typename T>
/** @brief True if type is const u_char. */
constexpr bool is_cst_u_char = std::is_same_v<T, const u_char>;

template <typename T>
/** @brief True if type is unsigned char *. */
constexpr bool is_u_char_p = std::is_same_v<T, u_char *>;

template <typename T>
/** @brief True if type is u_char &. */
constexpr bool is_u_char_r = std::is_same_v<T, u_char &>;

template <typename T>
/** @brief True if type is const u_char *. */
constexpr bool is_cst_u_char_p = std::is_same_v<T, const u_char *>;

template <typename T>
/** @brief True if type is const u_char &. */
constexpr bool is_cst_u_char_r = std::is_same_v<T, const u_char &>;

template <typename T>
/** @brief True if type is unsigned short. */
constexpr bool is_u_short = std::is_same_v<T, u_short>;

template <typename T>
/** @brief True if type is const u_short. */
constexpr bool is_cst_u_short = std::is_same_v<T, const u_short>;

template <typename T>
/** @brief True if type is unsigned short *. */
constexpr bool is_u_short_p = std::is_same_v<T, u_short *>;

template <typename T>
/** @brief True if type is u_short &. */
constexpr bool is_u_short_r = std::is_same_v<T, u_short &>;

template <typename T>
/** @brief True if type is const u_short *. */
constexpr bool is_cst_u_short_p = std::is_same_v<T, const u_short *>;

template <typename T>
/** @brief True if type is const u_short &. */
constexpr bool is_cst_u_short_r = std::is_same_v<T, const u_short &>;

template <typename T>
/** @brief True if type is unsigned. */
constexpr bool is_u_int = std::is_same_v<T, u_int>;

template <typename T>
/** @brief True if type is const u_int. */
constexpr bool is_cst_u_int = std::is_same_v<T, const u_int>;

template <typename T>
/** @brief True if type is unsigned *. */
constexpr bool is_u_int_p = std::is_same_v<T, u_int *>;

template <typename T>
/** @brief True if type is u_int &. */
constexpr bool is_u_int_r = std::is_same_v<T, u_int &>;

template <typename T>
/** @brief True if type is const u_int *. */
constexpr bool is_cst_u_int_p = std::is_same_v<T, const u_int *>;

template <typename T>
/** @brief True if type is const u_int &. */
constexpr bool is_cst_u_int_r = std::is_same_v<T, const u_int &>;

template <typename T>
/** @brief True if type is unsigned long. */
constexpr bool is_u_long = std::is_same_v<T, u_long>;

template <typename T>
/** @brief True if type is const u_long. */
constexpr bool is_cst_u_long = std::is_same_v<T, const u_long>;

template <typename T>
/** @brief True if type is unsigned long *. */
constexpr bool is_u_long_p = std::is_same_v<T, u_long *>;

template <typename T>
/** @brief True if type is u_long &. */
constexpr bool is_u_long_r = std::is_same_v<T, u_long &>;

template <typename T>
/** @brief True if type is const u_long *. */
constexpr bool is_cst_u_long_p = std::is_same_v<T, const u_long *>;

template <typename T>
/** @brief True if type is const u_long &. */
constexpr bool is_cst_u_long_r = std::is_same_v<T, const u_long &>;

template <typename T>
/** @brief True if type is unsigned long long. */
constexpr bool is_ul_long = std::is_same_v<T, unsigned long long>;

template <typename T>
/** @brief True if type is cont unsigned long long. */
constexpr bool is_cst_ul_long = std::is_same_v<T, const unsigned long long>;

template <typename T>
/** @brief True if type is unsigned long long *. */
constexpr bool is_ul_long_p = std::is_same_v<T, unsigned long long *>;

template <typename T>
/** @brief True if type is unsigned long long &. */
constexpr bool is_ul_long_r = std::is_same_v<T, unsigned long long &>;

template <typename T>
/** @brief True if type is const unsigned long long *. */
constexpr bool is_cst_ul_long_p = std::is_same_v<T, const unsigned long long *>;

template <typename T>
/** @brief True if type is const unsigned long long &. */
constexpr bool is_cst_ul_long_r = std::is_same_v<T, const unsigned long long &>;

template <typename T>
/** @brief True if type is float. */
constexpr bool is_float = std::is_same_v<T, float>;

template <typename T>
/** @brief True if type is const float. */
constexpr bool is_cst_float = std::is_same_v<T, const float>;

template <typename T>
/** @brief True if type is float *. */
constexpr bool is_float_p = std::is_same_v<T, float *>;

template <typename T>
/** @brief True if type is float &. */
constexpr bool is_float_r = std::is_same_v<T, float &>;

template <typename T>
/** @brief True if type is const float *. */
constexpr bool is_cst_float_p = std::is_same_v<T, const float *>;

template <typename T>
/** @brief True if type is const float &. */
constexpr bool is_cst_float_r = std::is_same_v<T, const float &>;

template <typename T>
/** @brief True if type is double. */
constexpr bool is_double = std::is_same_v<T, double>;

template <typename T>
/** @brief True if type is const double. */
constexpr bool is_cst_double = std::is_same_v<T, const double>;

template <typename T>
/** @brief True if type is double *. */
constexpr bool is_double_p = std::is_same_v<T, double *>;

template <typename T>
/** @brief True if type is double &. */
constexpr bool is_double_r = std::is_same_v<T, double &>;

template <typename T>
/** @brief True if type is const double *. */
constexpr bool is_cst_double_p = std::is_same_v<T, const double *>;

template <typename T>
/** @brief True if type is const double &. */
constexpr bool is_cst_double_r = std::is_same_v<T, const double &>;

template <typename T>
/** @brief True if type is long double. */
constexpr bool is_l_double = std::is_same_v<T, long double>;

template <typename T>
/** @brief True if type is const long double. */
constexpr bool is_cst_l_double = std::is_same_v<T, const long double>;

template <typename T>
/** @brief True if type is long double *. */
constexpr bool is_l_double_p = std::is_same_v<T, long double *>;

template <typename T>
/** @brief True if type is long double &. */
constexpr bool is_l_double_r = std::is_same_v<T, long double &>;

template <typename T>
/** @brief True if type is const long double *. */
constexpr bool is_cst_l_double_p = std::is_same_v<T, const long double *>;

template <typename T>
/** @brief True if type is const long double &. */
constexpr bool is_cst_l_double_r = std::is_same_v<T, const long double &>;

template <typename T>
/** @brief True if type is bool. */
constexpr bool is_bool = std::is_same_v<T, bool>;

template <typename T>
/** @brief True if type is const bool. */
constexpr bool is_cst_bool = std::is_same_v<T, const bool>;

template <typename T>
/** @brief True if type is bool *. */
constexpr bool is_bool_p = std::is_same_v<T, bool *>;

template <typename T>
/** @brief True if type is bool &. */
constexpr bool is_bool_r = std::is_same_v<T, bool &>;

template <typename T>
/** @brief True if type is const bool *. */
constexpr bool is_cst_bool_p = std::is_same_v<T, const bool *>;

template <typename T>
/** @brief True if type is const bool &. */
constexpr bool is_cst_bool_r = std::is_same_v<T, const bool &>;

template <typename T>
/** @brief True if type is void. */
constexpr bool is_void = std::is_same_v<T, void>;

template <typename T>
/** @brief True if type is const void. */
constexpr bool is_cst_void = std::is_same_v<T, const void>;

template <typename T>
/** @brief True if type is void *. */
constexpr bool is_void_p = std::is_same_v<T, void *>;

template <typename T>
/** @brief True if type is const void *. */
constexpr bool is_cst_void_p = std::is_same_v<T, const void *>;

template <typename T>
/** @brief True if type is nullptr_t. */
constexpr bool is_nullptr = std::is_same_v<T, nullptr_t>;

template <typename T>
/** @brief True if type is trivially copyable and is either a fundamental
   value or pointer. */
constexpr bool is_easily_copyable = std::is_trivially_copyable_v<T> &&
                                    (std::is_fundamental_v<T> ||
                                     std::is_pointer_v<T>);

/* /--------------------------------------------------------------------------/
  /----------------------- Class Type Check Shortcuts -----------------------/
 /--------------------------------------------------------------------------/ */

template <typename T>
/** @brief True if type is std::string. */
constexpr bool is_string = std::is_same_v<T, std::string>;

template <typename T>
/** @brief True if type is const std::string. */
constexpr bool is_cst_string = std::is_same_v<T, const std::string>;

template <typename T>
/** @brief True if type is std::string *. */
constexpr bool is_string_p = std::is_same_v<T, std::string *>;

template <typename T>
/** @brief True if type is const std::string *. */
constexpr bool is_cst_string_p = std::is_same_v<T, const std::string *>;

template <typename T>
/** @brief True if type is std::string &. */
constexpr bool is_string_r = std::is_same_v<T, std::string &>;

template <typename T>
/** @brief True if type is const std::string &. */
constexpr bool is_cst_string_r = std::is_same_v<T, const std::string &>;

template <typename T>
/** @brief True if type is std::string_view. */
constexpr bool is_string_view = std::is_same_v<T, std::string_view>;

template <typename T>
/** @brief True if type is const std::string_view. */
constexpr bool is_cst_string_view = std::is_same_v<T, const std::string_view>;

template <typename T>
/** @brief True if type is std::string_view *. */
constexpr bool is_string_view_p = std::is_same_v<T, std::string_view *>;

template <typename T>
/** @brief True if type is const std::string_view *. */
constexpr bool is_cst_string_view_p =
    std::is_same_v<T, const std::string_view *>;

template <typename T>
/** @brief True if type is std::string_view &. */
constexpr bool is_string_view_r = std::is_same_v<T, std::string_view &>;

template <typename T>
/** @brief True if type is const std::string_view &. */
constexpr bool is_cst_string_view_r =
    std::is_same_v<T, const std::string_view &>;

/* /--------------------------------------------------------------------------/
  /---------------- Textual Number Checks and Classifications ---------------/
 /--------------------------------------------------------------------------/ */

// template <typename T, std::enable_if_t<is_easily_copyable_type<T>> * =
// nullptr>
// /** @brief True if the provided value is a valid whole number or text whole
//  * number. */
// bool is_whole_number(const T value) {
//   if constexpr (is_numerical_type<T> && !is_floating_point_type<T>) {
//     return true;
//   } else if constexpr (is_char_p<T>) {
//     for (size_t i = 0; value[i] != '\0'; i++) {
//       if (i == 0 && value[i] == '-') continue;
//       if (!is_whole_number(value[i])) return false;
//     }
//     return true;
//   } else if constexpr (is_char<T>) {
//     return value == '0' || value == '1' || value == '2' || value == '3' ||
//            value == '4' || value == '5' || value == '6' || value == '7' ||
//            value == '8' || value == '9';
//   }
//   return false;
// }

// template <typename T, std::enable_if_t<!is_easily_copyable_type<T>> * =
// nullptr>
// /** @brief True if the provided value is a valid whole number or text whole
//  * number. */
// bool is_whole_number(const T &value) {
//   if constexpr (is_string<T>) {
//     for (size_t i = 0; value[i] < value.size(); i++) {
//       if (i == 0 && value[i] == '-') continue;
//       if (!is_whole_number(value[i])) return false;
//     }
//     return true;
//   }
//   return false;
// }

// template <typename T, std::enable_if_t<is_easily_copyable_type<T>> * =
// nullptr>
// /** @brief True if the provided value is a valid number or text number. */
// bool is_number(const T value) {
//   if constexpr (is_numerical_type<T>) {
//     return true;
//   } else if constexpr (is_char_p<T>) {
//     bool found_decimal = false;
//     for (size_t i = 0; value[i] != '\0'; i++) {
//       if (i == 0 && value[i] == '-') {
//         continue;
//       }
//       if (value[i] == '.') {
//         if (found_decimal) return false;
//         found_decimal = true;
//       } else if (!is_whole_number(value[i])) {
//         return false;
//       }
//     }
//     return true;
//   } else if constexpr (is_char<T>) {
//     return is_whole_number(value);
//   }
//   return false;
// }

// template <typename T, std::enable_if_t<!is_easily_copyable_type<T>> * =
// nullptr>
// /** @brief True if the provided value is a valid number or text number. */
// bool is_number(const T &value) {
//   if constexpr (is_string<T>) {
//     bool found_decimal = false;
//     for (size_t i = 0; i < value.size(); i++) {
//       if (i == 0 && value[i] == '-') continue;
//       if (value[i] == '.') {
//         if (found_decimal) return false;
//         found_decimal = true;
//       } else if (!is_whole_number(value[i]))
//         return false;
//     }
//     return true;
//   }
//   return false;
// }

// template <typename T, std::enable_if_t<is_easily_copyable_type<T>> * =
// nullptr>
// /** @brief True if the provided value is a valid number but not a whole
// number.
//  */
// bool is_fractional_number(const T value) {
//   if constexpr (is_numerical_type<T>) {
//     return true;
//   } else if constexpr (is_char_p<T>) {
//     bool found_decimal = false;
//     for (size_t i = 0; value[i] != '\0'; i++) {
//       if (i == 0 && value[i] == '-') {
//         continue;
//       }
//       if (value[i] == '.') {
//         if (found_decimal) return false;
//         found_decimal = true;
//       } else if (!is_whole_number(value[i])) {
//         return false;
//       }
//     }
//     return found_decimal;
//   } else if constexpr (is_char<T>) {
//     return false;
//   }
//   return false;
// }

// template <typename T, std::enable_if_t<!is_easily_copyable_type<T>> * =
// nullptr>
// /** @brief True if the provided value is a valid number but not a whole
// number.
//  */
// bool is_fractional_number(const T &value) {
//   if constexpr (is_string<T>) {
//     bool found_decimal = false;
//     for (size_t i = 0; i < value.size(); i++) {
//       if (i == 0 && value[i] == '-') continue;
//       if (value[i] == '.') {
//         if (found_decimal) return false;
//         found_decimal = true;
//       } else if (!is_whole_number(value[i]))
//         return false;
//     }
//     return found_decimal;
//   }
//   return false;
// }

}  // namespace types
}  // namespace ccutl
