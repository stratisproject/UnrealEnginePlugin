#pragma once

#include "Models/FUTXO.h"
#include "UTXO.h"

namespace converters {

inline UTXO convertUTXO(const FUTXO& utxo)
{
    return {.hash = utxo.hash, .n = (uint32)utxo.n, .satoshis = (uint64)utxo.satoshis};
}


} // namespace converters