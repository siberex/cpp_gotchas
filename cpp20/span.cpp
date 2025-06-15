#include <span>
#include <vector>
#include <iostream>

void print_span(std::span<int> s) {
    for (int x : s) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

// g++ -std=c++20 span.cpp -o /tmp/span && /tmp/span
int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // Create a span from the vector
    std::span<int> span = vec;

    // Use span
    print_span(span); // 1 2 3 4 5

    // Create a span for a subset
    std::span<int> subspan(span.data() + 1, 3); // View of {2, 3, 4}
    print_span(subspan); // 2 3 4

    return 0;
}