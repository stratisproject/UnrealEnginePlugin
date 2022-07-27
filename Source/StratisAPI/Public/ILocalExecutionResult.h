// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

/**
 * Stratis Node API
 * Access to the Stratis Node's api.
 *
 * OpenAPI spec version: 1.0
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#pragma once

#include "BaseModel.h"
#include "ContractErrorMessage.h"
#include "Gas.h"
#include "Log.h"
#include "TransferInfo.h"

namespace stratis {
namespace api {

/*
 * ILocalExecutionResult
 *
 *
 */
class STRATISAPI_API ILocalExecutionResult : public Model
{
public:
    virtual ~ILocalExecutionResult() {}
    bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
    void WriteJson(JsonWriter& Writer) const final;

    TOptional<TArray<TransferInfo>> InternalTransfers;
    TOptional<Gas> GasConsumed;
    TOptional<bool> Revert;
    TOptional<ContractErrorMessage> ErrorMessage;
    TOptional<TSharedPtr<FJsonValue>> _Return;
    TOptional<TArray<Log>> Logs;
    TOptional<TSharedPtr<FJsonObject>> StateRoot;
};

} // namespace api
} // namespace stratis