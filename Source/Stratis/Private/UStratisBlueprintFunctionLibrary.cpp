#include "UStratisBlueprintFunctionLibrary.h"

FString
UStratisBlueprintFunctionLibrary::Conv_FUInt64ToString(const FUInt64& value)
{
    return FString::Printf(TEXT("%llu"), value.Value);
}
