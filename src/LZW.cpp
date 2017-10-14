#include <LZW.hpp>

#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

const TLZW::TCode TLZW::EOM = std::numeric_limits<TLZW::TCode>::max() - 1;

TLZW::TLZW(TSize bufferSize) : BufferSize{bufferSize}, Counter{0} {
    Output = std::vector<TCode>(10000);
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

void TLZW::Coding(std::istream& is, std::ostream& os) {
    std::vector<TChar> input(BufferSize + 1);

    while (is) {
        // if fileSize = C * BufferSize
        // cycle will work C + 1 times
        is.read(input.data(), input.capacity() * sizeof(TChar));

        BufferCoding(os, input, is.gcount());
    }
}

void TLZW::BufferCoding(std::ostream& os,
                        const std::vector<TChar>& buffer,
                        TSize bufferSize) {
    TString phrase = {};

    phrase += buffer[0];
    for (TSize i = 1; i < bufferSize; i++) {
        auto currentPhrase = phrase + buffer[i];
        auto iter = Dictionary.find(currentPhrase);
        if (iter != Dictionary.end()) {
            phrase = currentPhrase;
        } else {
            auto[str, code] = *Dictionary.find(phrase);
            os << code << std::endl;

            auto[iter, isInserted] =
                Dictionary.insert(std::make_pair(currentPhrase, Counter));
            Counter++;

            phrase = buffer[i];
        }
    }
}

void TLZW::Decoding(std::istream& is, std::ostream& os) {
    // TODO: need realization
}
