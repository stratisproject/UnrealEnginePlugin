// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "FLargeUInt.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FUInt128 {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString value;

    FUInt128() : value("0") {}
    FUInt128(const FString& numericalValue) : value(numericalValue) {}
};

USTRUCT(BlueprintType)
struct STRATIS_API FUInt256 {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString value;

    FUInt256() : value("0") {}
    FUInt256(const FString& numericalValue) : value(numericalValue) {}
};
