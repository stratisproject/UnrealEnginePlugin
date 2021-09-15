#include "UStratisUnrealManager.h"

void UStratisUnrealManager::Initialize(FString mnemonic_)
{
    this->mnemonic = mnemonic_;
}

FString UStratisUnrealManager::getAddress()
{
    return TEXT("");
}

void UStratisUnrealManager::getBalance(FGetBalanceResponseReceivedDelegate delegate)
{
    
}

void UStratisUnrealManager::sendTransaction(FSendTransactionResponseReceivedDelegate delegate, const FString& destinationAddress, int money)
{

}

void UStratisUnrealManager::sendOpReturnStringTransaction(FSendOpReturnTransactionResponseReceivedDelegate delegate, const FString& opReturnData)
{

}

void UStratisUnrealManager::sendOpReturnArrayTransaction(FSendOpReturnTransactionResponseReceivedDelegate delegate, const TArray<uint8>& opReturnData)
{

}

void UStratisUnrealManager::getCoins(FGetCoinsResponseReceivedDelegate delegate)
{

}

void UStratisUnrealManager::sendCreateContractTransaction(FSendCreateContractTransactionResponseReceivedDelegate delegate, const FString& contractCode, const TArray<FString>& parameters, int money)
{

}

void UStratisUnrealManager::sendCallContractTransaction(FSendCallContractTransactionResponseReceivedDelegate delegate, const FString& contractAddress, const FString& methodName, const TArray<FString>& parameters, int money)
{

}

void UStratisUnrealManager::waitTillReceiptAvailable(FWaitTillReceiptAvailableResponseReceivedDelegate delegate, const FString& txId)
{

}