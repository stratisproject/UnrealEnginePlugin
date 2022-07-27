// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "FNetwork.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FNetwork {
    GENERATED_USTRUCT_BODY()

    static FNetwork STRAX;
    static FNetwork STRAX_TEST;
    static FNetwork CIRRUS;
    static FNetwork CIRRUS_TEST;

    UPROPERTY(BlueprintReadOnly, Category = "Default")
    uint8 base58_pubkey_address_prefix;

    FNetwork() {}

    FNetwork(uint8 prefix) : base58_pubkey_address_prefix(prefix) {}
};
