#ifndef CPPUTILS_CCUTL_MAPS_H_
#define CPPUTILS_CCUTL_MAPS_H_

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
 * @file ccutl/maps.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides template functions for deeply interacting with maps.
 * @version 0.3.1
 * @since cpputils 0.1.0
 * @date created 2019-05-01
 * @date modified 2019-07-12
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl/core/maps.h"

#include <map>
#include <utility>

namespace ccutl {

template <typename T_Key, typename T_Val>
/** @brief Checks if a map has a key. */
bool map_has(const std::map<T_Key, T_Val> &target, const T_Key &key) {
	return target.find(key) != target.end();
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively checks if a nested map has an established key path. */
bool map_has(const std::map<T_Key, T_Val> &target, const T_Key &key,
						 const T_Rest... rest) {
	auto it = target.find(key);
	if (it == target.end()) return false;
	return map_has(it->second, rest...);
}

template <typename T_Key, typename T_Val>
/** @brief Gets a value from a map using a key. */
T_Val map_get(const std::map<T_Key, T_Val> &target, const T_Key &key) {
	auto it = target.find(key);
	if (it == target.end()) throw "Key not found";
	return it->second;
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively gets a value from a nested map using a key path. */
auto map_get(const std::map<T_Key, T_Val> &target, const T_Key &key,
						 const T_Rest... rest) {
	auto it = target.find(key);
	if (it == target.end()) throw "Key not found";
	return map_get(it->second, rest...);
}

template <typename T_Key, typename T_Val>
/** @brief Sets a value to a map using a key. */
void map_set(std::map<T_Key, T_Val> *target, const T_Key &key,
						 const T_Val &val) {
	target->insert_or_assign(key, val);
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively sets a value to a nested map using a key path. The last
 *  provided argument will be the set value. */
void map_set(std::map<T_Key, T_Val> *target, const T_Key &key,
						 const T_Rest... rest) {
	map_set(&(*target)[key], rest...);
}

template <typename T_Key, typename T_Val>
/** @brief Deletes a key from a map. */
void map_del(std::map<T_Key, T_Val> *target, const T_Key &key) {
	target->erase(key);
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively deletes a value from a nested map using a key path. */
void map_del(std::map<T_Key, T_Val> *target, const T_Key &key,
						 const T_Rest... rest) {
	auto it = target->find(key);
	if (it == target->end()) return;
	map_del(&(*target)[key], rest...);
}

template <typename T_Key, typename T_Val,
					std::enable_if_t<std::is_trivially_copyable_v<T_Key> &&
													 std::is_trivially_copyable_v<T_Val>> *>
/** @brief Creates a map using a key and value pair. */
std::map<T_Key, T_Val> map_create(const T_Key key, const T_Val val) {
	return {{key, val}};
}

template <typename T_Key, typename T_Val,
					std::enable_if_t<!std::is_trivially_copyable_v<T_Key> &&
													 std::is_trivially_copyable_v<T_Val>> *>
/** @brief Creates a map using a key and value pair. */
std::map<T_Key, T_Val> map_create(const T_Key &key, const T_Val val) {
	return {{key, val}};
}

template <typename T_Key, typename T_Val,
					std::enable_if_t<std::is_trivially_copyable_v<T_Key> &&
													 !std::is_trivially_copyable_v<T_Val>> *>
/** @brief Creates a map using a key and value pair. */
std::map<T_Key, T_Val> map_create(const T_Key key, const T_Val &val) {
	return {{key, val}};
}

template <typename T_Key, typename T_Val,
					std::enable_if_t<!std::is_trivially_copyable_v<T_Key> &&
													 !std::is_trivially_copyable_v<T_Val>> *>
/** @brief Creates a map using a key and value pair. */
std::map<T_Key, T_Val> map_create(const T_Key &key, const T_Val &val) {
	return {{key, val}};
}

template <typename T_Key, typename... T_Rest,
					std::enable_if_t<std::is_trivially_copyable_v<T_Key>> *>
/** @brief Recursively creates a map using a key path and value. The last
 *  provided argument will be the set value. */
auto map_create(const T_Key key, const T_Rest... rest) {
	return map_create(key, map_create(rest...));
}

template <typename T_Key, typename... T_Rest,
					std::enable_if_t<!std::is_trivially_copyable_v<T_Key>> *>
/** @brief Recursively creates a map using a key path and value. The last
 *  provided argument will be the set value. */
auto map_create(const T_Key &key, const T_Rest... rest) {
	return map_create(key, map_create(rest...));
}

}	// namespace ccutl

#endif	// CPPUTILS_CCUTL_MAPS_H_
