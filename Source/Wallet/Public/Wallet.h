// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE-STRATIS at the root of the source code distribution tree.

#pragma once

#include <CoreMinimal.h>

#include "BuiltTransaction.h"
#include "Data.h"
#include "TWCoinType.h"
#include "WalletUTXO.h"

#include <string>

class WALLET_API Wallet
{
public:
    virtual ~Wallet() = 0;

    virtual std::string getMnemonic() const = 0;
    virtual void setMnemonic(const std::string& mnemonic) = 0;

    virtual TWCoinType getCoinType() const = 0;
    virtual void setCoinType(TWCoinType coinType) = 0;

    virtual std::string getAddress() const = 0;

    virtual BuiltTransaction createSendCoinsTransaction(const WalletUTXOs& utxos, std::string destinationAddress, uint64_t amount) const = 0;
    virtual BuiltTransaction createOpReturnTransaction(const WalletUTXOs& utxos, const TW::Data& opReturnData) const = 0;
    virtual BuiltTransaction createCustomScriptTransaction(const WalletUTXOs& utxos, const TW::Data& customScript, uint64_t amount) const = 0;
};

WALLET_API TSharedPtr<Wallet> createWallet(const std::string& mnemonic, TWCoinType coinType);