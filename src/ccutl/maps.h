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
 * @file ccutl/maps/maps.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Provides template functions for deeply interacting with maps.
 * @version 0.2.1
 * @since cpputils 0.1.0
 * @date created 2019-05-01
 * @date modified 2019-05-05
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <map>
#include <utility>

#include "ccutl/types.h"

namespace ccutl {
namespace maps {

template <typename T_Key, typename T_Val>
/** @brief Checks if a map has a key. */
bool has(const std::map<T_Key, T_Val> &target,
         types::const_ref_or_v<T_Key> key) {
  return target.find(key) != target.end();
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively checks if a nested map has an established key path. */
bool has(const std::map<T_Key, T_Val> &target, types::const_ref_or_v<T_Key> key,
         const T_Rest... rest) {
  auto it = target.find(key);
  if (it == target.end()) return false;
  return has(it->second, rest...);
}

template <typename T_Key, typename T_Val>
/** @brief Gets a value from a map using a key. */
T_Val get(const std::map<T_Key, T_Val> &target,
          types::const_ref_or_v<T_Key> key) {
  auto it = target.find(key);
  if (it == target.end()) throw "Key not found";
  return it->second;
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively gets a value from a nested map using a key path. */
auto get(const std::map<T_Key, T_Val> &target, types::const_ref_or_v<T_Key> key,
         const T_Rest... rest) {
  auto it = target.find(key);
  if (it == target.end()) throw "Key not found";
  return get(it->second, rest...);
}

template <typename T_Key, typename T_Val>
/** @brief Sets a value to a map using a key. */
void set(std::map<T_Key, T_Val> *target, types::const_ref_or_v<T_Key> key,
         types::const_ref_or_v<T_Val> val) {
  target->insert_or_assign(key, val);
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively sets a value to a nested map using a key path. The last
 *  provided argument will be the value set. */
void set(std::map<T_Key, T_Val> *target, types::const_ref_or_v<T_Key> key,
         const T_Rest... rest) {
  set(&(*target)[key], rest...);
}

template <typename T_Key, typename T_Val>
/** @brief Deletes a key from a map. */
void del(std::map<T_Key, T_Val> *target, types::const_ref_or_v<T_Key> key) {
  target->erase(key);
}

template <typename T_Key, typename T_Val, typename... T_Rest>
/** @brief Recursively deletes a value from a nested map using a key path. */
void del(std::map<T_Key, T_Val> *target, types::const_ref_or_v<T_Key> key,
         const T_Rest... rest) {
  auto it = target->find(key);
  if (it == target->end()) return;
  del(&(*target)[key], rest...);
}

}  // namespace maps
}  // namespace ccutl
