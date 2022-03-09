// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Models/FUTXO.h"
#include "UTXO.h"

namespace converters {

inline UTXO convertUTXO(const FUTXO& utxo)
{
    return {utxo.hash, (uint32)utxo.n, (uint64)utxo.satoshis};
}


} // namespace converters
