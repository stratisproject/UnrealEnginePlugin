#pragma once

#include "FLargeUInt.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FUInt128 {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString value;

    FUInt128() : value("0") {}
    FUInt128(const FString& numericalValue) : value(numericalValue) {}
};

USTRUCT(BlueprintType)
struct STRATIS_API FUInt256 {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString value;

    FUInt256() : value("0") {}
    FUInt256(const FString& numericalValue) : value(numericalValue) {}
};
