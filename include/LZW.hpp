#ifndef DA_CP_LZW_HPP_
#define DA_CP_LZW_HPP_

#include <cstdint>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

class TLZW {
public:
    using TSize = std::size_t;
    using TCode = std::uint16_t;
    using TChar = char;
    using TString = std::basic_string<TChar>;

    friend std::istream& operator>>(std::istream& is, TLZW& lzw);
    friend std::ostream& operator<<(std::ostream& os, TLZW& lzw);

    TLZW(TSize bufferSize);

private:
    static const TCode EOM;

    void InitDictionary();

    std::istream& Coding(std::istream& is);
    void BufferCoding(std::istream& is,
                      const std::vector<TChar>& buffer,
                      TSize bufferSize);

    std::ostream& Decoding(std::ostream& os);

    TSize BufferSize;
    TCode Counter;
    std::unordered_map<TString, TCode> Dictionary;
    std::vector<TCode> Output;
};

std::istream& operator>>(std::istream& is, TLZW& lzw);
std::ostream& operator<<(std::ostream& os, TLZW& lzw);

#endif  // DA_CP_LZW_HPP_
