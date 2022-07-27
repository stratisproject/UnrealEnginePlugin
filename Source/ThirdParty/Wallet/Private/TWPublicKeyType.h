// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

/// Public key types
enum TWPublicKeyType {
    TWPublicKeyTypeSECP256k1 = 0,
    TWPublicKeyTypeSECP256k1Extended = 1,
    TWPublicKeyTypeNIST256p1 = 2,
    TWPublicKeyTypeNIST256p1Extended = 3,
    TWPublicKeyTypeED25519 = 4,
    TWPublicKeyTypeED25519Blake2b = 5,
    TWPublicKeyTypeCURVE25519 = 6,
    TWPublicKeyTypeED25519Extended = 7,
};
