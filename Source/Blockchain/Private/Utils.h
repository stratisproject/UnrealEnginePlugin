#pragma once

#include "CoreMinimal.h"
#include "Address.h"
#include "Transaction.h"

#include "LibbitcoinSafeImports.h"

#include <string>
#include <vector>

#ifndef TO_STD_STRING
#define TO_STD_STRING(f_string) std::string(TCHAR_TO_UTF8(*f_string))
#endif

#ifndef TO_FSTRING
#define TO_FSTRING(std_string) UTF8_TO_TCHAR(std_string.c_str())
#endif

namespace utils
{

    FString hashDigestAsString(libbitcoin::system::hash_digest hash)
    {
        return TO_FSTRING(libbitcoin::system::encode_hash(hash));
    }
    
    FString encodeTransaction(const libbitcoin::system::chain::transaction &transaction)
    {
        return TO_FSTRING(libbitcoin::system::encode_base16(transaction.to_data()));
    }
    
    Transaction transformTransaction(const libbitcoin::system::chain::transaction &transaction)
    {
        return {
            .transactionHex = encodeTransaction(transaction),
            .transactionId = hashDigestAsString(transaction.hash())};
    }

    template <typename T>
    TArray<T> asTArray(const std::vector<T> &value)
    {
        return TArray<T>(value.data(), value.size());
    }

    template <typename T>
    std::vector<T> asVector(const TArray<T> &value)
    {
        std::vector<T> result(value.Num());

        for (int32 i = 0; i < value.Num(); i++)
        {
            result[i] = value[i];
        }

        return result;
    }

    FString bytesAsHexString(const std::vector<uint8_t> &bytes)
    {
        return TO_FSTRING(libbitcoin::system::encode_base16(bytes));
    }

    std::vector<uint8_t> hexAsBytes(const FString &value)
    {
        std::vector<uint8_t> bytes;
        libbitcoin::system::decode_base16(bytes, TO_STD_STRING(value));
        return bytes;
    }

    std::vector<uint8_t> asBytes(const Address &value)
    {
        return hexAsBytes(value.value());
    }

    std::vector<uint8_t> asBytes(const FString &value)
    {
        std::string utf8String(TO_STD_STRING(value));

        std::vector<uint8_t> bytes(utf8String.size());
        for (size_t i = 0; i < bytes.size(); i++)
        {
            bytes[i] = utf8String[i];
        }

        return bytes;
    }

    template <typename Integer,
              std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
    std::vector<uint8_t> asBytes(Integer value)
    {
        std::vector<uint8_t> result(sizeof(Integer));

        for (size_t i = 0; i < sizeof(Integer); i++)
        {
            result[i] = (value >> (i * 8)) & 0xFF;
        }

        return result;
    }

    template <typename Integer,
              std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
    void asBytes(std::vector<uint8_t> &output, Integer value)
    {
        size_t initialSize = output.size();

        output.resize(initialSize + sizeof(Integer));

        for (size_t i = 0; i < sizeof(Integer); i++)
        {
            output[i + initialSize] = (value >> (i * 8)) & 0xFF;
        }
    }

}