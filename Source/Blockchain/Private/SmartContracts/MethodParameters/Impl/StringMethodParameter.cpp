#pragma once

#include "SmartContracts/MethodParameters/StringMethodParameter.h"

#include "Utils.h"

namespace smart_contracts
{

namespace method_parameter
{

StringMethodParameter::StringMethodParameter(const FString& value)
: value_(value)
{
}

StringMethodParameter::StringMethodParameter(FString&& value)
: value_(MoveTemp(value))
{
}

std::vector<uint8_t> StringMethodParameter::serialize() const
{
    std::vector<uint8_t> bytes(utils::asBytes(value_));

    std::vector<uint8_t> result { (uint8_t) MethodParameter::Type::STRING };
    result.insert(result.end(), bytes.begin(), bytes.end());

    return result;
}

MethodParameter::Type StringMethodParameter::type() const
{
    return MethodParameter::Type::STRING;
}

}

}