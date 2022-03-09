// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Core.h"

#include "WhitelistedSmartContracts.generated.h"

UCLASS(BlueprintType)
class UWhitelistedSmartContracts : public UObject
{
    GENERATED_BODY()

public:
    static const TCHAR* DaoContractAddress;
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetDaoContractAddress();
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetDaoContractCode();

    static const TCHAR* YesNoVoteContractAddress;
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetYesNoVoteContractAddress();
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetYesNoVoteContractCode();

    static const TCHAR* NFTContractAddress;
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetNFTContractAddress();
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetNFTContractCode();

    static const TCHAR* StandartTokenContractAddress;
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetStandartTokenContractAddress();
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetStandartTokenContractCode();

    static const TCHAR* StandartToken256ContractAddress;
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetStandartToken256ContractAddress();
    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FString GetStandartToken256ContractCode();
private:
    static FString loadContractCodeByName(const TCHAR* contractName);
};
