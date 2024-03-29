// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Data.h"
#include "OutPoint.h"
#include "Script.h"

#include <vector>

namespace TW {
namespace Bitcoin {

/// Bitcoin transaction input.
class TransactionInput
{
public:
    /// Reference to the previous transaction's output.
    OutPoint previousOutput;

    /// Transaction version as defined by the sender.
    ///
    /// Intended for "replacement" of transactions when information is updated
    /// before inclusion into a block.
    uint32_t sequence;

    /// Computational Script for confirming transaction authorization.
    Script script;

    /// Witness stack.
    std::vector<Data> scriptWitness;

    /// Initializes a transaction input with a previous output, a script and a
    /// sequence number.
    TransactionInput(OutPoint previousOutput, Script script, uint32_t sequence)
        : previousOutput(std::move(previousOutput)), sequence(sequence), script(std::move(script)) {}

    /// Encodes the transaction into the provided buffer.
    void encode(Data& data) const;

    /// Encodes the witness data into the provided buffer.
    void encodeWitness(Data& data) const;
};

} // namespace Bitcoin
} // namespace TW