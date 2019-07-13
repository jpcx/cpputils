# cpputils 0.5.0

Provides a collection of general-purpose headers that facilitate fast C++ prototyping and development.

## 0.5.0 Notes

__MIGRATION NOTICE:__ Removed ccutl::TestGroup

- Some testing has been completed. Need to write tests for new functionality.
- New functions need documentation.
  - For now, the function names, template type names, and parameter names will serve as documentation.

## Functionality

### Algorithm

```cpp
// Calls std::transform with the respective input / output iterators
auto transform_it<bool BackInsert = false>(const TInputContainer &input, TOutputContainer *output,
                  const TUnaryOp &f);
auto transform_it<bool BackInsert = false>(const TExecutionPolicy &&policy, const TInputContainer &input,
                  TOutputContainer *output, const TUnaryOp &f);
auto transform_it<bool BackInsert = false>(const TInputContainer1 &input1,
                  const TInputContainer2 &input2, TOutputContainer *output,
                  const TBinaryOp &f);
auto transform_it<bool BackInsert = false>(const TExecutionPolicy &&policy,
                  const TInputContainer1 &input1,
                  const TInputContainer2 &input2, TOutputContainer *output,
                  const TUnaryOp &f);

// Calls std::for_each with the respective input const iterator
TUnaryOp for_each_it(const TInputContainer &input, const TUnaryOp &f);
void for_each_it(const TExecutionPolicy &&policy, const TInputContainer &input,
                 const TUnaryOp &f);

// Iterates a container using a const iterator
// Functionality changes depending on the lambda parameter signature
// ----
// TUnaryOp may be have one of the following parameter schemes:
//   f(it)
//   f(it, next_it)
//   f(it, next_it, end_it)
// TUnaryOp may return the desired next iteration iterator
void iterate_it<bool Reverse = false>(const TInputContainer &input, const TUnaryOp &f);
// TBinaryOp may be have one of the following parameter schemes:
//   f(it1, it2)
//   f(it1, it2, next_it1)
//   f(it1, it2, next_it1, next_it2)
//   f(it1, it2, next_it1, next_it2, end_it1)
//   f(it1, it2, next_it1, next_it2, end_it1, end_it2)
// TBinaryOp may return the desired next it1 iterator
void iterate_it<bool Reverse = false>(const TInputContainer1 &input1, const TInputContainer2 &input2,
                const TBinaryOp &f);

// Concatenates two or more containers. Converts to string if TContain is std::string.
TContain concat(const TVal &value, const TRest... rest);

// Joins two or more string-convertible containers to a string using an optional delimiter.
std::string join(const TContain<TVal> &target, const TDelim &delimiter = "");

// Returns all possible combinations of a container T as a vector<T>.
std::vector<T> combinate(const T &target, size_t sample_sz);

// Returns all possible permutations of a container T as a vector<T>. Optionally allows repetition.
std::vector<T> permutate(const T &target, size_t sample_sz = 0,
                         bool repetition = false);
```

### Compare

```cpp
// Returns true only if two values are equal. If Strict is false, types may be decay equal (cv, etc.).
bool are_equal<bool Strict = false>(const TA &a, const TB &b,
               std::optional<size_t> n_max_size_cmp = std::nullopt);

// Compares two template numbers. Handles signed/unsigned comparison.
template <typename TA, typename TB, TA Lhs, TB Rhs,
          std::enable_if_t<are_arithmetic_v<TA, TB>> * = nullptr>
constexpr signed char constexpr_ncmp = ... A > B ? 1 : A < B ? -1 : 0

// Compares two template. Handles signed/unsigned comparison.
signed char ncmp(TA lhs, TB rhs);

// Compares two values for equivalency-- 3 == '3', etc.
bool are_equivalent(const TA &a, const TB &b,
                    std::optional<size_t> n_max_size_cmp = std::nullopt);
```

### Convert

```cpp
// Converts a value to a string using std::ostringstream (or faster method, if possible).
std::string to_string(
    const T value,
    const std::optional<std::streamsize> &precision = std::nullopt);

// Converts a string to a value using std::istringstream (or faster method, if possible).
T from_string(const std::string &value,
              const std::optional<std::streamsize> &precision = std::nullopt);
```

### Format

```cpp
// Trims whitespace on the ends of a string-like value.
std::string trim_space(const T& text);

// Repeats a string n times
std::string string_repeat(TNum n_repeat, const TStr& input = " ");

```

### IO

