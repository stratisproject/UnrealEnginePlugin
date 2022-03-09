// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include <vector>

#include "CallContractData.h"
#include "CreateContractData.h"

namespace smart_contracts {

class SmartContractScriptFactory
{
public:
    virtual ~SmartContractScriptFactory() {}

    virtual std::vector<uint8_t> makeCreateSmartContractScript(const CreateContractData& data) const = 0;
    virtual std::vector<uint8_t> makeCallSmartContractScript(const CallContractData& data) const = 0;
};

} // namespace smart_contracts
