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

#include "UnrealApiOperations.h"

#include "StratisAPIModule.h"
#include "Helpers.h"

#include "Dom/JsonObject.h"
#include "Templates/SharedPointer.h"
#include "HttpModule.h"
#include "PlatformHttp.h"

namespace stratis 
{
namespace api 
{

FString UnrealApi::Unity3dApiUnity3dLocalCallPostRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/api/Unity3d/local-call"));
	return Path;
}

void UnrealApi::Unity3dApiUnity3dLocalCallPostRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json-patch+json"), TEXT("application/json"), TEXT("text/json"), TEXT("application/_*+json") };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		if (LocalCallContractRequest.IsSet())
		{
			WriteJsonValue(Writer, LocalCallContractRequest.GetValue());
		}
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Body parameter (LocalCallContractRequest) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Body parameter (LocalCallContractRequest) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dApiUnity3dLocalCallPostResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request"));
		break;
	case 500:
		SetResponseString(TEXT("Server Error"));
		break;
	}
}

bool UnrealApi::Unity3dApiUnity3dLocalCallPostResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dApiUnity3dReceiptGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/api/Unity3d/receipt"));
	TArray<FString> QueryParams;
	if(TxHash.IsSet())
	{
		QueryParams.Add(FString(TEXT("txHash=")) + ToUrlString(TxHash.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dApiUnity3dReceiptGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dApiUnity3dReceiptGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request"));
		break;
	}
}

bool UnrealApi::Unity3dApiUnity3dReceiptGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dBlockGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/block"));
	TArray<FString> QueryParams;
	QueryParams.Add(FString(TEXT("Hash=")) + ToUrlString(Hash));
	if(ShowTransactionDetails.IsSet())
	{
		QueryParams.Add(FString(TEXT("ShowTransactionDetails=")) + ToUrlString(ShowTransactionDetails.GetValue()));
	}
	if(OutputJson.IsSet())
	{
		QueryParams.Add(FString(TEXT("OutputJson=")) + ToUrlString(OutputJson.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dBlockGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dBlockGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request"));
		break;
	}
}

bool UnrealApi::Unity3dBlockGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dGetaddressbalanceGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/getaddressbalance"));
	TArray<FString> QueryParams;
	if(Address.IsSet())
	{
		QueryParams.Add(FString(TEXT("address=")) + ToUrlString(Address.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dGetaddressbalanceGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dGetaddressbalanceGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request"));
		break;
	}
}

bool UnrealApi::Unity3dGetaddressbalanceGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dGetblockheaderGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/getblockheader"));
	TArray<FString> QueryParams;
	if(Hash.IsSet())
	{
		QueryParams.Add(FString(TEXT("hash=")) + ToUrlString(Hash.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dGetblockheaderGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dGetblockheaderGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	}
}

bool UnrealApi::Unity3dGetblockheaderGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dGetrawtransactionGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/getrawtransaction"));
	TArray<FString> QueryParams;
	if(Trxid.IsSet())
	{
		QueryParams.Add(FString(TEXT("trxid=")) + ToUrlString(Trxid.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dGetrawtransactionGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dGetrawtransactionGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	}
}

bool UnrealApi::Unity3dGetrawtransactionGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dGetutxosforaddressGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/getutxosforaddress"));
	TArray<FString> QueryParams;
	if(Address.IsSet())
	{
		QueryParams.Add(FString(TEXT("address=")) + ToUrlString(Address.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dGetutxosforaddressGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dGetutxosforaddressGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	}
}

bool UnrealApi::Unity3dGetutxosforaddressGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dSendTransactionPostRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/send-transaction"));
	return Path;
}

void UnrealApi::Unity3dSendTransactionPostRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = { TEXT("application/json-patch+json"), TEXT("application/json"), TEXT("text/json"), TEXT("application/_*+json") };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("POST"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
		// Body parameters
		FString JsonBody;
		JsonWriter Writer = TJsonWriterFactory<>::Create(&JsonBody);

		if (SendTransactionRequest.IsSet())
		{
			WriteJsonValue(Writer, SendTransactionRequest.GetValue());
		}
		Writer->Close();

		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
		HttpRequest->SetContentAsString(JsonBody);
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Body parameter (SendTransactionRequest) was ignored, not supported in multipart form"));
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Body parameter (SendTransactionRequest) was ignored, not supported in urlencoded requests"));
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dSendTransactionPostResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request"));
		break;
	case 403:
		SetResponseString(TEXT("Forbidden"));
		break;
	case 500:
		SetResponseString(TEXT("Server Error"));
		break;
	}
}

bool UnrealApi::Unity3dSendTransactionPostResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return true;
}

FString UnrealApi::Unity3dTipGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/tip"));
	return Path;
}

void UnrealApi::Unity3dTipGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dTipGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	case 400:
		SetResponseString(TEXT("Bad Request"));
		break;
	}
}

bool UnrealApi::Unity3dTipGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

FString UnrealApi::Unity3dValidateaddressGetRequest::ComputePath() const
{
	FString Path(TEXT("/Unity3d/validateaddress"));
	TArray<FString> QueryParams;
	if(Address.IsSet())
	{
		QueryParams.Add(FString(TEXT("address=")) + ToUrlString(Address.GetValue()));
	}
	Path += TCHAR('?');
	Path += FString::Join(QueryParams, TEXT("&"));

	return Path;
}

void UnrealApi::Unity3dValidateaddressGetRequest::SetupHttpRequest(const FHttpRequestRef& HttpRequest) const
{
	static const TArray<FString> Consumes = {  };
	//static const TArray<FString> Produces = { TEXT("text/plain"), TEXT("application/json"), TEXT("text/json") };

	HttpRequest->SetVerb(TEXT("GET"));

	// Default to Json Body request
	if (Consumes.Num() == 0 || Consumes.Contains(TEXT("application/json")))
	{
	}
	else if (Consumes.Contains(TEXT("multipart/form-data")))
	{
	}
	else if (Consumes.Contains(TEXT("application/x-www-form-urlencoded")))
	{
	}
	else
	{
		UE_LOG(LogStratisAPI, Error, TEXT("Request ContentType not supported (%s)"), *FString::Join(Consumes, TEXT(",")));
	}
}

void UnrealApi::Unity3dValidateaddressGetResponse::SetHttpResponseCode(EHttpResponseCodes::Type InHttpResponseCode)
{
	Response::SetHttpResponseCode(InHttpResponseCode);
	switch ((int)InHttpResponseCode)
	{
	case 200:
		SetResponseString(TEXT("Success"));
		break;
	}
}

bool UnrealApi::Unity3dValidateaddressGetResponse::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	return TryGetJsonValue(JsonValue, Content);
}

}
}
