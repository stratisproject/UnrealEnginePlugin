// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <SmartContracts/MethodParameter.h>

#include "SmartContracts/MethodParameters/BoolMethodParameter.h"
#include "SmartContracts/MethodParameters/IntegerMethodParameter.h"
#include "SmartContracts/MethodParameters/LargeUintMethodParameter.h"
#include "SmartContracts/MethodParameters/StringMethodParameter.h"
#include "SmartContracts/MethodParameters/AddressMethodParameter.h"
#include "SmartContracts/MethodParameters/ByteArrayMethodParameter.h"

#include "CoreMinimal.h"

namespace smart_contracts
{

    namespace method_parameter
    {

        TUniquePtr<MethodParameter> convert(bool value)
        {
            return MakeUnique<BoolMethodParameter>(value);
        }

        TUniquePtr<MethodParameter> convert(uint8_t value)
        {
            return MakeUnique<IntegerMethodParameter<uint8_t> >(value);
        }

        TUniquePtr<MethodParameter> convert(uint16_t value)
        {
            return MakeUnique<IntegerMethodParameter<uint16_t> >(value);
        }

        TUniquePtr<MethodParameter> convert(uint32_t value)
        {
            return MakeUnique<IntegerMethodParameter<uint32_t> >(value);
        }

        TUniquePtr<MethodParameter> convert(int32_t value)
        {
            return MakeUnique<IntegerMethodParameter<int32_t> >(value);
        }

        TUniquePtr<MethodParameter> convert(uint64_t value)
        {
            return MakeUnique<IntegerMethodParameter<uint64_t> >(value);
        }

        TUniquePtr<MethodParameter> convert(int64_t value)
        {
            return MakeUnique<IntegerMethodParameter<int64_t> >(value);
        }

        TUniquePtr<MethodParameter> convert(const Uint128 &value)
        {
            return MakeUnique<LargeUintMethodParameter<128> >(value);
        }

        TUniquePtr<MethodParameter> convert(Uint128 &&value)
        {
            return MakeUnique<LargeUintMethodParameter<128> >(MoveTemp(value));
        }

        TUniquePtr<MethodParameter> convert(const Uint256 &value)
        {
            return MakeUnique<LargeUintMethodParameter<256> >(value);
        }

        TUniquePtr<MethodParameter> convert(Uint256 &&value)
        {
            return MakeUnique<LargeUintMethodParameter<256> >(MoveTemp(value));
        }

        TUniquePtr<MethodParameter> convert(const TCHAR *value)
        {
            return MakeUnique<StringMethodParameter>(value);
        }

        TUniquePtr<MethodParameter> convert(const FString &value)
        {
            return MakeUnique<StringMethodParameter>(value);
        }

        TUniquePtr<MethodParameter> convert(FString &&value)
        {
            return MakeUnique<StringMethodParameter>(MoveTemp(value));
        }

        TUniquePtr<MethodParameter> convert(const Address &value)
        {
            return MakeUnique<AddressMethodParameter>(value);
        }

        TUniquePtr<MethodParameter> convert(Address &&value)
        {
            return MakeUnique<AddressMethodParameter>(MoveTemp(value));
        }

        TUniquePtr<MethodParameter> convert(const TArray<uint8> &value)
        {
            return MakeUnique<ByteArrayMethodParameter>(value);
        }

        TUniquePtr<MethodParameter> convert(TArray<uint8> &&value)
        {
            return MakeUnique<ByteArrayMethodParameter>(MoveTemp(value));
        }

    }

}
