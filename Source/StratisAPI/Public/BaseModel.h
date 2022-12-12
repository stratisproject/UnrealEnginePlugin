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

#include "Containers/Ticker.h"
#include "Dom/JsonObject.h"
#include "HttpRetrySystem.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonWriter.h"

namespace stratis {
namespace api {

typedef TSharedRef<TJsonWriter<>> JsonWriter;
using namespace FHttpRetrySystem;

struct STRATISAPI_API HttpRetryManager : public FManager, public FTickerObjectBase {
    using FManager::FManager;

    bool Tick(float DeltaTime) final;
};

struct STRATISAPI_API HttpRetryParams {
    HttpRetryParams(
        const FRetryLimitCountSetting& InRetryLimitCountOverride = FRetryLimitCountSetting(),
        const FRetryTimeoutRelativeSecondsSetting& InRetryTimeoutRelativeSecondsOverride = FRetryTimeoutRelativeSecondsSetting(),
        const FRetryResponseCodes& InRetryResponseCodes = FRetryResponseCodes(),
        const FRetryVerbs& InRetryVerbs = FRetryVerbs(),
        const FRetryDomainsPtr& InRetryDomains = FRetryDomainsPtr());

    FRetryLimitCountSetting RetryLimitCountOverride;
    FRetryTimeoutRelativeSecondsSetting RetryTimeoutRelativeSecondsOverride;
    FRetryResponseCodes RetryResponseCodes;
    FRetryVerbs RetryVerbs;
    FRetryDomainsPtr RetryDomains;
};

class STRATISAPI_API Model
{
public:
    virtual ~Model() {}
    virtual void WriteJson(JsonWriter& Writer) const = 0;
    virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) = 0;
};

class STRATISAPI_API Request
{
public:
    virtual ~Request() {}
    virtual void SetupHttpRequest(const FHttpRequestRef& HttpRequest) const = 0;
    virtual FString ComputePath() const = 0;

    /* Enables retry and optionally sets a retry policy for this request */
    void SetShouldRetry(const HttpRetryParams& Params = HttpRetryParams()) { RetryParams = Params; }
    const TOptional<HttpRetryParams>& GetRetryParams() const { return RetryParams; }

private:
    TOptional<HttpRetryParams> RetryParams;
};

class STRATISAPI_API Response
{
public:
    virtual ~Response() {}
    virtual bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) = 0;

    void SetSuccessful(bool InSuccessful) { Successful = InSuccessful; }
    bool IsSuccessful() const { return Successful; }

    virtual void SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode);
    EHttpResponseCodes::Type GetHttpResponseCode() const { return ResponseCode; }

    void SetResponseString(const FString& InResponseString) { ResponseString = InResponseString; }
    const FString& GetResponseString() const { return ResponseString; }

    void SetHttpResponse(const FHttpResponsePtr& InHttpResponse) { HttpResponse = InHttpResponse; }
    const FHttpResponsePtr& GetHttpResponse() const { return HttpResponse; }

private:
    bool Successful;
    EHttpResponseCodes::Type ResponseCode;
    FString ResponseString;
    FHttpResponsePtr HttpResponse;
};

} // namespace api
} // namespace stratis
