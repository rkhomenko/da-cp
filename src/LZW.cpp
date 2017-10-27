#include <LZW.hpp>

#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

const TLZW::TCode TLZW::EOB = std::numeric_limits<TLZW::TCode>::max() - 1;

TLZW::TLZW(TSize bufferSize) : BufferSize{bufferSize}, Counter{0} {
    InitDictionary();
}

void TLZW::InitDictionary() {
    using TUpperType = std::int16_t;
    const auto STRING_LEN = 1;
    const auto MIN = std::numeric_limits<TChar>::min();
    const auto MAX = std::numeric_limits<TChar>::max();

    for (TUpperType c = MIN; c <= MAX; c++) {
        auto str = TString(STRING_LEN, static_cast<char>(c));

        StrToCodeDict.insert(std::make_pair(str, Counter));
        CodeToStrDict.insert(std::make_pair(Counter, str));

        Counter++;
    }
}

void TLZW::Coding(std::istream& is, std::ostream& os) {
    std::vector<TChar> input(BufferSize);

    while (is) {
        is.read(input.data(), input.capacity());
        if (is.gcount()) {
            BufferCoding(os, input, is.gcount());
        }
    }
}

void TLZW::BufferCoding(std::ostream& os,
                        const std::vector<TChar>& buffer,
                        TSize bufferSize) {
    auto counter = Counter;
    auto dictionary = StrToCodeDict;
    TString phrase = {};

    auto translate = [&dictionary](TString phrase) -> auto {
        return dictionary.find(phrase);
    };

    auto write = [&os](TCode code) {
        os.write(reinterpret_cast<const char*>(&code), sizeof(TCode));
    };

    phrase += buffer[0];
    for (TSize i = 1; i < bufferSize; i++) {
        auto currentPhrase = phrase + buffer[i];
        auto iter = translate(currentPhrase);
        if (iter != dictionary.end()) {
            phrase = currentPhrase;
        } else {
            auto[str, code] = *translate(phrase);
            write(code);

            dictionary.insert(std::make_pair(currentPhrase, counter));
            counter++;
            phrase = buffer[i];
        }
    }
    auto[str, code] = *translate(phrase);
    write(code);
    write(EOB);
}

void TLZW::Decoding(std::istream& is, std::ostream& os) {
    std::vector<TCode> output(BufferSize);
    TSize index = {};
    TCode code = {};

    while (is.read(reinterpret_cast<char*>(&code), sizeof(TCode))) {
        if (code == EOB) {
            BufferDecoding(os, output, index);
            index = 0;
        } else {
            output[index] = code;
            index++;
        }
    }
}

void TLZW::BufferDecoding(std::ostream& os,
                          const std::vector<TCode> buffer,
                          TSize bufferSize) {
    auto counter = Counter;
    auto dictionary = CodeToStrDict;
    TString phrase = {};
    TChar c = {};
    TCode code = buffer[0];

    auto translate = [&dictionary](TCode code) -> auto {
        return (*dictionary.find(code)).second;
    };

    os << translate(code);
    c = translate(code)[0];

    for (TSize i = 1; i < bufferSize; i++) {
        auto currentCode = buffer[i];
        auto iter = dictionary.find(currentCode);

        if (iter != dictionary.end()) {
            phrase = translate(currentCode);
        } else {
            phrase = translate(code);
            phrase += c;
        }

        os << phrase;

        c = phrase[0];

        auto str = translate(code) + c;
        dictionary.insert(make_pair(counter, str));
        counter++;

        code = currentCode;
    }
}
