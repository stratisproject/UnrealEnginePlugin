// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "FLocalCallData.generated.h"

constexpr int64 UNINITIALIZED = -1;

USTRUCT(BlueprintType)
struct STRATIS_API FLocalCallData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString contractAddress;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString methodName;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    int64 gasPrice = -1;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    int64 gasLimit = -1;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString amount;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString sender;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    int64 blockHeight = -1;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    TArray<FString> parameters;

    FLocalCallData() {}
};
