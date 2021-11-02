#pragma once

#include "CoreMinimal.h"
#include "SmartContracts/MethodParameter.h"

namespace smart_contracts
{

namespace method_parameter
{

class ByteArrayMethodParameter : public MethodParameter
{
public:
    ByteArrayMethodParameter(const TArray<uint8>& value);
    ByteArrayMethodParameter(TArray<uint8>&& value);

    std::vector<uint8_t> serialize() const override;
    MethodParameter::Type type() const override;

private:
    TArray<uint8> value_;
};

}

}