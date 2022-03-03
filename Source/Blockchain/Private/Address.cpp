// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Address.h"

Address::Address(const FString& address) : storage_(address)
{
}

Address::Address(FString&& address) : storage_(MoveTemp(address)) 
{
}

const FString& Address::value() const
{
    return storage_;
}
