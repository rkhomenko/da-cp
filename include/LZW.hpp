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
    static const TCode EOB;

    void InitDictionary();

    void BufferCoding(std::ostream& os,
                      const std::vector<TChar>& buffer,
                      TSize bufferSize);
    void BufferDecoding(std::ostream& os,
                        const std::vector<TCode>& buffer,
                        TSize bufferSize);

    TSize BufferSize;
    TCode Counter;
    std::unordered_map<TString, TCode> StrToCodeDict;
    std::unordered_map<TCode, TString> CodeToStrDict;
};

#endif  // DA_CP_LZW_HPP_
