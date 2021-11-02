#pragma once

#include <vector>

#include "CreateContractData.h"
#include "CallContractData.h"

namespace smart_contracts
{

class SmartContractScriptFactory
{
public:
    virtual ~SmartContractScriptFactory() {}

    virtual std::vector<uint8_t> makeCreateSmartContractScript(const CreateContractData& data) const = 0;
    virtual std::vector<uint8_t> makeCallSmartContractScript(const CallContractData& data) const = 0;
};

}