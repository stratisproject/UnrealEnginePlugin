// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "CoreMinimal.h"

#include "Address.h"
#include "UintTypes.h"

#include <type_traits>
#include <vector>

namespace smart_contracts
{

    namespace method_parameter
    {

        class BLOCKCHAIN_API MethodParameter
        {
        public:
            enum class Type : uint8_t
            {
                BOOL = 1,
                BYTE = 2,
                CHAR = 3,
                STRING = 4,
                UINT = 5,
                INT = 6,
                ULONG = 7,
                LONG = 8,
                ADDRESS = 9,
                BYTE_ARRAY = 10,
                UINT128 = 11,
                UINT256 = 12
            };

            virtual ~MethodParameter(){};

            virtual std::vector<uint8_t> serialize() const = 0;
            virtual Type type() const = 0;
        };

        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(bool value);

        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(uint8_t value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(uint16_t value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(uint32_t value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(int32_t value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(uint64_t value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(int64_t value);

        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(const Uint128 &value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(Uint128 &&value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(const Uint256 &value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(Uint256 &&value);

        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(const TCHAR *value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(const FString &value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(FString &&value);

        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(const Address &value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(Address &&value);

        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(const TArray<uint8> &value);
        BLOCKCHAIN_API TUniquePtr<MethodParameter> convert(TArray<uint8> &&value);

        BLOCKCHAIN_API TUniquePtr<MethodParameter> parseFromString(const FString &encodedValue);

    }

}
