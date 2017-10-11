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

    friend std::istream& operator>>(const TLZW lzw, std::istream& is);
    friend std::ostream& operator<<(const TLZW lzw, std::ostream& os);

    TLZW();
private:
    void InitDictionary();

    std::unordered_map<std::string, TCode> Dictionary;
    std::vector<TCode> Output;
};

#endif // DA_CP_LZW_HPP_
