## C++20 Concepts

Basic Concepts and order definition importance.

Concepts with Type traits example.

```bash
g++ -std=c++20 concepts.cpp -o concepts
g++ -std=c++20 concepts_typetraits.cpp -o concepts_traits
```


## Basic example

```c++
#include <concepts>
#include <iostream>

auto func(std::floating_point auto f) { return f * 2; }
auto func(std::integral auto i) { return i + 2; }

int main() {
    std::cout << func(1.0) << std::endl;    // 2
    std::cout << func(1) << std::endl;      // 3
    return 0;
}
```
