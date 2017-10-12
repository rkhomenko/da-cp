#include <LZW.hpp>

#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

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

std::istream& TLZW::Coding(std::istream& is) {
    std::vector<TChar> input(BufferSize);

    while (is) {
        // if fileSize = C * BufferSize
        // cycle will work C + 1 times
        is.read(input.data(), input.capacity() * sizeof(TChar));
        BufferCoding(input, is.gcount());
    }
    return is;
}

void TLZW::BufferCoding(const std::vector<TChar>& buffer, TSize bufferSize) {}

std::ostream& TLZW::Decoding(std::ostream& os) {
    // TODO: need realization
    return os;
}

std::istream& operator>>(std::istream& is, TLZW& lzw) {
    return lzw.Coding(is);
}

std::ostream& operator<<(std::ostream& os, TLZW& lzw) {
    return lzw.Decoding(os);
}
