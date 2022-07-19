// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "WhitelistedSmartContracts.h"

#include "Projects.h"

#define PLUGIN_NAME "Stratis"

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/DAOContract
const TCHAR* UWhitelistedSmartContracts::DaoContractAddress(TEXT("0ae0598146338decb129978a1370c1500a5306cdb4db1ba32d3e42118ddf0e18"));
FString UWhitelistedSmartContracts::GetDaoContractAddress()
{
    return UWhitelistedSmartContracts::DaoContractAddress;
}
FString UWhitelistedSmartContracts::GetDaoContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("Dao"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/PrivateYesNoVote
const TCHAR* UWhitelistedSmartContracts::YesNoVoteContractAddress(TEXT("6bdaf42f95c0bd8ae7ffdd942c034ceaaa1be0774218536e830110e234e67d83"));
FString UWhitelistedSmartContracts::GetYesNoVoteContractAddress()
{
    return UWhitelistedSmartContracts::YesNoVoteContractAddress;
}
FString UWhitelistedSmartContracts::GetYesNoVoteContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("YesNoVote"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/NonFungibleToken
const TCHAR* UWhitelistedSmartContracts::NFTContractAddress(TEXT("1c4dafabf65c2e28e5ed451d69947ef4e5a8c3ad5d113f24537a5cf561db4693"));
FString UWhitelistedSmartContracts::GetNFTContractAddress()
{
    return UWhitelistedSmartContracts::NFTContractAddress;
}
FString UWhitelistedSmartContracts::GetNFTContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("NFT"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/NonFungibleToken-ManualTokenIdStrategy
const TCHAR* UWhitelistedSmartContracts::ManualIdNFTContractAddress(TEXT("e3d611802010d04b0762cc365b529fcf5b4bfdd85202a162a92d5ef84989c6d0"));
FString UWhitelistedSmartContracts::GetManualIdNFTContractAddress()
{
    return UWhitelistedSmartContracts::ManualIdNFTContractAddress;
}
FString UWhitelistedSmartContracts::GetManualIdNFTContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("ManualIdNFT"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/NonFungibleToken-Royalties
const TCHAR* UWhitelistedSmartContracts::RoyaltyNFTContractAddress(TEXT("9be6ead8318288d3a992a8fcc077be49fb8e672237da56852fb02b3d3999c0df"));
FString UWhitelistedSmartContracts::GetRoyaltyNFTContractAddress()
{
    return UWhitelistedSmartContracts::RoyaltyNFTContractAddress;
}
FString UWhitelistedSmartContracts::GetRoyaltyNFTContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("RoyaltyNFT"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/StandardToken/StandardToken
const TCHAR* UWhitelistedSmartContracts::StandardTokenContractAddress(TEXT("bd99879e992ea9d655f59f4b0f0b3bec08a34439459568f38f534e45e719d283"));
FString UWhitelistedSmartContracts::GetStandardTokenContractAddress()
{
    return UWhitelistedSmartContracts::StandardTokenContractAddress;
}
FString UWhitelistedSmartContracts::GetStandardTokenContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("StandardToken"));
}

FString UWhitelistedSmartContracts::loadContractCodeByName(const TCHAR* contractName)
{
    FString contractFile(IPluginManager::Get().FindPlugin(TEXT(PLUGIN_NAME))->GetContentDir());
    contractFile.Append(TEXT("/Contracts/"));
    contractFile.Append(contractName);

    FString result;

    if (FPaths::FileExists(contractFile)) {
        FFileHelper::LoadFileToString(result, *contractFile, FFileHelper::EHashOptions::None);
    }

    return result;
}
