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

namespace stratis {
namespace api {

/*
 * Gas
 *
 *
 */
class STRATISAPI_API Gas : public Model
{
public:
    virtual ~Gas() {}
    bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
    void WriteJson(JsonWriter& Writer) const final;

    TOptional<int64> Value;
};

} // namespace api
} // namespace stratis
