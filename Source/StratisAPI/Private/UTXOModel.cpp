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

#include "UTXOModel.h"

#include "StratisAPIModule.h"
#include "Helpers.h"

#include "Templates/SharedPointer.h"

namespace stratis
{
namespace api
{

void UTXOModel::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Hash.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("hash")); WriteJsonValue(Writer, Hash.GetValue());
	}
	if (N.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("n")); WriteJsonValue(Writer, N.GetValue());
	}
	if (Satoshis.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("satoshis")); WriteJsonValue(Writer, Satoshis.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool UTXOModel::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("hash"), Hash);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("n"), N);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("satoshis"), Satoshis);

	return ParseSuccess;
}

}
}
