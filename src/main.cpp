#include <LZW.hpp>

#include <iostream>

int main(int argc, char** argv) {
    TLZW lzw(100);

    if (argv[1][1] == 'c') {
        lzw.Coding(std::cin, std::cout);
    } else {
        lzw.Decoding(std::cin, std::cout);
    }
}
