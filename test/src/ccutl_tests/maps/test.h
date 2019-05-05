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
 * @file ccutl_tests/maps/test.h
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions in ccutl/maps/maps.h.
 * @version 0.2.0
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-05
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include <map>
#include <string>
#include <vector>

namespace ccutl_tests {
namespace maps {

// ------------------------- Predefined Object Keys ------------------------- //
static std::vector<std::string> obj_key_A1 = {};
static std::vector<std::string> obj_key_A2 = {"foo"};
static std::vector<std::map<int, int>> obj_key_B1 = {};
static std::vector<std::map<int, int>> obj_key_B2 = {{{32, 42}}};

// ---------------------------- Fundamental Maps ---------------------------- //
// 1-Dimensional
static std::map<int, float> fundamental_map_1D_has = {{32, 3.14f}};
static std::map<int, float> fundamental_map_1D_get = {{32, 3.14f}};
static std::map<int, float> fundamental_map_1D_set = {{32, 3.14f}};
static std::map<int, float> fundamental_map_1D_del = {{32, 3.14f}};
// 2-Dimensional
static std::map<int, std::map<float, double>> fundamental_map_2D_has = {
    {321, {{1.23f, 28323.15}}}};
static std::map<int, std::map<float, double>> fundamental_map_2D_get = {
    {321, {{1.23f, 28323.15}}}};
static std::map<int, std::map<float, double>> fundamental_map_2D_set = {
    {321, {{1.23f, 28323.15}}}};
static std::map<int, std::map<float, double>> fundamental_map_2D_del = {
    {321, {{1.23f, 28323.15}}}};

// ------------------------------ Object Maps ------------------------------- //
// 1-Dimensional
static std::map<std::vector<std::string>, float> object_map_1D_has = {
    {obj_key_A1, 3.14f}};
static std::map<std::vector<std::string>, float> object_map_1D_get = {
    {obj_key_A1, 3.14f}};
static std::map<std::vector<std::string>, float> object_map_1D_set = {
    {obj_key_A1, 3.14f}};
static std::map<std::vector<std::string>, float> object_map_1D_del = {
    {obj_key_A1, 3.14f}};
// 2-Dimensional
static std::map<std::vector<std::string>,
                std::map<std::vector<std::map<int, int>>, float>>
    object_map_2D_has = {{obj_key_A1, {{obj_key_B1, 3.1415f}}}};
static std::map<std::vector<std::string>,
                std::map<std::vector<std::map<int, int>>, float>>
    object_map_2D_get = {{obj_key_A1, {{obj_key_B1, 3.1415f}}}};
static std::map<std::vector<std::string>,
                std::map<std::vector<std::map<int, int>>, float>>
    object_map_2D_set = {{obj_key_A1, {{obj_key_B1, 3.1415f}}}};
static std::map<std::vector<std::string>,
                std::map<std::vector<std::map<int, int>>, float>>
    object_map_2D_del = {{obj_key_A1, {{obj_key_B1, 3.1415f}}}};

// ------------------------------ Pointer Maps ------------------------------ //
// 1-Dimensional
static std::map<std::vector<std::string> *, float> pointer_map_1D_has = {
    {&obj_key_A1, 3.14f}};
static std::map<std::vector<std::string> *, float> pointer_map_1D_get = {
    {&obj_key_A1, 3.14f}};
static std::map<std::vector<std::string> *, float> pointer_map_1D_set = {
    {&obj_key_A1, 3.14f}};
static std::map<std::vector<std::string> *, float> pointer_map_1D_del = {
    {&obj_key_A1, 3.14f}};
// 2-Dimensional
static std::map<std::vector<std::string> *,
                std::map<std::vector<std::map<int, int>> *, float>>
    pointer_map_2D_has = {{&obj_key_A1, {{&obj_key_B1, 3.1415f}}}};
static std::map<std::vector<std::string> *,
                std::map<std::vector<std::map<int, int>> *, float>>
    pointer_map_2D_get = {{&obj_key_A1, {{&obj_key_B1, 3.1415f}}}};
static std::map<std::vector<std::string> *,
                std::map<std::vector<std::map<int, int>> *, float>>
    pointer_map_2D_set = {{&obj_key_A1, {{&obj_key_B1, 3.1415f}}}};
static std::map<std::vector<std::string> *,
                std::map<std::vector<std::map<int, int>> *, float>>
    pointer_map_2D_del = {{&obj_key_A1, {{&obj_key_B1, 3.1415f}}}};

// --------------------------- const char * maps ---------------------------- //
// 1-Dimensional
static std::map<const char *, float> ccharp_map_1D_has = {{"foo", 3.14f}};
static std::map<const char *, float> ccharp_map_1D_get = {{"foo", 3.14f}};
static std::map<const char *, float> ccharp_map_1D_set = {{"foo", 3.14f}};
static std::map<const char *, float> ccharp_map_1D_del = {{"foo", 3.14f}};
// 2-Dimensional
static std::map<const char *, std::map<const char *, float>> ccharp_map_2D_has =
    {{"foo", {{"bar", 3.1415f}}}};
static std::map<const char *, std::map<const char *, float>> ccharp_map_2D_get =
    {{"foo", {{"bar", 3.1415f}}}};
static std::map<const char *, std::map<const char *, float>> ccharp_map_2D_set =
    {{"foo", {{"bar", 3.1415f}}}};
static std::map<const char *, std::map<const char *, float>> ccharp_map_2D_del =
    {{"foo", {{"bar", 3.1415f}}}};

void has();
void get();
void set();
void del();
void run_tests();

}  // namespace maps
}  // namespace ccutl_tests
