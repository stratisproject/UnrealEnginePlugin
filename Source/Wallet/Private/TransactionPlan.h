// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Amount.h"
#include "Data.h"
#include "SigningError.h"
#include "UTXO.h"

namespace TW::Bitcoin {

/// Describes a preliminary transaction plan.
struct TransactionPlan {
    /// Amount to be received at the other end.
    Amount amount = 0;

    /// Maximum available amount.
    Amount availableAmount = 0;

    /// Estimated transaction fee.
    Amount fee = 0;

    /// Change.
    Amount change = 0;

    /// Selected unspent transaction outputs.
    UTXOs utxos;

    /// Zcash branch id
    Data branchId;

    Data outputOpReturn;

    Script outputCustomScript;

    SigningError error{"OK"};

    TransactionPlan() = default;
};

} // namespace TW::Bitcoin
