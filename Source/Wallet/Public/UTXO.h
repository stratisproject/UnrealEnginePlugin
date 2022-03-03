// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Amount.h"
#include "OutPoint.h"
#include "Script.h"

#include <vector>

namespace TW::Bitcoin {

class UTXO
{
public:
    // The unspent output
    OutPoint outPoint;

    // Script for claiming this UTXO
    Script script;

    // Amount of the UTXO
    Amount amount;

public:
    UTXO() = default;
};

/// A list of UTXO's
class UTXOs : public std::vector<UTXO>
{
public:
    UTXOs() = default;
    UTXOs(const std::vector<UTXO>& vector) : std::vector<UTXO>(vector) {}
    UTXOs(UTXO utxo) : std::vector<UTXO>({utxo}) {}
};

} // namespace TW::Bitcoin
