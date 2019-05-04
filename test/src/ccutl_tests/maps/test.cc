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
 * @file ccutl_tests/maps/test.cc
 * @author Justin Collier (jpcxist@gmail.com)
 * @brief Tests the functions in ccutl/maps/maps.h.
 * @version 0.1.0
 * @since cpputils 0.2.0
 * @date created 2019-05-02
 * @date modified 2019-05-04
 * @copyright Copyright (c) 2019 Justin Collier
 */

#include "ccutl_tests/maps/test.h"

#include <map>

#include "ccutl/maps/maps.h"
#include "ccutl/tests/testgroup.h"

namespace ccutl_tests {
namespace maps {

void get() {
  using ccutl::maps::get;
  using ccutl::tests::TestGroup;
  auto test_fundamental_get = TestGroup("ccutl::maps::get | fundamental maps");
  test_fundamental_get.assert_value(
      "get from 1D fundamental map returns the correct value",
      [=]() { return get(fundamental_map_1D_get, 32); }, 3.14f);
  test_fundamental_get.assert_value(
      "get from 2D fundamental map returns the correct value",
      [=]() { return get(fundamental_map_2D_get, 321, 1.23f); }, 28323.15);
  test_fundamental_get.assert_throws(
      "invalid get from 1D fundamental map throws the correct value",
      [=]() { return get(fundamental_map_1D_get, 404); }, "Key not found");
  test_fundamental_get.assert_throws(
      "invalid get from 2D fundamental map throws the correct value with an "
      "invalid parent key",
      [=]() { return get(fundamental_map_2D_get, 404, 1.23f); },
      "Key not found");
  test_fundamental_get.assert_throws(
      "invalid get from 2D fundamental map throws the correct value with an "
      "invalid child key",
      [=]() { return get(fundamental_map_2D_get, 321, 4.04f); },
      "Key not found");
  test_fundamental_get.assert_throws(
      "invalid get from 2D fundamental map throws the correct value when both "
      "keys are invalid",
      [=]() { return get(fundamental_map_2D_get, 404, 4.04f); },
      "Key not found");
  test_fundamental_get.end();

  auto test_object_get = TestGroup("ccutl::maps::get | object maps");
  test_object_get.assert_value(
      "get from 1D object map returns the correct value",
      [=]() { return get(object_map_1D_get, obj_key_A1); }, 3.14f);
  test_object_get.assert_value(
      "get from 2D object map returns the correct value",
      [=]() { return get(object_map_2D_get, obj_key_A1, obj_key_B1); },
      3.1415f);
  test_object_get.assert_throws(
      "invalid get from 1D object map throws the correct value",
      [=]() { return get(object_map_1D_get, obj_key_A2); }, "Key not found");
  test_object_get.assert_throws(
      "invalid get from 2D object map throws the correct value with an "
      "invalid parent key",
      [=]() { return get(object_map_2D_get, obj_key_A2, obj_key_B1); },
      "Key not found");
  test_object_get.assert_throws(
      "invalid get from 2D object map throws the correct value with an "
      "invalid child key",
      [=]() { return get(object_map_2D_get, obj_key_A1, obj_key_B2); },
      "Key not found");
  test_object_get.assert_throws(
      "invalid get from 2D object map throws the correct value when both "
      "keys are invalid",
      [=]() { return get(object_map_2D_get, obj_key_A2, obj_key_B2); },
      "Key not found");
  test_object_get.end();

  auto test_pointer_get = TestGroup("ccutl::maps::get | pointer maps");
  test_pointer_get.assert_value(
      "get from 1D pointer map returns the correct value",
      [=]() { return get(pointer_map_1D_get, &obj_key_A1); }, 3.14f);
  test_pointer_get.assert_value(
      "get from 2D pointer map returns the correct value",
      [=]() { return get(pointer_map_2D_get, &obj_key_A1, &obj_key_B1); },
      3.1415f);
  test_pointer_get.assert_throws(
      "invalid get from 1D pointer map throws the correct value",
      [=]() { return get(pointer_map_1D_get, &obj_key_A2); }, "Key not found");
  test_pointer_get.assert_throws(
      "invalid get from 2D pointer map throws the correct value with an "
      "invalid parent key",
      [=]() { return get(pointer_map_2D_get, &obj_key_A2, &obj_key_B1); },
      "Key not found");
  test_pointer_get.assert_throws(
      "invalid get from 2D pointer map throws the correct value with an "
      "invalid child key",
      [=]() { return get(pointer_map_2D_get, &obj_key_A1, &obj_key_B2); },
      "Key not found");
  test_pointer_get.assert_throws(
      "invalid get from 2D pointer map throws the correct value when both "
      "keys are invalid",
      [=]() { return get(pointer_map_2D_get, &obj_key_A2, &obj_key_B2); },
      "Key not found");
  test_pointer_get.end();

  auto test_ccharp_get = TestGroup("ccutl::maps::get | ccharp maps");
  test_ccharp_get.assert_value(
      "get from 1D const char * map returns the correct value",
      [=]() { return get(ccharp_map_1D_get, "foo"); }, 3.14f);
  test_ccharp_get.assert_value(
      "get from 2D const char * map returns the correct value",
      [=]() { return get(ccharp_map_2D_get, "foo", "bar"); }, 3.1415f);
  test_ccharp_get.assert_throws(
      "invalid get from 1D const char * map throws the correct value",
      [=]() { return get(ccharp_map_1D_get, "qux"); }, "Key not found");
  test_ccharp_get.assert_throws(
      "invalid get from 2D const char * map throws the correct value with an "
      "invalid parent key",
      [=]() { return get(ccharp_map_2D_get, "qux", "bar"); }, "Key not found");
  test_ccharp_get.assert_throws(
      "invalid get from 2D const char * map throws the correct value with an "
      "invalid child key",
      [=]() { return get(ccharp_map_2D_get, "foo", "quz"); }, "Key not found");
  test_ccharp_get.assert_throws(
      "invalid get from 2D const char * map throws the correct value when both "
      "keys are invalid",
      [=]() { return get(ccharp_map_2D_get, "qux", "quz"); }, "Key not found");
  test_ccharp_get.end();
}

void set() {
  using ccutl::maps::get;
  using ccutl::maps::set;
  using ccutl::tests::TestGroup;
  auto test_fundamental_set = TestGroup("ccutl::maps::set | fundamental maps");
  test_fundamental_set.assert_value(
      "set to 1D fundamental map value results in an expected change",
      [=]() {
        set(&fundamental_map_1D_set, 32, 6.18f);
        return get(fundamental_map_1D_set, 32);
      },
      6.18f);
  test_fundamental_set.assert_value(
      "set to 1D fundamental map key results in an expected change",
      [=]() {
        set(&fundamental_map_1D_set, 64, 12.36f);
        return get(fundamental_map_1D_set, 64);
      },
      12.36f);
  test_fundamental_set.assert_value(
      "set to 2D fundamental map value results in an expected change",
      [=]() {
        set(&fundamental_map_2D_set, 321, 1.23f, 56646.3);
        return get(fundamental_map_2D_set, 321, 1.23f);
      },
      56646.3);
  test_fundamental_set.assert_value(
      "set to 2D fundamental map child key results in an expected change",
      [=]() {
        set(&fundamental_map_2D_set, 321, 2.46f, 113292.6);
        return get(fundamental_map_2D_set, 321, 2.46f);
      },
      113292.6);
  test_fundamental_set.assert_value(
      "set to 2D fundamental map parent key results in an expected change",
      [=]() {
        set(&fundamental_map_2D_set, 642, 2.46f, 113292.6);
        return get(fundamental_map_2D_set, 642, 2.46f);
      },
      113292.6);
  test_fundamental_set.end();

  auto test_object_set = TestGroup("ccutl::maps::set | object maps");
  test_object_set.assert_value(
      "set to 1D object map value results in an expected change",
      [=]() {
        set(&object_map_1D_set, obj_key_A1, 6.18f);
        return get(object_map_1D_set, obj_key_A1);
      },
      6.18f);
  test_object_set.assert_value(
      "set to 1D object map key results in an expected change",
      [=]() {
        set(&object_map_1D_set, obj_key_A2, 12.36f);
        return get(object_map_1D_set, obj_key_A2);
      },
      12.36f);
  test_object_set.assert_value(
      "set to 2D object map value results in an expected change",
      [=]() {
        set(&object_map_2D_set, obj_key_A1, obj_key_B1, 6.283f);
        return get(object_map_2D_set, obj_key_A1, obj_key_B1);
      },
      6.283f);
  test_object_set.assert_value(
      "set to 2D object map child key results in an expected change",
      [=]() {
        set(&object_map_2D_set, obj_key_A1, obj_key_B2, 12.566f);
        return get(object_map_2D_set, obj_key_A1, obj_key_B2);
      },
      12.566f);
  test_object_set.assert_value(
      "set to 2D object map parent key results in an expected change",
      [=]() {
        set(&object_map_2D_set, obj_key_A2, obj_key_B2, 25.132f);
        return get(object_map_2D_set, obj_key_A2, obj_key_B2);
      },
      25.132f);
  test_object_set.end();

  auto test_pointer_set = TestGroup("ccutl::maps::set | pointer maps");
  test_pointer_set.assert_value(
      "set to 1D pointer map value results in an expected change",
      [=]() {
        set(&pointer_map_1D_set, &obj_key_A1, 6.18f);
        return get(pointer_map_1D_set, &obj_key_A1);
      },
      6.18f);
  test_pointer_set.assert_value(
      "set to 1D pointer map key results in an expected change",
      [=]() {
        set(&pointer_map_1D_set, &obj_key_A2, 12.36f);
        return get(pointer_map_1D_set, &obj_key_A2);
      },
      12.36f);
  test_pointer_set.assert_value(
      "set to 2D pointer map value results in an expected change",
      [=]() {
        set(&pointer_map_2D_set, &obj_key_A1, &obj_key_B1, 6.283f);
        return get(pointer_map_2D_set, &obj_key_A1, &obj_key_B1);
      },
      6.283f);
  test_pointer_set.assert_value(
      "set to 2D pointer map child key results in an expected change",
      [=]() {
        set(&pointer_map_2D_set, &obj_key_A1, &obj_key_B2, 12.566f);
        return get(pointer_map_2D_set, &obj_key_A1, &obj_key_B2);
      },
      12.566f);
  test_pointer_set.assert_value(
      "set to 2D pointer map parent key results in an expected change",
      [=]() {
        set(&pointer_map_2D_set, &obj_key_A2, &obj_key_B2, 25.132f);
        return get(pointer_map_2D_set, &obj_key_A2, &obj_key_B2);
      },
      25.132f);
  test_pointer_set.end();

  auto test_ccharp_set = TestGroup("ccutl::maps::set | const char * maps");
  test_ccharp_set.assert_value(
      "set to 1D const char * map value results in an expected change",
      [=]() {
        set(&ccharp_map_1D_set, "foo", 6.18f);
        return get(ccharp_map_1D_set, "foo");
      },
      6.18f);
  test_ccharp_set.assert_value(
      "set to 1D const char * map key results in an expected change",
      [=]() {
        set(&ccharp_map_1D_set, "qux", 12.36f);
        return get(ccharp_map_1D_set, "qux");
      },
      12.36f);
  test_ccharp_set.assert_value(
      "set to 2D const char * map value results in an expected change",
      [=]() {
        set(&ccharp_map_2D_set, "foo", "bar", 6.283f);
        return get(ccharp_map_2D_set, "foo", "bar");
      },
      6.283f);
  test_ccharp_set.assert_value(
      "set to 2D const char * map child key results in an expected change",
      [=]() {
        set(&ccharp_map_2D_set, "foo", "quz", 12.566f);
        return get(ccharp_map_2D_set, "foo", "quz");
      },
      12.566f);
  test_ccharp_set.assert_value(
      "set to 2D const char * map parent key results in an expected change",
      [=]() {
        set(&ccharp_map_2D_set, "qux", "quz", 25.132f);
        return get(ccharp_map_2D_set, "qux", "quz");
      },
      25.132f);
  test_ccharp_set.end();
}

void del() {
  using ccutl::maps::del;
  using ccutl::maps::get;
  using ccutl::tests::TestGroup;
  auto test_fundamental_del = TestGroup("ccutl::maps::del | fundamental maps");
  test_fundamental_del.assert_throws(
      "del from 1D fundamental map results in expected get failure",
      [=]() {
        try {
          get(fundamental_map_1D_del, 32);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&fundamental_map_1D_del, 32);
        get(fundamental_map_1D_del, 32);
      },
      "Key not found");
  test_fundamental_del.assert_throws(
      "del from 2D fundamental map child results in expected get failure",
      [=]() {
        try {
          get(fundamental_map_2D_del, 321, 1.23f);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&fundamental_map_2D_del, 321, 1.23f);
        try {
          get(fundamental_map_2D_del, 321);
        } catch (...) {
          throw "ccutl::maps::del has inadvertently deleted the parent key!";
        }
        get(fundamental_map_2D_del, 321, 1.23f);
      },
      "Key not found");
  test_fundamental_del.assert_throws(
      "del from 2D fundamental map parent results in expected get failure",
      [=]() {
        try {
          get(fundamental_map_2D_del, 321);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&fundamental_map_2D_del, 321);
        get(fundamental_map_2D_del, 321);
      },
      "Key not found");
  test_fundamental_del.end();

  auto test_object_del = TestGroup("ccutl::maps::del | object maps");
  test_object_del.assert_throws(
      "del from 1D object map results in expected get failure",
      [=]() {
        try {
          get(object_map_1D_del, obj_key_A1);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&object_map_1D_del, obj_key_A1);
        get(object_map_1D_del, obj_key_A1);
      },
      "Key not found");
  test_object_del.assert_throws(
      "del from 2D object map child results in expected get failure",
      [=]() {
        try {
          get(object_map_2D_del, obj_key_A1, obj_key_B1);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&object_map_2D_del, obj_key_A1, obj_key_B1);
        try {
          get(object_map_2D_del, obj_key_A1);
        } catch (...) {
          throw "ccutl::maps::del has inadvertently deleted the parent key!";
        }
        get(object_map_2D_del, obj_key_A1, obj_key_B1);
      },
      "Key not found");
  test_object_del.assert_throws(
      "del from 2D object map parent results in expected get failure",
      [=]() {
        try {
          get(object_map_2D_del, obj_key_A1);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&object_map_2D_del, obj_key_A1);
        get(object_map_2D_del, obj_key_A1);
      },
      "Key not found");
  test_object_del.end();

  auto test_pointer_del = TestGroup("ccutl::maps::del | pointer maps");
  test_pointer_del.assert_throws(
      "del from 1D pointer map results in expected get failure",
      [=]() {
        try {
          get(pointer_map_1D_del, &obj_key_A1);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&pointer_map_1D_del, &obj_key_A1);
        get(pointer_map_1D_del, &obj_key_A1);
      },
      "Key not found");
  test_pointer_del.assert_throws(
      "del from 2D pointer map child results in expected get failure",
      [=]() {
        try {
          get(pointer_map_2D_del, &obj_key_A1, &obj_key_B1);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&pointer_map_2D_del, &obj_key_A1, &obj_key_B1);
        try {
          get(pointer_map_2D_del, &obj_key_A1);
        } catch (...) {
          throw "ccutl::maps::del has inadvertently deleted the parent key!";
        }
        get(pointer_map_2D_del, &obj_key_A1, &obj_key_B1);
      },
      "Key not found");
  test_pointer_del.assert_throws(
      "del from 2D pointer map parent results in expected get failure",
      [=]() {
        try {
          get(pointer_map_2D_del, &obj_key_A1);
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&pointer_map_2D_del, &obj_key_A1);
        get(pointer_map_2D_del, &obj_key_A1);
      },
      "Key not found");
  test_pointer_del.end();

  auto test_ccharp_del = TestGroup("ccutl::maps::del | const char * maps");
  test_ccharp_del.assert_throws(
      "del from 1D const char * map results in expected get failure",
      [=]() {
        try {
          get(ccharp_map_1D_del, "foo");
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&ccharp_map_1D_del, "foo");
        get(ccharp_map_1D_del, "foo");
      },
      "Key not found");
  test_ccharp_del.assert_throws(
      "del from 2D const char * map child results in expected get failure",
      [=]() {
        try {
          get(ccharp_map_2D_del, "foo", "bar");
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&ccharp_map_2D_del, "foo", "bar");
        try {
          get(ccharp_map_2D_del, "foo");
        } catch (...) {
          throw "ccutl::maps::del has inadvertently deleted the parent key!";
        }
        get(ccharp_map_2D_del, "foo", "bar");
      },
      "Key not found");
  test_ccharp_del.assert_throws(
      "del from 2D const char * map parent results in expected get failure",
      [=]() {
        try {
          get(ccharp_map_2D_del, "foo");
        } catch (...) {
          throw "Get was unable to find expected value during del pre-check!";
        }
        del(&ccharp_map_2D_del, "foo");
        get(ccharp_map_2D_del, "foo");
      },
      "Key not found");
  test_ccharp_del.end();
}

void run_tests() {
  get();
  set();
  del();
  std::cout << "\033[1;32mAll tests completed successfully!\033[0m"
            << std::endl;
}

}  // namespace maps
}  // namespace ccutl_tests
