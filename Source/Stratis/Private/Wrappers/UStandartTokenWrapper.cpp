// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Wrappers/UStandartTokenWrapper.h"

#include "USmartContractsParametersEncoder.h"
#include "WhitelistedSmartContracts.h"

UStandartTokenWrapper::UStandartTokenWrapper()
{
}

UStandartTokenWrapper* UStandartTokenWrapper::createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer)
{
    UStandartTokenWrapper* wrapper = NewObject<UStandartTokenWrapper>(outer);
    wrapper->stratisManager = manager;
    wrapper->contractAddress = contractAddress;

    return wrapper;
}

UStandartTokenWrapper* UStandartTokenWrapper::createDefaultInstance(UStratisUnrealManager* manager, UObject* outer)
{
    return UStandartTokenWrapper::createInstance(UWhitelistedSmartContracts::GetStandartTokenContractAddress, manager, outer);
}

UWorld* UStandartTokenWrapper::GetWorld() const
{
    return GetOuter()->GetWorld();
}

void UStandartTokenWrapper::deployStandartToken(
    const FUInt256& totalSupply, const FString& name, const FString& symbols,
    uint8 decimals, const FDeployStandartToken256Delegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->deployStandartToken(
        totalSupply, name, symbols, decimals,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UStandartTokenWrapper::deployStandartToken(
    const FUInt256& totalSupply, const FString& name, const FString& symbols,
    uint8 decimals, TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeUInt256(totalSupply.value),
        USmartContractsParametersEncoder::encodeString(name),
        USmartContractsParametersEncoder::encodeString(symbols),
        USmartContractsParametersEncoder::encodeByte(decimals)};

    this->stratisManager->sendCreateContractTransaction(
        UWhitelistedSmartContracts::GetStandartTokenContractCode(), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UStandartTokenWrapper::getSymbol(
    const FSTGetSymbolDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getSymbol([delegate, errorDelegate](const TResult<FString>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UStandartTokenWrapper::getSymbol(
    TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("Symbol");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& returnValue) {
            callback(returnValue);
        });
}

void UStandartTokenWrapper::getName(
    const FSTGetNameDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getName([delegate, errorDelegate](const TResult<FString>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UStandartTokenWrapper::getName(
    TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("Name");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& returnValue) {
            callback(returnValue);
        });
}

void UStandartTokenWrapper::getTotalSupply(
    const FSTGetTotalSupplyDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getTotalSupply(
        [delegate, errorDelegate](const TResult<FUInt256>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UStandartTokenWrapper::getTotalSupply(
    TFunction<void(const TResult<FUInt256>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("TotalSupply");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, FUInt256>(
                result, [](const FString& returnValue) {
                    return FUInt256(returnValue);
                }));
        });
}

void UStandartTokenWrapper::getDecimals(
    const FSTGetDecimalsDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getDecimals([delegate, errorDelegate](const TResult<uint8>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UStandartTokenWrapper::getDecimals(
    TFunction<void(const TResult<uint8>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("GetDecimals");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, uint8>(
                result, [](const FString& returnValue) {
                    return (uint8)FCString::Strtoi(*returnValue, nullptr, 10);
                }));
        });
}

void UStandartTokenWrapper::getBalance(
    const FString& address, const FSTGetBalanceDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getBalance(
        address, [delegate, errorDelegate](const TResult<FUInt256>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UStandartTokenWrapper::getBalance(
    const FString& address, TFunction<void(const TResult<FUInt256>&)> callback)
{
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
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, FUInt256>(
                result, [](const FString& returnValue) {
                    return FUInt256(returnValue);
                }));
        });
}

void UStandartTokenWrapper::getAllowance(
    const FString& ownerAddress, const FString& spenderAddress,
    const FSTGetAllowanceDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getAllowance(ownerAddress, spenderAddress,
                       [delegate, errorDelegate](const TResult<FUInt256>& result) {
                           if (result::isSuccessful(result))
                               delegate.ExecuteIfBound(result::getValue(result));
                           else
                               errorDelegate.ExecuteIfBound(
                                   result::getErrorMessage(result));
                       });
}

void UStandartTokenWrapper::getAllowance(
    const FString& ownerAddress, const FString& spenderAddress,
    TFunction<void(const TResult<FUInt256>&)> callback)
{
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
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, FUInt256>(
                result, [](const FString& returnValue) {
                    return FUInt256(returnValue);
                }));
        });
}
void UStandartTokenWrapper::transferTo(
    const FString& address, const FUInt256& amount,
    const FSTTransferToDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->transferTo(address, amount,
                     [delegate, errorDelegate](const TResult<FString>& result) {
                         if (result::isSuccessful(result))
                             delegate.ExecuteIfBound(result::getValue(result));
                         else
                             errorDelegate.ExecuteIfBound(
                                 result::getErrorMessage(result));
                     });
}

void UStandartTokenWrapper::transferTo(
    const FString& address, const FUInt256& amount,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("TransferTo"),
        {USmartContractsParametersEncoder::encodeAddress(address),
         USmartContractsParametersEncoder::encodeUInt256(amount.value)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UStandartTokenWrapper::transferFrom(
    const FString& fromAddress, const FString& toAddress, const FUInt256& amount,
    const FSTTransferFromDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->transferFrom(fromAddress, toAddress, amount,
                       [delegate, errorDelegate](const TResult<FString>& result) {
                           if (result::isSuccessful(result))
                               delegate.ExecuteIfBound(result::getValue(result));
                           else
                               errorDelegate.ExecuteIfBound(
                                   result::getErrorMessage(result));
                       });
}

void UStandartTokenWrapper::transferFrom(
    const FString& fromAddress, const FString& toAddress, const FUInt256& amount,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("TransferFrom"),
        {USmartContractsParametersEncoder::encodeAddress(fromAddress),
         USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeUInt256(amount.value)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UStandartTokenWrapper::approve(
    const FString& spender, const FUInt256& currentAmount, const FUInt256& amount,
    const FSTApproveDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->approve(spender, currentAmount, amount,
                  [delegate, errorDelegate](const TResult<FString>& result) {
                      if (result::isSuccessful(result))
                          delegate.ExecuteIfBound(result::getValue(result));
                      else
                          errorDelegate.ExecuteIfBound(
                              result::getErrorMessage(result));
                  });
}

void UStandartTokenWrapper::approve(
    const FString& spender, const FUInt256& currentAmount, const FUInt256& amount,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Approve"),
        {USmartContractsParametersEncoder::encodeAddress(spender),
         USmartContractsParametersEncoder::encodeUInt256(currentAmount.value),
         USmartContractsParametersEncoder::encodeUInt256(amount.value)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}
