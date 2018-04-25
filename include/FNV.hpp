#ifndef DA_CP_FNV_HPP_
#define DA_CP_FNV_HPP_

#include <cstdint>
#include <iosfwd>
#include <vector>

class TFNV {
public:
    static std::vector<std::uint64_t> CalculateHash(std::istream& is,
                                                    std::size_t lenght);

private:
    static const std::uint64_t FNV_PRIME = 1099511628211ULL;
    static const std::uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
};

#endif  // DA_CP_FNV_HPP_
