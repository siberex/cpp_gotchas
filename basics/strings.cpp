/**
 * strings
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 13 Jul 2025
 */


#include <algorithm>
#include <cctype>
#include <cwctype>
#include <iostream>
#include <locale>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>


/**
 * UTF-8 string example:
 *
 * for (char& ch : hello) std::cout << std::format("{0:4d} = {0:#04x} = '{0}'\n", ch);
 *
 * ¶ is a 2-byte character: {0xC2, 0xB6}
 * 早 and 安 are both 3-byte characters: {0xE6, 0x97, 0xA9} and {0xE5, 0xAE, 0x89}
 * 🐳 is a 4-byte character: {0xF0, 0x9F, 0x90, 0xB3}
 */
constexpr std::string hello = "¶ Hi 早安 🐳";


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




// g++ -std=c++20 strings.cpp -o /tmp/strings && /tmp/strings
int main() {
    // std::locale::global( std::locale("en_US.UTF-8") );

    const std::string strTestSplit = "abc::de:XXX:fghi";
    for (const auto& token: splitStringByChar(strTestSplit, ':')) {
        std::cout << token << "\n";
    }

    //std::wstring strTestUpper = L"naïve";
    //std::cout << std::format("narrow string: {} → {}\n", strTestUpper, toUpper(strTestUpper));


    return 0;
}
