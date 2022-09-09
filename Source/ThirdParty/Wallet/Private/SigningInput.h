// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Amount.h"
#include "TWBitcoinSigHashType.h"
#include "Transaction.h"
#include "UTXO.h"

#include "Misc/Optional.h"
#include <map>
#include <string>
#include <vector>

namespace TW {
namespace Bitcoin {

/// Input for signing, info of an unsigned transaction
class SigningInput
{
public:
    // Hash type to use when signing
    enum TWBitcoinSigHashType hashType = TWBitcoinSigHashTypeAll;

    // Amount to send.  Transaction created will have this amount in its output,
    // except when use_max_amount is set, in that case this amount is not relevant, maximum possible amount will be used (max avail less fee).
    // If amount is equal or more than the available amount, also max amount will be used.
    Amount amount = 0;

    // Transaction fee per byte
    Amount byteFee = 0;

    // Transaction fee per gas unit
    Amount gasPrice = 0;

    // Max gas amount per transaction
    Amount gasLimit = 0;

    // Recipient's address
    std::string toAddress;

    // Change address
    std::string changeAddress;

    // Available private keys
    std::vector<PrivateKey> privateKeys;

    // Available redeem scripts indexed by script hash
    std::map<std::string, Script> scripts;

    // Available unspent transaction outputs
    UTXOs utxos;

    // If sending max amount
    bool useMaxAmount = false;

    // Coin type (forks)
    TWCoinType coinType = TWCoinTypeBitcoin;

    // Optional transaction plan
    TOptional<TransactionPlan> plan;

    Data outputOpReturn;

    Script outputCustomScript;

    uint32_t lockTime = 0;

public:
    SigningInput() = default;
};

} // namespace Bitcoin
} // namespace TW