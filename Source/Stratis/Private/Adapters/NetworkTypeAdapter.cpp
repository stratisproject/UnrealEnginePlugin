// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Adapters/NetworkTypeAdapter.h"

StratisNetwork adapters::fromFNetwork(FNetwork network)
{
    auto prefix = network.base58_pubkey_address_prefix;

    if (prefix == FNetwork::STRAX.base58_pubkey_address_prefix) {
        return StratisNetwork::STRAX;
    } else if (prefix == FNetwork::STRAX_TEST.base58_pubkey_address_prefix) {
        return StratisNetwork::STRAX_TEST;
    } else if (prefix == FNetwork::CIRRUS.base58_pubkey_address_prefix) {
        return StratisNetwork::CIRRUS;
    } else if (prefix == FNetwork::CIRRUS_TEST.base58_pubkey_address_prefix) {
        return StratisNetwork::CIRRUS_TEST;
    } else {
        return StratisNetwork::STRAX;
    }
}
