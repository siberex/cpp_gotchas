/**
 * snippets
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 07 Oct 2025
 */

#include <optional>
#include <string>

class Dummy {
public:
    Dummy() {
        puts("+ constructor");
    }

    // Copy
    Dummy(const Dummy& lv) {
        puts("copy from lvalue");
    }
    Dummy& operator=(const Dummy& lv) {
        puts("copy assignment");
        return *this;
    }

    // Move
    Dummy(Dummy&& rv) noexcept {
        puts("move from rvalue");
    }
    Dummy& operator=(Dummy&& rv) noexcept {
        puts("move assignment");
        return *this;
    }

    ~Dummy() {
        puts("× destructor");
    }

    static void dummyFN(const Dummy& lv) {
        // _v = lv;
    }
    static void dummyFN(Dummy&& rv) {
        // _v = std::move(rv);
    }

};

inline Dummy getInstance() {
    return Dummy{};
}

inline std::optional<Dummy> getOptionalInstance() {
    // Dummy d;     // Constructor
    // Implicit move on return:
    // return d;    // move from rvalue (to optional<Dummy>, which is a value type)
    // Which is the same as:
    // return std::optional<Dummy>{std::move(d)};
    // Meaning there will be an extra destructor call for d
    // Note this will not help:
    // return std::optional<Dummy>(std::in_place, std::move(d));
    // return std::optional<Dummy>(std::in_place_t{}, std::move(d));

    // Correct approach:
    // return std::optional<Dummy>(std::in_place);
    // return std::optional<Dummy>(std::in_place, arg1, arg2, ...);
    return std::optional<Dummy>(std::in_place_t{});
}


int main() {

    // Dummy d1; // constructor
    // d1 = getInstance(); // constructor + move assignment

    // Dummy d2 = getInstance(); // RVO with copy elision

    auto d3 = getOptionalInstance();

    return 0;
}