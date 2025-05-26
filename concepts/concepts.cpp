#include <concepts>
#include <iostream>
#include <string>
#include <unordered_set>

// Operator << overload for std::unordered_set<std::string>
// Should be defined BEFORE the Printable concept definition.
// Should be in the global namespace for Argument-Dependent Lookup (ADL) to find it.
std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string>& set) {
    bool isMultiple{};
    for (const auto& item : set)
        out << (isMultiple ? ", " : (isMultiple = true, "")) << item;
    return out;

}

// Define a concept that requires a type to be printable with std::cout (i.e. streamable to std::ostream).
template<typename T>
concept Printable = requires(std::ostream& os, const T& obj) {
    // Check if obj can be streamed to std::ostream& and the result is std::ostream&
    { os << obj } -> std::same_as<std::ostream&>;
};

// Log function template using the Printable concept.
// Flushes the buffer (intentionally).
template<Printable... Args>
void log(const Args&... objs) {
    // Fold expression to print all arguments
    (std::cout << ... << objs) << std::endl;
}

// Usage:
int main() {
    const auto eventsMapped = std::unordered_set<std::string>{"UP", "DOWN", "LEFT", "RIGHT"};

    log("Events: ", eventsMapped);
    log("An int: ", 123, ", a float: ", 3.14159265358979, ", and a char: ", 'X');

    return 0;
}