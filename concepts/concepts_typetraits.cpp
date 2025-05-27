#include <concepts>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <type_traits>


// Specialize templates to identify std::set and std::unordered_set
// Must be declared before the first use.
// https://en.cppreference.com/w/cpp/language/template_specialization
template<typename T>
struct isStdSet : std::false_type {};
template<typename Key, typename Compare, typename Alloc>
struct isStdSet<std::set<Key, Compare, Alloc>> : std::true_type {};

template<typename T>
struct isStdUnorderedSet : std::false_type {};
template<typename Key, typename Hash, typename KeyEqual, typename Alloc>
struct isStdUnorderedSet<std::unordered_set<Key, Hash, KeyEqual, Alloc>> : std::true_type {};

// Concept for the container type (must be defined before the operator<<)
// Kind of union type / std::variant, PrintableContainer = set || unordered_set
// C++20: use `std::remove_cvref_t` instead of `std::decay_t`
// https://www.cppreference.com/w/cpp/types/remove_cvref.html
template<typename ContainerType>
concept PrintableContainer =
    isStdSet<std::remove_cvref_t<ContainerType>>::value ||
    isStdUnorderedSet<std::remove_cvref_t<ContainerType>>::value;

// Operator << overload for a restricted number of container types
// (either set or unordered_set, defined by PrintableContainer concept).
// Should be defined BEFORE the Printable concept definition.
template<PrintableContainer T>
std::ostream& operator<<(std::ostream& out, const T& set) {
    bool isFirst = true;
    for (const auto& item : set) {
        if (!isFirst) out << ", ";
        // If item of set (T::value_type) is not Printable, a compilation error will occur.
        out << item;
        isFirst = false;
    }
    return out;
}

// Printable Concept: concept that requires a type to be printable with std::cout (i.e. streamable to std::ostream).
template<typename T>
concept Printable = requires(std::ostream& os, const T& obj) {
    // Check if obj can be streamed to std::ostream& and the result is std::ostream&
    { os << obj } -> std::same_as<std::ostream&>;
};

namespace console {
    // Log function template using the Printable concept.
    template<Printable... Args>
    void log(const Args&... objs) {
        (std::cout << ... << objs) << std::endl;
    }
}



// Custom Printable class compatible with set and unordered_set containers
class Ink {
private:
    std::string color;
public:
    explicit Ink(std::string color) : color(std::move(color)) {}

    // Add comparison operator for std::set compatibility
    bool operator<(const Ink& other) const {
        return color < other.color;
    }
    // Optional: Add equality operator for completeness
    bool operator==(const Ink& other) const {
        return color == other.color;
    }

    // Getter for accessing color (needed for hash function)
    const std::string& getColor() const {
        return color;
    }

    // Printable friend: the non-member function operator<< will have access to private members
    friend std::ostream& operator<<(std::ostream& out, const Ink& ink);

    // unordered_set compatibility: Friend declaration for hash function access to private members
    friend struct std::hash<Ink>;
};

// Overload the << operator to make Ink printable.
// Must be in the std namespace.
std::ostream& operator<<(std::ostream& out, const Ink& ink)
{
    using namespace std::literals;
    return out << "Ink { color: "s << ink.color << " }"s;
}

// Specialize std::hash for Ink to make it compatible with std::unordered_set
// Must be in the std namespace.
template<>
struct std::hash<Ink> {
    std::size_t operator()(const Ink& ink) const noexcept {
        // Use the hash of the color string
        return std::hash<std::string>{}(ink.color);
    }
};


// Usage:
int main() {
    console::log("Unordered set of strings: ", std::unordered_set<std::string>{"UP", "DOWN", "LEFT", "RIGHT"});
    console::log("Ordered set of strings:   ", std::set<std::string>{"UP", "DOWN", "LEFT", "RIGHT"});
    console::log("Unordered set of ints:    ", std::unordered_set<int>{1, 2, 3, 4, 2});
    console::log("Ordered set of ints:      ", std::set<int>{10, 30, 20, 10});
    
    const std::set<std::string> emptySet;
    console::log("Empty set: [", emptySet, "]");

    // Custom Printable
    console::log(Ink{"or range"});
    // Set of custom Printables
    const std::unordered_set<Ink> inks = {Ink{"khorne"}, Ink{"yellow"}, Ink{"magenta"}, Ink{"cyan"}};
    console::log("Set of Printable Inks: ", inks);

    // Expected failure: Try to log a set of non-Printable items:
    // struct NonPrintable {};
    // const std::set<NonPrintable> setOfNonPrintable = {NonPrintable{}, NonPrintable{}};
    // console::log("Set of NonPrintable: ", setOfNonPrintable); // This would cause a compile error

    return 0;
}
