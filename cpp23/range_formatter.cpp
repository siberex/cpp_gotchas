/**
 * range_formatter
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 22 Jun 2025
 */

#include <algorithm>
#include <array>
#include <format>
#include <iostream>
#include <ranges>
#include <vector>

// g++ -std=c++23 range_formatter.cpp -o /tmp/range_formatter && /tmp/range_formatter
int main() {

    // 1, 2, 3, 4
    std::cout <<
        std::format("{:n}", std::views::iota(1, 5));
    std::cout << '\n';


    auto range = std::views::iota(1, 5);
    std::vector<int> range_vector(range.begin(), range.end());
    std::ranges::for_each(range_vector, [](int& n) { n = n * 2 + 1; });
    // 3, 5, 7, 9
    std::cout << std::format("{:n}", range_vector) << '\n';


    std::array ints{12, 10, 15, 14};
    const auto out = std::format("{:n:X}", ints);
    // C, A, F, E
    std::cout << out << '\n';


    std::vector<int> vec = {12, 10, 15, 14};
    auto hex_vec = vec | std::views::transform([](int n) { return std::format("{:X}", n); })
                        | std::ranges::to<std::vector<std::string>>();
    std::string result = hex_vec | std::views::join | std::ranges::to<std::string>();
    // CAFE
    std::cout << result << '\n';


    return 0;
}