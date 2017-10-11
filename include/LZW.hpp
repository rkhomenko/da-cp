#ifndef DA_CP_LZW_HPP_
#define DA_CP_LZW_HPP_

#include <cstdint>
#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

class TLZW {
public:
    using TCode = uint16_t;
    using TChar = char;
    using TString = std::basic_string<TChar>;

    friend std::istream& operator>>(const TLZW& lzw, std::istream& is);
    friend std::ostream& operator<<(const TLZW& lzw, std::ostream& os);

    TLZW();
private:
    void InitDictionary();

    TCode Counter;
    std::unordered_map<TString, TCode> Dictionary;
    std::vector<TCode> Output;
};

std::istream& operator>>(const TLZW& lzw, std::istream& is);
std::ostream& operator<<(const TLZW& lzw, std::ostream& os);

#endif // DA_CP_LZW_HPP_
