#pragma once

#include "SmartContracts/MethodParameters/ByteArrayMethodParameter.h"

namespace smart_contracts
{

namespace method_parameter
{

ByteArrayMethodParameter::ByteArrayMethodParameter(const TArray<uint8>& value)
: value_(value)
{
}

ByteArrayMethodParameter::ByteArrayMethodParameter(TArray<uint8>&& value)
: value_(MoveTemp(value))
{
}

std::vector<uint8_t> ByteArrayMethodParameter::serialize() const
{
    std::vector<uint8_t> result(value_.Num() + 1);

    result[0] = (uint8_t) MethodParameter::Type::BYTE_ARRAY;

    for (int32 i = 0; i < value_.Num(); i++)
    {
        result[i + 1] = value_[i];
    }

    return result;
}

MethodParameter::Type ByteArrayMethodParameter::type() const
{
    return MethodParameter::Type::BYTE_ARRAY;
}

}

}