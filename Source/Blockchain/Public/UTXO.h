#pragma once

#include "CoreMinimal.h"

struct BLOCKCHAIN_API UTXO
{
    FString hash;
    uint32 n;
    uint64 satoshis;
};