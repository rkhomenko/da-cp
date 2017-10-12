#include <LZW.hpp>

#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

using TChar = TLZW::TChar;
using TString = TLZW::TString;
using TCode = TLZW::TCode;

TLZW::TLZW(TSize bufferSize) : BufferSize{bufferSize}, Counter{0} {
    InitDictionary();
}

void TLZW::InitDictionary() {
    using TUpperType = std::int16_t;
    const auto STRING_LEN = 1;
    const auto MIN = std::numeric_limits<TChar>::min();
    const auto MAX = std::numeric_limits<TChar>::max();

    for (TUpperType c = MIN; c <= MAX; c++) {
        auto[_, isInserted] = Dictionary.insert(
            std::make_pair(TString(STRING_LEN, static_cast<char>(c)), Counter));

        if (!isInserted) {
            throw std::runtime_error(
                "TLZW::InitDictionary: Cannot insert to dictionary");
        }

        Counter++;
    }
}

std::istream& operator>>(TLZW& lzw, std::istream& is) {
    return lzw.Coding(is);
}

std::ostream& operator<<(TLZW& lzw, std::ostream& os) {
    return lzw.Decoding(os);
    s
}
