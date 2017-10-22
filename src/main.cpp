#include <LZW.hpp>

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef DEBUG
#define __DEBUG_VALUE true
#else
#define __DEBUG_VALUE false
#endif

static constexpr bool DEBUG_ENABLED = {__DEBUG_VALUE};

enum class Error : int { BAD_ARGUMENTS = 1 };

template <typename E>
constexpr typename std::underlying_type<E>::type ToUnderlying(E e) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

using namespace std::literals::string_literals;

std::string MakeHelpRow(const std::string& command,
                        const std::string& message) {
    const auto COMMAND_LENGHT = 10;
    const auto MESSAGE_LENGHT = 69;
    const auto SPACE = ' ';

    std::vector<std::string> strings;
    std::ostringstream os;

    os << std::left << std::setw(COMMAND_LENGHT) << "  -" + command;

    if (message.size() > MESSAGE_LENGHT) {
        std::istringstream is{message};
        auto str = ""s;
        while (std::getline(is, str)) {
            strings.push_back(str);
        }

        os << std::setw(MESSAGE_LENGHT) << *strings.begin() << std::endl;
        for (auto iter = strings.begin() + 1; iter != strings.end(); iter++) {
            os << std::setw(COMMAND_LENGHT) << SPACE
               << std::setw(MESSAGE_LENGHT) << std::setw(MESSAGE_LENGHT)
               << *iter << std::endl;
        }
    } else {
        os << std::setw(MESSAGE_LENGHT) << message << std::endl;
    }

    return os.str();
}

using StringPair = std::pair<std::string, std::string>;

std::string GenerateHelp(std::vector<StringPair>& vec) {
    auto result = ""s;

    std::sort(vec.begin(), vec.end(),
              [](const StringPair& left, const StringPair& right) {
                  return left.first < right.first;
              });

    for (auto& pair : vec) {
        result += MakeHelpRow(pair.first, pair.second);
    }

    return result;
}

int main(int argc, char** argv) {
    const auto FIRST = 1;

    // help message constants
    const auto INDENT = "    "s;
    const auto badArgumentsMessage = "Bad arguments! Try -h for help."s;
    const auto helpCommand = "h"s;
    const auto decompressCommand = "d"s;
    const auto decompressMessage = "decompress"s;
    const auto useStdInCommand = ""s;
    const auto useStdInMessage = "use stdin"s;
    const auto useStdOutCommand = "c"s;
    const auto useStdOutMessage =
        "write output on standard output; keep original files unchanged."s;
    const auto listCommand = "l"s;
    const auto listMessage =
        "for each compressed file list the following field\n"s + INDENT +
        "compressed size: size of the compressed file\n"s + INDENT +
        "uncompressed size: size of the uncompressed file\n"s + INDENT +
        "ratio: compression ratio (0.0% if unknown)\n"s + INDENT +
        "uncompressed_name: name of the uncompressed file\n"s;
    const auto testCommand = "t"s;
    const auto testMessage = "check the compressed file integrity"s;
    const auto fastCommand = "1"s;
    const auto fastMessage = "fastest compression  method (less compression)"s;
    const auto bestCommand = "9"s;
    const auto bestMessage =
        "the slowest compression method (best compression)"s;
    auto helpRowVector = std::vector<StringPair>{
        std::make_pair(helpCommand, "print this message and exit"s),
        std::make_pair(useStdInCommand, useStdInMessage),
        std::make_pair(useStdOutCommand, useStdOutMessage),
        std::make_pair(listCommand, listMessage),
        std::make_pair(testCommand, testMessage),
        std::make_pair(fastCommand, fastMessage),
        std::make_pair(bestCommand, bestMessage),
        std::make_pair(decompressCommand, decompressMessage)};

    auto debugOnly = [](const std::string& s) -> auto {
        const auto DEBUG_ONLY = "(debug only)"s;
        const auto INDENT = " "s;
        return s + INDENT + DEBUG_ONLY;
    };

    // debug help message constants
    const auto bufferSizeCommand = "b"s;
    const auto bufferSizeMessage = debugOnly("set buffer size"s);

    if constexpr (DEBUG_ENABLED) {
        const auto debugHelpRowVector = std::vector<StringPair>{
            std::make_pair(bufferSizeCommand, bufferSizeMessage)};

        helpRowVector.insert(helpRowVector.end(), debugHelpRowVector.begin(),
                             debugHelpRowVector.end());
    }

    const auto helpMessage =
        "DA curse project LZW + AC archiver.\n"
        "THIS PROGRAM SHOULD NOT BE USED BY ANYONE!\n" +
        GenerateHelp(helpRowVector);

    bool useStdIn = {};
    bool useStdOut = {};
    bool decompress = {};
    TLZW::TSize bufferSize = 100000;

    if (argc == 1) {
        std::cerr << badArgumentsMessage << std::endl;
        std::exit(ToUnderlying(Error::BAD_ARGUMENTS));
    }

    for (int i = 1; i < argc; i++) {
        auto s = std::string(argv[i]).substr(FIRST);

        if (s == helpCommand) {
            std::cerr << helpMessage;
        } else if (s == useStdInCommand) {
            useStdIn = true;
        } else if (s == useStdOutCommand) {
            useStdOut = true;
        } else if (s == decompressCommand) {
            decompress = true;
        } else {
            if constexpr (DEBUG_ENABLED) {
                if (s == bufferSizeCommand) {
                    bufferSize = std::strtoull(argv[i + 1], nullptr, 10);
                    i++;
                }
            }
        }
    }

    // TODO: It's temprary code
    if (useStdIn && useStdOut) {
        TLZW lzw(bufferSize);

        if (decompress) {
            lzw.Decoding(std::cin, std::cout);
        } else {
            lzw.Coding(std::cin, std::cout);
        }
    }
}
