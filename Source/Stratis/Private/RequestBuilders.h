// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "UnrealApiOperations.h"

#include "Transaction.h"

#include "Models/FLocalCallData.h"

namespace request_builders {
stratis::api::UnrealApi::Unity3dGetaddressbalanceGetRequest
buildGetBalanceRequest(const FString& address);
stratis::api::UnrealApi::Unity3dGetutxosforaddressGetRequest
buildGetUtxosRequest(const FString& address);
stratis::api::UnrealApi::Unity3dSendTransactionPostRequest
buildSendTransactionRequest(const Transaction& address);
stratis::api::UnrealApi::Unity3dLocalCallPostRequest
buildLocalCallRequest(const FLocalCallData& data);
stratis::api::UnrealApi::Unity3dReceiptGetRequest
buildGetReceiptRequest(const FString& transactionID);
stratis::api::UnrealApi::Unity3dWatchNftContractGetRequest
buildWatchNFTContractRequest(const FString& address);
stratis::api::UnrealApi::Unity3dGetOwnedNftsGetRequest
buildGetOwnedNFTsRequest(const FString& address);
} // namespace request_builders
