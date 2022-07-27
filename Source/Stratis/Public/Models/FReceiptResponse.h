// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "FReceiptResponse.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FReceiptResponse {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isTransactionHashValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString transactionHash;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isBlockHashValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString blockHash;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isBlockNumberValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    int64 blockNumber;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isPostStateValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString postState;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    int64 gasUsed;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isFromAddressValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString fromAddress;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isToAddressValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString toAddress;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isNewContractAddressValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString newContractAddress;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool success = false;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isReturnValueValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString returnValue;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isBloomValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString bloom;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    bool isErrorValid = false;
    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString error;
};
