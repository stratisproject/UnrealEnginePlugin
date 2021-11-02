#pragma once

#include "CoreMinimal.h"

#include "SmartContractScriptFactory.h"

namespace smart_contracts
{

TUniquePtr<SmartContractScriptFactory> createSmartContractScriptFactory();

}