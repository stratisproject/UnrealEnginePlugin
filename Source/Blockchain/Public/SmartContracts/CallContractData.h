#pragma once

#include "CoreMinimal.h"

#include "Address.h"
#include "MethodParameter.h"

namespace smart_contracts
{

struct CallContractData
{
    uint64 gasPrice;
    uint64 gasLimit;

    Address contractAddress;
    FString methodName;

    TArray< TUniquePtr<method_parameter::MethodParameter> > methodParameters;
};

}