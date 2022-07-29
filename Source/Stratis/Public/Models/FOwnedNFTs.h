// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "FOwnedNFTs.generated.h"

UCLASS(BlueprintType)
class UOwnedNFTAccessor : public UObject
{
    GENERATED_BODY()
public:
    UOwnedNFTAccessor();

    void Initialize(TMap<FString, TArray<int64>> ownedIDsByContractAddress);

    UFUNCTION(BlueprintCallable, Category = "UOwnedNFTAccessor")
    TArray<int64> getOwnedIDsByContractAddress(const FString& contractAddress);

private:
    TMap<FString, TArray<int64>> ownedIDsByContractAddress;
};

USTRUCT(BlueprintType)
struct STRATIS_API FOwnedNFTs {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    UOwnedNFTAccessor* accessor;
};
