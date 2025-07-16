/**
 * strings
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 13 Jul 2025
 */


#include <algorithm>
#include <cctype>
#include <cwctype>
#include <format>
#include <iostream>
#include <locale>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


/**
 * UTF-8 string example:
 *
 * for (char& ch : hello) std::cout << std::format("{0:4d} = 0x{0:X} = '{0}'\n", ch);
 *
 * ¶ is a 2-byte character: {0xC2, 0xB6}
 * 早 and 安 are both 3-byte characters: {0xE6, 0x97, 0xA9} and {0xE5, 0xAE, 0x89}
 * 🐳 is a 4-byte character: {0xF0, 0x9F, 0x90, 0xB3}
 */
const std::string hello = "¶ Hi 早安 🐳";


[[nodiscard]] auto toLower(const std::string &str) -> std::string {
    std::string result = str; // explicit copy ref
    std::ranges::transform(
        result,
        result.begin(),
        [](const unsigned char c) { return std::tolower(c); }
    );
    return result;
}

/**
 * ASCII-only version.
 *
 * @param str input
 * @return string
 */
[[nodiscard]] auto toUpper(const std::string &str) -> std::string {
    std::string result = str; // explicit copy ref
    std::ranges::transform(
        result,
        result.begin(),
        [](const unsigned char c) { return std::toupper(c); }
    );
    return result;
}

/**
 * Wide strings version.
 *
 * Usage:
 *  std::locale::global( std::locale("en_US.UTF-8") );
 *  std::wstring str1 = L"naïve 😀";
 *  std::wcout << toUpper(str1) << L'\n';
 *
 * @param str mixed-case wide string input
 * @param loc locale (optional)
 * @return upper-case wide string
 */
[[nodiscard]] auto toUpper(const std::wstring &str, const std::locale &loc = std::locale()) -> std::wstring {
    std::wstring result = str; // explicit copy ref
    std::ranges::transform(
        result,
        result.begin(),
        [&loc](const wchar_t c) { return std::toupper(c, loc); }
    );
    return result;
}


/**
 * Split UTF-8 string into individual code points (each represented as a string, not char)
 * See also: https://en.wikipedia.org/wiki/UTF-8#Description
 *
 * @param str UTF-8 string / string_view
 * @return vector of string_views referencing each code point
 */
[[nodiscard]] auto splitIntoCodePoints(const std::string_view &str) -> std::vector<std::string_view> {
    std::vector<std::string_view> codePoints;

    size_t i = 0;
    while (i < str.size()) {
        // Cast the leading byte as char8_t (unsigned) to avoid sign issues
        const char8_t leadByte = static_cast<char8_t>(str[i]);

        // Determine sequence length from the leading byte
        // Default is plain ASCII, U+0000 to U+007F, 1-byte length
        size_t charLen = 1;

        if (leadByte >= 0xF0) { // 4-byte sequence (U+10000 to U+10FFFF), 11110*** = 0xF0
            charLen = 4;
        } else if (leadByte >= 0xE0) { // 3-byte sequence (U+0800 to U+FFFF), 1110**** = 0xE0
            charLen = 3;
        } else if (leadByte >= 0xC0) { // 2-byte sequence (U+0080 to U+07FF), 110***** = 0xC0
            charLen = 2;
        }

        // Ensure we don't exceed the string bounds
        if (i + charLen > str.size()) {
            // Probably string is malformed. Will use remaining bytes as a single codepoint
            charLen = str.size() - i;
        }

        // Add the substring view and advance the index
        codePoints.push_back(str.substr(i, charLen));
        i += charLen;
    }

    return codePoints;
}


