#include "Wrappers/UNFTWrapper.h"

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

UWorld* UNFTWrapper::GetWorld() const { return GetOuter()->GetWorld(); }

void UNFTWrapper::deployNFTContract(
    const FString& name, const FString& symbol, const FString& tokenURIFormat,
    bool ownerOnlyMinting, const FDeployNFTContractDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->deployNFTContract(
        name, symbol, tokenURIFormat, ownerOnlyMinting,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::deployNFTContract(
    const FString& name, const FString& symbol, const FString& tokenURIFormat,
    bool ownerOnlyMinting, TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeString(name),
        USmartContractsParametersEncoder::encodeString(symbol),
        USmartContractsParametersEncoder::encodeString(tokenURIFormat),
        USmartContractsParametersEncoder::encodeBoolean(ownerOnlyMinting)};

    this->stratisManager->sendCreateContractTransaction(
        UWhitelistedSmartContracts::GetNFTContractCode(), parameters, 0,
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
        address, [delegate, errorDelegate](const TResult<uint64>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getBalanceOf(
    const FString& address, TFunction<void(const TResult<uint64>&)> callback)
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
            callback(result::transformValue<FString, uint64>(
                result, [](const FString& value) {
                    return FCString::Strtoui64(*value, nullptr, 10);
                }));
        });
}

void UNFTWrapper::getOwnerOf(const FUInt64& tokenID,
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
    uint64 tokenID, TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("OwnerOf");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeULong(tokenID)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getApproved(const FUInt64& tokenID,
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
    uint64 tokenID, TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("GetApproved");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeULong(tokenID)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::getApprovedForAll(
    const FString& ownderAddress, const FString& operatorAddress,
    const FNFTGetApprovedForAllDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->getApprovedForAll(
        ownderAddress, operatorAddress,
        [delegate, errorDelegate](const TResult<bool>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::getApprovedForAll(
    const FString& ownderAddress, const FString& operatorAddress,
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
        USmartContractsParametersEncoder::encodeAddress(ownderAddress),
        USmartContractsParametersEncoder::encodeAddress(operatorAddress)};

    this->stratisManager->makeLocalCall(
        localCallData, [callback](const TResult<FString>& result) {
            callback(result::transformValue<FString, bool>(
                result,
                [](const FString& value) { return value.Equals(TEXT("true")); }));
        });
}

void UNFTWrapper::getTokenURI(const FUInt64& tokenID,
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
    uint64 tokenID, TFunction<void(const TResult<FString>&)> callback)
{
    FLocalCallData localCallData;
    localCallData.gasPrice = 10000;
    localCallData.gasLimit = 250000;
    localCallData.amount = 0;
    localCallData.contractAddress = this->contractAddress;
    localCallData.methodName = TEXT("TokenURI");
    localCallData.sender = stratisManager->getAddress();
    localCallData.parameters = {
        USmartContractsParametersEncoder::encodeULong(tokenID)};

    this->stratisManager->makeLocalCall(
        localCallData,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::safeTransferFrom(
    const FString& fromAddress, const FString& toAddress,
    const FUInt64& tokenID, TArray<uint8> data,
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
    const FString& fromAddress, const FString& toAddress, uint64 tokenID,
    TArray<uint8> data, TFunction<void(const TResult<FString>&)> callback)
{
    TArray<FString> parameters{
        USmartContractsParametersEncoder::encodeAddress(fromAddress),
        USmartContractsParametersEncoder::encodeAddress(toAddress),
        USmartContractsParametersEncoder::encodeULong(tokenID)};

    if (data.Num() > 0) {
        parameters.Add(USmartContractsParametersEncoder::encodeByteArray(data));
    }

    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SafeTransferFrom"), parameters, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::transferFrom(const FString& fromAddress,
                               const FString& toAddress, const FUInt64& tokenID,
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
    const FString& fromAddress, const FString& toAddress, uint64 tokenID,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("TransferFrom"),
        {USmartContractsParametersEncoder::encodeAddress(fromAddress),
         USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeULong(tokenID)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::approve(const FString& address, const FUInt64& tokenID,
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

void UNFTWrapper::approve(const FString& address, uint64 tokenID,
                          TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Approve"),
        {USmartContractsParametersEncoder::encodeAddress(address),
         USmartContractsParametersEncoder::encodeULong(tokenID)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::setApprovalForAll(
    const FString& address, const FUInt64& tokenID,
    const FNFTSetApprovalForAllDelegate& delegate,
    const FErrorReceivedDelegate& errorDelegate)
{
    this->setApprovalForAll(
        address, tokenID,
        [delegate, errorDelegate](const TResult<FString>& result) {
            if (result::isSuccessful(result))
                delegate.ExecuteIfBound(result::getValue(result));
            else
                errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
        });
}

void UNFTWrapper::setApprovalForAll(
    const FString& address, uint64 tokenID,
    TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SetApprovalForAll"),
        {USmartContractsParametersEncoder::encodeAddress(address),
         USmartContractsParametersEncoder::encodeULong(tokenID)},
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
                       const FNFTMintDelegate& delegate,
                       const FErrorReceivedDelegate& errorDelegate)
{
    this->mint(toAddress,
               [delegate, errorDelegate](const TResult<FString>& result) {
                   if (result::isSuccessful(result))
                       delegate.ExecuteIfBound(result::getValue(result));
                   else
                       errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
               });
}

void UNFTWrapper::mint(const FString& toAddress,
                       TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Mint"),
        {USmartContractsParametersEncoder::encodeAddress(toAddress)}, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::safeMint(const FString& toAddress, const TArray<uint8>& data,
                           const FNFTSafeMintDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate)
{
    this->safeMint(toAddress, data,
                   [delegate, errorDelegate](const TResult<FString>& result) {
                       if (result::isSuccessful(result))
                           delegate.ExecuteIfBound(result::getValue(result));
                       else
                           errorDelegate.ExecuteIfBound(
                               result::getErrorMessage(result));
                   });
}

void UNFTWrapper::safeMint(const FString& toAddress, const TArray<uint8>& data,
                           TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("SafeMint"),
        {USmartContractsParametersEncoder::encodeAddress(toAddress),
         USmartContractsParametersEncoder::encodeByteArray(data)},
        0, [callback](const TResult<FString>& result) { callback(result); });
}

void UNFTWrapper::burn(const FUInt64& tokenID,
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

void UNFTWrapper::burn(uint64 tokenID,
                       TFunction<void(const TResult<FString>&)> callback)
{
    this->stratisManager->sendCallContractTransaction(
        this->contractAddress, TEXT("Burn"),
        {USmartContractsParametersEncoder::encodeULong(tokenID)}, 0,
        [callback](const TResult<FString>& result) { callback(result); });
}
