// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Models/FUInt64.h"

FUInt64::operator uint64() const { return this->Value; }

FUInt64::FUInt64() : Value(0) {}

FUInt64::FUInt64(uint64 value) : Value(value) {}

FUInt64 UUInt64Factory::UInt64FromString(const FString& value)
{
    return FUInt64(FCString::Strtoui64(*value, NULL, 10));
}
