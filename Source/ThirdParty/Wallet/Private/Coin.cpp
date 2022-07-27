// Copyright © 2017-2021 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include "Coin.h"

#include <map>

using namespace TW;
using namespace std;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#endif
bool TW::validateAddress(TWCoinType coin, const std::string& string)
{
    auto p2pkh = TW::p2pkhPrefix(coin);
    auto p2sh = TW::p2shPrefix(coin);
    return Address::isValid(string, {{p2pkh}, {p2sh}});
};

std::string TW::normalizeAddress(TWCoinType coin, const std::string& address)
{
    if (!TW::validateAddress(coin, address)) {
        // invalid address, not normalizing
        return "";
    }

    return address;
}

std::string TW::deriveAddress(TWCoinType coin, const PrivateKey& privateKey)
{
    auto keyType = TW::publicKeyType(coin);
    return TW::deriveAddress(coin, privateKey.getPublicKey(keyType));
}

std::string TW::deriveAddress(TWCoinType coin, const PublicKey& publicKey)
{
    auto p2pkh = TW::p2pkhPrefix(coin);
    return Address(publicKey, p2pkh).string();
}

// Coin info accessors

TWPurpose TW::purpose(TWCoinType coin)
{
    // hardcoded value for Bitcoin/Stratis
    return TWPurpose::TWPurposeBIP44;
}

TWCurve TW::curve(TWCoinType coin)
{
    // hardcoded value for Bitcoin/Stratis
    return TWCurve::TWCurveSECP256k1;
}

DerivationPath TW::derivationPath(TWCoinType coin)
{
    const char* path = nullptr;
    switch (coin) {
    case TWCoinTypeStrax:
        path = "m/44'/105105'/0'/0/0";
        break;
    case TWCoinTypeStraxTest:
        path = "m/44'/1'/0'/0/0";
        break;
    case TWCoinTypeCirrus:
        path = "m/44'/401'/0'/0/0";
        break;
    case TWCoinTypeCirrusTest:
        path = "m/44'/400'/0'/0/0";
        break;
    case TWCoinTypeBitcoin:
        path = "m/84'/0'/0'/0/0";
        break;
    default:
        break;
    }
    return DerivationPath(path);
}

enum TWPublicKeyType TW::publicKeyType(TWCoinType coin)
{
    // hardcoded value for Bitcoin/Stratis
    return TWPublicKeyType::TWPublicKeyTypeSECP256k1;
}

TW::byte TW::p2pkhPrefix(TWCoinType coin)
{
    switch (coin) {
    case TWCoinTypeStrax:
        return 75;
    case TWCoinTypeStraxTest:
        return 120;
    case TWCoinTypeCirrus:
        return 28;
    case TWCoinTypeCirrusTest:
        return 127;
    case TWCoinTypeBitcoin:
        return 0;
    default:
        break;
    }
    return 0;
}

TW::byte TW::p2shPrefix(TWCoinType coin)
{
    switch (coin) {
    case TWCoinTypeStrax:
        return 140;
    case TWCoinTypeStraxTest:
        return 127;
    case TWCoinTypeCirrus:
        return 88;
    case TWCoinTypeCirrusTest:
        return 137;
    case TWCoinTypeBitcoin:
        return 5;
    default:
        break;
    }
    return 0;
}

Hash::Hasher TW::publicKeyHasher(TWCoinType coin)
{
    // hardcoded value for Bitcoin/Stratis
    return Hash::sha256ripemd;
}

Hash::Hasher TW::base58Hasher(TWCoinType coin)
{
    // hardcoded value for Bitcoin/Stratis
    return Hash::sha256d;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif