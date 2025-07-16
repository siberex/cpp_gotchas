# cpp_gotchas

C++ and C basics, tips, tricks, guidelines, pitfalls and gotchas

TODO:

- consteval / constinit
- thread_local

# Cool stuff

[Static-allocation coroutines](https://pigweed.dev/docs/blog/05-coroutines.html)

- Similar approach: https://github.com/jamboree/coz


# C++26 upcoming

- [Reflection](https://brevzin.github.io/c++/2025/06/26/json-reflection/)

- [Contracts](https://en.cppreference.com/w/cpp/language/contracts.html)

- [parallel range](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p3179r8.html)

# C++23

- [std::println](https://en.cppreference.com/w/cpp/io/println.html)

    throws system_error if writing to the stream fails.

- [if consteval](https://en.cppreference.com/w/cpp/language/if.html#Consteval_if)

    ```cpp
    if consteval { /* compile-time code */ } else { /* runtime code */ }
    ```

- `this` deduction for templates and explicit `this` parameter.

    Allows member functions to deduce the type of `this` (e.g. whether it’s a reference, pointer, or const).

    ```cpp
    struct X {
        // this deduction:
        template<typename Self> void f(this Self&& self);
        // Explicit this:
        void f(this S& self) { /* use self */ }
    };
    ```

- Multidimensional Subscript and `std::mdspan`

    ```cpp
    struct Matrix { int operator[](size_t i, size_t j) { return data[i * cols + j]; } };
    // std::println( m[1uz, 2uz] );
    ```

- `std::expected<T, E>`, like `Result<T, E>` in Rust.

- `z` and `uz` suffixes for `std::size_t` and `std::ssize_t`

- `std::stacktrace`: `auto trace = std::stacktrace::current();`

- `.and_then()`, `.transform()`, and `.or_else()` for `std::optional`:

    ```c++
    std::optional<int> x = 5;
    auto y = x.transform([](int v) { return v * 2; });
    // y == std::optional<int>{10}
    ```

- [range_formatter](https://en.cppreference.com/w/cpp/utility/format/range_formatter.html#Range_format_specification)

- [std::ranges::to](https://en.cppreference.com/w/cpp/ranges/to.html)

  Example: [cpp23/range_formatter.cpp](./cpp23/range_formatter.cpp)

- [std::ranges::iota](https://en.cppreference.com/w/cpp/algorithm/ranges/iota.html)

# C++20 novelties

→ https://github.com/AnthonyCalandra/modern-cpp-features/

- [Coroutines](https://en.cppreference.com/w/cpp/language/coroutines) (stackless, unlike [Boost.Coroutine](https://www.boost.org/doc/libs/latest/libs/coroutine2/doc/html/coroutine2/intro.html))

    Examples: https://github.com/dian-lun-lin/cpp_coroutine_examples

    Boost.Cobalt provides [experimental context](https://www.boost.org/doc/libs/latest/libs/cobalt/doc/html/index.html#context) to make C++20 coroutines stackfull.

- [Concepts](https://en.cppreference.com/w/cpp/language/constraints)
    - [intro](https://quantdev.blog/posts/c++20-concepts/)
    - [standard concepts library](https://en.cppreference.com/w/cpp/concepts.html)

- [Modules](https://en.cppreference.com/w/cpp/language/modules)

- [constinit & consteval](https://www.cppstories.com/2022/const-options-cpp20/)

    - constinit: comptime init, can be redeclared

    - consteval: strict comptime constexpr, forces all calls to happen at compile time

- [Ranges and pipes](https://en.cppreference.com/w/cpp/ranges.html)

    ```с++
    auto const ints = {0, 1, 2, 3, 4, 5};
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };
    for (int i : ints | std::views::filter(even) | std::views::transform(square))
        std::cout << i << ' ';  
    ```

- [std::accumulate](https://en.cppreference.com/w/cpp/algorithm/accumulate.html)

    ```c++     
    std::vector<int> v{1, 2, 3, 4};
    int sum = std::accumulate(v.begin(), v.end(), 0);
    ```

- [std::format](https://en.cppreference.com/w/cpp/utility/format/format.html) | [cheatsheet](https://github.com/paulkazusek/std_format_cheatsheet)

- [std::span](./cpp20/span.cpp) — non-owning type, fat pointer (pointer with type size), kinda string_view for vectors.

    Note: you must ensure the underlying data outlives the span.

- Template [Requirements](https://en.cppreference.com/w/cpp/language/requires.html)

    ```c++
    template <int percent>
    requires (percent >= 0 && percent <= 100)
    struct RainChance{};
    ```

- `<=>` spaceship operator

- [std::ranges::views::iota](https://en.cppreference.com/w/cpp/ranges/iota_view.html)

- [math constants](https://en.cppreference.com/w/cpp/numeric/constants.html): `std::numbers::pi` etc.

# C++17 novelties

- [CTAD](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction)

- [structured bindings](https://lemire.me/blog/2025/05/18/returning-several-values-from-a-function-in-c-c23-edition/)

    ```c++
    for (const auto &[key, value] : map) {...}
    ```

    Like JS destructuring, but without element skipping.

    See also: [std::tie](https://en.cppreference.com/w/cpp/utility/tuple/tie)

- [std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view.html)

- [filesystem library](https://en.cppreference.com/w/cpp/filesystem.html)

- std::for_each

- [Execution policy](https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag.html)

    ```c++
    std::sort(std::execution::par, v.begin(), v.end());
    std::for_each(std::execution::par_unseq, v.begin(), v.end(), f);
    ```

- Guaranteed copy elision, aka mandatory RVO (return value optimization)

# Fundamentals

[C++ Best Practices](https://github.com/cpp-best-practices/cppbestpractices/)

[C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

[C++ coder roadmap](https://roadmap.sh/cpp)

- RAII
- [lvalue, rvalue](https://en.cppreference.com/w/cpp/language/value_category.html)
- Copy and move semantics
    - [Copy elision](https://en.cppreference.com/w/cpp/language/copy_elision.html)
- [Templates](https://learn.microsoft.com/en-us/cpp/cpp/templates-cpp?view=msvc-170) | [wiki](https://en.wikipedia.org/wiki/Template_(C%2B%2B)) | [cppreference](https://en.cppreference.com/w/cpp/language/templates.html)
- [STL](./basics/STL.md)
- constexpr
- Smart pointers
- [Virtual methods](https://learn.microsoft.com/en-us/cpp/cpp/virtual-functions) | [wiki](https://en.wikipedia.org/wiki/Virtual_function#C++)
- [Variadic templates](https://en.wikipedia.org/wiki/Variadic_template) | [example1](./basics/variadic_template.cpp) | [example2](https://github.com/siberex/cpp_gotchas/blob/332813508e491f5f0c7d9a8fac0f9a69e01ca4e2/concepts/concepts.cpp#L96)
  ```c++
  template<typename... Args>
  void func(Args... args) {}
  ```
- lambda expressions
- Implicit conversions
- SIOF, Static Initialisation Order Fiasco
- (outdated) [CRTP, Curiously Recurring Template Pattern](https://en.cppreference.com/w/cpp/language/crtp.html) — use [this deduction](https://en.cppreference.com/w/cpp/language/member_functions.html#Explicit_object_member_functions) when possible
- (outdated) Preprocessor Macros — use consteval and constexpr when possible
- (outdated) [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae.html) — use Concepts instead

## Syntax quirks

[Trailing return type](https://en.wikipedia.org/wiki/Trailing_return_type)

## Preprocessor tricks

[X macro](https://en.wikipedia.org/wiki/X_macro)

[Variadic macro](https://en.wikipedia.org/wiki/Variadic_macro_in_the_C_preprocessor)

# Links

https://hackingcpp.com/

https://caiorss.github.io/C-Cpp-Notes/

## Bjarne Stroustrup FAQ

[Bjarne Stroustrup's FAQ](https://www.stroustrup.com/bs_faq.html)

[Bjarne Stroustrup's C++ Style and Technique FAQ](https://www.stroustrup.com/bs_faq2.html)

## Stream buffers

[Cout or printf?](https://web.archive.org/web/20240223211016/http://wordaligned.org/articles/cpp-streambufs)

[istream, ostream, streambuf, fstream, sstream](https://cplusplus.com/reference/iolibrary/)

[Switching Streams](http://www.gotw.ca/gotw/048.htm)

[Input/output manipulators](https://www.cppreference.com/w/cpp/io/manip.html)
