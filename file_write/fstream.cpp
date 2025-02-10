#include <fstream>
#include <iostream>

int main() {
    std::ofstream outFile;
    outFile.open("output.txt", std::ios::out);

    if (!outFile.is_open()) {
        // std::cerr << "Error: File could not be opened." << std::endl;
        throw std::runtime_error("file is not writeable");
    }

    outFile << "Hello fstream" << std::endl;
    if (outFile.fail()) {
        // std::cerr << "Error during write operation." << std::endl;
        throw std::runtime_error("could not write to file");
    }
    outFile.close();

    return 0;
}
