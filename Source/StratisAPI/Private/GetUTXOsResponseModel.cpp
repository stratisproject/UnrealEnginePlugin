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

#include "GetUTXOsResponseModel.h"

#include "Helpers.h"
#include "StratisAPIModule.h"

#include "Templates/SharedPointer.h"

namespace stratis {
namespace api {

void GetUTXOsResponseModel::WriteJson(JsonWriter& Writer) const
{
    Writer->WriteObjectStart();
    if (BalanceSat.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("BalanceSat"));
        WriteJsonValue(Writer, BalanceSat.GetValue());
    }
    if (UTXOs.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("UTXOs"));
        WriteJsonValue(Writer, UTXOs.GetValue());
    }
    if (Reason.IsSet()) {
        Writer->WriteIdentifierPrefix(TEXT("Reason"));
        WriteJsonValue(Writer, Reason.GetValue());
    }
    Writer->WriteObjectEnd();
}

bool GetUTXOsResponseModel::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
    const TSharedPtr<FJsonObject>* Object;
    if (!JsonValue->TryGetObject(Object))
        return false;

    bool ParseSuccess = true;

    ParseSuccess &= TryGetJsonValue(*Object, TEXT("BalanceSat"), BalanceSat);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("UTXOs"), UTXOs);
    ParseSuccess &= TryGetJsonValue(*Object, TEXT("Reason"), Reason);

    return ParseSuccess;
}

} // namespace api
} // namespace stratis
