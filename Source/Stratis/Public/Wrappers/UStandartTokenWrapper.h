// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "Models/FUInt64.h"
#include "UStratisUnrealManager.h"
#include "WhitelistedSmartContracts.h"

#include "UStandartTokenWrapper.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeployStandartTokenDelegate, const FString&, transactionId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetSymbolDelegate, const FString&, symbol);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetNameDelegate, const FString&, name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetTotalSupplyDelegate, const FUInt64&, totalSupply);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetDecimalsDelegate, int64, decimals);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetBalanceDelegate, const FUInt64&, balance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetAllowanceDelegate, const FUInt64&, allowance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTransferToDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTransferFromDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FApproveDelegate, const FString&, transactionID);

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UStandartTokenWrapper : public UObject
{
    GENERATED_BODY()

public:
    UStandartTokenWrapper();

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    static UStandartTokenWrapper* createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer);
    
    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    static UStandartTokenWrapper* createDefaultInstance(UStratisUnrealManager* manager, UObject* outer);
    
    UPROPERTY(EditAnywhere)
    UStratisUnrealManager* stratisManager;

    UPROPERTY(EditAnywhere)
    FString contractAddress;

    UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void deployStandartToken(const FUInt64& totalSupply, const FString& name,
                             const FString& symbols, int64 decimals,
                             const FDeployStandartTokenDelegate& delegate,
                             const FErrorReceivedDelegate& errorDelegate);
    void deployStandartToken(uint64 totalSupply, const FString& name,
                             const FString& symbols, uint32 decimals,
                             TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void getSymbol(const FGetSymbolDelegate& delegate,
                   const FErrorReceivedDelegate& errorDelegate);
    void getSymbol(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void getName(const FGetNameDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void getName(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void getTotalSupply(const FGetTotalSupplyDelegate& delegate,
                        const FErrorReceivedDelegate& errorDelegate);
    void getTotalSupply(TFunction<void(const TResult<uint64>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void getDecimals(const FGetDecimalsDelegate& delegate,
                     const FErrorReceivedDelegate& errorDelegate);
    void getDecimals(TFunction<void(const TResult<uint32>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void getBalance(const FString& address, const FGetBalanceDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void getBalance(const FString& address,
                    TFunction<void(const TResult<uint64>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void getAllowance(const FString& ownerAddress, const FString& spenderAddress,
                      const FGetAllowanceDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void getAllowance(const FString& ownerAddress, const FString& spenderAddress,
                      TFunction<void(const TResult<uint64>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void transferTo(const FString& address, const FUInt64& amount,
                    const FTransferToDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void transferTo(const FString& address, uint64 amount,
                    TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt64& amount,
                      const FTransferFromDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      uint64 amount,
                      TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
    void approve(const FString& spender, const FUInt64& currentAmount,
                 const FUInt64& amount, const FApproveDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void approve(const FString& spender, uint64 currentAmount, uint64 amount,
                 TFunction<void(const TResult<FString>&)> callback);
};
