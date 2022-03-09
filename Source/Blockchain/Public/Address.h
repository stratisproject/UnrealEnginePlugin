// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

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
