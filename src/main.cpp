#include <LZW.hpp>

#include <iostream>

int main(int argc, char** argv) {
    TLZW lzw(100);

    lzw.Coding(std::cin, std::cout);

    std::cout << "Go away! It doesn't work!" << std::endl;
}
