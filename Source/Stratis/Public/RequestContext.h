// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Core.h"
#include "UnrealApi.h"

using ApiDelegate = TVariant<
    stratis::api::UnrealApi::FUnity3dApiUnity3dLocalCallPostDelegate,
    stratis::api::UnrealApi::FUnity3dApiUnity3dReceiptGetDelegate,
    stratis::api::UnrealApi::FUnity3dBlockGetDelegate,
    stratis::api::UnrealApi::FUnity3dGetaddressbalanceGetDelegate,
    stratis::api::UnrealApi::FUnity3dGetblockheaderGetDelegate,
    stratis::api::UnrealApi::FUnity3dGetrawtransactionGetDelegate,
    stratis::api::UnrealApi::FUnity3dGetutxosforaddressGetDelegate,
    stratis::api::UnrealApi::FUnity3dSendTransactionPostDelegate,
    stratis::api::UnrealApi::FUnity3dTipGetDelegate,
    stratis::api::UnrealApi::FUnity3dValidateaddressGetDelegate>;

struct RequestContext {
    FHttpRequestPtr request;
    TSharedPtr<ApiDelegate> delegate;
};
