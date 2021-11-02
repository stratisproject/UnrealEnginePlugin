#pragma once

#include "SmartContracts/MethodParameter.h"
#include "Address.h"

namespace smart_contracts
{

namespace method_parameter
{

class AddressMethodParameter : public MethodParameter
{
public:
    AddressMethodParameter(const Address& value);
    AddressMethodParameter(Address&& value);

    std::vector<uint8_t> serialize() const override;
    MethodParameter::Type type() const override;

private:
    Address value_;
};

}

}