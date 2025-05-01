#include <iostream>
// #include <cstdio>
// #include <cerrno>

int main() {
    std::cout << "Hello CPP" << std::endl;
    if (std::cout.fail()) {
        
        std::cerr << "Error writing to stdout" << std::endl;
        return 1;
    }

    /*
    fflush(stdout);
    int result = fprintf(stdout, "Hello cstdio!\n");
    if (result < 0) {
        perror("Error writing to stdout");
        if (result == ENOSPC) {...}
        return 1;
    }
    */
    
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
