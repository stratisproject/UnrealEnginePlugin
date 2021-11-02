#include "UNFTWrapper.h"

#include "SmartContracts.h"
#include "USmartContractsParametersEncoder.h"

UNFTWrapper::UNFTWrapper() {
  stratisManager = NewObject<UStratisUnrealManager>();
}

void UNFTWrapper::deployNFTContract(
    const FString &name, const FString &symbol, const FString &tokenURIFormat,
    bool ownerOnlyMinting, const FDeployNFTContractDelegate &delegate) {
  this->deployNFTContract(name, symbol, tokenURIFormat, ownerOnlyMinting,
                          [&delegate](const FString &transactionID) {
                            delegate.ExecuteIfBound(transactionID);
                          });
}

void UNFTWrapper::deployNFTContract(const FString &name, const FString &symbol,
                                    const FString &tokenURIFormat,
                                    bool ownerOnlyMinting,
                                    TFunction<void(const FString &)> callback) {
  TArray<FString> parameters{
      USmartContractsParametersEncoder::encodeString(name),
      USmartContractsParametersEncoder::encodeString(symbol),
      USmartContractsParametersEncoder::encodeString(tokenURIFormat),
      USmartContractsParametersEncoder::encodeBoolean(ownerOnlyMinting)};

  this->stratisManager->sendCreateContractTransaction(
      FString(smart_contracts::NFTContractCode), parameters, 0,
      [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::getOwner(const FNFTGetOwnerDelegate &delegate) {
  this->getOwner(
      [&delegate](const FString &symbol) { delegate.ExecuteIfBound(symbol); });
}

void UNFTWrapper::getOwner(TFunction<void(const FString &)> callback) {
  FLocalCallData localCallData;
  localCallData.gasPrice = 10000;
  localCallData.gasLimit = 250000;
  localCallData.amount = 0;
  localCallData.contractAddress = this->contractAddress;
  localCallData.methodName = TEXT("Owner");
  localCallData.sender = stratisManager->getAddress();

  this->stratisManager->makeLocalCall(
      localCallData,
      [callback](const FString &returnValue) { callback(returnValue); });
}

void UNFTWrapper::getName(const FNFTGetNameDelegate &delegate) {
  this->getName(
      [&delegate](const FString &name) { delegate.ExecuteIfBound(name); });
}

void UNFTWrapper::getName(TFunction<void(const FString &)> callback) {
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

void UNFTWrapper::getSymbol(const FNFTGetSymbolDelegate &delegate) {
  this->getSymbol(
      [&delegate](const FString &symbol) { delegate.ExecuteIfBound(symbol); });
}

void UNFTWrapper::getSymbol(TFunction<void(const FString &)> callback) {
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

void UNFTWrapper::supportsInterface(
    int64 interfaceID, const FNFTSupportsInterfaceDelegate &delegate) {
  this->supportsInterface(interfaceID, [&delegate](bool supports) {
    delegate.ExecuteIfBound(supports);
  });
}

void UNFTWrapper::supportsInterface(uint32 interfaceID,
                                    TFunction<void(bool)> callback) {
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
      localCallData, [callback](const FString &returnValue) {
        callback(returnValue.Equals(TEXT("true")));
      });
}

void UNFTWrapper::getBalanceOf(const FString &address,
                               const FNFTGetBalanceOfDelegate &delegate) {
  this->getBalanceOf(address, [&delegate](uint64 balance) {
    delegate.ExecuteIfBound(balance);
  });
}

void UNFTWrapper::getBalanceOf(const FString &address,
                               TFunction<void(uint64)> callback) {
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
      localCallData, [callback](const FString &returnValue) {
        callback(FCString::Strtoui64(*returnValue, nullptr, 10));
      });
}

void UNFTWrapper::getOwnerOf(const FUInt64 &tokenID,
                             const FNFTGetOwnerOfDelegate &delegate) {
  this->getOwnerOf(tokenID, [&delegate](const FString &owner) {
    delegate.ExecuteIfBound(owner);
  });
}

void UNFTWrapper::getOwnerOf(uint64 tokenID,
                             TFunction<void(const FString &)> callback) {
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
      [callback](const FString &returnValue) { callback(returnValue); });
}

void UNFTWrapper::getApproved(const FUInt64 &tokenID,
                              const FNFTGetApprovedDelegate &delegate) {
  this->getApproved(tokenID, [&delegate](const FString &approved) {
    delegate.ExecuteIfBound(approved);
  });
}

void UNFTWrapper::getApproved(uint64 tokenID,
                              TFunction<void(const FString &)> callback) {
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
      [callback](const FString &returnValue) { callback(returnValue); });
}

void UNFTWrapper::getApprovedForAll(
    const FString &ownderAddress, const FString &operatorAddress,
    const FNFTGetApprovedForAllDelegate &delegate) {
  this->getApprovedForAll(
      ownderAddress, operatorAddress,
      [&delegate](bool approved) { delegate.ExecuteIfBound(approved); });
}

void UNFTWrapper::getApprovedForAll(const FString &ownderAddress,
                                    const FString &operatorAddress,
                                    TFunction<void(bool)> callback) {
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
      localCallData, [callback](const FString &returnValue) {
        callback(returnValue.Equals(TEXT("true")));
      });
}

