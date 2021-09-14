#pragma once

#include "CoreMinimal.h"

typedef uint64 FMoney;

DECLARE_DYNAMIC_DELEGATE_OneParam(FGetBalanceResponseReceivedDelegate, FMoney, money);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendOpReturnTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetCoinsResponseReceivedDelegate, TArray<FString>, data);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendCreateContractTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendCallContractTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FWaitTillReceiptAvailableResponseReceivedDelegate, FString, response); //TODO set proper return type declaration