#include <stddef.h>

#include <trezor/ed25519-donna/ed25519-keccak.h>
#include <trezor/ed25519-donna/ed25519-hash-custom-keccak.h>

#define ED25519_SUFFIX _keccak

#include "ed25519.c"
