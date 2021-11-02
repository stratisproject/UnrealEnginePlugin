#pragma once

#include "LibbitcoinSafeImports.h"

#include <CoreMinimal.h>

#include "TransactionBuilder.h"

class TransactionBuilderImpl : public TransactionBuilder {
public:
  TransactionBuilderImpl(const std::string &mnemonic,
                         const StratisNetwork &network);
  virtual ~TransactionBuilderImpl() {}

  void setNetwork(const StratisNetwork &network) override;

  FString paymentAddress() const override;

  Transaction buildSendTransaction(const FString &destinationAddress,
                                   const TArray<UTXO> &utxos, uint64 amount,
                                   uint64 fee) const override;

  Transaction buildOpReturnTransaction(const TArray<uint8> &data,
                                       const TArray<UTXO> &utxos,
                                       uint64 fee) const override;

  Transaction buildCreateContractTransaction(
      const FString &contractCode, const TArray<UTXO> &utxos, uint64 fee,
      uint64 gasPrice, uint64 gasLimit, uint64 amount,
      TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>
          &&parameters) const override;

  Transaction buildCallContractTransaction(
      const FString &methodName, const Address &contractAddress,
      const TArray<UTXO> &utxos, uint64 fee, uint64 gasPrice, uint64 gasLimit,
      uint64 amount,
      TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>
          &&parameters) const override;

private:
  StratisNetwork network_;

  libbitcoin::system::wallet::hd_private privateKey_;
  libbitcoin::system::wallet::payment_address address_;

  TUniquePtr<smart_contracts::SmartContractScriptFactory>
      smartContractScriptFactory_;

  libbitcoin::system::chain::input::list
  buildInputs(const TArray<UTXO> &utxos, uint64 &totalBalance) const;
  void
  signTransaction(libbitcoin::system::chain::transaction &transaction,
                  const libbitcoin::system::chain::script &paybackScript) const;
};