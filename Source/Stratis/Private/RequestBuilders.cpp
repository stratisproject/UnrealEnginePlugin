#include "RequestBuilders.h"

namespace request_builders {
stratis::api::UnrealApi::Unity3dGetaddressbalanceGetRequest
buildGetBalanceRequest(const FString& address)
{
    stratis::api::UnrealApi::Unity3dGetaddressbalanceGetRequest request;
    request.Address = address;
    return request;
}

stratis::api::UnrealApi::Unity3dGetutxosforaddressGetRequest
buildGetUtxosRequest(const FString& address)
{
    stratis::api::UnrealApi::Unity3dGetutxosforaddressGetRequest request;
    request.Address = address;
    return request;
}

stratis::api::UnrealApi::Unity3dSendTransactionPostRequest
buildSendTransactionRequest(const FString& transactionHex)
{
    stratis::api::UnrealApi::Unity3dSendTransactionPostRequest request;
    stratis::api::SendTransactionRequest sendTransactionRequest;

    sendTransactionRequest.Hex = transactionHex;
    request.SendTransactionRequest = sendTransactionRequest;

    return request;
}

stratis::api::UnrealApi::Unity3dApiUnity3dLocalCallPostRequest
buildLocalCallRequest(const FLocalCallData& data)
{
    stratis::api::UnrealApi::Unity3dApiUnity3dLocalCallPostRequest request;
    stratis::api::LocalCallContractRequest requestData;

    requestData.ContractAddress = data.contractAddress;
    requestData.MethodName = data.methodName;

    if (!data.amount.IsEmpty()) {
        requestData.Amount = data.amount;
    }

    if (data.blockHeight != UNINITIALIZED) {
        requestData.BlockHeight = data.blockHeight;
    }

    if (data.gasPrice != UNINITIALIZED) {
        requestData.GasPrice = data.gasPrice;
    }

    if (data.gasLimit != UNINITIALIZED) {
        requestData.GasLimit = data.gasLimit;
    }

    if (!data.sender.IsEmpty()) {
        requestData.Sender = data.sender;
    }

    if (data.parameters.Num() != 0) {
        requestData.Parameters = data.parameters;
    }

    request.LocalCallContractRequest = requestData;

    return request;
}

stratis::api::UnrealApi::Unity3dApiUnity3dReceiptGetRequest
buildGetReceiptRequest(const FString& transactionID)
{
    stratis::api::UnrealApi::Unity3dApiUnity3dReceiptGetRequest request;
    request.TxHash = transactionID;
    return request;
}
} // namespace request_builders