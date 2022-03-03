// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <vector>

namespace RLP {
std::vector<uint8_t> encodeString(const std::vector<uint8_t>& data);
std::vector<uint8_t> encodeList(const std::vector<std::vector<uint8_t>>& data);
std::vector<uint8_t> encodeListAndItems(const std::vector<std::vector<uint8_t>>& data);
} // namespace RLP
