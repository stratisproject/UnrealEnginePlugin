// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "Address.h"
#include "MethodParameter.h"

namespace smart_contracts {

struct CallContractData {
    uint64 gasPrice;
    uint64 gasLimit;

    Address contractAddress;
    FString methodName;

    TArray<TUniquePtr<method_parameter::MethodParameter>> methodParameters;
};

} // namespace smart_contracts
