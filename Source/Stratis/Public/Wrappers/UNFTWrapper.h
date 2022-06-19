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

#include "UNFTWrapper.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API RoyaltyInfo {
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString royaltyRecipient;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FUInt64 royaltyAmount;

    RoyaltyInfo() {}

    RoyaltyInfo(const FString& royaltyRecipientArg, const FUInt64& royaltyAmountArg)
        : royaltyRecipient(royaltyRecipientArg), royaltyAmount(royaltyAmountArg) {}
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeployNFTContractDelegate, const FString&, transactionId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetOwnerDelegate, const FString&, owner);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetPendingOwnerDelegate, const FString&, owner);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetNameDelegate, const FString&, name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetSymbolDelegate, const FString&, symbol);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSupportsInterfaceDelegate, bool, supports);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetBalanceOfDelegate, const FUInt256&, balance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetOwnerOfDelegate, const FString&, owner);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetApprovedDelegate, const FString&, address);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetApprovedForAllDelegate, bool, approved);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetTokenURIDelegate, const FString&, uri);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSafeTransferFromDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTTransferFromDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTApproveDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSetApprovalForAllDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTTransferOwnershipDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTMintDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSafeMintDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTBurnDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSetPendingOwnerDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTClaimOwnershipDelegate, const FString&, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetRoyaltyInfoDelegate, const RoyaltyInfo&, royaltyInfo);

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UNFTWrapper : public UObject
{
    GENERATED_BODY()

public:
    UNFTWrapper();

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    static UNFTWrapper* createInstance(const FString& contractAddress, UStratisUnrealManager* manager, UObject* outer);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    static UNFTWrapper* createDefaultInstance(UStratisUnrealManager* manager, UObject* outer);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    static UNFTWrapper* createDefaultManualIdInstance(UStratisUnrealManager* manager, UObject* outer);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    static UNFTWrapper* createDefaultRoyaltyInstance(UStratisUnrealManager* manager, UObject* outer);

    UPROPERTY(EditAnywhere)
    UStratisUnrealManager* stratisManager;

    UPROPERTY(EditAnywhere)
    FString contractAddress;

    UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void deployNFTContract(const FString& name,
                           const FString& symbol,
                           bool ownerOnlyMinting,
                           const FDeployNFTContractDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate);
    void deployNFTContract(const FString& name, const FString& symbol,
                           bool ownerOnlyMinting,
                           TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void deployManualIdNFTContract(const FString& name,
                                   const FString& symbol,
                                   bool ownerOnlyMinting,
                                   const FDeployNFTContractDelegate& delegate,
                                   const FErrorReceivedDelegate& errorDelegate);
    void deployManualIdNFTContract(const FString& name, const FString& symbol,
                                   bool ownerOnlyMinting,
                                   TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void deployRoyaltyNFTContract(const FString& name,
                                  const FString& symbol,
                                  bool ownerOnlyMinting,
                                  const FString& royaltyRecipient,
                                  int32 royaltyPercent,
                                  const FDeployNFTContractDelegate& delegate,
                                  const FErrorReceivedDelegate& errorDelegate);
    void deployRoyaltyNFTContract(const FString& name,
                                  const FString& symbol,
                                  bool ownerOnlyMinting,
                                  const FString& royaltyRecipient,
                                  uint32 royaltyPercent,
                                  TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getOwner(const FNFTGetOwnerDelegate& delegate,
                  const FErrorReceivedDelegate& errorDelegate);
    void getOwner(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getPendingOwner(const FNFTGetOwnerDelegate& delegate,
                         const FErrorReceivedDelegate& errorDelegate);
    void getPendingOwner(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getName(const FNFTGetNameDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void getName(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getSymbol(const FNFTGetSymbolDelegate& delegate,
                   const FErrorReceivedDelegate& errorDelegate);
    void getSymbol(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void supportsInterface(int64 interfaceID,
                           const FNFTSupportsInterfaceDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate);
    void supportsInterface(uint32 interfaceID,
                           TFunction<void(const TResult<bool>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getBalanceOf(const FString& address,
                      const FNFTGetBalanceOfDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void getBalanceOf(const FString& address,
                      TFunction<void(const TResult<uint64>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getOwnerOf(const FUInt256& tokenID,
                    const FNFTGetOwnerOfDelegate& delegate,
                    const FErrorReceivedDelegate& errorDelegate);
    void getOwnerOf(const FUInt256& tokenID,
                    TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getApproved(const FUInt256& tokenID,
                     const FNFTGetApprovedDelegate& delegate,
                     const FErrorReceivedDelegate& errorDelegate);
    void getApproved(const FUInt256& tokenID,
                     TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getApprovedForAll(const FString& ownerAddress,
                           const FString& operatorAddress,
                           const FNFTGetApprovedForAllDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate);
    void getApprovedForAll(const FString& ownerAddress,
                           const FString& operatorAddress,
                           TFunction<void(const TResult<bool>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void getTokenURI(const FUInt256& tokenID,
                     const FNFTGetTokenURIDelegate& delegate,
                     const FErrorReceivedDelegate& errorDelegate);
    void getTokenURI(const FUInt256& tokenID,
                     TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void safeTransferFrom(const FString& fromAddress, const FString& toAddress,
                          const FUInt256& tokenID, TArray<uint8> data,
                          const FNFTSafeTransferFromDelegate& delegate,
                          const FErrorReceivedDelegate& errorDelegate);
    void safeTransferFrom(const FString& fromAddress, const FString& toAddress,
                          const FUInt256& tokenID, TArray<uint8> data,
                          TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt256& tokenID,
                      const FNFTTransferFromDelegate& delegate,
                      const FErrorReceivedDelegate& errorDelegate);
    void transferFrom(const FString& fromAddress, const FString& toAddress,
                      const FUInt256& tokenID,
                      TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void approve(const FString& address, const FUInt256& tokenID,
                 const FNFTApproveDelegate& delegate,
                 const FErrorReceivedDelegate& errorDelegate);
    void approve(const FString& address, const FUInt256& tokenID,
                 TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void setApprovalForAll(const FString& address, bool approved,
                           const FNFTSetApprovalForAllDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate);
    void setApprovalForAll(const FString& address, bool approved,
                           TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void transferOwnership(const FString& address,
                           const FNFTTransferOwnershipDelegate& delegate,
                           const FErrorReceivedDelegate& errorDelegate);
    void transferOwnership(const FString& address,
                           TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void mint(const FString& toAddress, const FString& metadataUri,
              const FNFTMintDelegate& delegate,
              const FErrorReceivedDelegate& errorDelegate);
    void mint(const FString& toAddress, const FString& metadataUri,
              TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void safeMint(const FString& toAddress, const FString& metadataUri,
                  const TArray<uint8>& data,
                  const FNFTSafeMintDelegate& delegate,
                  const FErrorReceivedDelegate& errorDelegate);
    void safeMint(const FString& toAddress, const FString& metadataUri,
                  const TArray<uint8>& data,
                  TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void mintWithManualID(const FString& toAddress,
                          const FUInt256& tokenID,
                          const FString& metadataUri,
                          const FNFTMintDelegate& delegate,
                          const FErrorReceivedDelegate& errorDelegate);
    void mintWithManualID(const FString& toAddress,
                          const FUInt256& tokenID,
                          const FString& metadataUri,
                          TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void safeMintWithManualID(const FString& toAddress,
                              const FUInt256& tokenID,
                              const FString& metadataUri,
                              const TArray<uint8>& data,
                              const FNFTSafeMintDelegate& delegate,
                              const FErrorReceivedDelegate& errorDelegate);
    void safeMintWithManualID(const FString& toAddress,
                              const FUInt256& tokenID,
                              const FString& metadataUri,
                              const TArray<uint8>& data,
                              TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void burn(const FUInt256& tokenID, const FNFTSafeMintDelegate& delegate,
              const FErrorReceivedDelegate& errorDelegate);
    void burn(const FUInt256& tokenID, TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void setPendingOwner(const FString& newOwner,
                         const FNFTSetPendingOwnerDelegate& delegate,
                         const FErrorReceivedDelegate& errorDelegate);
    void setPendingOwner(const FString& newOwner, TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void claimOwnership(const FNFTClaimOwnershipDelegate& delegate,
                        const FErrorReceivedDelegate& errorDelegate);
    void claimOwnership(TFunction<void(const TResult<FString>&)> callback);

    UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
    void royaltyInfo(const UInt64& salePrice,
                     const FNFTGetRoyaltyInfoDelegate& delegate,
                     const FErrorReceivedDelegate& errorDelegate);
    void royaltyInfo(uint64 salePrice, TFunction<void(const TResult<RoyaltyInfo>&)> callback);
};
