/**
 * Cpp istreambuf_iterator + rdbuf example
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 27 May 2025
 */


#include <fstream>
#include <iostream>
#include <string>

// g++ -std=c++20 rdbuf.cpp -o readme
int main() {
    const std::string content(
        std::istreambuf_iterator<char>(
            std::ifstream("../README.md").rdbuf()
        ),
        {}
    );
    std::cout << content << std::endl;
    return 0;
}
