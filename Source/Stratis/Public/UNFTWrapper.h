#pragma once

#include "CoreMinimal.h"

#include "Models/FUInt64.h"
#include "UStratisUnrealManager.h"

#include "UNFTWrapper.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDeployNFTContractDelegate, const FString &,
                                  transactionId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetOwnerDelegate, const FString &, owner);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetNameDelegate, const FString &, name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetSymbolDelegate, const FString &,
                                  symbol);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSupportsInterfaceDelegate, bool,
                                  supports);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetBalanceOfDelegate, const FUInt64 &,
                                  balance);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetOwnerOfDelegate, const FString &,
                                  owner);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetApprovedDelegate, const FString &,
                                  address);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetApprovedForAllDelegate, bool,
                                  approved);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTGetTokenURIDelegate, const FString &,
                                  uri);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSafeTransferFromDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTTransferFromDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTApproveDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSetApprovalForAllDelegate,
                                  const FString &, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTTransferOwnershipDelegate,
                                  const FString &, transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTMintDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTSafeMintDelegate, const FString &,
                                  transactionID);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNFTBurnDelegate, const FString &,
                                  transactionID);

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API UNFTWrapper : public UObject {

  GENERATED_BODY()

public:
  UNFTWrapper();

  UPROPERTY(EditAnywhere)
  UStratisUnrealManager *stratisManager;

  UPROPERTY(EditAnywhere)
  FString contractAddress;

  UWorld *GetWorld() const override;

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void deployNFTContract(const FString &name, const FString &symbol,
                         const FString &tokenURIFormat, bool ownerOnlyMinting,
                         const FDeployNFTContractDelegate &delegate);
  void deployNFTContract(const FString &name, const FString &symbol,
                         const FString &tokenURIFormat, bool ownerOnlyMinting,
                         TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getOwner(const FNFTGetOwnerDelegate &delegate);
  void getOwner(TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getName(const FNFTGetNameDelegate &delegate);
  void getName(TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getSymbol(const FNFTGetSymbolDelegate &delegate);
  void getSymbol(TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void supportsInterface(int64 interfaceID,
                         const FNFTSupportsInterfaceDelegate &delegate);
  void supportsInterface(uint32 interfaceID, TFunction<void(bool)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getBalanceOf(const FString &address,
                    const FNFTGetBalanceOfDelegate &delegate);
  void getBalanceOf(const FString &address, TFunction<void(uint64)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getOwnerOf(const FUInt64 &tokenID,
                  const FNFTGetOwnerOfDelegate &delegate);
  void getOwnerOf(uint64 tokenID, TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getApproved(const FUInt64 &tokenID,
                   const FNFTGetApprovedDelegate &delegate);
  void getApproved(uint64 tokenID, TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getApprovedForAll(const FString &ownderAddress,
                         const FString &operatorAddress,
                         const FNFTGetApprovedForAllDelegate &delegate);
  void getApprovedForAll(const FString &ownderAddress,
                         const FString &operatorAddress,
                         TFunction<void(bool)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void getTokenURI(const FUInt64 &tokenID,
                   const FNFTGetTokenURIDelegate &delegate);
  void getTokenURI(uint64 tokenID, TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void safeTransferFrom(const FString &fromAddress, const FString &toAddress,
                        const FUInt64 &tokenID, TArray<uint8> data,
                        const FNFTSafeTransferFromDelegate &delegate);
  void safeTransferFrom(const FString &fromAddress, const FString &toAddress,
                        uint64 tokenID, TArray<uint8> data,
                        TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void transferFrom(const FString &fromAddress, const FString &toAddress,
                    const FUInt64 &tokenID,
                    const FNFTTransferFromDelegate &delegate);
  void transferFrom(const FString &fromAddress, const FString &toAddress,
                    uint64 tokenID, TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void approve(const FString &address, const FUInt64 &tokenID,
               const FNFTApproveDelegate &delegate);
  void approve(const FString &address, uint64 tokenID,
               TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void setApprovalForAll(const FString &address, const FUInt64 &tokenID,
                         const FNFTSetApprovalForAllDelegate &delegate);
  void setApprovalForAll(const FString &address, uint64 tokenID,
                         TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void transferOwnership(const FString &address,
                         const FNFTTransferOwnershipDelegate &delegate);
  void transferOwnership(const FString &address,
                         TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void mint(const FString &toAddress, const FNFTMintDelegate &delegate);
  void mint(const FString &toAddress,
            TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void safeMint(const FString &toAddress, const TArray<uint8> &data,
                const FNFTSafeMintDelegate &delegate);
  void safeMint(const FString &toAddress, const TArray<uint8> &data,
                TFunction<void(const FString &)> callback);

  UFUNCTION(BlueprintCallable, Category = "NFTWrapper")
  void burn(const UInt64 &tokenID, const FNFTSafeMintDelegate &delegate);
  void burn(uint64 tokenID, TFunction<void(const FString &)> callback);
};