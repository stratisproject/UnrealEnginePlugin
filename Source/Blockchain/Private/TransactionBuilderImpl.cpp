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

#include "Coin.h"
#include "Signer.h"

constexpr uint32_t DEFAULT_SEQUENCE = std::numeric_limits<uint32_t>::max();

TransactionBuilderImpl::TransactionBuilderImpl(const std::string& mnemonic,
                                               const StratisNetwork& network)
    : network_(network),
      smartContractScriptFactory_(
          smart_contracts::createSmartContractScriptFactory()),
      wallet_(TW::HDWallet(mnemonic, "", false))
{
}

void TransactionBuilderImpl::setMnemonic(const FString& mnemonic)
{
    wallet_ = TW::HDWallet(TO_STD_STRING(mnemonic), "", false);
}

void TransactionBuilderImpl::setNetwork(const StratisNetwork& network)
{
    network_ = network;
}

FString TransactionBuilderImpl::paymentAddress() const
{
    return TO_FSTRING(this->address());
}

std::string TransactionBuilderImpl::address() const
{
    return wallet_.deriveAddress(this->coinType());
}

Transaction
TransactionBuilderImpl::buildSendTransaction(const FString& destinationAddress,
                                             const TArray<UTXO>& utxos,
                                             uint64 amount, uint64 fee) const
{
    TW::Bitcoin::SigningInput signingInput(this->buildSigningInput(utxos));

    signingInput.amount = amount;
    signingInput.toAddress = TO_STD_STRING(destinationAddress);

    return this->signTransaction(signingInput);
}

Transaction TransactionBuilderImpl::buildOpReturnTransaction(
    const TArray<uint8>& data, const TArray<UTXO>& utxos, uint64 fee) const
{
    TW::Bitcoin::SigningInput signingInput(this->buildSigningInput(utxos));

    TW::Data dataChunk;
    dataChunk.reserve(data.Num());

    for (uint8 dataByte : data) {
        dataChunk.push_back(dataByte);
    }

    signingInput.outputOpReturn = dataChunk;

    return this->signTransaction(signingInput);
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

    TW::Bitcoin::SigningInput signingInput(this->buildSigningInput(utxos));

    signingInput.amount = amount;
    signingInput.outputCustomScript = TW::Bitcoin::Script(scriptBytes);

    return this->signTransaction(signingInput);
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

    TW::Bitcoin::SigningInput signingInput(this->buildSigningInput(utxos));

    signingInput.amount = amount;
    signingInput.outputCustomScript = TW::Bitcoin::Script(scriptBytes);

    return this->signTransaction(signingInput);
}

TW::Bitcoin::SigningInput TransactionBuilderImpl::buildSigningInput(const TArray<UTXO>& utxos) const
{
    TW::Bitcoin::SigningInput signingInput;

    auto coin = this->coinType();

    signingInput.changeAddress = this->address();
    signingInput.coinType = coin;

    signingInput.privateKeys = {wallet_.getKey(coin, TW::derivationPath(coin))};

    TW::Bitcoin::UTXOs convertedUtxos;
    convertedUtxos.reserve(utxos.Num());

    for (const auto& utxo : utxos) {
        TW::Bitcoin::OutPoint outpoint{
            TW::parse_hex(TO_STD_STRING(utxo.hash)), // TODO: check hex decoding and check reversed order (decode_hash)
            utxo.n,
            DEFAULT_SEQUENCE};

        convertedUtxos.push_back({outpoint, TW::Bitcoin::Script(), static_cast<TW::Bitcoin::Amount>(utxo.satoshis)});
    }

    signingInput.utxos = convertedUtxos;

    return signingInput;
}

Transaction TransactionBuilderImpl::signTransaction(const TW::Bitcoin::SigningInput& input) const
{
    auto signedOutput = TW::Bitcoin::Signer::sign(input);

    return Transaction{
        TO_FSTRING(TW::hex(signedOutput.encoded)), // TODO: check encode transaction
        TO_FSTRING(signedOutput.transactionId)};
}

TWCoinType TransactionBuilderImpl::coinType() const
{
    switch (network_) {
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

TSharedPtr<TransactionBuilder>
createTransactionBuilder(const FString& mnemonic,
                         const StratisNetwork& network)
{
    return MakeShared<TransactionBuilderImpl>(TO_STD_STRING(mnemonic), network);
}
