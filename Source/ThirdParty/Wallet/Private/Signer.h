// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once
#include "SigningInput.h"
#include "SigningOutput.h"
#include "TransactionPlan.h"

namespace TW {
namespace Bitcoin {

class Signer
{
public:
    Signer() = delete;

    /// Returns a transaction plan (utxo selection, fee estimation)
    static TransactionPlan plan(const SigningInput& input) noexcept;

    /// Signs a SigningInput transaction
    static SigningOutput sign(const SigningInput& input) noexcept;
};

} // namespace Bitcoin
} // namespace TW