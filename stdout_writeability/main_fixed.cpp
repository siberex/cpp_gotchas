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

    /*
    std::locale::global(std::locale("en_US.UTF8"));
    std::wcout.imbue(std::locale());
    std::wcout.flush();
    std::wcout << L"Hello ❤️ CPP wcout" << std::endl;
    if (std::wcout.fail()) {
        std::wcerr << L"Error writing to stdout" << std::endl;
        return 1;
    }
    */
    
    return 0;
}
