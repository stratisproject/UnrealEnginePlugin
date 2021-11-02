#pragma once

#include "CoreMinimal.h"
#include "Models/FUInt64.h"

#include "USmartContractsParametersEncoder.generated.h"

UENUM(BlueprintType)
enum class ESmartContractParameterType : uint8 {
  NONE = 0 UMETA(Hidden),
  BOOL = 1 UMETA(DisplayName = "Boolean"),
  BYTE = 2 UMETA(DisplayName = "Byte"),
  CHAR = 3 UMETA(DisplayName = "Char"),
  STRING = 4 UMETA(DisplayName = "String"),
  UINT = 5 UMETA(DisplayName = "Unsigned 32-bit integer"),
  INT = 6 UMETA(DisplayName = "Signed 32-bit integer"),
  ULONG = 7 UMETA(DisplayName = "Unsigned 64-bit integer"),
  LONG = 8 UMETA(DisplayName = "Signed 64-bit integer"),
  ADDRESS = 9 UMETA(DisplayName = "Address"),
  BYTE_ARRAY = 10 UMETA(DisplayName = "Array of bytes"),
  UINT128 = 11 UMETA(DisplayName = "Unsigned 128-bit integer"),
  UINT256 = 12 UMETA(DisplayName = "Unsigned 256-bit integer")
};

UCLASS(BlueprintType, Blueprintable)
class STRATIS_API USmartContractsParametersEncoder : public UObject {

  GENERATED_BODY()

public:
  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeBoolean(bool value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeByte(uint8 value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeChar(const FString &value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeString(const FString &value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeUInt(int64 value);
  static FString encodeUInt(uint32 value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeInt(int64 value);
  static FString encodeInt(int32 value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeULong(const FUInt64 &value);
  static FString encodeULong(uint64 value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeLong(int64 value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeAddress(const FString &value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeByteArray(const TArray<uint8> &value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeUInt128(const FString &value);

  UFUNCTION(BlueprintCallable, Category = "SmartContractsParametersEncoder")
  static FString encodeUInt256(const FString &value);
};