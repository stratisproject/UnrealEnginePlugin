// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Wrappers/UNFTWrapper.h"

#include "Serialization/JsonSerializer.h"
#include "USmartContractsParametersEncoder.h"
#include "WhitelistedSmartContracts.h"

UNFTWrapper::UNFTWrapper()
{
}

UNFTWrapper* UNFTWrapper::createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer)
{
    UNFTWrapper* wrapper = NewObject<UNFTWrapper>(outer);
    wrapper->stratisManager = manager;
    wrapper->contractAddress = contractAddress;

    return wrapper;
}

UNFTWrapper* UNFTWrapper::createDefaultInstance(UStratisUnrealManager* manager, UObject* outer)
{
    return UNFTWrapper::createInstance(UWhitelistedSmartContracts::NFTContractAddress, manager, outer);
}

UNFTWrapper* UNFTWrapper::createDefaultManualIdInstance(UStratisUnrealManager* manager, UObject* outer)
{
    return UNFTWrapper::createInstance(UWhitelistedSmartContracts::ManualIdNFTContractAddress, manager, outer);
}

UNFTWrapper* UNFTWrapper::createDefaultRoyaltyInstance(UStratisUnrealManager* manager, UObject* outer)
{
    return UNFTWrapper::createInstance(UWhitelistedSmartContracts::RoyaltyNFTContractAddress, manager, outer);
}

UWorld* UNFTWrapper::GetWorld() const { return GetOuter()->GetWorld(); }

