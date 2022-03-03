// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "SmartContracts/MethodParameter.h"
#include "Utils.h"

namespace smart_contracts {

namespace method_parameter {

template <typename Integer,
          std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
class IntegerMethodParameter : public MethodParameter
{
public:
    IntegerMethodParameter(Integer value);

    // TODO: optimization - eliminate vector resizing
    std::vector<uint8_t> serialize() const override
    {
        std::vector<uint8_t> result{(uint8_t)type_};
        utils::asBytes(result, value_); // TODO: validation - check BigEndian issue
        return result;
    }

    MethodParameter::Type type() const override { return type_; }

private:
    Integer value_;
    MethodParameter::Type type_;
};

template <>
inline IntegerMethodParameter<uint8_t>::IntegerMethodParameter(uint8_t value)
    : value_(value), type_(MethodParameter::Type::BYTE)
{
}

template <>
inline IntegerMethodParameter<uint16_t>::IntegerMethodParameter(uint16_t value)
    : value_(value), type_(MethodParameter::Type::CHAR)
{
}

template <>
inline IntegerMethodParameter<uint32_t>::IntegerMethodParameter(uint32_t value)
    : value_(value), type_(MethodParameter::Type::UINT)
{
}

template <>
inline IntegerMethodParameter<int32_t>::IntegerMethodParameter(int32_t value)
    : value_(value), type_(MethodParameter::Type::INT)
{
}

template <>
inline IntegerMethodParameter<uint64_t>::IntegerMethodParameter(uint64_t value)
    : value_(value), type_(MethodParameter::Type::ULONG)
{
}

template <>
inline IntegerMethodParameter<int64_t>::IntegerMethodParameter(int64_t value)
    : value_(value), type_(MethodParameter::Type::LONG)
{
}

} // namespace method_parameter

} // namespace smart_contracts
