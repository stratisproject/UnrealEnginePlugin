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

namespace stratis 
{
namespace api 
{

/*
 * BlockModel
 *
 * 
 */
class STRATISAPI_API BlockModel : public Model
{
public:
    virtual ~BlockModel() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<FString> Hash;
	TOptional<int32> Confirmations;
	TOptional<int32> Size;
	TOptional<int64> Weight;
	TOptional<int32> Height;
	TOptional<int32> Version;
	TOptional<FString> VersionHex;
	TOptional<FString> Merkleroot;
	TOptional<TArray<TSharedPtr<FJsonValue>>> Tx;
	TOptional<int64> Time;
	TOptional<int64> Mediantime;
	TOptional<int32> Nonce;
	TOptional<FString> Bits;
	TOptional<double> Difficulty;
	TOptional<FString> Chainwork;
	TOptional<int32> NTx;
	TOptional<FString> Previousblockhash;
	TOptional<FString> Nextblockhash;
	TOptional<FString> Signature;
	TOptional<FString> Modifierv2;
	TOptional<FString> Flags;
	TOptional<FString> Hashproof;
	TOptional<FString> Blocktrust;
	TOptional<FString> Chaintrust;
};

}
}