void UNFTWrapper::getTokenURI(const FUInt64 &tokenID,
                              const FNFTGetTokenURIDelegate &delegate) {
  this->getTokenURI(tokenID, [&delegate](const FString &approved) {
    delegate.ExecuteIfBound(approved);
  });
}

void UNFTWrapper::getTokenURI(uint64 tokenID,
                              TFunction<void(const FString &)> callback) {
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
      [callback](const FString &returnValue) { callback(returnValue); });
}

void UNFTWrapper::safeTransferFrom(
    const FString &fromAddress, const FString &toAddress,
    const FUInt64 &tokenID, TArray<uint8> data,
    const FNFTSafeTransferFromDelegate &delegate) {
  this->safeTransferFrom(fromAddress, toAddress, tokenID, data,
                         [&delegate](const FString &transactionID) {
                           delegate.ExecuteIfBound(transactionID);
                         });
}

void UNFTWrapper::safeTransferFrom(const FString &fromAddress,
                                   const FString &toAddress, uint64 tokenID,
                                   TArray<uint8> data,
                                   TFunction<void(const FString &)> callback) {
  TArray<FString> parameters{
      USmartContractsParametersEncoder::encodeAddress(fromAddress),
      USmartContractsParametersEncoder::encodeAddress(toAddress),
      USmartContractsParametersEncoder::encodeULong(tokenID)};

  if (data.Num() > 0) {
    parameters.Add(USmartContractsParametersEncoder::encodeByteArray(data));
  }

  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("SafeTransferFrom"), parameters, 0,
      [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::transferFrom(const FString &fromAddress,
                               const FString &toAddress, const FUInt64 &tokenID,
                               const FNFTTransferFromDelegate &delegate) {
  this->transferFrom(fromAddress, toAddress, tokenID,
                     [&delegate](const FString &transactionID) {
                       delegate.ExecuteIfBound(transactionID);
                     });
}

void UNFTWrapper::transferFrom(const FString &fromAddress,
                               const FString &toAddress, uint64 tokenID,
                               TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("TransferFrom"),
      {USmartContractsParametersEncoder::encodeAddress(fromAddress),
       USmartContractsParametersEncoder::encodeAddress(toAddress),
       USmartContractsParametersEncoder::encodeULong(tokenID)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::approve(const FString &address, const FUInt64 &tokenID,
                          const FNFTApproveDelegate &delegate) {
  this->approve(address, tokenID, [&delegate](const FString &transactionID) {
    delegate.ExecuteIfBound(transactionID);
  });
}

void UNFTWrapper::approve(const FString &address, uint64 tokenID,
                          TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("Approve"),
      {USmartContractsParametersEncoder::encodeAddress(address),
       USmartContractsParametersEncoder::encodeULong(tokenID)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::setApprovalForAll(
    const FString &address, const FUInt64 &tokenID,
    const FNFTSetApprovalForAllDelegate &delegate) {
  this->setApprovalForAll(address, tokenID,
                          [&delegate](const FString &transactionID) {
                            delegate.ExecuteIfBound(transactionID);
                          });
}

void UNFTWrapper::setApprovalForAll(const FString &address, uint64 tokenID,
                                    TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("SetApprovalForAll"),
      {USmartContractsParametersEncoder::encodeAddress(address),
       USmartContractsParametersEncoder::encodeULong(tokenID)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::transferOwnership(
    const FString &address, const FNFTTransferOwnershipDelegate &delegate) {
  this->transferOwnership(address, [&delegate](const FString &transactionID) {
    delegate.ExecuteIfBound(transactionID);
  });
}

void UNFTWrapper::transferOwnership(const FString &address,
                                    TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("TransferOwnership"),
      {USmartContractsParametersEncoder::encodeAddress(address)}, 0,
      [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::mint(const FString &toAddress,
                       const FNFTMintDelegate &delegate) {
  this->mint(toAddress, [&delegate](const FString &transactionID) {
    delegate.ExecuteIfBound(transactionID);
  });
}

void UNFTWrapper::mint(const FString &toAddress,
                       TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("Mint"),
      {USmartContractsParametersEncoder::encodeAddress(toAddress)}, 0,
      [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::safeMint(const FString &toAddress, const TArray<uint8> &data,
                           const FNFTSafeMintDelegate &delegate) {
  this->safeMint(toAddress, data, [&delegate](const FString &transactionID) {
    delegate.ExecuteIfBound(transactionID);
  });
}

void UNFTWrapper::safeMint(const FString &toAddress, const TArray<uint8> &data,
                           TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("SafeMint"),
      {USmartContractsParametersEncoder::encodeAddress(toAddress),
       USmartContractsParametersEncoder::encodeByteArray(data)},
      0, [callback](const FString &transactionID) { callback(transactionID); });
}

void UNFTWrapper::burn(const UInt64 &tokenID,
                       const FNFTSafeMintDelegate &delegate) {
  this->burn(tokenID, [&delegate](const FString &transactionID) {
    delegate.ExecuteIfBound(transactionID);
  });
}

void UNFTWrapper::burn(uint64 tokenID,
                       TFunction<void(const FString &)> callback) {
  this->stratisManager->sendCallContractTransaction(
      this->contractAddress, TEXT("Burn"),
      {USmartContractsParametersEncoder::encodeULong(tokenID)}, 0,
      [callback](const FString &transactionID) { callback(transactionID); });
}