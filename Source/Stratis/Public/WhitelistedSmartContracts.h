#pragma once

#include "Core.h"

#include "WhitelistedSmartContracts.generated.h"

USTRUCT(BlueprintType)
struct FWhitelistedSmartContract {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FString code;

    UPROPERTY(EditAnywhere)
    FString address;
};

UCLASS(BlueprintType)
class UWhitelistedSmartContracts : public UObject
{
    GENERATED_BODY()

public:
    static const TCHAR* DaoContractCode;
    static const TCHAR* DaoContractAddress;

    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FWhitelistedSmartContract DaoContract();


    static const TCHAR* YesNoVoteContractCode;
    static const TCHAR* YesNoVoteContractAddress;

    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FWhitelistedSmartContract YesNoVoteContract();


    static const TCHAR* NFTContractCode;
    static const TCHAR* NFTContractAddress;

    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FWhitelistedSmartContract NFTContract();


    static const TCHAR* StandartTokenContractCode;
    static const TCHAR* StandartTokenContractAddress;

    UFUNCTION(BlueprintCallable, Category = "WhitelistedSmartContracts")
    static FWhitelistedSmartContract StandartTokenContract();
};