#pragma once

#include "CoreMinimal.h"

#include "FReceiptResponse.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FReceiptResponse {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isTransactionHashValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString transactionHash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isBlockHashValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString blockHash;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isBlockNumberValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 blockNumber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isPostStateValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString postState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int64 gasUsed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isFromAddressValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString fromAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isToAddressValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString toAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isNewContractAddressValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString newContractAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool success = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isReturnValueValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString returnValue;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isBloomValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString bloom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isErrorValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString error;
};