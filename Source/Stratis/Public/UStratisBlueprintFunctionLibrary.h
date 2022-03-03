// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"
#include "Models/FUInt64.h"

#include "UStratisBlueprintFunctionLibrary.generated.h"

UCLASS()
class UStratisBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure,
              meta = (DisplayName = "FUInt64 To String", CompactNodeTitle = "->",
                      BlueprintAutocast),
              Category = "FUInt64")
    static FString Conv_FUInt64ToString(const FUInt64& value);
};