```cpp
// Logs a float to cout using an optional precision (stores/resets cout default)
void log<bool InsertEndLine = true>(T value,
         const std::optional<std::streamsize>& precision = std::nullopt);

// Logs a value to cout
void log<bool InsertEndLine = true>(const T& value = "");

// Logs an iterable container to cout using a delimiter
void log<bool InsertEndLine = true>(const TContain<T>& value, const TDelim& delimiter = " ");

// Logs a 2D iterable container to cout using a delimiter
void log<bool InsertEndLine = true>(const TRows<TColumns<T>>& value, const TRowDelim& row_delimiter = "",
         const TColDelim& col_delimiter = " ");
```

### Limits

```cpp
// Shorthand for numeric_limits
constexpr T max_v = std::numeric_limits<T>::max();

// Shorthand for numeric_limits
constexpr T min_v = std::numeric_limits<T>::lowest();

// Checks if a given value can fit within a specified type
constexpr bool is_val_overflow<TLim>(TTest value);

// Checks if two numbers will overflow if added (without actually adding them). Handles signed/unsigned.
bool is_add_overflow(TA a, TB b);

// Checks if two numbers will overflow if added (without actually subtracting them). Handles signed/unsigned.
bool is_sub_overflow(TA a, TB b);
```

### Macros

```cpp
// Logs an expression to cout:
//   CCUTL_LOG(3 + 4) --- 3 + 4: 7
//   CCUTL_LOG(3 + 4, "descr") --- 3 + 4 [descr]: 7
CCUTL_LOG();            // logs a new line
CCUTL_LOG(expr);        // logs the string representation of an expression and its result
CCUTL_LOG(expr, descr); // logs the string representation of an expression and its result, with a description
```

### Maps

```cpp
// Returns true if an N-D map has a given key path and value.
bool map_has(const std::map<T_Key, T_Val> &target, const T_Key &key,
             const T_Rest... rest);

// Gets a value from an N-D map
auto map_get(const std::map<T_Key, T_Val> &target, const T_Key &key,
             const T_Rest... rest);

// Sets a value to an N-D map
void map_set(std::map<T_Key, T_Val> *target, const T_Key &key,
             const T_Rest... rest);

// Delets a value from an N-D map
void map_del(std::map<T_Key, T_Val> *target, const T_Key &key,
             const T_Rest... rest);

// Creates an N-D map
auto map_create(const T_Key &key, const T_Rest... rest);
```

### Math

```cpp
// Throws "EOverflow" if unsafe; returns addition result. Handles signed/unsigned.
TResult safe_add(TA a, TB b);

// Adds to a; throws "EOverflow" if unsafe. Handles signed/unsigned.
void safe_add(TOutput* a, TAddend b);
```

### Type Traits

