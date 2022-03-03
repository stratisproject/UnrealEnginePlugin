// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "SmartContracts/MethodParameters/BoolMethodParameter.h"

namespace smart_contracts
{

namespace method_parameter
{

BoolMethodParameter::BoolMethodParameter(bool value): value_(value) 
{
}

std::vector<uint8_t> BoolMethodParameter::serialize() const
{
    return { (uint8_t) MethodParameter::Type::BOOL, (uint8_t) value_ };
}

MethodParameter::Type BoolMethodParameter::type() const
{
    return MethodParameter::Type::BOOL;
}

}

}
