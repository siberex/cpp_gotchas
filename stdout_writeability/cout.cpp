#include <iostream>

int main() {
    std::ostream out(std::cout.rdbuf());

    // Does not work either:
    // g++ -std=c++11 cout.cpp -o cout
    // ./cout > /dev/full
    if (out.fail()) {
        throw std::runtime_error("could not write to stdout");
    }
    std::cout << "Hello cout" << std::endl;

    return 0;
}
