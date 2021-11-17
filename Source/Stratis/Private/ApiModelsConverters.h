#pragma once

#include "Models/FReceiptResponse.h"
#include "Models/FUTXO.h"

#include "ReceiptResponse.h"

inline void convert(TArray<FUTXO> &out,
                    const TArray<stratis::api::UTXOModel> &utxos) {
  out.Reserve(utxos.Num());

  for (auto &utxo : utxos) {
    if (utxo.Hash.IsSet() && utxo.N.IsSet() && utxo.Satoshis.IsSet()) {
      FUTXO _utxo;
      _utxo.hash = *utxo.Hash;
      _utxo.n = *utxo.N;
      _utxo.satoshis = *utxo.Satoshis;

      out.Add(_utxo);
    }
  }
}

inline FReceiptResponse convert(const stratis::api::ReceiptResponse &response) {
  FReceiptResponse result = FReceiptResponse();

  if (response.TransactionHash) {
    result.transactionHash = *response.TransactionHash;
    result.isTransactionHashValid = true;
  }

  if (response.BlockHash) {
    result.blockHash = *response.BlockHash;
    result.isBlockHashValid = true;
  }

  if (response.BlockNumber) {
    result.blockNumber = *response.BlockNumber;
    result.isBlockNumberValid = true;
  }

  if (response.PostState) {
    result.postState = *response.PostState;
    result.isPostStateValid = true;
  }

  result.gasUsed = *response.GasUsed;

  if (response.From) {
    result.fromAddress = *response.From;
    result.isFromAddressValid = true;
  }

  if (response.To) {
    result.newContractAddress = *response.To;
    result.isToAddressValid = true;
  }

  if (response.NewContractAddress) {
    result.newContractAddress = *response.NewContractAddress;
    result.isNewContractAddressValid = true;
  }

  result.success = *response.Success;

  if (response.ReturnValue) {
    result.returnValue = *response.ReturnValue;
    result.isReturnValueValid = true;
  }

  if (response.Bloom) {
    result.bloom = *response.Bloom;
    result.isBloomValid = true;
  }

  if (response.Error) {
    result.error = *response.Error;
    result.isErrorValid = true;
  }

  return result;
}