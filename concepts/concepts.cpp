#include <concepts>
#include <iostream>
#include <string>
#include <variant>
#include <set>
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



// IntOrString typesafe union with std::variant
using IntOrString = std::variant<int, std::string>;

// Custom comparison operator for std::set compatibility
struct IntOrStringComparator {
    bool operator()(const IntOrString& a, const IntOrString& b) const noexcept {
        // Define a consistent ordering for different types:
        // - Integers come before strings.
        // - Within the same type, use natural ordering.

        if (a.index() == 0 && b.index() == 0) { // Both are int
            return std::get<int>(a) < std::get<int>(b);
        } else if (a.index() == 1 && b.index() == 1) { // Both are std::string
            return std::get<std::string>(a) < std::get<std::string>(b);
        } else if (a.index() == 0 && b.index() == 1) { // a is int, b is string
            return true; // int comes before string
        } else if (a.index() == 1 && b.index() == 0) { // a is string, b is int
            return false; // string comes after int
        }
        // This should not be reached:
        return false;
    }
};

// Templated hash for IntOrString (for unordered_set compatibility)
template<>
struct std::hash<IntOrString> {
    std::size_t operator()(const IntOrString& val) const noexcept {
        // Use the hash of the color string
        return (val.index() == 0)
            ? std::hash<int>{}(std::get<int>(val))
            : std::hash<std::string>{}(std::get<string>(val));
    }
};

// Make IntOrString Printable
std::ostream& operator<<(std::ostream& out, const IntOrString& val) {
    std::visit([&out]<typename IntOrString>(const IntOrString& v) {
        if constexpr (std::is_same_v<IntOrString, int>) {
            out << "i_";
        } else if constexpr (std::is_same_v<IntOrString, std::string>) {
            out << "s_";
        }
        out << v;
    }, val);
    return out;
};

// Different Printable implementation for ordered sets of type IntOrString
std::ostream& operator<<(std::ostream& out, const std::set<IntOrString, IntOrStringComparator>& set) {
    for (auto iter = set.begin(); iter != set.end(); ++iter) {
        const auto dist = std::distance(set.begin(), iter);
        out << dist << ": " << (*iter) << "; ";
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

// Overload the << operator to make Ink Printable.
// Must be in the std namespace.
std::ostream& operator<<(std::ostream& out, const Ink& ink)
{
    return out << "Ink { color: " << ink.color << " }";
}

// Usage:
int main() {
    console::log("Events: ", getUnorderedSet());
    console::log("An int: ", 123, ", a float: ", 3.1415926535897932385L, ", and a char: ", 'X');
    console::log(Ink{"orange"});

    constexpr IntOrString x = 1;
    const IntOrString y = "1";
    console::log(x, ", ", y);

    const std::set<IntOrString, IntOrStringComparator> weirdSet{x, y};
    console::log(weirdSet);

    return 0;
}
