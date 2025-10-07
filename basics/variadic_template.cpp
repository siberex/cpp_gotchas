#include <iostream>
#include <format>

template<typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void print(T value, Args... args) {
    std::cout << value << ", ";
    print(args...);
}

template<typename... Args>
void fmt(std::format_string<Args...> fmt, Args&&... args) {
    // note std::forward to preserve move semantics
    print( std::format(fmt, std::forward<Args>(args)...) );
}

// g++ -std=c++11 variadic_template.cpp -o /tmp/variadic_template && /tmp/variadic_template
int main() {
    print(1, "two", 3.14f, false);
    fmt("{:d}, {:s}, {:.2f}, {:b}", 1, "two", 3.14f, false);
    return 0;
}

