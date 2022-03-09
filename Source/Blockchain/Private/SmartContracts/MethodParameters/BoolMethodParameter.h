// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "SmartContracts/MethodParameter.h"

namespace smart_contracts {

namespace method_parameter {

class BoolMethodParameter : public MethodParameter
{
public:
    BoolMethodParameter(bool value);

    std::vector<uint8_t> serialize() const override;
    MethodParameter::Type type() const override;

private:
    bool value_;
};

} // namespace method_parameter

} // namespace smart_contracts
