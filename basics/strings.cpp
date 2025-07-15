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


[[nodiscard]] auto splitStringByChar(const std::string &str, const char delimiter = ' ') -> std::vector<std::string> {
    std::vector<std::string> result;
    std::istringstream streamWrapper(str);

    std::string token;
    while (std::getline(streamWrapper, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

[[nodiscard]] auto toLower(const std::string &str) -> std::string {
    std::string result = str; // explicit copy ref
    std::ranges::transform(
        result,
        result.begin(),
        [](const unsigned char c) { return std::tolower(c); }
    );
    return result;
}

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
[[nodiscard]] auto toUpper(const std::wstring& str, const std::locale& loc = std::locale()) -> std::wstring {
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

    for (size_t i = 0; i < str.size();) {
        // Read the leading byte as unsigned to avoid sign issues
        const unsigned char leadByte = static_cast<unsigned char>(str[i]);

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


// g++ -std=c++20 strings.cpp -o /tmp/strings && /tmp/strings
int main() {
    std::locale::global( std::locale("en_US.UTF-8") );
    std::wcout.imbue(std::locale());

    const std::string strTestSplit = "abc::de:XXX:fghi";
    std::cout << std::format(
        "Split: {0} → {1}\n",
        strTestSplit,
        splitStringByChar(strTestSplit, ':')
    );

    std::wstring strTestUpperWide = L"naïve";
    std::wcout << std::format(
        L"Wide string: {0} → {1}\n",
        strTestUpperWide,
        toUpper(strTestUpperWide, std::locale("en_US.UTF-8"))
    );
    std::wcout.flush();

    std::string strTestUpper = "naïve";
    std::cout << std::format(
        "Narrow string: {0} → {1}\n",
        strTestUpper,
        toUpper(strTestUpper)
    );

    std::cout << std::format(
        "Code points: \"{0}\" → {1}\n",
        hello,
        splitIntoCodePoints(hello)
    );

    return 0;
}
