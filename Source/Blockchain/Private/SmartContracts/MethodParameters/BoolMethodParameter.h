#pragma once

#include "SmartContracts/MethodParameter.h"

namespace smart_contracts
{

namespace method_parameter
{

class BoolMethodParameter : public MethodParameter
{
public:
    BoolMethodParameter(bool value);

    std::vector<uint8_t> serialize() const override;
    MethodParameter::Type type() const override;

private:
    bool value_;
};

}

}