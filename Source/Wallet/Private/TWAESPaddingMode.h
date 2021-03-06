// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

enum TWAESPaddingMode {
    TWAESPaddingModeZero = 0,  // padding value is zero
    TWAESPaddingModePKCS7 = 1, // padding value is the number of padding bytes; for even size add an extra block
};
