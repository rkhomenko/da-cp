#include <LZW.hpp>

#include <iostream>

int main(int argc, char** argv) {
    TLZW lzw(3);

    if (argv[1][1] == 'c') {
        lzw.Coding(std::cin, std::cout);
    } else {
        lzw.Decoding(std::cin, std::cout);
    }
}
