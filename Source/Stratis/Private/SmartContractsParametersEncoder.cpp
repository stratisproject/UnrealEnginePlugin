#include "USmartContractsParametersEncoder.h"

FString USmartContractsParametersEncoder::encodeBoolean(bool value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::BOOL, value ? TEXT("true") : TEXT("false") );
}

FString USmartContractsParametersEncoder::encodeByte(uint8 value)
{
    return FString::Printf(TEXT("%d#%d"), (uint8) ESmartContractParameterType::BYTE, value );
}

FString USmartContractsParametersEncoder::encodeChar(const FString& value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::CHAR, value[0] );
}

FString USmartContractsParametersEncoder::encodeString(const FString& value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::STRING, *value );
}

FString USmartContractsParametersEncoder::encodeUInt(int64 value)
{
    return FString::Printf(TEXT("%d#%d"), (uint8) ESmartContractParameterType::UINT, value );
}

FString USmartContractsParametersEncoder::encodeUInt(uint32 value)
{
    return USmartContractsParametersEncoder::encodeUInt((int64) value);
}

FString USmartContractsParametersEncoder::encodeInt(int64 value)
{
    return FString::Printf(TEXT("%d#%d"), (uint8) ESmartContractParameterType::INT, value );
}

FString USmartContractsParametersEncoder::encodeInt(int32 value)
{
    return USmartContractsParametersEncoder::encodeInt((int64) value);
}

FString USmartContractsParametersEncoder::encodeULong(const FUInt64& value)
{
    return USmartContractsParametersEncoder::encodeULong((uint64) value);
}

FString USmartContractsParametersEncoder::encodeULong(uint64 value)
{
    return FString::Printf(TEXT("%d#%d"), (uint8) ESmartContractParameterType::ULONG, value );
}

FString USmartContractsParametersEncoder::encodeLong(int64 value)
{
    return FString::Printf(TEXT("%d#%d"), (uint8) ESmartContractParameterType::LONG, value );
}

FString USmartContractsParametersEncoder::encodeAddress(const FString& value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::ADDRESS, *value );
}

FString USmartContractsParametersEncoder::encodeByteArray(const TArray<uint8>& value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::BYTE_ARRAY, *BytesToHex(value.GetData(), value.Num()) );
}

FString USmartContractsParametersEncoder::encodeUInt128(const FString& value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::UINT128, *value );
}

FString USmartContractsParametersEncoder::encodeUInt256(const FString& value)
{
    return FString::Printf(TEXT("%d#%s"), (uint8) ESmartContractParameterType::UINT256, *value );
}