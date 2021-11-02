#pragma once

#include "CoreMinimal.h"
#include "Math/BigInt.h"

template <int32 BITS>
class BLOCKCHAIN_API UIntType
{
public:
    UIntType(const TBigInt<BITS, false> &data) : data_(data)
    {
    }

    UIntType(TBigInt<BITS, false> &&data) : data_(MoveTemp(data))
    {
    }

    UIntType(const FString &encoded) : data_(TBigInt<BITS, false>(encoded))
    {
    }

    const TBigInt<BITS, false> &value() const
    {
        return data_;
    }

private:
    TBigInt<BITS, false> data_;
};

using Uint128 = UIntType<128>;
using Uint256 = UIntType<256>;