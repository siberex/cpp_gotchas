/**
 * snippets
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 30 Sep 2025
 */


#pragma once

#include <concepts>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <format>


// Make std::unordered_set printable
// Should be defined BEFORE the Printable concept definition.
// Should be in the global namespace for Argument-Dependent Lookup (ADL) to find it.
inline std::ostream& operator<<(std::ostream& out, const std::unordered_set<std::string> & set)
{
    bool isMultiple{};
    for (const auto& item : set)
        out << (isMultiple ? ", " : (isMultiple = true, "")) << item;
    return out;
}

namespace sib {

    // Define a concept that requires a type to be printable with std::cout (i.e., streamable to std::ostream)
    template<typename T>
    concept Printable = requires(std::ostream& os, const T& obj) {
        // Check if the result is std::ostream&
        { os << obj } -> std::same_as<std::ostream&>;
    };

    // Log function template using the Printable concept
    // Flushes the buffer (intentionally)
    template<Printable... T>
    void log(const T&... objs) {
        (std::cout << ... << objs) << std::endl;
    }

    template<Printable... T>
    void err(const T&... objs) {
        (std::cerr << ... << objs) << std::endl;
    }

    template<typename... Args>
    void fmt(std::format_string<Args...> fmt, Args&&... args) {
        log( std::format(fmt, std::forward<Args>(args)...) );
    }

    template<typename... Args>
    void fmtErr(std::format_string<Args...> fmt, Args&&... args) {
        err( std::format(fmt, std::forward<Args>(args)...) );
    }

} // namespace sib