#include <span>
#include <vector>
#include <iostream>

void print_span(const std::span<int> s) {
    for (const int x : s) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// g++ -std=c++20 span.cpp -o /tmp/span && /tmp/span
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Create a span from the vector
    std::span span = vec;

    // Use span
    print_span(span); // 1 2 3 4 5

    // Create a span for a subset
    const std::span subspan(span.data() + 1, 3); // View of {2, 3, 4}
    print_span(subspan); // 2 3 4

    return 0;
}