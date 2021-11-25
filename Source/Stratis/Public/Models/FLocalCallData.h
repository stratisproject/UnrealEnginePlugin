#pragma once

#include "CoreMinimal.h"

#include "FLocalCallData.generated.h"

constexpr int64 UNINITIALIZED = -1;

USTRUCT(BlueprintType)
struct STRATIS_API FLocalCallData {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString contractAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString methodName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 gasPrice = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 gasLimit = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString amount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString sender;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 blockHeight = -1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> parameters;

    FLocalCallData() {}
};