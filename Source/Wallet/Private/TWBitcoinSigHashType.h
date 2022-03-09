// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

enum TWBitcoinSigHashType {
    TWBitcoinSigHashTypeAll = 0x01,
    TWBitcoinSigHashTypeNone = 0x02,
    TWBitcoinSigHashTypeSingle = 0x03,
    TWBitcoinSigHashTypeFork = 0x40,
    TWBitcoinSigHashTypeForkBTG = 0x4f40,
    TWBitcoinSigHashTypeAnyoneCanPay = 0x80
};