void UNFTWrapper::deployNFTContract(
    const FString& name, const FString& symbol,
    bool ownerOnlyMinting, const FDeployNFTContractDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->deployNFTContract(
        name, symbol, ownerOnlyMinting,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::deployNFTContract(
    const FString& name, const FString& symbol,
    bool ownerOnlyMinting, TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeString(name),
        USmartContractsParametersEncoder::encodeString(symbol),
        USmartContractsParametersEncoder::encodeBoolean(ownerOnlyMinting)};

    this->stratisManager->sendCreateContractTransaction(
        UWhitelistedSmartContracts::GetNFTContractCode(), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::deployManualIdNFTContract(const FString& name,
                                            const FString& symbol,
                                            bool ownerOnlyMinting,
                                            const FDeployNFTContractDelegate& delegate,
                                            const FErrorReceivedDelegate& errorDelegate)
{
    this->deployManualIdNFTContract(
        name, symbol, ownerOnlyMinting,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::deployManualIdNFTContract(const FString& name, const FString& symbol,
                                            bool ownerOnlyMinting,
                                            TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeString(name),
        USmartContractsParametersEncoder::encodeString(symbol),
        USmartContractsParametersEncoder::encodeBoolean(ownerOnlyMinting)};

    this->stratisManager->sendCreateContractTransaction(
        UWhitelistedSmartContracts::GetManualIdNFTContractCode(), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::deployRoyaltyNFTContract(const FString& name,
                                           const FString& symbol,
                                           bool ownerOnlyMinting,
                                           const FString& royaltyRecipient,
                                           int32 royaltyPercent,
                                           const FDeployNFTContractDelegate& delegate,
                                           const FErrorReceivedDelegate& errorDelegate)
{
    this->deployRoyaltyNFTContract(
        name, symbol, ownerOnlyMinting, royaltyRecipient, royaltyPercent,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::deployRoyaltyNFTContract(const FString& name,
                                           const FString& symbol,
                                           bool ownerOnlyMinting,
                                           const FString& royaltyRecipient,
                                           uint32 royaltyPercent,
                                           TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeString(name),
        USmartContractsParametersEncoder::encodeString(symbol),
        USmartContractsParametersEncoder::encodeBoolean(ownerOnlyMinting),
        USmartContractsParametersEncoder::encodeAddress(royaltyRecipient),
        USmartContractsParametersEncoder::encodeUInt(royaltyPercent)};

    this->stratisManager->sendCreateContractTransaction(
        UWhitelistedSmartContracts::GetRoyaltyNFTContractCode(), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getOwner(const FNFTGetOwnerDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate)
{
    this->getOwner([delegate, errorDelegate](const TResult<FString>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UNFTWrapper::getOwner(TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("Owner");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getPendingOwner(const FNFTGetOwnerDelegate& delegate,
                                  const FErrorReceivedDelegate& errorDelegate)
{
    this->getPendingOwner([delegate, errorDelegate](const TResult<FString>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UNFTWrapper::getPendingOwner(TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("PendingOwner");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getName(const FNFTGetNameDelegate& delegate,
                          const FErrorReceivedDelegate& errorDelegate)
{
    this->getName([delegate, errorDelegate](const TResult<FString>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UNFTWrapper::getName(TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("Name");
    localCallData.sender = stratisManager->getAddress();

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getSymbol(const FNFTGetSymbolDelegate& delegate,
                            const FErrorReceivedDelegate& errorDelegate)
{
    this->getSymbol([delegate, errorDelegate](const TResult<FString>& result) {
        if (result::isSuccessful(result))
            delegate.ExecuteIfBound(result::getValue(result));
        else
            errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
    });
}

void UNFTWrapper::getSymbol(
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
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::supportsInterface(
    int64 interfaceID, const FNFTSupportsInterfaceDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->supportsInterface(
        interfaceID, [delegate, errorDelegate](const TResult<bool>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::supportsInterface(
    uint32 interfaceID, TFunction<void(const TResult<bool>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("SupportsInterface");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeUInt(interfaceID)};

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, bool>(
                result,
                [](const FString& value) { return value.Equals(TEXT("true")); }));
        });
}

void UNFTWrapper::getBalanceOf(const FString& address,
                               const FNFTGetBalanceOfDelegate& delegate,
                               const FErrorReceivedDelegate& errorDelegate)
{
    this->getBalanceOf(
        address, [delegate, errorDelegate](const TResult<FUInt256>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getBalanceOf(
    const FString& address, TFunction<void(const TResult<FUInt256>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("BalanceOf");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeAddress(address)};

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, FUInt256>(
                result, [](const FString& value) {
                    return value;
                }));
        });
}

void UNFTWrapper::getOwnerOf(const FUInt256& tokenID,
                             const FNFTGetOwnerOfDelegate& delegate,
                             const FErrorReceivedDelegate& errorDelegate)
{
    this->getOwnerOf(
        tokenID, [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getOwnerOf(
    const FUInt256& tokenID, TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("OwnerOf");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeUInt256(tokenID.value)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getApproved(const FUInt256& tokenID,
                              const FNFTGetApprovedDelegate& delegate,
                              const FErrorReceivedDelegate& errorDelegate)
{
    this->getApproved(
        tokenID, [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getApproved(
    const FUInt256& tokenID, TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("GetApproved");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeUInt256(tokenID.value)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getApprovedForAll(
    const FString& ownerAddress, const FString& operatorAddress,
    const FNFTGetApprovedForAllDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getApprovedForAll(
        ownerAddress, operatorAddress,
        [delegate, errorDelegate](const TResult<bool>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getApprovedForAll(
    const FString& ownerAddress, const FString& operatorAddress,
    TFunction<void(const TResult<bool>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("IsApprovedForAll");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeAddress(ownerAddress),
        USmartContractsParametersEncoder::encodeAddress(operatorAddress)};

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, bool>(
                result,
                [](const FString& value) { return value.Equals(TEXT("true")); }));
        });
}

void UNFTWrapper::getTokenURI(const FUInt256& tokenID,
                              const FNFTGetTokenURIDelegate& delegate,
                              const FErrorReceivedDelegate& errorDelegate)
{
    this->getTokenURI(
        tokenID, [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getTokenURI(
    const FUInt256& tokenID, TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("TokenURI");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeUInt256(tokenID.value)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::safeTransferFrom(
    const FString& fromAddress, const FString& toAddress,
    const FUInt256& tokenID, TArray<uint8> data,
    const FNFTSafeTransferFromDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->safeTransferFrom(
        fromAddress, toAddress, tokenID, data,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::safeTransferFrom(
    const FString& fromAddress, const FString& toAddress, const FUInt256& tokenID,
    TArray<uint8> data, TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeAddress(fromAddress),
        USmartContractsParametersEncoder::encodeAddress(toAddress),
        USmartContractsParametersEncoder::encodeUInt256(tokenID.value)};

    if (data.Num() > 0) {
        parameters.Add(USmartContractsParametersEncoder::encodeByteArray(data));
    }

    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SafeTransferFrom"), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::transferFrom(const FString& fromAddress,
                               const FString& toAddress, const FUInt256& tokenID,
                               const FNFTTransferFromDelegate& delegate,
                               const FErrorReceivedDelegate& errorDelegate)
{
    this->transferFrom(fromAddress, toAddress, tokenID,
                       [delegate, errorDelegate](const TResult<FString>& result) {
                           if (result::isSuccessful(result))
                               delegate.ExecuteIfBound(result::getValue(result));
                           else
                               errorDelegate.ExecuteIfBound(
                                   result::getErrorMessage(result));
                       });
}

void UNFTWrapper::transferFrom(
    const FString& fromAddress, const FString& toAddress, const FUInt256& tokenID,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("TransferFrom"),
        {USmartContractsParametersEncoder::encodeAddress(fromAddress),
         USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeUInt256(tokenID.value)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::approve(const FString& address, const FUInt256& tokenID,
                          const FNFTApproveDelegate& delegate,
                          const FErrorReceivedDelegate& errorDelegate)
{
    this->approve(address, tokenID,
                  [delegate, errorDelegate](const TResult<FString>& result) {
                      if (result::isSuccessful(result))
                          delegate.ExecuteIfBound(result::getValue(result));
                      else
                          errorDelegate.ExecuteIfBound(
                              result::getErrorMessage(result));
                  });
}

void UNFTWrapper::approve(const FString& address, const FUInt256& tokenID,
                          TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Approve"),
        {USmartContractsParametersEncoder::encodeAddress(address),
         USmartContractsParametersEncoder::encodeUInt256(tokenID.value)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::setApprovalForAll(
    const FString& address, bool approval,
    const FNFTSetApprovalForAllDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->setApprovalForAll(
        address, approval,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::setApprovalForAll(
    const FString& address, bool approval,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SetApprovalForAll"),
        {USmartContractsParametersEncoder::encodeAddress(address),
         USmartContractsParametersEncoder::encodeBoolean(approval)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::transferOwnership(
    const FString& address, const FNFTTransferOwnershipDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->transferOwnership(
        address, [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::transferOwnership(
    const FString& address,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("TransferOwnership"),
        {USmartContractsParametersEncoder::encodeAddress(address)}, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::mint(const FString& toAddress,
                       const FString& metadataUri,
                       const FNFTMintDelegate& delegate,
                       const FErrorReceivedDelegate& errorDelegate)
{
    this->mint(
        toAddress, metadataUri,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::mint(const FString& toAddress,
                       const FString& metadataUri,
                       TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Mint"),
        {USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeString(metadataUri)},
        0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::safeMint(const FString& toAddress,
                           const FString& metadataUri,
                           const TArray<uint8>& data,
                           const FNFTSafeMintDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate)
{
    this->safeMint(toAddress, metadataUri, data,
                   [delegate, errorDelegate](const TResult<FString>& result) {
                       if (result::isSuccessful(result))
                           delegate.ExecuteIfBound(result::getValue(result));
                       else
                           errorDelegate.ExecuteIfBound(
                               result::getErrorMessage(result));
                   });
}

void UNFTWrapper::safeMint(const FString& toAddress,
                           const FString& metadataUri,
                           const TArray<uint8>& data,
                           TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SafeMint"),
        {USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeString(metadataUri),
         USmartContractsParametersEncoder::encodeByteArray(data)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::mintWithManualID(const FString& toAddress,
                                   const FUInt256& tokenID,
                                   const FString& metadataUri,
                                   const FNFTMintDelegate& delegate,
                                   const FErrorReceivedDelegate& errorDelegate)
{
    this->mintWithManualID(toAddress, tokenID, metadataUri,
                           [delegate, errorDelegate](const TResult<FString>& result) {
                               if (result::isSuccessful(result))
                                   delegate.ExecuteIfBound(result::getValue(result));
                               else
                                   errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
                           });
}

void UNFTWrapper::mintWithManualID(const FString& toAddress,
                                   const FUInt256& tokenID,
                                   const FString& metadataUri,
                                   TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Mint"),
        {USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeUInt256(tokenID.value),
         USmartContractsParametersEncoder::encodeString(metadataUri)},
        0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::safeMintWithManualID(const FString& toAddress,
                                       const FUInt256& tokenID,
                                       const FString& metadataUri,
                                       const TArray<uint8>& data,
                                       const FNFTSafeMintDelegate& delegate,
                                       const FErrorReceivedDelegate& errorDelegate)
{
    this->safeMintWithManualID(toAddress, tokenID, metadataUri, data,
                               [delegate, errorDelegate](const TResult<FString>& result) {
                                   if (result::isSuccessful(result))
                                       delegate.ExecuteIfBound(result::getValue(result));
                                   else
                                       errorDelegate.ExecuteIfBound(
                                           result::getErrorMessage(result));
                               });
}

void UNFTWrapper::safeMintWithManualID(const FString& toAddress,
                                       const FUInt256& tokenID,
                                       const FString& metadataUri,
                                       const TArray<uint8>& data,
                                       TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SafeMint"),
        {USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeUInt256(tokenID.value),
         USmartContractsParametersEncoder::encodeString(metadataUri),
         USmartContractsParametersEncoder::encodeByteArray(data)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::burn(const FUInt256& tokenID,
                       const FNFTSafeMintDelegate& delegate,
                       const FErrorReceivedDelegate& errorDelegate)
{
    this->burn(tokenID,
               [delegate, errorDelegate](const TResult<FString>& result) {
                   if (result::isSuccessful(result))
                       delegate.ExecuteIfBound(result::getValue(result));
                   else
                       errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
               });
}

void UNFTWrapper::burn(const FUInt256& tokenID,
                       TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Burn"),
        {USmartContractsParametersEncoder::encodeUInt256(tokenID.value)}, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::claimOwnership(const FNFTClaimOwnershipDelegate& delegate,
                                 const FErrorReceivedDelegate& errorDelegate)
{
    this->claimOwnership(
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::claimOwnership(TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("ClaimOwnership"),
        {}, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::setPendingOwner(const FString& newOwner,
                                  const FNFTSetPendingOwnerDelegate& delegate,
                                  const FErrorReceivedDelegate& errorDelegate)
{
    this->setPendingOwner(
        newOwner,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::setPendingOwner(const FString& newOwner, TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SetPendingOwner"),
        {USmartContractsParametersEncoder::encodeAddress(newOwner)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::royaltyInfo(const FUInt64& salePrice,
                              const FNFTGetRoyaltyInfoDelegate& delegate,
                              const FErrorReceivedDelegate& errorDelegate)
{
    this->royaltyInfo(
        salePrice,
        [delegate, errorDelegate](const TResult<FRoyaltyInfo>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::royaltyInfo(uint64 salePrice, TFunction<void(const TResult<FRoyaltyInfo>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("RoyaltyInfo");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeUInt256(TEXT("0")),
        USmartContractsParametersEncoder::encodeULong(salePrice)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) {
            callback(result::transform<FString, FRoyaltyInfo>(result, [](const FString& value) {
                TSharedPtr<FJsonValue> JsonValue;
                auto Reader = TJsonReaderFactory<>::Create(value);

                if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid()) {
                    const TArray<TSharedPtr<FJsonValue>>* JsonArray;
                    if (!JsonValue->TryGetArray(JsonArray))
                        return result::error<FRoyaltyInfo>(TError(TEXT("JSON is invalid.")));

                    bool ParseSuccess = true;

                    FString royaltyRecipient;
                    uint64 royaltyAmount;

                    ParseSuccess &= ((*JsonArray)[0])->TryGetString(royaltyRecipient);
                    ParseSuccess &= ((*JsonArray)[1])->TryGetNumber(royaltyAmount);

                    if (ParseSuccess)
                        return result::ok<FRoyaltyInfo>(FRoyaltyInfo{royaltyRecipient, royaltyAmount});
                    else
                        return result::error<FRoyaltyInfo>(TError(TEXT("JSON is invalid.")));
                } else {
                    return result::error<FRoyaltyInfo>(TError(TEXT("JSON is invalid.")));
                }
            }));
        });
}
