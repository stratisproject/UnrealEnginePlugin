#pragma once

#include "Core.h"

#include "UStratisUnrealManager.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FGetBalanceResponseReceivedDelegate, int, money);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendOpReturnTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetCoinsResponseReceivedDelegate, TArray<FString>, data);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendCreateContractTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSendCallContractTransactionResponseReceivedDelegate, FString, txId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FWaitTillReceiptAvailableResponseReceivedDelegate, FString, response); //TODO set proper return type declaration

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UStratisUnrealManager : public UObject
{

GENERATED_BODY()

public:
    void Initialize(FString mnemonic);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    FString getAddress();
    
    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void getBalance(FGetBalanceResponseReceivedDelegate delegate);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendTransaction(FSendTransactionResponseReceivedDelegate delegate, const FString& destinationAddress, int money);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendOpReturnStringTransaction(FSendOpReturnTransactionResponseReceivedDelegate delegate, const FString& opReturnData);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendOpReturnArrayTransaction(FSendOpReturnTransactionResponseReceivedDelegate delegate, const TArray<uint8>& opReturnData);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void getCoins(FGetCoinsResponseReceivedDelegate delegate);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendCreateContractTransaction(FSendCreateContractTransactionResponseReceivedDelegate delegate, const FString& contractCode, const TArray<FString>& parameters, int money);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void sendCallContractTransaction(FSendCallContractTransactionResponseReceivedDelegate delegate, const FString& contractAddress, const FString& methodName, const TArray<FString>& parameters, int money);

    UFUNCTION(BlueprintCallable, Category = "StratisUnrealManager")
    void waitTillReceiptAvailable(FWaitTillReceiptAvailableResponseReceivedDelegate delegate, const FString& txId);

    UPROPERTY(EditAnywhere)
    uint64 gasPrice;

    UPROPERTY(EditAnywhere)
    uint64 gasLimit;

private:
    FString mnemonic;
};