#pragma once

UENUM(BlueprintType)
enum class ENetwork : uint8 {
    STRAX = 0 UMETA(DisplayName = "Strax"),
    STRAX_TEST = 1 UMETA(DisplayName = "StraxTest"),
    CIRRUS = 2 UMETA(DisplayName = "Cirrus"),
    CIRRUS_TEST = 3 UMETA(DisplayName = "CirrusTest"),
    CUSTOM = 4 UMETA(DisplayName = "Custom")
};