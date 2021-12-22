#include "WhitelistedSmartContracts.h"

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

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Testnet/NonFungibleToken/NonFungibleToken
const TCHAR* UWhitelistedSmartContracts::NFTContractAddress(TEXT("1c4dafabf65c2e28e5ed451d69947ef4e5a8c3ad5d113f24537a5cf561db4693"));
FString UWhitelistedSmartContracts::GetNFTContractAddress()
{
    return UWhitelistedSmartContracts::NFTContractAddress;
}
FString UWhitelistedSmartContracts::GetNFTContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("NFT"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Mainnet/StandardToken/StandardToken
const TCHAR* UWhitelistedSmartContracts::StandartTokenContractAddress(TEXT("bd99879e992ea9d655f59f4b0f0b3bec08a34439459568f38f534e45e719d283"));
FString UWhitelistedSmartContracts::GetStandartTokenContractAddress()
{
    return UWhitelistedSmartContracts::StandartTokenContractAddress;
}
FString UWhitelistedSmartContracts::GetStandartTokenContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("StandartToken"));
}

// https://github.com/stratisproject/CirrusSmartContracts/tree/master/Testnet/StandardToken/StandardToken
const TCHAR* UWhitelistedSmartContracts::StandartToken256ContractAddress(TEXT("8e73efc3b4b6a4ef42b195e0343f2a2c82c8ac68d7912afc59fd7ae1ce3c16a4"));
FString UWhitelistedSmartContracts::GetStandartToken256ContractAddress()
{
    return UWhitelistedSmartContracts::StandartToken256ContractAddress;
}
FString UWhitelistedSmartContracts::GetStandartToken256ContractCode()
{
    return UWhitelistedSmartContracts::loadContractCodeByName(TEXT("StandartToken256"));
}

FString UWhitelistedSmartContracts::loadContractCodeByName(const TCHAR* contractName)
{
    FString contractFile(IPluginManager::Get().FindPlugin(TEXT(PLUGIN_NAME))->GetContentDir());
    contractFile.Append(TEXT("/Contracts/"));
    contractFile.Append(contractName);

    FString result;

    if (FPaths::FileExists(contractFile))
    {
        FFileHelper::LoadFileToString(result, *contractFile, FFileHelper::EHashOptions::None);
    }

    return result;
}
