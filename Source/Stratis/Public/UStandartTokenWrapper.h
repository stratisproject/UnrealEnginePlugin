#pragma once

#include "CoreMinimal.h"

#include "Models/FUInt64.h"
#include "UStratisUnrealManager.h"

#include "UStandartTokenWrapper.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeployStandartTokenDelegate, const FString &,
                                  transactionId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetSymbolDelegate, const FString &, symbol);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetNameDelegate, const FString &, name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetTotalSupplyDelegate, const FUInt64 &,
                                  totalSupply);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetDecimalsDelegate, int64, decimals);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetBalanceDelegate, const FUInt64 &,
                                  balance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FGetAllowanceDelegate, const FUInt64 &,
                                  allowance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTransferToDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FTransferFromDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FApproveDelegate, const FString &,
                                  transactionID);

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UStandartTokenWrapper : public UObject {

  GENERATED_BODY()

public:
  UStandartTokenWrapper();

  UPROPERTY(EditAnywhere)
  UStratisUnrealManager *stratisManager;

  UPROPERTY(EditAnywhere)
  FString contractAddress;

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void deployStandartToken(const FUInt64 &totalSupply, const FString &name,
                           const FString &symbols, int64 decimals,
                           const FDeployStandartTokenDelegate &delegate);
  void deployStandartToken(uint64 totalSupply, const FString &name,
                           const FString &symbols, uint32 decimals,
                           TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void getSymbol(const FGetSymbolDelegate &delegate);
  void getSymbol(TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void getName(const FGetNameDelegate &delegate);
  void getName(TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void getTotalSupply(const FGetTotalSupplyDelegate &delegate);
  void getTotalSupply(TFunction<void(uint64)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void getDecimals(const FGetDecimalsDelegate &delegate);
  void getDecimals(TFunction<void(uint32)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void getBalance(const FString &address, const FGetBalanceDelegate &delegate);
  void getBalance(const FString &address, TFunction<void(uint64)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void getAllowance(const FString &ownerAddress, const FString &spenderAddress,
                    const FGetAllowanceDelegate &delegate);
  void getAllowance(const FString &ownerAddress, const FString &spenderAddress,
                    TFunction<void(uint64)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void transferTo(const FString &address, const FUInt64 &amount,
                  const FTransferToDelegate &delegate);
  void transferTo(const FString &address, uint64 amount,
                  TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void transferFrom(const FString &fromAddress, const FString &toAddress,
                    const FUInt64 &amount,
                    const FTransferFromDelegate &delegate);
  void transferFrom(const FString &fromAddress, const FString &toAddress,
                    uint64 amount, TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "StandartTokenWrapper")
  void approve(const FString &spender, const FUInt64 &currentAmount,
               const FUInt64 &amount, const FApproveDelegate &delegate);
  void approve(const FString &spender, uint64 currentAmount, uint64 amount,
               TFunction<void(const FString &)> callback);
};