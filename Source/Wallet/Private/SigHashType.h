// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <cstdint>

#include "TWBitcoinSigHashType.h"
#include "TWCoinType.h"

namespace TW::Bitcoin {

// Defines the number of bits of the hash type which is used to identify which
// outputs are signed.
static const uint32_t SigHashMask = 0x1f;

// Return the default HashType for the given coin, such as TWBitcoinSigHashTypeAll.
inline enum TWBitcoinSigHashType hashTypeForCoin(enum TWCoinType coinType)
{
    return TWBitcoinSigHashTypeAll;
}

inline bool hashTypeIsSingle(enum TWBitcoinSigHashType type) { return ((uint32_t)type & SigHashMask) == (uint32_t)TWBitcoinSigHashTypeSingle; }

inline bool hashTypeIsNone(enum TWBitcoinSigHashType type) { return ((uint32_t)type & SigHashMask) == (uint32_t)TWBitcoinSigHashTypeNone; }

} // namespace TW::Bitcoin
