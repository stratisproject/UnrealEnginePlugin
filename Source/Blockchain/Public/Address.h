#pragma once

#include "CoreMinimal.h"

constexpr uint32 ADDRESS_WIDTH = 20;

class BLOCKCHAIN_API Address
{
public:
    Address(const FString& address);
    Address(FString&& address);

    const FString& value() const;
private:
    FString storage_;
};