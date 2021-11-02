#pragma once

#include "CoreMinimal.h"

#include "MethodParameter.h"

namespace smart_contracts
{

struct CreateContractData
{
    uint64 gasPrice;
    uint64 gasLimit;

    TArray<uint8_t> contractCode;

    TArray< TUniquePtr<method_parameter::MethodParameter> > methodParameters;
};

}