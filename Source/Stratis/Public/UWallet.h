// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "UWallet.generated.h"

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UWallet : public UObject
{
    GENERATED_BODY()

public:
    UWallet();

    UFUNCTION(BlueprintCallable, Category = "UWallet")
    static FString getAddress();
};
