// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Wrappers/UStandardTokenWrapper.h"

#include "USmartContractsParametersEncoder.h"
#include "WhitelistedSmartContracts.h"

UStandardTokenWrapper::UStandardTokenWrapper()
{
}

UStandardTokenWrapper* UStandardTokenWrapper::createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer)
{
    UStandardTokenWrapper* wrapper = NewObject<UStandardTokenWrapper>(outer);
    wrapper->stratisManager = manager;
    wrapper->contractAddress = contractAddress;

    return wrapper;
}

UStandardTokenWrapper* UStandardTokenWrapper::createDefaultInstance(UStratisUnrealManager* manager, UObject* outer)
{
    return UStandardTokenWrapper::createInstance(UWhitelistedSmartContracts::GetStandardTokenContractAddress(), manager, outer);
}

UWorld* UStandardTokenWrapper::GetWorld() const
{
    return GetOuter()->GetWorld();
}

void UStandardTokenWrapper::deployStandardToken(
    const FUInt256& totalSupply, const FString& name, const FString& symbols,
    uint8 decimals, const FDeployStandardToken256Delegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->deployStandardToken(
        totalSupply, name, symbols, decimals,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UStandardTokenWrapper::deployStandardToken(
    const FUInt256& totalSupply, const FString& name, const FString& symbols,
    uint8 decimals, TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeUInt256(totalSupply.value),
        USmartContractsParametersEncoder::encodeString(name),
        USmartContractsParametersEncoder::encodeString(symbols),
        USmartContractsParametersEncoder::encodeByte(decimals)};

    this->stratisManager->sendCreateContractTransaction(
        UWhitelistedSmartContracts::GetStandardTokenContractCode(), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UStandardTokenWrapper::getSymbol(
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

void UStandardTokenWrapper::getSymbol(
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

void UStandardTokenWrapper::getName(
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

void UStandardTokenWrapper::getName(
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

void UStandardTokenWrapper::getTotalSupply(
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

void UStandardTokenWrapper::getTotalSupply(
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

void UStandardTokenWrapper::getDecimals(
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

void UStandardTokenWrapper::getDecimals(
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

void UStandardTokenWrapper::getBalance(
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

void UStandardTokenWrapper::getBalance(
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

void UStandardTokenWrapper::getAllowance(
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

void UStandardTokenWrapper::getAllowance(
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
void UStandardTokenWrapper::transferTo(
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

void UStandardTokenWrapper::transferTo(
    const FString& address, const FUInt256& amount,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("TransferTo"),
        {USmartContractsParametersEncoder::encodeAddress(address),
         USmartContractsParametersEncoder::encodeUInt256(amount.value)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UStandardTokenWrapper::transferFrom(
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

void UStandardTokenWrapper::transferFrom(
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

void UStandardTokenWrapper::approve(
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

void UStandardTokenWrapper::approve(
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
