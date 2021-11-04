#pragma once

#include "CoreMinimal.h"

#include "SmartContracts/MethodParameter.h"
#include "StratisNetwork.h"
#include "Transaction.h"
#include "UTXO.h"

class BLOCKCHAIN_API TransactionBuilder {
public:
  virtual ~TransactionBuilder() = 0;

  virtual void setMnemonic(const FString &mnemonic) = 0;
  virtual void setNetwork(const StratisNetwork &network) = 0;

  virtual FString paymentAddress() const = 0;

  virtual Transaction buildSendTransaction(const FString &destinationAddress,
                                           const TArray<UTXO> &utxos,
                                           uint64 amount, uint64 fee) const = 0;

  virtual Transaction buildOpReturnTransaction(const TArray<uint8> &data,
                                               const TArray<UTXO> &utxos,
                                               uint64 fee) const = 0;

  virtual Transaction buildCreateContractTransaction(
      const FString &contractCode, const TArray<UTXO> &utxos, uint64 fee,
      uint64 gasPrice, uint64 gasLimit, uint64 amount = 0,
      TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>
          &&parameters = {}) const = 0;

  virtual Transaction buildCallContractTransaction(
      const FString &methodName, const Address &contractAddress,
      const TArray<UTXO> &utxos, uint64 fee, uint64 gasPrice, uint64 gasLimit,
      uint64 amount = 0,
      TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>
          &&parameters = {}) const = 0;
};