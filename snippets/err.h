/**
 * snippets
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 01 Oct 2025
 */


#pragma once

#include <format>

namespace sib {
    enum class SomeError {
        Timeout     = -2,
        Generic     = -1,
        Client      = 4,
        Server      = 5,
    };
}

// Make SomeError formattable
// (make sure it is declared in the global namespace)
template<>
struct std::formatter<sib::SomeError> : std::formatter<std::string_view> {
    auto format(sib::SomeError e, std::format_context& ctx) const {
        std::string_view name = "Unknown SomeError";
        switch (e) {
            case sib::SomeError::Timeout: name = "Timeout SomeError"; break;
            case sib::SomeError::Generic: name = "Generic SomeError"; break;
            case sib::SomeError::Client:  name = "Client SomeError";  break;
            case sib::SomeError::Server:  name = "Server SomeError";  break;
        }
        return std::formatter<std::string_view>::format(name, ctx);
    }
};

// Make SomeError to implement the Printable concept
inline std::ostream& operator<<(std::ostream& out, const sib::SomeError& error)
{
    out << std::format("{}", error);
    return out;
}
