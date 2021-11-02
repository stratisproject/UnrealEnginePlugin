#pragma once

#include "LibbitcoinSafeImports.h"
#include "Utils.h"

namespace converters
{
    libbitcoin::system::chain::script makeP2PKH(const libbitcoin::system::wallet::payment_address &address)
    {
        return libbitcoin::system::chain::script(libbitcoin::system::chain::script::to_pay_key_hash_pattern(address.hash()));
    }

    libbitcoin::system::wallet::payment_address makeAddress(const FString &address)
    {
        return libbitcoin::system::wallet::payment_address(TO_STD_STRING(address));
    }
}