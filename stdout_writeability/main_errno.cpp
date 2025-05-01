#include <iostream>
#include <system_error>
#include <cerrno> // For errno

int main() {
    std::cout << "Hello CPP" << std::endl;
    if (std::cout.fail()) {
        std::error_code ec(errno, std::system_category());
        std::cerr << "Error writing to standard output: " << ec.message()
                  << " (Error code: " << ec.value() << ")" << std::endl;
        return 1;
    }
    return 0;
}
