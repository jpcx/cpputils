# cpputils

Provides a collection of header files that aid in C++ development.

Feel free to copy any file you'd like into your project.
Keep in mind that all functions are namespaced under "cpputils".

## maptools.h

Provides a collection of template functions for working with std::maps.

### bool map_has(std::map<...> target, T_Key ...key)

Returns true if a map has a given path of keys.

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}}}};
// true
map_has(example, "foo", "bar");
// false
map_has(example, "foo", "baz");
```

### T_Val map_get(std::map<...> target, T_Key ...key)

Gets a value from a map given a path of keys.

Throws:
  const char * "Key not found" if the key is not found

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}}}};
// "baz"
map_get(example, "foo", "bar");
// throws: "Key not found"
map_get(example, "foo", "baz");
```

### void map_set(std::map<...> *target, T_Key ...key, T_Val value)

Sets a value in a map given a path of keys and a value.
The last argument provided will be the value.

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}}}};
// example is now: {{"foo", {{"bar", "qux"}}}};
map_set(&example, "foo", "bar", "qux");
```

### void map_del(std::map<...> *target, T_Key ...key)

Deletes a key from a map given a path of keys.

Example:

```c++
std::map<...> example = {{"foo", {{"bar", "baz"}, {"qux", "quz"}}}};
// example is now: {{"foo", {{"bar", "baz"}}}};
map_del(&example, "foo", "qux"");
```