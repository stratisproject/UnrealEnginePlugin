#pragma once

#include "FUInt64.generated.h"

#define PACKED
#pragma pack(push,1)

USTRUCT(BlueprintType)
struct STRATIS_API FUInt64
{
	GENERATED_BODY()

	uint64 Value;

	operator uint64() const { return this->Value; }

	FUInt64(): Value(0) {}

	FUInt64(uint64 value) { this->Value = value; }

};

#pragma pack(pop)
#undef PACKED