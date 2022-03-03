// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "UStratisBlueprintFunctionLibrary.h"

FString
UStratisBlueprintFunctionLibrary::Conv_FUInt64ToString(const FUInt64& value)
{
    return FString::Printf(TEXT("%llu"), value.Value);
}
