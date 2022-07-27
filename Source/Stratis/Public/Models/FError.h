// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "FError.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FError {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString message;

    FError() {}

    FError(const FString& errorMessage) : message(errorMessage) {}
};
