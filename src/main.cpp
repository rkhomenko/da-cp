#include <LZW.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Bad usage!" << std::endl;
    }

    auto [decompress, index] = std::string(argv[1]) == "-d" ?
            std::make_tuple(true, 2) :
            std::make_tuple(false, 1);

    TLZW lzw(100000);

    std::ifstream input;
    std::ofstream output;

    for (int i = index; i < argc; i++) {
        auto name = std::string(argv[i]);

        input.open(name, std::ifstream::in);
        if (decompress) {
            output.open(name.substr(0, name.length() - 4) + ".orig", std::ofstream::out);
        } else {
            output.open(name + ".lzw", std::ofstream::out);
        }

        if (!input.is_open() || !output.is_open()) {
            input.close();
            output.close();
            std::cout << "bad name: " << name << std::endl;
            continue;
        }

        if (decompress) {
            lzw.Decoding(input, output);
        } else {
            lzw.Coding(input, output);
        }

        input.close();
        output.close();
    }
}
