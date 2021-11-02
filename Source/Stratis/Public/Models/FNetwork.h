#pragma once

#include "FNetwork.generated.h"

USTRUCT(BlueprintType)
struct STRATIS_API FNetwork {
  GENERATED_USTRUCT_BODY()

  static FNetwork STRAX;
  static FNetwork STRAX_TEST;
  static FNetwork CIRRUS;
  static FNetwork CIRRUS_TEST;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  uint8 base58_pubkey_address_prefix;

  FNetwork() {}

  FNetwork(uint8 prefix) : base58_pubkey_address_prefix(prefix) {}
};
