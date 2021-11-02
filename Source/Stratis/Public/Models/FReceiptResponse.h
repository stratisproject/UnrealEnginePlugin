#pragma once

#include "CoreMinimal.h"

#include "FReceiptResponse.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FReceiptResponse {
  GENERATED_USTRUCT_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString transactionHash;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString blockHash;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int64 blockNumber;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString postState;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  int64 gasUsed;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString fromAddress;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString toAddress;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString newContractAddress;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  bool success;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString returnValue;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString bloom;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  FString error;
};