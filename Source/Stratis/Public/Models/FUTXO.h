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