#pragma once

#include "StratisNetwork.h"
#include <CoreMinimal.h>

class TransactionBuilder;

BLOCKCHAIN_API TSharedPtr<TransactionBuilder>
createTransactionBuilder(const FString &mnemonic,
                         const StratisNetwork &network);