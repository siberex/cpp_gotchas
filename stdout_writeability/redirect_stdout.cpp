#include <fstream>
#include <iostream>
 
// g++ -std=c++11 redirect_stdout.cpp -o redirect_stdout
// see also https://web.archive.org/web/20240223211016/http://wordaligned.org/articles/cpp-streambufs
int main() 
{ 
    std::ofstream ofs{"stdout.log"};
    // save original cout's buffer 
    auto cout_buff = std::cout.rdbuf();
    // redirect to file
    std::cout.rdbuf(ofs.rdbuf()); 
    std::cout << "Hello redirected buffer!" << std::endl; 
 
    // cout has a longer lifetime than ofs, so we need to reset cout's buffer
    std::cout.rdbuf(cout_buff);

    // throw std::runtime_error("An error occurred");
    return 0;    
}
