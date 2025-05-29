# cpp_gotchas

C++ and C basics, tips, tricks, guidelines, pitfalls and gotchas

TODO:

- consteval / constinit
- STL & templates
- thread_local

# Cool stuff

[Static-allocation coroutines](https://pigweed.dev/docs/blog/05-coroutines.html)


# C++26

- [Contracts](https://en.cppreference.com/w/cpp/language/contracts.html)

# C++23

- [std::println](https://en.cppreference.com/w/cpp/io/println.html)

    throws system_error if writing to the stream fails.

- [if consteval](https://en.cppreference.com/w/cpp/language/if.html#Consteval_if)


# C++20 novelties

→ https://github.com/AnthonyCalandra/modern-cpp-features/

- [Coroutines](https://en.cppreference.com/w/cpp/language/coroutines)

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

- [std::format](https://en.cppreference.com/w/cpp/utility/format/format.html)


# C++17 novelties

- [CTAD](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction)

- [structured bindings](https://lemire.me/blog/2025/05/18/returning-several-values-from-a-function-in-c-c23-edition/)
    ```c++
    for (const auto &[key, value] : map) {...}
    ```
    Like JS destructuring, but without element skipping

- std::string_view

- [filesystem library](https://en.cppreference.com/w/cpp/filesystem.html)

- std::for_each


# Fundamentals

[C++ Best Practices](https://github.com/cpp-best-practices/cppbestpractices/)

[C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

[C++ coder roadmap](https://roadmap.sh/cpp)

- RAII
- Copy/move semantics
- Templates
- Smart pointers
- Virtual methods
- lambda expressions
- Implicit conversions
- (outdated) Compiler Macros — use consteval and constexpr
- (outdated) [SFINAE](https://en.cppreference.com/w/cpp/language/sfinae.html) — use Concepts instead

## Bjarne Stroustrup FAQ

[Bjarne Stroustrup's FAQ](https://www.stroustrup.com/bs_faq.html)

[Bjarne Stroustrup's C++ Style and Technique FAQ](https://www.stroustrup.com/bs_faq2.html)

## Stream buffers

[Cout or printf?](https://web.archive.org/web/20240223211016/http://wordaligned.org/articles/cpp-streambufs)

[istream, ostream, streambuf, fstream, sstream](https://cplusplus.com/reference/iolibrary/)

[Switching Streams](http://www.gotw.ca/gotw/048.htm)

[Input/output manipulators](https://www.cppreference.com/w/cpp/io/manip.html)