[[nodiscard]] auto splitString(const std::string_view &str, const char delimiter) -> std::vector<std::string_view> {
    std::vector<std::string_view> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string_view::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

[[nodiscard]] auto splitString(const std::string_view &str, const std::string &delimiter = "") -> std::vector<std::string_view> {
    std::vector<std::string_view> result;

    if (delimiter.empty()) {
        return splitIntoCodePoints(str);
    }

    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}


// Decode a string-represented UTF-8 code point from string into a UTF-32 character (4-byte fixed width)
[[nodiscard]] auto decodeCodePoint(const std::string_view &codePoint) -> char32_t {
    char32_t wChr = 0;

    switch (codePoint.length()) {
        case 1:
            wChr = codePoint.at(0);
            break;
        case 2:
            // Implicit cast from binary-manipulated chars to char32_t should be fine here
            wChr = ((codePoint.at(0) & 0x1F) << 6)
                 | (codePoint.at(1) & 0x3F);
            break;
        case 3:
            wChr = ((codePoint.at(0) & 0x0F) << 12)
                 | ((codePoint.at(1) & 0x3F) << 6)
                 | (codePoint.at(2) & 0x3F);
            break;
        case 4:
            wChr = ((codePoint.at(0) & 0x07) << 18)
                 | ((codePoint.at(1) & 0x3F) << 12)
                 | ((codePoint.at(2) & 0x3F) << 6)
                 | (codePoint.at(3) & 0x3F);
            break;
        default:
            wChr = 0xFFFD; // >4 bytes, invalid code point: �
    }

    return wChr;
}

// Encode a UTF-32 character into a string-represented UTF-8 code point
// See also: https://en.wikipedia.org/wiki/UTF-8#Description
[[nodiscard]] auto encodeUTF8(const char32_t wChr) -> std::string {
    std::string result;

    if (wChr <= 0x7F) {
        // U+0000 to U+007F, 1-byte
        result = static_cast<char8_t>(wChr);
    } else if (wChr <= 0x7FF) {
        // U+0080 to U+07FF, 2-byte
        result = static_cast<char8_t>(0xC0 | ((wChr >> 6) & 0x1F));
        result += static_cast<char8_t>(0x80 | (wChr & 0x3F));
    } else if (wChr <= 0xFFFF) {
        // U+0800 to U+FFFF, 3-byte
        result = static_cast<char8_t>(0xE0 | ((wChr >> 12) & 0x0F));
        result += static_cast<char8_t>(0x80 | ((wChr >> 6) & 0x3F));
        result += static_cast<char8_t>(0x80 | (wChr & 0x3F));
    } else if (wChr <= 0x10FFFF) {
        // U+10000 to U+10FFFF, 4-byte
        result = static_cast<char8_t>(0xF0 | ((wChr >> 18) & 0x07));
        result += static_cast<char8_t>(0x80 | ((wChr >> 12) & 0x3F));
        result += static_cast<char8_t>(0x80 | ((wChr >> 6) & 0x3F));
        result += static_cast<char8_t>(0x80 | (wChr & 0x3F));
    } else {
        // Invalid code point (out of U+10FFFF range)
        // Append replacement character U+FFFD
        result = "�";
    }

    return result;
}

// Function to convert UTF-8 encoded string to uppercase
// UTF-8 sequence → code points[] → wchar_t[] → toupper → join
std::string toUpperCase(const std::string_view &str, const std::locale &loc = std::locale()) {
    std::string result;
    const auto codePoints = splitIntoCodePoints(str);

    for (const std::string_view &codePoint : codePoints) {
        // Decode to 4-byte char
        const char32_t cp = decodeCodePoint(codePoint);
        // Cast to wide char
        const wchar_t chr = static_cast<wchar_t>(cp);
        // Convert to uppercase using std::locale::toupper
        const wchar_t upperChr = std::toupper<wchar_t>(chr, loc);
        // Cast back to UTF-32 char
        const char32_t upperCp = static_cast<char32_t>(upperChr);
        // Encode to UTF-8 code point
        result += encodeUTF8(upperCp);
    }

    return result;
}


// GCC:
// g++ -std=c++23 strings.cpp -o /tmp/strings && /tmp/strings
// Clang:
// clang++ -std=c++23 -stdlib=libc++ strings.cpp -o /tmp/strings && /tmp/strings
int main() {
    std::locale::global( std::locale("en_US.UTF-8") );
    std::wcout.imbue(std::locale());

    const std::string strTestSplit = "abc::de:XXX:fghi";
    std::cout << std::format(
        "Split by chr: \"{0}\" → {1}\n",
        strTestSplit,
        splitString(strTestSplit, ':')
    );
    std::cout << std::format(
        "Split by str: \"{0}\" → {1}\n",
        strTestSplit,
        splitString(strTestSplit, ":")
    );
    std::cout.flush();

    std::cout << std::format(
        "Split by space: \"{0}\" → {1}\n",
        hello,
        splitString(hello, " ")
    );

    std::cout << std::format(
        "Split by UTF-8 sequence (早安): \"{0}\" → {1}\n",
        hello,
        splitString(hello, "早安")
    );

    std::cout << std::format(
        "Code points: \"{0}\" → {1}\n",
        hello,
        splitString(hello)
    );

    // Test cases including multi-codepoint mappings
    std::string strTestUpper1 = "hello🌍world";
    std::string strTestUpper2 = "naïve café";
    std::string strTestUpper3 = "αβγδε"; // Greek
    std::string strTestUpper4 = "привет мир"; // Cyrillic
    std::string strTestUpper5 = "MixeD_CaSe1_ÄÖÜ #üñö!"; // Mixed latin
    std::string strTestUpper6 = "Straße"; // German with ß, should be capitalized as ẞ
    std::string strTestUpper7 = "æon+早安øӕ"; // Mixed with ligatures U+00E6, U+04D5


    // Note: wide strings functions are mostly deprecated
    // See also: https://en.cppreference.com/w/cpp/locale/codecvt_utf8.html
    std::wstring strTestUpperWide = L"naïve æöñ привет🌍 αβγδε";
    std::wcout << std::format(
        L"Uppercase wide string: \"{0}\" → \"{1}\"\n",
        strTestUpperWide,
        toUpper(strTestUpperWide, std::locale("en_US.UTF-8"))
    );
    std::wcout.flush();

    /*
     * Meanwhile with Boost:
     * #include <boost/locale.hpp>
     * boost::locale::to_upper(str, "en_US.UTF-8");
     */

    std::cout << std::format("Generic string: \"{0}\" → \"{1}\"\n", strTestUpper1, toUpperCase(strTestUpper1));
    std::cout << std::format("Latin diacritics: \"{0}\" → \"{1}\"\n", strTestUpper2, toUpperCase(strTestUpper2));
    std::cout << std::format("Greek: \"{0}\" → \"{1}\"\n", strTestUpper3, toUpperCase(strTestUpper3));
    std::cout << std::format("Cyrillic: \"{0}\" → \"{1}\"\n", strTestUpper4, toUpperCase(strTestUpper4));
    std::cout << std::format("Mixed: \"{0}\" → \"{1}\"\n", strTestUpper5, toUpperCase(strTestUpper5));
    std::cout << std::format("German: \"{0}\" → \"{1}\"\n", strTestUpper6, toUpperCase(strTestUpper6));
    std::cout << std::format("Ligatures mixed: \"{0}\" → \"{1}\"\n", strTestUpper7, toUpperCase(strTestUpper7));


    std::cout.flush();
    return 0;
}
