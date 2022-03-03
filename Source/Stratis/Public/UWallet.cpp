// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "UWallet.h"

#include "WalletChecker.h"

UWallet::UWallet() {}

FString UWallet::getAddress()
{
    WalletChecker walletChecker;
    return walletChecker.checkWallet();
}
