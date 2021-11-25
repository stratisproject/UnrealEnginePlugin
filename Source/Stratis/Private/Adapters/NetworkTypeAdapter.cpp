#pragma once

#include "Adapters/NetworkTypeAdapter.h"

StratisNetwork adapters::fromFNetwork(FNetwork network)
{
    return {.base58_pubkey_address_prefix = network.base58_pubkey_address_prefix};
}