```cpp

/*                             ccutl::are_true_v */
// True if all passed conditions are true
template <typename... Ts>
constexpr bool are_true_v = core::are_true<Ts...>::value;

/*                           ccutl::are_iterable_v                           */
// True if values have .begin()
template <typename... Ts>
constexpr bool are_iterable_v =
    are_true_v<std::integral_constant<bool, core::is_iterable<Ts>::value>...>;

/*                       ccutl::are_reverse_iterable_v                       */
// True if values have .rbegin()
template <typename... Ts>
constexpr bool are_reverse_iterable_v = are_true_v<
    std::integral_constant<bool, core::is_reverse_iterable<Ts>::value>...>;

/*                        ccutl::are_const_iterable_v                        */
// True if values have .cbegin()
template <typename... Ts>
constexpr bool are_const_iterable_v = are_true_v<
    std::integral_constant<bool, core::is_const_iterable<Ts>::value>...>;

/*                    ccutl::are_const_reverse_iterable_v                    */
// True if values have .crbegin()
template <typename... Ts>
constexpr bool are_const_reverse_iterable_v = are_true_v<std::integral_constant<
    bool, core::is_const_reverse_iterable<Ts>::value>...>;

/*                         ccutl::are_streamable_to_v                        */
// True if values may be streamed to TStream
template <typename TStream, typename... Ts>
constexpr bool are_streamable_to_v = are_true_v<
    std::integral_constant<bool, core::is_streamable_to<TStream, Ts>::value>...>;

/*                          ccutl::are_arithmetic_v                          */
// True if types are arithmetic
template <typename... Ts>
constexpr bool are_arithmetic_v =
    are_true_v<std::integral_constant<bool, std::is_arithmetic_v<Ts>>...>;

/*                           ccutl::are_integral_v                           */
// True if types are integral
template <typename... Ts>
constexpr bool are_integral_v =
    are_true_v<std::integral_constant<bool, std::is_integral_v<Ts>>...>;

/*                        ccutl::are_floating_point_v                        */
// True if types are floats
template <typename... Ts>
constexpr bool are_floating_point_v =
    are_true_v<std::integral_constant<bool, std::is_floating_point_v<Ts>>...>;

/*                           ccutl::are_unsigned_v                           */
// True if types are unsigned
template <typename... Ts>
constexpr bool are_unsigned_v =
    are_true_v<std::integral_constant<bool, std::is_unsigned_v<Ts>>...>;

/*                            ccutl::are_signed_v                            */
// True if types are signed
template <typename... Ts>
constexpr bool are_signed_v =
    are_true_v<std::integral_constant<bool, std::is_signed_v<Ts>>...>;

/*                            ccutl::are_pointer_v                            */
// True if types are pointers
template <typename... Ts>
constexpr bool are_pointer_v =
    are_true_v<std::integral_constant<bool, std::is_pointer_v<Ts>>...>;

/*                             ccutl::are_const_v                             */
// True if types are const
template <typename... Ts>
constexpr bool are_const_v =
    are_true_v<std::integral_constant<bool, std::is_const_v<Ts>>...>;

/*                           ccutl::are_volatile_v                           */
// True if types are volatile
template <typename... Ts>
constexpr bool are_volatile_v =
    are_true_v<std::integral_constant<bool, std::is_volatile_v<Ts>>...>;

/*                              ccutl::are_cv_v                              */
// True if types are const or volatile
template <typename... Ts>
constexpr bool are_cv_v =
    are_true_v<std::integral_constant<bool, std::is_const_v<Ts> ||
                                                std::is_volatile_v<Ts>>...>;

/*                           ccutl::are_function_v                           */
// True if values are functions (not functors)
template <typename... Ts>
constexpr bool are_function_v =
    are_true_v<std::integral_constant<bool, std::is_function_v<Ts>>...>;

/*                             ccutl::are_array_v                             */
// True if values are arrays
template <typename... Ts>
constexpr bool are_array_v =
    are_true_v<std::integral_constant<bool, std::is_array_v<Ts>>...>;

/*                          ccutl::remove_function_t                          */
// Removes a function signature from a type -- int(int) -> int
template <typename T>
using remove_function_t = typename core::remove_function<T>::type;

/*                         ccutl::remove_everything_t                         */
// Removes ALL qualifiers on a given type -- const volatile int(&&)[17] -> int
template <typename T>
using remove_everything_t = typename core::remove_everything<T>::type;

/*                            ccutl::decay_deep_t                            */
// Same as remove_everything_t but converts extents to pointers and leaves
// function signatures
template <typename T>
using decay_deep_t = typename core::decay_deep<T>::type;

/*                             ccutl::are_same_v                             */
// Checks if types are the same
template <typename T, typename... Ts>
constexpr bool are_same_v =
    are_true_v<std::integral_constant<bool, std::is_same_v<T, Ts>>...>;

/*                          ccutl::are_decay_same_v                          */
// Checks if types are similar (const int vs int)
template <typename T, typename... Ts>
constexpr bool are_decay_same_v = are_true_v<std::integral_constant<
    bool, std::is_same_v<decay_deep_t<T>, decay_deep_t<Ts>>>...>;

/*                       ccutl::function_return_type_t                       */
// Gets the return type of a function
template <typename Tf, std::enable_if_t<are_function_v<Tf>>* = nullptr>
using function_return_type_t = typename core::function_return_type<Tf>::type;

/*                        ccutl::functor_return_type_t                        */
// Gets the return type of a functor
template <typename Tf, typename... TArgs>
using functor_return_type_t =
    decltype((std::declval<Tf>())(std::declval<TArgs>()...));

/*                         ccutl::n_function_params_v                         */
// Number of parameters in a function signature
template <typename T, std::enable_if_t<are_function_v<T>>* = nullptr>
constexpr size_t n_function_params_v = core::n_function_params<T>::value;

```

## Testing

Testing using gtest. Please run `make test` in order to test the package.

## Contributing

Contributing is welcome! Please make a pull request.

## License

Copyright © Justin Collier  License GPLv3+: GNU GPL version 3 or later
<<https://gnu.org/licenses/gpl.html>>.

This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
