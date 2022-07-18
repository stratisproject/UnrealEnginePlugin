// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Models/FOwnedNFTs.h"

UOwnedNFTAccessor::UOwnedNFTAccessor()
{
}

void UOwnedNFTAccessor::Initialize(TMap<FString, TArray<int64>> ownedIDsByContractAddress_)
{
    this->ownedIDsByContractAddress = ownedIDsByContractAddress_;
}

TArray<int64> UOwnedNFTAccessor::getOwnedIDsByContractAddress(const FString& contractAddress)
{
    if (this->ownedIDsByContractAddress.Contains(contractAddress)) {
        return ownedIDsByContractAddress[contractAddress];
    }
    return {};
}
