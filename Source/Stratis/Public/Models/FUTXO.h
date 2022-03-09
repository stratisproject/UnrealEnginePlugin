// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "FUTXO.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FUTXO {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString hash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 n;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 satoshis;

    FUTXO() {}
};
