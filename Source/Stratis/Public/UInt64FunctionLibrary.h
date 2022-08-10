// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "Models/FUInt64.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "UInt64FunctionLibrary.generated.h"

UCLASS()
class STRATIS_API UInt64FunctionLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UInt64",
              meta = (DisplayName = "Format UInt64 as money",
                      Keywords = "format uint64 money"))
    static FString FormatUInt64(const FUInt64& value);

    UFUNCTION(BlueprintCallable, Category = "UInt64",
              meta = (DisplayName = "Represent UInt64 as byte array",
                      Keywords = "byte array uint64"))
    static TArray<uint8> ToByteArray(const FUInt64& value);
};
