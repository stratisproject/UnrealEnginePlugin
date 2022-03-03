// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "InputSelector.h"
#include "SigningInput.h"
#include "Transaction.h"
#include "TransactionPlan.h"
#include <TWCoinType.h>

#include <algorithm>
#include <optional>

namespace TW::Bitcoin {

class TransactionBuilder
{
public:
    /// Plans a transaction by selecting UTXOs and calculating fees.
    static TransactionPlan plan(const SigningInput& input);

    /// Builds a transaction with the selected input UTXOs, and one main output and an optional change output.
    template <typename Transaction>
    static Transaction build(const TransactionPlan& plan, const std::string& toAddress,
                             const std::string& changeAddress, enum TWCoinType coin, uint32_t lockTime)
    {
        Transaction tx;
        tx.lockTime = lockTime;

        if (plan.outputCustomScript.empty()) {
            auto outputTo = prepareOutputWithScript(toAddress, plan.amount, coin);
            if (!outputTo.has_value()) {
                return {};
            }
            tx.outputs.push_back(outputTo.value());
        } else {
            tx.outputs.push_back({plan.amount, plan.outputCustomScript});
        }


        if (plan.change > 0) {
            auto outputChange = prepareOutputWithScript(changeAddress, plan.change, coin);
            if (!outputChange.has_value()) {
                return {};
            }
            tx.outputs.push_back(outputChange.value());
        }

        const auto emptyScript = Script();
        for (auto& utxo : plan.utxos) {
            tx.inputs.emplace_back(utxo.outPoint, emptyScript, utxo.outPoint.sequence);
        }

        // Optional OP_RETURN output
        if (plan.outputCustomScript.empty() && plan.outputOpReturn.size() > 0) {
            auto lockingScriptOpReturn = Script::buildOpReturnScript(plan.outputOpReturn);
            tx.outputs.push_back(TransactionOutput(0, lockingScriptOpReturn));
        }

        return tx;
    }

    /// Prepares a TransactionOutput with given address and amount, prepares script for it
    static std::optional<TransactionOutput> prepareOutputWithScript(std::string address, Amount amount, enum TWCoinType coin);

    /// The maximum number of UTXOs to consider.  UTXOs above this limit are cut off because it cak take very long.
    static const size_t MaxUtxosHardLimit;
};

} // namespace TW::Bitcoin
