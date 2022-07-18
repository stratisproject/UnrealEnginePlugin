// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE-STRATIS at the root of the source code distribution tree.

#pragma once

#include <Wallet.h>

#include "SigningInput.h"

class WalletImpl : public Wallet
{
public:
    WalletImpl(const std::string& mnemonic, TWCoinType coinType);

    virtual ~WalletImpl() {}

    std::string generateMnemonic() const override;

    std::string getMnemonic() const override;
    void setMnemonic(const std::string& mnemonic) override;

    TWCoinType getCoinType() const override;
    void setCoinType(TWCoinType coinType) override;

    std::string getAddress() const override;

    BuiltTransaction createSendCoinsTransaction(const WalletUTXOs& utxos, std::string destinationAddress, uint64_t amount) const override;
    BuiltTransaction createOpReturnTransaction(const WalletUTXOs& utxos, const TW::Data& opReturnData) const override;
    BuiltTransaction createCustomScriptTransaction(const WalletUTXOs& utxos, const TW::Data& customScript, uint64_t amount, uint64_t gasPrice, uint64_t gasLimit) const override;

private:
    TW::HDWallet hdWallet_;

    TWCoinType coinType_;

    TW::Bitcoin::SigningInput buildSigningInput(const WalletUTXOs& utxos) const;
    BuiltTransaction signTransaction(const TW::Bitcoin::SigningInput& input) const;
};