#include <iostream>

template<typename T>
void print(T value) {
    std::cout << value << std::endl;
}

template<typename T, typename... Args>
void print(T value, Args... args) {
    std::cout << value << ", ";
    print(args...);
}

// g++ -std=c++11 variadic_template.cpp -o /tmp/variadic_template && /tmp/variadic_template
int main() {
    print(1, "two", 3.14f, false);
    return 0;
}
