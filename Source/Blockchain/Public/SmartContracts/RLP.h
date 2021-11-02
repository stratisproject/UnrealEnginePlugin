#pragma once

#include <vector>

namespace RLP
{
    std::vector<uint8_t> encodeString(const std::vector<uint8_t>& data);
    std::vector<uint8_t> encodeList(const std::vector< std::vector<uint8_t> >& data);
    std::vector<uint8_t> encodeListAndItems(const std::vector< std::vector<uint8_t> >& data);
}