#pragma once

#include "CoreMinimal.h"

#include "FError.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FError {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString message;

  FError() {}

  FError(const FString &errorMessage) : message(errorMessage) {}
};