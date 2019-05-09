# cpputils 0.4.3

Provides a collection of header files that facilitate C++ development.

## Documentation

### `ccutl::maps` (ccutl/maps/maps.h) 0.3.0

Provides a collection of template functions for working with std::maps.

#### `ccutl::maps::has(std::map<...> target, ...T_Key key)` -> `bool`

Returns true if a map has an established key path.

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}}}};
// true
ccutl::maps::has(example, "foo", "bar");
// false
ccutl::maps::has(example, "foo", "baz");
```

#### `ccutl::maps::get(std::map<...> target, ...T_Key key)` -> `T_Val`

Gets a value from a nested map using a key path.

Throws:
  const char * "Key not found" if the key is not found

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}}}};
// "baz"
ccutl::maps::get(example, "foo", "bar");
// throws: "Key not found"
ccutl::maps::get(example, "foo", "baz");
```

#### `ccutl::maps::set(std::map<...> *target, ...T_Key key, T_Val value)` -> `void`

Sets a value in a nested map given a key path and value.
The last argument provided will be the value.

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}}}};
// example is now: {{"foo", {{"bar", "qux"}}}};
ccutl::maps::set(&example, "foo", "bar", "qux");
```

#### `ccutl::maps::del(std::map<...> *target, ...T_Key key)` -> `void`

Deletes a key from a map given a key path.

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}, {"qux", "quz"}}}};
// example is now: {{"foo", {{"bar", "baz"}}}};
ccutl::maps::del(&example, "foo", "qux"");
```

#### `ccutl::maps::create(...T_Key key, T_Val value)` -> `std::map<...>`

Creates a new map given a key path and a value.

Example:

```c++
// std::map<const char *, std::map<const char *, const char *>> map = {{ "foo", {{"bar", "baz"}} }};
auto map = ccutl::maps::create("foo", "bar", "baz");
```

### `ccutl::tests::TestGroup` (ccutl/tests/testgroup.h) 0.1.0

Provides a very basic framework for unit testing.

#### `TestGroup(std::string title)` -> `TestGroup`

Creates a new test group. Announces the title to stdout.

#### `TestGroup::assert_value(std::string description, T_Lambda test, T_Value value)` -> `void`

Asserts that the execution of a provided lambda function returns the expected value.

#### `TestGroup::assert_throws(std::string description, T_Lambda test, T_Error err)` -> `void`

Asserts that the execution of a provided lambda function throws the expected error.

#### `TestGroup::end()` -> `void`

Logs a bottom border to stdout.

### `ccutl::types` (ccutl/types/types.h) 0.2.0

Provides various type-related templates.

#### `typename ccutl::types::const_copyable_t<T>`

Wrapper for std::conditional that is a `const T` if T is a trivially copyable type or `const T&` if not.

## Testing

Please run `make test` in order to test the package.

## License

Copyright © Justin Collier  License GPLv3+: GNU GPL version 3 or later
<<https://gnu.org/licenses/gpl.html>>.

This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
