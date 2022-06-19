// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "TransactionBuilder.h"
#include <CoreMinimal.h>

#include "TWCoinType.h"
#include "Wallet.h"
#include "WalletUTXO.h"

class TransactionBuilderImpl : public TransactionBuilder
{
public:
    TransactionBuilderImpl(const std::string& mnemonic,
                           const StratisNetwork& network);
    virtual ~TransactionBuilderImpl() {}

    FString generateMnemonic() override;

    void setMnemonic(const FString& mnemonic) override;
    void setNetwork(const StratisNetwork& network) override;

    FString paymentAddress() const override;

    Transaction buildSendTransaction(const FString& destinationAddress,
                                     const TArray<UTXO>& utxos, uint64 amount,
                                     uint64 fee) const override;

    Transaction buildOpReturnTransaction(const TArray<uint8>& data,
                                         const TArray<UTXO>& utxos,
                                         uint64 fee) const override;

    Transaction buildCreateContractTransaction(
        const FString& contractCode, const TArray<UTXO>& utxos, uint64 fee,
        uint64 gasPrice, uint64 gasLimit, uint64 amount,
        TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>&& parameters) const override;

    Transaction buildCallContractTransaction(
        const FString& methodName, const Address& contractAddress,
        const TArray<UTXO>& utxos, uint64 fee, uint64 gasPrice, uint64 gasLimit,
        uint64 amount,
        TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>&& parameters) const override;

private:
    static TWCoinType coinType(StratisNetwork network);
    static WalletUTXOs convertUTXOs(const TArray<UTXO>& utxos);
    static Transaction convertTransaction(const BuiltTransaction& transaction);

    TSharedPtr<Wallet> wallet_;

    TUniquePtr<smart_contracts::SmartContractScriptFactory>
        smartContractScriptFactory_;
};
