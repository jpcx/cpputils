#ifndef CPPUTILS_CCUTL_CORE_MAPS_H_
#define CPPUTILS_CCUTL_CORE_MAPS_H_

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
 * @file ccutl/core/maps.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides template functions for deeply interacting with maps.
 * @version 0.3.1
 * @since cpputils 0.1.0
 * @date created 2019-05-01
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <map>
#include <utility>

namespace ccutl {

template <typename T_Key, typename T_Val>
bool map_has(const std::map<T_Key, T_Val> &target, const T_Key &key);

template <typename T_Key, typename T_Val, typename... T_Rest>
bool map_has(const std::map<T_Key, T_Val> &target, const T_Key &key,
						 const T_Rest... rest);

template <typename T_Key, typename T_Val>
T_Val map_get(const std::map<T_Key, T_Val> &target, const T_Key &key);

template <typename T_Key, typename T_Val, typename... T_Rest>
auto map_get(const std::map<T_Key, T_Val> &target, const T_Key &key,
						 const T_Rest... rest);

template <typename T_Key, typename T_Val>
void map_set(std::map<T_Key, T_Val> *target, const T_Key &key,
						 const T_Val &val);

template <typename T_Key, typename T_Val, typename... T_Rest>
void map_set(std::map<T_Key, T_Val> *target, const T_Key &key,
						 const T_Rest... rest);

template <typename T_Key, typename T_Val>
void map_del(std::map<T_Key, T_Val> *target, const T_Key &key);

template <typename T_Key, typename T_Val, typename... T_Rest>
void map_del(std::map<T_Key, T_Val> *target, const T_Key &key,
						 const T_Rest... rest);

template <typename T_Key, typename T_Val,
					std::enable_if_t<std::is_trivially_copyable_v<T_Key> &&
													 std::is_trivially_copyable_v<T_Val>> * = nullptr>
std::map<T_Key, T_Val> map_create(const T_Key key, const T_Val val);

template <typename T_Key, typename T_Val,
					std::enable_if_t<!std::is_trivially_copyable_v<T_Key> &&
													 std::is_trivially_copyable_v<T_Val>> * = nullptr>
std::map<T_Key, T_Val> map_create(const T_Key &key, const T_Val val);

template <typename T_Key, typename T_Val,
					std::enable_if_t<std::is_trivially_copyable_v<T_Key> &&
													 !std::is_trivially_copyable_v<T_Val>> * = nullptr>
std::map<T_Key, T_Val> map_create(const T_Key key, const T_Val &val);

template <typename T_Key, typename T_Val,
					std::enable_if_t<!std::is_trivially_copyable_v<T_Key> &&
													 !std::is_trivially_copyable_v<T_Val>> * = nullptr>
std::map<T_Key, T_Val> map_create(const T_Key &key, const T_Val &val);

template <typename T_Key, typename... T_Rest,
					std::enable_if_t<std::is_trivially_copyable_v<T_Key>> * = nullptr>
auto map_create(const T_Key key, const T_Rest... rest);

template <typename T_Key, typename... T_Rest,
					std::enable_if_t<!std::is_trivially_copyable_v<T_Key>> * = nullptr>
auto map_create(const T_Key &key, const T_Rest... rest);

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_CORE_MAPS_H_
