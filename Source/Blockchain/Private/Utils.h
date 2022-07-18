// Copyright © 2022 Stratis Platform.
//
// This file is part of Stratis Plugin for Unreal Engine. The full copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Address.h"
#include "CoreMinimal.h"
#include "Transaction.h"

#include "Data.h"
#include "HexCoding.h"

#include "AddressUtils.h"

#include <string>
#include <vector>

#ifndef TO_STD_STRING
#define TO_STD_STRING(f_string) std::string(TCHAR_TO_UTF8(*f_string))
#endif

#ifndef TO_FSTRING
#define TO_FSTRING(std_string) UTF8_TO_TCHAR(std_string.c_str())
#endif

namespace utils {

template <typename T>
TArray<T> asTArray(const std::vector<T>& value)
{
    return TArray<T>(value.data(), value.size());
}

template <typename T>
std::vector<T> asVector(const TArray<T>& value)
{
    std::vector<T> result(value.Num());

    for (int32 i = 0; i < value.Num(); i++) {
        result[i] = value[i];
    }

    return result;
}

TW::Data asData(const TArray<uint8>& value)
{
    return asVector(value);
}

FString bytesAsHexString(const std::vector<uint8_t>& bytes)
{
    return TO_FSTRING(TW::hex(bytes));
}

std::vector<uint8_t> hexAsBytes(const FString& value)
{
    return TW::parse_hex(TO_STD_STRING(value));
}

std::vector<uint8_t> asBytes(const Address& value)
{
    return TW::addressToHex(TO_STD_STRING(value.value()));
}

std::vector<uint8_t> asBytes(const FString& value)
{
    std::string utf8String(TO_STD_STRING(value));

    std::vector<uint8_t> bytes(utf8String.size());
    for (size_t i = 0; i < bytes.size(); i++) {
        bytes[i] = utf8String[i];
    }

    return bytes;
}

template <typename Integer,
          std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
std::vector<uint8_t> asBytes(Integer value)
{
    std::vector<uint8_t> result(sizeof(Integer));

    for (size_t i = 0; i < sizeof(Integer); i++) {
        result[i] = (value >> (i * 8)) & 0xFF;
    }

    return result;
}

template <typename Integer,
          std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
void asBytes(std::vector<uint8_t>& output, Integer value)
{
    size_t initialSize = output.size();

    output.resize(initialSize + sizeof(Integer));

    for (size_t i = 0; i < sizeof(Integer); i++) {
        output[i + initialSize] = (value >> (i * 8)) & 0xFF;
    }
}

} // namespace utils
