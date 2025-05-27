#include <concepts>
#include <iostream>
#include <string>
#include <unordered_set>

// Operator << overload for std::unordered_set<std::string>
// Should be defined BEFORE the Printable concept definition.
// Should be in the global namespace for Argument-Dependent Lookup (ADL) to find it.
std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string>& set) {
    bool isFirst = true;
    for (const auto& item : set) {
        if (!isFirst) out << ", ";
        // std::string item is Printable, no need to convert it
        out << item;
        isFirst = false;
    }
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
namespace console {
    template<Printable... Args>
    void log(const Args&... objs) {
        // Fold expression to print all arguments
        (std::cout << ... << objs) << std::endl;
    }
}

// Dynamically generate sample set
std::unordered_set<std::string> getUnorderedSet() {
    std::unordered_set<std::string> set = {"UP"};
    set.insert({"DOWN", "LEFT"});
    set.insert("RIGHT");
    return set;
}

// Dummy Printable class
class Ink {
private:
    std::string color;
public:
    explicit Ink(std::string color) : color(std::move(color)) {}
    // Printable friend: the non-member function operator<< will have access to private members
    friend std::ostream& operator<<(std::ostream& out, const Ink& ink);
};

// Overload the << operator to make Ink printable.
// Must be in the std namespace.
std::ostream& operator<<(std::ostream& out, const Ink& ink)
{
    using namespace std::literals;
    return out << "Ink { color: "s << ink.color << " }"s;
}

// Usage:
int main() {
    console::log("Events: ", getUnorderedSet());
    console::log("An int: ", 123, ", a float: ", 3.1415926535897932385L, ", and a char: ", 'X');
    console::log(Ink{"orange"});
    return 0;
}
