// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"
#include "SmartContracts/MethodParameter.h"

#include "UintTypes.h"

namespace smart_contracts {

namespace method_parameter {

template <int32 BITS>
class LargeUintMethodParameter : public MethodParameter
{
public:
    static constexpr const int32 BYTES = BITS / 8;

    LargeUintMethodParameter(const UIntType<BITS>& value) : value_(value) {}

    LargeUintMethodParameter(UIntType<BITS>&& value) : value_(MoveTemp(value)) {}

    // TODO: validation - big endian / little endian
    std::vector<uint8_t> serialize() const override
    {
        std::vector<uint8_t> result;
        result.reserve(1 + BYTES);
        result.push_back((uint8_t)type());

        const uint8_t* rawBits = (uint8_t*)(value_.value().GetBits());

        std::copy(rawBits, rawBits + BYTES, std::back_inserter(result));
        return result;
    }

    MethodParameter::Type type() const override;

private:
    UIntType<BITS> value_;
};

template <>
inline MethodParameter::Type LargeUintMethodParameter<128>::type() const
{
    return MethodParameter::Type::UINT128;
}

template <>
inline MethodParameter::Type LargeUintMethodParameter<256>::type() const
{
    return MethodParameter::Type::UINT256;
}

} // namespace method_parameter

} // namespace smart_contracts
