#pragma once

#include "Models/FReceiptResponse.h"
#include "Models/FUTXO.h"

#include "ReceiptResponse.h"

inline void convert(TArray<FUTXO> &out,
                    const TArray<stratis::api::UTXOModel> &utxos) {
  out.SetNum(utxos.Num());

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
  FReceiptResponse result;
  result.transactionHash = *response.TransactionHash;
  result.blockHash = *response.BlockHash;
  result.blockNumber = *response.BlockNumber;
  result.postState = *response.PostState;
  result.gasUsed = *response.GasUsed;
  result.fromAddress = *response.From;
  result.toAddress = *response.To;
  result.newContractAddress = *response.NewContractAddress;
  result.success = *response.Success;
  result.returnValue = *response.ReturnValue;
  result.bloom = *response.Bloom;
  result.error = *response.Error;
  return result;
}