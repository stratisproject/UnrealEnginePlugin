// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#include <SmartContracts/MethodParameter.h>

#include "DataUtils.h"

namespace smart_contracts
{

    namespace method_parameter
    {

        TUniquePtr<MethodParameter> parseFromString(const FString &encodedValue)
        {
            FString typeString, valueString;
            encodedValue.Split(TEXT("#"), &typeString, &valueString);

            int32 type = FCString::Atoi(*typeString);

            switch (type)
            {
            case (int32)MethodParameter::Type::BOOL:
                if (valueString.Equals(TEXT("true"), ESearchCase::Type::IgnoreCase))
                    return convert(true);
                else
                    return convert(false);

            case (int32)MethodParameter::Type::BYTE:
            {
                int32 value = FCString::Atoi(*valueString);
                return convert((uint8)value);
            }

            case (int32)MethodParameter::Type::CHAR:
                return convert((uint16)valueString[0]);

            case (int32)MethodParameter::Type::STRING:
                return convert(valueString);

            case (int32)MethodParameter::Type::UINT:
            {
                int64 value = FCString::Atoi64(*valueString);
                return convert((uint32)value);
            }

            case (int32)MethodParameter::Type::INT:
            {
                int32 value = FCString::Atoi(*valueString);
                return convert((int32)value);
            }

            case (int32)MethodParameter::Type::ULONG:
            {
                uint64 value = FCString::Strtoui64(*valueString, nullptr, 10);
                return convert((uint64)value);
            }

            case (int32)MethodParameter::Type::LONG:
            {
                int64 value = FCString::Atoi64(*valueString);
                return convert((int64)value);
            }
            case (int32)MethodParameter::Type::ADDRESS:
                return convert(Address(MoveTemp(valueString)));

            case (int32)MethodParameter::Type::BYTE_ARRAY:
                return convert(HexToBytesArray(valueString));

            case (int32)MethodParameter::Type::UINT128:
                return convert(Uint128(valueString));

            case (int32)MethodParameter::Type::UINT256:
                return convert(Uint256(valueString));

            default:
                break;
            }

            return nullptr;
        }
    }

}
