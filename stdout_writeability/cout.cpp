#include <iostream>

// g++ -std=c++11 cout.cpp -o cout
// ./cout > /dev/full
int main() {
    std::ostream out(std::cout.rdbuf());
    
    out << "Hello cout" << std::endl;
    if (out.fail()) {
        throw std::runtime_error("could not write to stdout");
    }
    
    return 0;
}
