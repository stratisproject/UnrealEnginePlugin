#pragma once

#include "CoreMinimal.h"
#include "SmartContracts/MethodParameter.h"

namespace smart_contracts
{

namespace method_parameter
{

class StringMethodParameter : public MethodParameter
{
public:
    StringMethodParameter(const FString& value);
    StringMethodParameter(FString&& value);

    std::vector<uint8_t> serialize() const override;
    MethodParameter::Type type() const override;

private:
    FString value_;
};

}

}