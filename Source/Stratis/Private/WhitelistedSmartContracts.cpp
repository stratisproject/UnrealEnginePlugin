#include "WhitelistedSmartContracts.h"

const TCHAR* UWhitelistedSmartContracts::DaoContractCode(TEXT("A"));
const TCHAR* UWhitelistedSmartContracts::DaoContractAddress(TEXT("A"));

FWhitelistedSmartContract UWhitelistedSmartContracts::DaoContract()
{
    return {UWhitelistedSmartContracts::DaoContractCode, UWhitelistedSmartContracts::DaoContractAddress};
}


const TCHAR* UWhitelistedSmartContracts::YesNoVoteContractCode(TEXT("A"));
const TCHAR* UWhitelistedSmartContracts::YesNoVoteContractAddress(TEXT("A"));

FWhitelistedSmartContract UWhitelistedSmartContracts::YesNoVoteContract()
{
    return {UWhitelistedSmartContracts::YesNoVoteContractCode, UWhitelistedSmartContracts::YesNoVoteContractAddress};
}

const TCHAR* UWhitelistedSmartContracts::NFTContractCode(TEXT("A"));
const TCHAR* UWhitelistedSmartContracts::NFTContractAddress(TEXT("A"));

FWhitelistedSmartContract UWhitelistedSmartContracts::NFTContract()
{
    return {UWhitelistedSmartContracts::NFTContractCode, UWhitelistedSmartContracts::NFTContractAddress};
}

const TCHAR* UWhitelistedSmartContracts::StandartTokenContractCode(TEXT("A"));
const TCHAR* UWhitelistedSmartContracts::StandartTokenContractAddress(TEXT("A"));

FWhitelistedSmartContract UWhitelistedSmartContracts::StandartTokenContract()
{
    return {UWhitelistedSmartContracts::StandartTokenContractCode, UWhitelistedSmartContracts::StandartTokenContractAddress};
}
