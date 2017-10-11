#include <LZW.hpp>

#include <iostream>

#include <limits>
#include <stdexcept>
#include <utility>

using TChar = TLZW::TChar;
using TString = TLZW::TString;
using TCode = TLZW::TCode;

TLZW::TLZW()
    : Counter {0} {

    InitDictionary();
}

void TLZW::InitDictionary() {
    const auto STRING_LEN = 1;
    const auto MIN = std::numeric_limits<TChar>::min();
    const auto MAX = std::numeric_limits<TChar>::max();

    for (std::int16_t c = MIN; c <= MAX; c++) {
        auto [_, isInserted] = Dictionary.insert(
            std::make_pair(TString(STRING_LEN, static_cast<char>(c)), Counter)
        );

        if (!isInserted) {
            throw std::runtime_error(
                "TLZW::InitDictionary: Cannot insert to dictionary"
            );
        }

        Counter++;
    }
}
