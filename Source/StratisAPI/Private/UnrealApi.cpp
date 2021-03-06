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

#include "UnrealApi.h"

#include "StratisAPIModule.h"
#include "UnrealApiOperations.h"

#include "HttpModule.h"
#include "Serialization/JsonSerializer.h"

namespace stratis {
namespace api {

UnrealApi::UnrealApi()
    : Url(TEXT("http://localhost"))
{
}

UnrealApi::~UnrealApi() {}

void UnrealApi::SetURL(const FString& InUrl)
{
    Url = InUrl;
}

void UnrealApi::AddHeaderParam(const FString& Key, const FString& Value)
{
    AdditionalHeaderParams.Add(Key, Value);
}

void UnrealApi::ClearHeaderParams()
{
    AdditionalHeaderParams.Reset();
}

bool UnrealApi::IsValid() const
{
    if (Url.IsEmpty()) {
        UE_LOG(LogStratisAPI, Error, TEXT("UnrealApi: Endpoint Url is not set, request cannot be performed"));
        return false;
    }

    return true;
}

void UnrealApi::SetHttpRetryManager(FHttpRetrySystem::FManager& InRetryManager)
{
    if (RetryManager != &GetHttpRetryManager()) {
        DefaultRetryManager.Reset();
        RetryManager = &InRetryManager;
    }
}

FHttpRetrySystem::FManager& UnrealApi::GetHttpRetryManager()
{
    checkf(RetryManager, TEXT("UnrealApi: RetryManager is null.  You may have meant to set it with SetHttpRetryManager first, or you may not be using a custom RetryManager at all.")) return *RetryManager;
}

FHttpRequestRef UnrealApi::CreateHttpRequest(const Request& Request) const
{
    if (!Request.GetRetryParams().IsSet()) {
        return FHttpModule::Get().CreateRequest();
    } else {
        if (!RetryManager) {
            // Create default retry manager if none was specified
            DefaultRetryManager = MakeUnique<HttpRetryManager>(6, 60);
            RetryManager = DefaultRetryManager.Get();
        }

        const HttpRetryParams& Params = Request.GetRetryParams().GetValue();
        return RetryManager->CreateRequest(Params.RetryLimitCountOverride, Params.RetryTimeoutRelativeSecondsOverride, Params.RetryResponseCodes, Params.RetryVerbs, Params.RetryDomains);
    }
}

void UnrealApi::HandleResponse(FHttpResponsePtr HttpResponse, bool bSucceeded, Response& InOutResponse) const
{
    InOutResponse.SetHttpResponse(HttpResponse);
    InOutResponse.SetSuccessful(bSucceeded);

    if (bSucceeded && HttpResponse.IsValid()) {
        InOutResponse.SetHttpResponseCode((EHttpResponseCodes::Type)HttpResponse->GetResponseCode());
        FString ContentType = HttpResponse->GetContentType();
        FString Content(HttpResponse->GetContentAsString());
        UE_LOG(LogTemp, Error, TEXT("Result content: %s"), *Content);
        if (ContentType.IsEmpty()) {
            return; // Nothing to parse
        } else if (ContentType.StartsWith(TEXT("application/json")) || ContentType.StartsWith("text/json")) {
            Content = HttpResponse->GetContentAsString();

            TSharedPtr<FJsonValue> JsonValue;
            auto Reader = TJsonReaderFactory<>::Create(Content);

            if (FJsonSerializer::Deserialize(Reader, JsonValue) && JsonValue.IsValid()) {
                if (InOutResponse.FromJson(JsonValue))
                    return; // Successfully parsed
            }
        } else if (ContentType.StartsWith(TEXT("text/plain"))) {
            Content = HttpResponse->GetContentAsString();
            InOutResponse.SetResponseString(Content);
            return; // Successfully parsed
        }

        // Report the parse error but do not mark the request as unsuccessful. Data could be partial or malformed, but the request succeeded.
        UE_LOG(LogStratisAPI, Error, TEXT("Failed to deserialize Http response content (type:%s):\n%s"), *ContentType, *Content);
        return;
    }

    // By default, assume we failed to establish connection
    InOutResponse.SetHttpResponseCode(EHttpResponseCodes::RequestTimeout);
}

FHttpRequestPtr UnrealApi::Unity3dBlockGet(const Unity3dBlockGetRequest& Request, const FUnity3dBlockGetDelegate& Delegate /*= FUnity3dBlockGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dBlockGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dBlockGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dBlockGetDelegate Delegate) const
{
    Unity3dBlockGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetAllNftOwnersByContractAddressGet(const Unity3dGetAllNftOwnersByContractAddressGetRequest& Request, const FUnity3dGetAllNftOwnersByContractAddressGetDelegate& Delegate /*= FUnity3dGetAllNftOwnersByContractAddressGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetAllNftOwnersByContractAddressGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetAllNftOwnersByContractAddressGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetAllNftOwnersByContractAddressGetDelegate Delegate) const
{
    Unity3dGetAllNftOwnersByContractAddressGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetOwnedNftsGet(const Unity3dGetOwnedNftsGetRequest& Request, const FUnity3dGetOwnedNftsGetDelegate& Delegate /*= FUnity3dGetOwnedNftsGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetOwnedNftsGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetOwnedNftsGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetOwnedNftsGetDelegate Delegate) const
{
    Unity3dGetOwnedNftsGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetWatchedNftContractsGet(const Unity3dGetWatchedNftContractsGetRequest& Request, const FUnity3dGetWatchedNftContractsGetDelegate& Delegate /*= FUnity3dGetWatchedNftContractsGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetWatchedNftContractsGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetWatchedNftContractsGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetWatchedNftContractsGetDelegate Delegate) const
{
    Unity3dGetWatchedNftContractsGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetaddressbalanceGet(const Unity3dGetaddressbalanceGetRequest& Request, const FUnity3dGetaddressbalanceGetDelegate& Delegate /*= FUnity3dGetaddressbalanceGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetaddressbalanceGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetaddressbalanceGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetaddressbalanceGetDelegate Delegate) const
{
    Unity3dGetaddressbalanceGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetblockheaderGet(const Unity3dGetblockheaderGetRequest& Request, const FUnity3dGetblockheaderGetDelegate& Delegate /*= FUnity3dGetblockheaderGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetblockheaderGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetblockheaderGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetblockheaderGetDelegate Delegate) const
{
    Unity3dGetblockheaderGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetrawtransactionGet(const Unity3dGetrawtransactionGetRequest& Request, const FUnity3dGetrawtransactionGetDelegate& Delegate /*= FUnity3dGetrawtransactionGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetrawtransactionGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetrawtransactionGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetrawtransactionGetDelegate Delegate) const
{
    Unity3dGetrawtransactionGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dGetutxosforaddressGet(const Unity3dGetutxosforaddressGetRequest& Request, const FUnity3dGetutxosforaddressGetDelegate& Delegate /*= FUnity3dGetutxosforaddressGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dGetutxosforaddressGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dGetutxosforaddressGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dGetutxosforaddressGetDelegate Delegate) const
{
    Unity3dGetutxosforaddressGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dLocalCallPost(const Unity3dLocalCallPostRequest& Request, const FUnity3dLocalCallPostDelegate& Delegate /*= FUnity3dLocalCallPostDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dLocalCallPostResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dLocalCallPostResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dLocalCallPostDelegate Delegate) const
{
    Unity3dLocalCallPostResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dReceiptGet(const Unity3dReceiptGetRequest& Request, const FUnity3dReceiptGetDelegate& Delegate /*= FUnity3dReceiptGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dReceiptGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dReceiptGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dReceiptGetDelegate Delegate) const
{
    Unity3dReceiptGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dReceiptSearchGet(const Unity3dReceiptSearchGetRequest& Request, const FUnity3dReceiptSearchGetDelegate& Delegate /*= FUnity3dReceiptSearchGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dReceiptSearchGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dReceiptSearchGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dReceiptSearchGetDelegate Delegate) const
{
    Unity3dReceiptSearchGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dReindexAllContractsGet(const Unity3dReindexAllContractsGetRequest& Request, const FUnity3dReindexAllContractsGetDelegate& Delegate /*= FUnity3dReindexAllContractsGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dReindexAllContractsGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dReindexAllContractsGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dReindexAllContractsGetDelegate Delegate) const
{
    Unity3dReindexAllContractsGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dSendTransactionPost(const Unity3dSendTransactionPostRequest& Request, const FUnity3dSendTransactionPostDelegate& Delegate /*= FUnity3dSendTransactionPostDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dSendTransactionPostResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dSendTransactionPostResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dSendTransactionPostDelegate Delegate) const
{
    Unity3dSendTransactionPostResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dTipGet(const Unity3dTipGetRequest& Request, const FUnity3dTipGetDelegate& Delegate /*= FUnity3dTipGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dTipGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dTipGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dTipGetDelegate Delegate) const
{
    Unity3dTipGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dUnwatchNftContractGet(const Unity3dUnwatchNftContractGetRequest& Request, const FUnity3dUnwatchNftContractGetDelegate& Delegate /*= FUnity3dUnwatchNftContractGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dUnwatchNftContractGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dUnwatchNftContractGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dUnwatchNftContractGetDelegate Delegate) const
{
    Unity3dUnwatchNftContractGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dValidateaddressGet(const Unity3dValidateaddressGetRequest& Request, const FUnity3dValidateaddressGetDelegate& Delegate /*= FUnity3dValidateaddressGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dValidateaddressGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dValidateaddressGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dValidateaddressGetDelegate Delegate) const
{
    Unity3dValidateaddressGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dWatchNftContractGet(const Unity3dWatchNftContractGetRequest& Request, const FUnity3dWatchNftContractGetDelegate& Delegate /*= FUnity3dWatchNftContractGetDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dWatchNftContractGetResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dWatchNftContractGetResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dWatchNftContractGetDelegate Delegate) const
{
    Unity3dWatchNftContractGetResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

FHttpRequestPtr UnrealApi::Unity3dWatchNftContractsPost(const Unity3dWatchNftContractsPostRequest& Request, const FUnity3dWatchNftContractsPostDelegate& Delegate /*= FUnity3dWatchNftContractsPostDelegate()*/) const
{
    if (!IsValid())
        return nullptr;

    FHttpRequestRef HttpRequest = CreateHttpRequest(Request);
    HttpRequest->SetURL(*(Url + Request.ComputePath()));

    for (const auto& It : AdditionalHeaderParams) {
        HttpRequest->SetHeader(It.Key, It.Value);
    }

    Request.SetupHttpRequest(HttpRequest);

    HttpRequest->OnProcessRequestComplete().BindRaw(this, &UnrealApi::OnUnity3dWatchNftContractsPostResponse, Delegate);
    HttpRequest->ProcessRequest();
    return HttpRequest;
}

void UnrealApi::OnUnity3dWatchNftContractsPostResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FUnity3dWatchNftContractsPostDelegate Delegate) const
{
    Unity3dWatchNftContractsPostResponse Response;
    HandleResponse(HttpResponse, bSucceeded, Response);
    Delegate.ExecuteIfBound(Response);
}

} // namespace api
} // namespace stratis
