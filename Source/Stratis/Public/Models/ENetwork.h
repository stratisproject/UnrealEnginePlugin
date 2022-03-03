// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

UENUM(BlueprintType)
enum class ENetwork : uint8 {
    STRAX = 0 UMETA(DisplayName = "Strax"),
    STRAX_TEST = 1 UMETA(DisplayName = "StraxTest"),
    CIRRUS = 2 UMETA(DisplayName = "Cirrus"),
    CIRRUS_TEST = 3 UMETA(DisplayName = "CirrusTest"),
    CUSTOM = 4 UMETA(DisplayName = "Custom")
};
