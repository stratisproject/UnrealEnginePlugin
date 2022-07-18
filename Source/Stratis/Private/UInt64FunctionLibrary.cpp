// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "UInt64FunctionLibrary.h"


FString UInt64FunctionLibrary::FormatUInt64(const FUInt64& value)
{
    return FString::Printf(TEXT("%.3f"), (double)value.Value / 100000000);
}

TArray<uint8> UInt64FunctionLibrary::ToByteArray(const FUInt64& value)
{
    return TArray<uint8>((uint8*)&(value.Value), 8);
}