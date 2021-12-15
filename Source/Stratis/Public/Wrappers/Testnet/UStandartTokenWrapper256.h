#pragma once

#include "CoreMinimal.h"

#include "Models/FLargeUInt.h"
#include "Models/FUInt64.h"

#include "UStratisUnrealManager.h"
#include "WhitelistedSmartContracts.h"

#include "UStandartTokenWrapper256.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeployStandartToken256Delegate, const FString&, transactionId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256GetSymbolDelegate, const FString&, symbol);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256GetNameDelegate, const FString&, name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256GetTotalSupplyDelegate, const FUInt256&, totalSupply);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256GetDecimalsDelegate, uint8, decimals);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256GetBalanceDelegate, const FUInt256&, balance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256GetAllowanceDelegate, const FUInt256&, allowance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256TransferToDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256TransferFromDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FST256ApproveDelegate, const FString&, transactionID);

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UStandartTokenWrapper256 : public UObject
{
    GENERATED_BODY()

public:
    UStandartTokenWrapper256();

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    static UStandartTokenWrapper256* createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer);
    
    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    static UStandartTokenWrapper256* createDefaultInstance(UStratisUnrealManager* manager, UObject* outer);
    
    UPROPERTY(EditAnywhere)
    UStratisUnrealManager* stratisManager;

    UPROPERTY(EditAnywhere)
    FString contractAddress;

    UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void deployStandartToken(const FUInt256& totalSupply, const FString& name,
                             const FString& symbols, uint8 decimals,
                             const FDeployStandartToken256Delegate& delegate,
                             const FErrorReceivedDelegate& errorDelegate);
    void deployStandartToken(const FUInt256& totalSupply, const FString& name,
                             const FString& symbols, uint8 decimals,
                             TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void getSymbol(const FST256GetSymbolDelegate& delegate,
                   const FErrorReceivedDelegate& errorDelegate);
    void getSymbol(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void getName(const FST256GetNameDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void getName(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void getTotalSupply(const FST256GetTotalSupplyDelegate& delegate,
                        const FErrorReceivedDelegate& errorDelegate);
    void getTotalSupply(TFunction<void(const TResult<FUInt256>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void getDecimals(const FST256GetDecimalsDelegate& delegate,
                     const FErrorReceivedDelegate& errorDelegate);
    void getDecimals(TFunction<void(const TResult<uint8>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void getBalance(const FString& address, const FST256GetBalanceDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void getBalance(const FString& address,
                    TFunction<void(const TResult<FUInt256>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void getAllowance(const FString& ownerAddress, const FString& spenderAddress,
                      const FST256GetAllowanceDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void getAllowance(const FString& ownerAddress, const FString& spenderAddress,
                      TFunction<void(const TResult<FUInt256>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void transferTo(const FString& address, const FUInt256& amount,
                    const FST256TransferToDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void transferTo(const FString& address, const FUInt256& amount,
                    TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt256& amount,
                      const FST256TransferFromDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt256& amount,
                      TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper256")
    void approve(const FString& spender, const FUInt256& currentAmount,
                 const FUInt256& amount, const FST256ApproveDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void approve(const FString& spender, const FUInt256& currentAmount, const FUInt256& amount,
                 TFunction<void(const TResult<FString>&)> callback);
};
