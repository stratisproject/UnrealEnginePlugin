#pragma once

#include "Models/FUTXO.h"
#include "UTXO.h"

namespace converters {

inline UTXO convertUTXO(const FUTXO& utxo)
{
    return {utxo.hash, (uint32)utxo.n, (uint64)utxo.satoshis};
}


} // namespace converters