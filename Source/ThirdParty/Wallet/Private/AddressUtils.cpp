// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "AddressUtils.h"

#include "Address.h"

TW::Data TW::addressToHex(std::string address)
{
    TW::Bitcoin::Address addressTyped(address);
    TW::Data result(addressTyped.bytes.begin() + 1, addressTyped.bytes.end());
    return result;
}