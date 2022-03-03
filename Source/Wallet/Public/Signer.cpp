// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Signer.h"
#include "Hash.h"
#include "HexCoding.h"
#include "Transaction.h"
#include "TransactionBuilder.h"
#include "TransactionSigner.h"

using namespace TW;
using namespace TW::Bitcoin;

TransactionPlan Signer::plan(const SigningInput& input) noexcept
{
    return TransactionSigner<Transaction, TransactionBuilder>::plan(input);
}

SigningOutput Signer::sign(const SigningInput& input) noexcept
{
    SigningOutput output;
    auto result = TransactionSigner<Transaction, TransactionBuilder>::sign(input);
    if (!result) {
        output.error = result.error();
        return output;
    }

    const auto& tx = result.payload();
    output.transaction = tx;

    Data encoded;
    tx.encode(encoded);
    output.encoded = encoded;

    Data txHashData = encoded;
    if (tx.hasWitness()) {
        txHashData.clear();
        tx.encode(txHashData, Transaction::SegwitFormatMode::NonSegwit);
    }
    auto txHash = Hash::sha256d(txHashData.data(), txHashData.size());
    std::reverse(txHash.begin(), txHash.end());
    output.transactionId = hex(txHash);
    return output;
}
