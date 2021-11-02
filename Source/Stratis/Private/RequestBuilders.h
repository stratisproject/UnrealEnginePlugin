#pragma once

#include "UnrealApiOperations.h"

#include "Transaction.h"

#include "Models/FLocalCallData.h"

namespace request_builders {
stratis::api::UnrealApi::Unity3dGetaddressbalanceGetRequest
buildGetBalanceRequest(const FString &address);
stratis::api::UnrealApi::Unity3dGetutxosforaddressGetRequest
buildGetUtxosRequest(const FString &address);
stratis::api::UnrealApi::Unity3dSendTransactionPostRequest
buildSendTransactionRequest(const Transaction &address);
stratis::api::UnrealApi::Unity3dApiUnity3dLocalCallPostRequest
buildLocalCallRequest(const FLocalCallData &data);
stratis::api::UnrealApi::Unity3dApiUnity3dReceiptGetRequest
buildGetReceiptRequest(const FString &transactionID);
} // namespace request_builders