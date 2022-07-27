// Copyright © 2017-2020 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Data.h"
#include "DerivationPath.h"
#include "Hash.h"
#include "PrivateKey.h"
#include "PublicKey.h"

#include "TWCoinType.h"
#include "TWCurve.h"
#include "TWHDVersion.h"
#include "TWPurpose.h"

#include <string>
#include <vector>

namespace TW {

/// Validates an address for a particular coin.
bool validateAddress(TWCoinType coin, const std::string& address);

/// Validates and normalizes an address for a particular coin.
std::string normalizeAddress(TWCoinType coin, const std::string& address);

/// Returns the purpose for a coin type.
TWPurpose purpose(TWCoinType coin);

/// Returns the curve that should be used for a coin type.
TWCurve curve(TWCoinType coin);

/// Returns the default derivation path for a particular coin.
DerivationPath derivationPath(TWCoinType coin);

/// Returns the public key type for a particular coin.
enum TWPublicKeyType publicKeyType(TWCoinType coin);

/// Derives the address for a particular coin from the private key.
std::string deriveAddress(TWCoinType coin, const PrivateKey& privateKey);

/// Derives the address for a particular coin from the public key.
std::string deriveAddress(TWCoinType coin, const PublicKey& publicKey);

/// Hasher for deriving the public key hash.
Hash::Hasher publicKeyHasher(TWCoinType coin);

/// Hasher to use for base 58 checksums.
Hash::Hasher base58Hasher(TWCoinType coin);

/// Returns P2PKH prefix for a coin type.
TW::byte p2pkhPrefix(TWCoinType coin);

/// Returns P2SH prefix for a coin type.
TW::byte p2shPrefix(TWCoinType coin);

} // namespace TW
