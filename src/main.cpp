#include <FNV.hpp>
#include <LZW.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    auto help =
        "\t-c\twrite output to stdout\n"
        "\t-d\tdecompress\n"
        "\t-l\tprint compress size, uncompress size, ratio, uncompressed "
        "name\n"
        "\t-t\tcheck compress file integrity\n"
        "\t-r\tcompress files in dir recursively\n"
        "\t-1\tfastes compression method\n"
        "\t-9\tbest compression\n";

    if (argc == 1) {
        std::cerr << "Bad argument count. Try -h for help." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        if (std::string(argv[1]) == "-h") {
            std::cout << help;
            std::exit(EXIT_SUCCESS);
        }

        // using default compress params
    }

    auto params = std::string(argv[1]);
    for (auto i = 1UL; i < params.size(); i++) {
        switch (params[i]) {
            case 't':
                break;
            case 'h':
                std::cout << help;
                std::exit(EXIT_SUCCESS);
            default:
                std::cerr << "Bad argument. Try -h for help." << std::endl;
                std::exit(EXIT_FAILURE);
        }
    }
}
