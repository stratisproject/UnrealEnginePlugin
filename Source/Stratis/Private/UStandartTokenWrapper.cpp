#include "UStandartTokenWrapper.h"

#include "SmartContracts.h"
#include "USmartContractsParametersEncoder.h"

UStandartTokenWrapper::UStandartTokenWrapper() {
  stratisManager =
      CreateDefaultSubobject<UStratisUnrealManager>(TEXT("StratisManager"));
}

UWorld *UStandartTokenWrapper::GetWorld() const {
  return GetOuter()->GetWorld();
}

void UStandartTokenWrapper::deployStandartToken(
    const FUInt64 &totalSupply, const FString &name, const FString &symbols,
    int64 decimals, const FDeployStandartTokenDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->deployStandartToken(
      (uint64)totalSupply, name, symbols, (uint32)decimals,
      [delegate, errorDelegate](const FString &transactionID) {
        delegate.ExecuteIfBound(transactionID);
      });
}

void UStandartTokenWrapper::deployStandartToken(
    uint64 totalSupply, const FString &name, const FString &symbols,
    uint32 decimals, TFunction<void(const FString &)> callback) {
  TArray<FString> parameters{
      USmartContractsParametersEncoder::encodeULong(totalSupply),
      USmartContractsParametersEncoder::encodeString(name),
      USmartContractsParametersEncoder::encodeString(symbols),
      USmartContractsParametersEncoder::encodeUInt(decimals)};

  this->stratisManager->sendCreateContractTransaction(
      FString(smart_contracts::StandartTokenContractCode), parameters, 0,
      [callback](const FString &transactionID) { callback(transactionID); });
}

void UStandartTokenWrapper::getSymbol(
    const FGetSymbolDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getSymbol([delegate, errorDelegate](const FString &symbol) {
    delegate.ExecuteIfBound(symbol);
  });
}

void UStandartTokenWrapper::getSymbol(
    TFunction<void(const FString &)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("Symbol");
  localCallData.sender = stratisManager->getAddress();

  this->stratisManager->makeLocalCall(
      localCallData,
      [callback](const FString &returnValue) { callback(returnValue); });
}

void UStandartTokenWrapper::getName(
    const FGetNameDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getName([delegate, errorDelegate](const FString &name) {
    delegate.ExecuteIfBound(name);
  });
}

void UStandartTokenWrapper::getName(TFunction<void(const FString &)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("Name");
  localCallData.sender = stratisManager->getAddress();

  this->stratisManager->makeLocalCall(
      localCallData,
      [callback](const FString &returnValue) { callback(returnValue); });
}

void UStandartTokenWrapper::getTotalSupply(
    const FGetTotalSupplyDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getTotalSupply([delegate, errorDelegate](uint64 totalSupply) {
    delegate.ExecuteIfBound(totalSupply);
  });
}

void UStandartTokenWrapper::getTotalSupply(TFunction<void(uint64)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("TotalSupply");
  localCallData.sender = stratisManager->getAddress();

  this->stratisManager->makeLocalCall(
      localCallData, [callback](const FString &returnValue) {
        callback(FCString::Strtoui64(*returnValue, nullptr, 10));
      });
}

void UStandartTokenWrapper::getDecimals(
    const FGetDecimalsDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getDecimals([delegate, errorDelegate](uint32 decimals) {
    delegate.ExecuteIfBound(decimals);
  });
}

void UStandartTokenWrapper::getDecimals(TFunction<void(uint32)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("GetDecimals");
  localCallData.sender = stratisManager->getAddress();

  this->stratisManager->makeLocalCall(
      localCallData, [callback](const FString &returnValue) {
        callback((uint32)FCString::Strtoui64(*returnValue, nullptr, 10));
      });
}

void UStandartTokenWrapper::getBalance(
    const FString &address, const FGetBalanceDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getBalance(address, [delegate, errorDelegate](uint64 balance) {
    delegate.ExecuteIfBound(balance);
  });
}

void UStandartTokenWrapper::getBalance(const FString &address,
                                       TFunction<void(uint64)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("GetBalance");
  localCallData.sender = stratisManager->getAddress();
  localCallData.parameters = {
      USmartContractsParametersEncoder::encodeAddress(address)};

  this->stratisManager->makeLocalCall(
      localCallData, [callback](const FString &returnValue) {
        callback(FCString::Strtoui64(*returnValue, nullptr, 10));
      });
}

void UStandartTokenWrapper::getAllowance(
    const FString &ownerAddress, const FString &spenderAddress,
    const FGetAllowanceDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getAllowance(ownerAddress, spenderAddress,
                     [delegate, errorDelegate](uint64 allowance) {
                       delegate.ExecuteIfBound(allowance);
                     });
}

void UStandartTokenWrapper::getAllowance(const FString &ownerAddress,
                                         const FString &spenderAddress,
                                         TFunction<void(uint64)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("Allowance");
  localCallData.sender = stratisManager->getAddress();
  localCallData.parameters = {
      USmartContractsParametersEncoder::encodeAddress(ownerAddress),
      USmartContractsParametersEncoder::encodeAddress(spenderAddress)};

  this->stratisManager->makeLocalCall(
      localCallData, [callback](const FString &returnValue) {
        callback(FCString::Strtoui64(*returnValue, nullptr, 10));
      });
}

void UStandartTokenWrapper::transferTo(
    const FString &address, const FUInt64 &amount,
    const FTransferToDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->transferTo(address, amount,
                   [delegate, errorDelegate](const FString &transactionID) {
                     delegate.ExecuteIfBound(transactionID);
                   });
}

void UStandartTokenWrapper::transferTo(
    const FString &address, uint64 amount,
    TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("TransferTo"),
      {USmartContractsParametersEncoder::encodeAddress(address),
       USmartContractsParametersEncoder::encodeULong(amount)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}

void UStandartTokenWrapper::transferFrom(
    const FString &fromAddress, const FString &toAddress, const FUInt64 &amount,
    const FTransferFromDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->transferFrom(fromAddress, toAddress, amount,
                     [delegate, errorDelegate](const FString &transactionID) {
                       delegate.ExecuteIfBound(transactionID);
                     });
}

void UStandartTokenWrapper::transferFrom(
    const FString &fromAddress, const FString &toAddress, uint64 amount,
    TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("TransferFrom"),
      {USmartContractsParametersEncoder::encodeAddress(fromAddress),
       USmartContractsParametersEncoder::encodeAddress(toAddress),
       USmartContractsParametersEncoder::encodeULong(amount)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}

void UStandartTokenWrapper::approve(
    const FString &spender, const FUInt64 &currentAmount, const FUInt64 &amount,
    const FApproveDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->approve(spender, currentAmount, amount,
                [delegate, errorDelegate](const FString &transactionID) {
                  delegate.ExecuteIfBound(transactionID);
                });
}

void UStandartTokenWrapper::approve(const FString &spender,
                                    uint64 currentAmount, uint64 amount,
                                    TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("Approve"),
      {USmartContractsParametersEncoder::encodeAddress(spender),
       USmartContractsParametersEncoder::encodeULong(currentAmount),
       USmartContractsParametersEncoder::encodeULong(amount)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}