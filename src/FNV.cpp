#include <FNV.hpp>

#include <algorithm>
#include <iostream>

std::vector<std::uint64_t> TFNV::CalculateHash(std::istream& is,
                                               std::size_t lenght) {
    std::vector<std::uint64_t> hashVector;
    std::vector<std::uint8_t> bytes(lenght);

    while (is) {
        is.read(reinterpret_cast<char*>(bytes.data()), lenght);
        if (!is.gcount()) {
            break;
        }

        auto hash = FNV_OFFSET_BASIS;
        for (auto i = 0ULL; i < static_cast<std::uint64_t>(is.gcount()); i++) {
            hash ^= bytes[i];
            hash *= FNV_PRIME;
        }
        hashVector.push_back(hash);
        std::fill(bytes.begin(), bytes.end(), 0);
    }

    return hashVector;
}
