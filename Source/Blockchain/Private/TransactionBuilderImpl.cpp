// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "TransactionBuilderImpl.h"

#include <TransactionBuilderFactory.h>

#include "SmartContracts/SmartContractScriptFactoryProvider.h"

#include <string>
#include <vector>

TransactionBuilderImpl::TransactionBuilderImpl(const std::string& mnemonic,
                                               const StratisNetwork& network)
    : wallet_(createWallet(mnemonic, coinType(network))),
      smartContractScriptFactory_(
          smart_contracts::createSmartContractScriptFactory())
{
}

void TransactionBuilderImpl::setMnemonic(const FString& mnemonic)
{
    wallet_->setMnemonic(TO_STD_STRING(mnemonic));
}

void TransactionBuilderImpl::setNetwork(const StratisNetwork& network)
{
    wallet_->setCoinType(coinType(network));
}

FString TransactionBuilderImpl::paymentAddress() const
{
    return TO_FSTRING(this->wallet_->getAddress());
}

Transaction
TransactionBuilderImpl::buildSendTransaction(const FString& destinationAddress,
                                             const TArray<UTXO>& utxos,
                                             uint64 amount, uint64 fee) const
{
    return convertTransaction(
        this->wallet_->createSendCoinsTransaction(convertUTXOs(utxos), TO_STD_STRING(destinationAddress), amount));
}

Transaction TransactionBuilderImpl::buildOpReturnTransaction(
    const TArray<uint8>& data, const TArray<UTXO>& utxos, uint64 fee) const
{
    return convertTransaction(this->wallet_->createOpReturnTransaction(convertUTXOs(utxos), utils::asData(data)));
}

Transaction TransactionBuilderImpl::buildCreateContractTransaction(
    const FString& contractCode, const TArray<UTXO>& utxos, uint64 fee,
    uint64 gasPrice, uint64 gasLimit, uint64 amount,
    TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>&& parameters) const
{
    std::vector<uint8_t> scriptBytes =
        smartContractScriptFactory_->makeCreateSmartContractScript(
            {gasPrice,
             gasLimit,
             utils::asTArray(utils::hexAsBytes(contractCode)),
             MoveTemp(parameters)});

    return convertTransaction(this->wallet_->createCustomScriptTransaction(convertUTXOs(utxos), scriptBytes, amount));
}

Transaction TransactionBuilderImpl::buildCallContractTransaction(
    const FString& methodName, const Address& contractAddress,
    const TArray<UTXO>& utxos, uint64 fee, uint64 gasPrice, uint64 gasLimit,
    uint64 amount,
    TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>&& parameters) const
{
    std::vector<uint8_t> scriptBytes =
        smartContractScriptFactory_->makeCallSmartContractScript(
            {gasPrice,
             gasLimit,
             contractAddress,
             methodName,
             MoveTemp(parameters)});

    return convertTransaction(this->wallet_->createCustomScriptTransaction(convertUTXOs(utxos), scriptBytes, amount));
}

TWCoinType TransactionBuilderImpl::coinType(StratisNetwork network)
{
    switch (network) {
    case STRAX:
        return TWCoinType::TWCoinTypeStrax;
    case STRAX_TEST:
        return TWCoinType::TWCoinTypeStraxTest;
    case CIRRUS:
        return TWCoinType::TWCoinTypeCirrus;
    case CIRRUS_TEST:
        return TWCoinType::TWCoinTypeCirrusTest;
    default:
        return TWCoinType::TWCoinTypeStrax;
    }
}

WalletUTXOs TransactionBuilderImpl::convertUTXOs(const TArray<UTXO>& utxos)
{
    WalletUTXOs convertedUTXOs;
    convertedUTXOs.reserve(utxos.Num());

    for (const auto& utxo : utxos) {
        convertedUTXOs.push_back({TO_STD_STRING(utxo.hash), utxo.n, utxo.satoshis});
    }

    return convertedUTXOs;
}

Transaction TransactionBuilderImpl::convertTransaction(const BuiltTransaction& transaction)
{
    return {TO_FSTRING(transaction.transactionHex), TO_FSTRING(transaction.transactionID)};
}


TSharedPtr<TransactionBuilder>
createTransactionBuilder(const FString& mnemonic,
                         const StratisNetwork& network)
{
    return MakeShared<TransactionBuilderImpl>(TO_STD_STRING(mnemonic), network);
}
