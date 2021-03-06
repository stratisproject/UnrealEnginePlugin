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

#include "ILocalExecutionResult.h"

#include "Helpers.h"
#include "StratisAPIModule.h"

#include "Templates/SharedPointer.h"

namespace stratis {
namespace api {

void ILocalExecutionResult::WriteJson(JsonWriter& Writer) const
{
    Writer->WriteObjectStart();
    if (InternalTransfers.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("InternalTransfers"));
        WriteJsonValue(Writer, InternalTransfers.GetValue());
    }
    if (GasConsumed.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("GasConsumed"));
        WriteJsonValue(Writer, GasConsumed.GetValue());
    }
    if (Revert.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("Revert"));
        WriteJsonValue(Writer, Revert.GetValue());
    }
    if (ErrorMessage.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("ErrorMessage"));
        WriteJsonValue(Writer, ErrorMessage.GetValue());
    }
    if (_Return.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("Return"));
        WriteJsonValue(Writer, _Return.GetValue());
    }
    if (Logs.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("Logs"));
        WriteJsonValue(Writer, Logs.GetValue());
    }
    if (StateRoot.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("StateRoot"));
        WriteJsonValue(Writer, StateRoot.GetValue());
    }
    Writer->WriteObjectEnd();
}

bool ILocalExecutionResult::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
    const TSharedPtr<FJsonObject>* Object;
    if (!JsonValue->TryGetObject(Object))
        return false;

    bool ParseSuccess = true;

    ParseSuccess &= TryGetJsonValue(*Object, TEXT("InternalTransfers"), InternalTransfers);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("GasConsumed"), GasConsumed);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("Revert"), Revert);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("ErrorMessage"), ErrorMessage);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("Return"), _Return);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("Logs"), Logs);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("StateRoot"), StateRoot);

    return ParseSuccess;
}

} // namespace api
} // namespace stratis
