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

    TLZW(TSize bufferSize);

    void Coding(std::istream& is, std::ostream& os);
    void Decoding(std::istream& is, std::ostream& os);

private:
    static const TCode EOM;

    void InitDictionary();

    void BufferCoding(std::ostream& os,
                      const std::vector<TChar>& buffer,
                      TSize bufferSize);

    TSize BufferSize;
    TCode Counter;
    std::unordered_map<TString, TCode> Dictionary;
    std::vector<TCode> Output;
};

#endif  // DA_CP_LZW_HPP_
