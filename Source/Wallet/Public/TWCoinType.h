// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

/// Coin type for Level 2 of BIP44.
///
/// - SeeAlso: https://github.com/satoshilabs/slips/blob/master/slip-0044.md
enum TWCoinType {
    TWCoinTypeStrax = 105105,
    TWCoinTypeStraxTest = 1,
    TWCoinTypeCirrus = 401,
    TWCoinTypeCirrusTest = 400,
    TWCoinTypeBitcoin = 0
};
