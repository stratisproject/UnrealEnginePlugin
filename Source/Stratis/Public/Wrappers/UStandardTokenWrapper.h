// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "Models/FLargeUInt.h"
#include "Models/FUInt64.h"

#include "UStratisUnrealManager.h"
#include "WhitelistedSmartContracts.h"

#include "UStandardTokenWrapper.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeployStandardToken256Delegate, const FString&, transactionId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTGetSymbolDelegate, const FString&, symbol);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTGetNameDelegate, const FString&, name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTGetTotalSupplyDelegate, const FUInt256&, totalSupply);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTGetDecimalsDelegate, uint8, decimals);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTGetBalanceDelegate, const FUInt256&, balance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTGetAllowanceDelegate, const FUInt256&, allowance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTTransferToDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTTransferFromDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSTApproveDelegate, const FString&, transactionID);

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UStandardTokenWrapper : public UObject
{
    GENERATED_BODY()

public:
    UStandardTokenWrapper();

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    static UStandardTokenWrapper* createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    static UStandardTokenWrapper* createDefaultInstance(UStratisUnrealManager* manager, UObject* outer);

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    UStratisUnrealManager* stratisManager;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    FString contractAddress;

    UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void deployStandardToken(const FUInt256& totalSupply, const FString& name,
                             const FString& symbols, uint8 decimals,
                             const FDeployStandardToken256Delegate& delegate,
                             const FErrorReceivedDelegate& errorDelegate);
    void deployStandardToken(const FUInt256& totalSupply, const FString& name,
                             const FString& symbols, uint8 decimals,
                             TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void getSymbol(const FSTGetSymbolDelegate& delegate,
                   const FErrorReceivedDelegate& errorDelegate);
    void getSymbol(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void getName(const FSTGetNameDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void getName(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void getTotalSupply(const FSTGetTotalSupplyDelegate& delegate,
                        const FErrorReceivedDelegate& errorDelegate);
    void getTotalSupply(TFunction<void(const TResult<FUInt256>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void getDecimals(const FSTGetDecimalsDelegate& delegate,
                     const FErrorReceivedDelegate& errorDelegate);
    void getDecimals(TFunction<void(const TResult<uint8>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void getBalance(const FString& address, const FSTGetBalanceDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void getBalance(const FString& address,
                    TFunction<void(const TResult<FUInt256>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void getAllowance(const FString& ownerAddress, const FString& spenderAddress,
                      const FSTGetAllowanceDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void getAllowance(const FString& ownerAddress, const FString& spenderAddress,
                      TFunction<void(const TResult<FUInt256>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void transferTo(const FString& address, const FUInt256& amount,
                    const FSTTransferToDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void transferTo(const FString& address, const FUInt256& amount,
                    TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt256& amount,
                      const FSTTransferFromDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt256& amount,
                      TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandardTokenWrapper256")
    void approve(const FString& spender, const FUInt256& currentAmount,
                 const FUInt256& amount, const FSTApproveDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void approve(const FString& spender, const FUInt256& currentAmount, const FUInt256& amount,
                 TFunction<void(const TResult<FString>&)> callback);
};
