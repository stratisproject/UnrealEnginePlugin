#pragma once

#include "CoreMinimal.h"
#include "StratisTypes.h"

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API StratisUnrealManager : public UObject
{

GENERATED_BODY()

public:
    StratisUnrealManager(FString mnemonic);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    FString getAddress();
    
    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void getBalance(FGetBalanceResponseReceivedDelegate delegate);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendTransaction(FSendTransactionResponseReceivedDelegate delegate, const FString& destinationAddress, FMoney money);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendOpReturnTransaction(FSendOpReturnTransactionResponseReceivedDelegate delegate, const FString& opReturnData);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendOpReturnTransaction(FSendOpReturnTransactionResponseReceivedDelegate delegate, const TArray<uint8>& opReturnData);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void getCoins(FGetCoinsResponseReceivedDelegate delegate);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendCreateContractTransaction(FSendCreateContractTransactionResponseReceivedDelegate delegate, const FString& contractCode, const TArray<FString>& parameters, uint64 money);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendCallContractTransaction(FSendCallContractTransactionResponseReceivedDelegate delegate, const FString& contractAddress, const FString& methodName, const TArray<FString>& parameters, uint64 money);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void waitTillReceiptAvailable(FWaitTillReceiptAvailableResponseReceivedDelegate delegate, const FString& txId);

    UPROPERTY(EditAnywhere)
    uint64 gasPrice;

    UPROPERTY(EditAnywhere)
    uint64 gasLimit;

private:
    FString mnemonic;
};