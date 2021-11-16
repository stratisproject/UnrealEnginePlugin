#include "UStratisUnrealManager.h"

#include <string>
#include <vector>

#include "Adapters/NetworkTypeAdapter.h"
#include "Algo/Transform.h"
#include "Converters.h"
#include "Models/FReceiptResponse.h"
#include "StratisNetwork.h"
#include "TransactionBuilder.h"
#include "TransactionBuilderFactory.h"
#include "UnrealApiOperations.h"

#include "ApiModelsConverters.h"

#include "RequestBuilders.h"

#include "DataUtils.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

#include <functional>

namespace {
namespace scparam = smart_contracts::method_parameter;
using API = stratis::api::UnrealApi;
} // namespace

UStratisUnrealManager::UStratisUnrealManager()
    : gasPrice(100), gasLimit(150000), defaultFee(10000),
      baseUrl_(TEXT("http://localhost:44336")) {

  setPredefinedNetwork(ENetwork::CIRRUS);
  transactionBuilder_ =
      createTransactionBuilder(mnemonic_, adapters::fromFNetwork(network_));

  unrealApi_ = MakeShared<stratis::api::UnrealApi>();
  unrealApi_->SetURL(baseUrl_);
  unrealApi_->AddHeaderParam(TEXT("Accept"), TEXT("application/json"));
}

void UStratisUnrealManager::setMnemonic(const FString &mnemonic) {
  mnemonic_ = mnemonic;
  if (transactionBuilder_.IsValid()) {
    transactionBuilder_->setMnemonic(mnemonic_);
  }
}

void UStratisUnrealManager::setBaseUrl(const FString &baseUrl) {
  baseUrl_ = baseUrl;
  if (unrealApi_.IsValid()) {
    unrealApi_->SetURL(baseUrl_);
  }
}

void UStratisUnrealManager::setNetwork(const FNetwork &network) {
  network_ = network;
  this->notifyNetworkChanged();
}

void UStratisUnrealManager::setPredefinedNetwork(ENetwork networkType) {
  switch (networkType) {
  case ENetwork::STRAX:
    network_ = FNetwork::STRAX;
    break;
  case ENetwork::STRAX_TEST:
    network_ = FNetwork::STRAX_TEST;
    break;
  case ENetwork::CIRRUS:
    network_ = FNetwork::CIRRUS;
    break;
  case ENetwork::CIRRUS_TEST:
    network_ = FNetwork::CIRRUS_TEST;
    break;
  default:
    break;
  }
  this->notifyNetworkChanged();
}

FString UStratisUnrealManager::getAddress() {
  return transactionBuilder_->paymentAddress();
}

void UStratisUnrealManager::getBalance(
    const FGetBalanceResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getBalance([delegate, errorDelegate](const TResult<int64> &result) {
    if (result::isSuccessful(result))
      delegate.ExecuteIfBound(result::getValue(result));
    else
      errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
  });
}

void UStratisUnrealManager::getBalance(
    TFunction<void(const TResult<int64> &)> callback) {
  this->requestContextManager_
      .createContext<API::FUnity3dGetaddressbalanceGetDelegate,
                     API::Unity3dGetaddressbalanceGetRequest>(
          request_builders::buildGetBalanceRequest(getAddress()),
          std::bind(&API::Unity3dGetaddressbalanceGet, unrealApi_.Get(),
                    std::placeholders::_1, std::placeholders::_2),
          [callback](const auto &response) {
            if (response.IsSuccessful()) {
              int64 balance = response.Content.Balance.GetValue();
              callback(result::ok(balance));
            } else {
              callback(result::error<int64>(response.GetResponseString()));
            }
          });
}

void UStratisUnrealManager::getCoins(
    const FGetCoinsResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->getCoins(
      [delegate, errorDelegate](const TResult<TArray<FUTXO>> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::getCoins(
    TFunction<void(const TResult<TArray<FUTXO>> &)> callback) {
  this->requestContextManager_
      .createContext<API::FUnity3dGetutxosforaddressGetDelegate,
                     API::Unity3dGetutxosforaddressGetRequest>(
          request_builders::buildGetUtxosRequest(getAddress()),
          std::bind(&API::Unity3dGetutxosforaddressGet, unrealApi_.Get(),
                    std::placeholders::_1, std::placeholders::_2),
          [callback](const auto &response) {
            TArray<FUTXO> utxos;

            if (!response.IsSuccessful()) {
              callback(
                  result::error<TArray<FUTXO>>(response.GetResponseString()));
              return;
            }

            const auto &itemsOptional = response.Content.UtxOs;
            if (itemsOptional.IsSet()) {
              convert(utxos, itemsOptional.GetValue());
            }

            callback(result::ok(utxos));
          });
}

void UStratisUnrealManager::sendRawTransaction(
    const FString &transactionHex, const FString &transactionID,
    const FSendTransactionResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->sendRawTransaction(
      transactionHex, transactionID,
      [delegate, errorDelegate](const TResult<FString> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::sendRawTransaction(
    const FString &transactionHex, const FString &transactionID,
    TFunction<void(const TResult<FString> &)> callback) {
  this->requestContextManager_
      .createContext<API::FUnity3dSendTransactionPostDelegate,
                     API::Unity3dSendTransactionPostRequest>(
          request_builders::buildSendTransactionRequest(transactionHex),
          std::bind(&API::Unity3dSendTransactionPost, unrealApi_.Get(),
                    std::placeholders::_1, std::placeholders::_2),
          [callback, transactionID](const auto &response) {
            if (!response.IsSuccessful()) {
              callback(result::error<FString>(response.GetResponseString()));
              return;
            }

            callback(result::ok(transactionID));
          });
}

void UStratisUnrealManager::sendCoinsTransaction(
    const FString &destinationAddress, int64 money,
    const FSendTransactionResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->sendCoinsTransaction(
      destinationAddress, money,
      [delegate, errorDelegate](const TResult<FString> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::sendCoinsTransaction(
    const FString &destinationAddress, int64 money,
    TFunction<void(const TResult<FString> &)> callback) {
  this->getCoins([this, destinationAddress, money,
                  callback](const TResult<TArray<FUTXO>> &coinsResult) {
    if (!result::isSuccessful(coinsResult)) {
      callback(result::error<FString>(result::getError(coinsResult)));
      return;
    }

    const auto &utxos = coinsResult.Get<TArray<FUTXO>>();
    TArray<UTXO> mappedUTXOs;
    mappedUTXOs.Reserve(utxos.Num());
    Algo::Transform(utxos, mappedUTXOs, converters::convertUTXO);

    Transaction transaction(this->transactionBuilder_->buildSendTransaction(
        destinationAddress, mappedUTXOs, (uint64)money, this->defaultFee));

    this->sendRawTransaction(
        transaction.transactionHex, transaction.transactionId,
        [callback](const TResult<FString> &result) { callback(result); });
  });
}

void UStratisUnrealManager::sendOpReturnStringTransaction(
    const FString &opReturnData,
    const FSendTransactionResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  TArray<uint8> opReturnDataArray(HexToBytesArray(opReturnData));
  this->sendOpReturnArrayTransaction(opReturnDataArray, delegate,
                                     errorDelegate);
}

void UStratisUnrealManager::sendOpReturnStringTransaction(
    const FString &opReturnData,
    TFunction<void(const TResult<FString> &)> callback) {
  TArray<uint8> opReturnDataArray(HexToBytesArray(opReturnData));
  this->sendOpReturnArrayTransaction(opReturnDataArray, callback);
}

void UStratisUnrealManager::sendOpReturnArrayTransaction(
    const TArray<uint8> &opReturnData,
    const FSendTransactionResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->sendOpReturnArrayTransaction(
      opReturnData, [delegate, errorDelegate](const TResult<FString> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::sendOpReturnArrayTransaction(
    const TArray<uint8> &opReturnData,
    TFunction<void(const TResult<FString> &)> callback) {
  this->getCoins([this, opReturnData,
                  callback](const TResult<TArray<FUTXO>> &result) {
    if (!result::isSuccessful(result)) {
      callback(result::error<FString>(result::getError(result)));
      return;
    }

    const TArray<FUTXO> &utxos = result::getValue(result);

    TArray<UTXO> mappedUTXOs;
    mappedUTXOs.Reserve(utxos.Num());
    Algo::Transform(utxos, mappedUTXOs, converters::convertUTXO);

    Transaction transaction(this->transactionBuilder_->buildOpReturnTransaction(
        opReturnData, mappedUTXOs, this->defaultFee));

    this->sendRawTransaction(transaction.transactionHex,
                             transaction.transactionId,
                             [callback](const TResult<FString> &transactionID) {
                               callback(transactionID);
                             });
  });
}

void UStratisUnrealManager::sendCreateContractTransaction(
    const FString &contractCode, const TArray<FString> &parameters, int64 money,
    const FSendTransactionResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->sendCreateContractTransaction(
      contractCode, parameters, money,
      [delegate, errorDelegate](const TResult<FString> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::sendCreateContractTransaction(
    const FString &contractCode, const TArray<FString> &parameters, int64 money,
    TFunction<void(const TResult<FString> &)> callback) {
  this->getCoins([this, contractCode, parameters, money,
                  callback](const TResult<TArray<FUTXO>> &result) {
    if (!result::isSuccessful(result)) {
      callback(result::error<FString>(result::getError(result)));
      return;
    }
    const TArray<FUTXO> &utxos = result::getValue(result);

    TArray<TUniquePtr<scparam::MethodParameter>> wrappedParameters;
    wrappedParameters.Reserve(parameters.Num());
    Algo::Transform(parameters, wrappedParameters, scparam::parseFromString);

    TArray<UTXO> mappedUTXOs;
    mappedUTXOs.Reserve(utxos.Num());
    Algo::Transform(utxos, mappedUTXOs, converters::convertUTXO);

    Transaction transaction(
        this->transactionBuilder_->buildCreateContractTransaction(
            contractCode, mappedUTXOs,
            (this->gasPrice * this->gasLimit) + this->defaultFee,
            this->gasPrice, this->gasLimit, (uint64)money,
            MoveTemp(wrappedParameters)));

    this->sendRawTransaction(transaction.transactionHex,
                             transaction.transactionId,
                             [callback](const TResult<FString> &transactionID) {
                               callback(transactionID);
                             });
  });
}

void UStratisUnrealManager::sendCallContractTransaction(
    const FString &contractAddress, const FString &methodName,
    const TArray<FString> &parameters, const FUInt64 &money,
    const FSendTransactionResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->sendCallContractTransaction(
      contractAddress, methodName, parameters, (uint64)money,
      [delegate, errorDelegate](const TResult<FString> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::sendCallContractTransaction(
    const FString &contractAddress, const FString &methodName,
    const TArray<FString> &parameters, uint64 money,
    TFunction<void(const TResult<FString> &)> callback) {
  this->getCoins([this, contractAddress, methodName, parameters, money,
                  callback](const TResult<TArray<FUTXO>> &result) {
    if (!result::isSuccessful(result)) {
      callback(result::error<FString>(result::getError(result)));
      return;
    }

    const TArray<FUTXO> &utxos = result::getValue(result);

    TArray<TUniquePtr<scparam::MethodParameter>> wrappedParameters;
    wrappedParameters.Reserve(parameters.Num());
    Algo::Transform(parameters, wrappedParameters, scparam::parseFromString);

    TArray<UTXO> mappedUTXOs;
    mappedUTXOs.Reserve(utxos.Num());
    Algo::Transform(utxos, mappedUTXOs, converters::convertUTXO);

    Transaction transaction(
        this->transactionBuilder_->buildCallContractTransaction(
            methodName, Address(contractAddress), mappedUTXOs,
            (this->gasPrice * this->gasLimit) + this->defaultFee,
            this->gasPrice, this->gasLimit, money,
            MoveTemp(wrappedParameters)));

    this->sendRawTransaction(transaction.transactionHex,
                             transaction.transactionId,
                             [callback](const TResult<FString> &transactionID) {
                               callback(transactionID);
                             });
  });
}

void UStratisUnrealManager::waitTillReceiptAvailable(
    const FString &transactionID,
    const FWaitTillReceiptAvailableResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->waitTillReceiptAvailable(
      transactionID,
      [delegate, errorDelegate](const TResult<FReceiptResponse> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::waitTillReceiptAvailable(
    const FString &transactionID,
    TFunction<void(const TResult<FReceiptResponse> &)> callback) {
  this->requestContextManager_
      .createContext<API::FUnity3dApiUnity3dReceiptGetDelegate,
                     API::Unity3dApiUnity3dReceiptGetRequest>(
          request_builders::buildGetReceiptRequest(transactionID),
          std::bind(&API::Unity3dApiUnity3dReceiptGet, unrealApi_.Get(),
                    std::placeholders::_1, std::placeholders::_2),
          [this, transactionID, callback](const auto &response) {
            if (response.IsSuccessful()) {
              callback(result::ok(convert(response.Content)));
            } else {
              auto &timerManager = GetWorld()->GetTimerManager();
              auto handle = FTimerHandle();
              timerManager.SetTimer(
                  handle,
                  [this, transactionID, callback]() {
                    this->waitTillReceiptAvailable(transactionID, callback);
                  },
                  5.0f, false);
            }
          });
}

void UStratisUnrealManager::makeLocalCall(
    const FLocalCallData &data,
    const FLocalCallResponseReceivedDelegate &delegate,
    const FErrorReceivedDelegate &errorDelegate) {
  this->makeLocalCall(
      data, [delegate, errorDelegate](const TResult<FString> &result) {
        if (result::isSuccessful(result))
          delegate.ExecuteIfBound(result::getValue(result));
        else
          errorDelegate.ExecuteIfBound(result::getErrorMessage(result));
      });
}

void UStratisUnrealManager::makeLocalCall(
    const FLocalCallData &data,
    TFunction<void(const TResult<FString> &)> callback) {
  this->requestContextManager_
      .createContext<API::FUnity3dApiUnity3dLocalCallPostDelegate,
                     API::Unity3dApiUnity3dLocalCallPostRequest>(
          request_builders::buildLocalCallRequest(data),
          std::bind(&API::Unity3dApiUnity3dLocalCallPost, unrealApi_.Get(),
                    std::placeholders::_1, std::placeholders::_2),
          [callback](const auto &response) {
            if (response.IsSuccessful()) {
              callback(
                  result::ok(response.Content._Return.GetValue()->AsString()));
            } else {
              callback(result::error<FString>(response.GetResponseString()));
            }
          });
}

UWorld *UStratisUnrealManager::GetWorld() const {
  UGameInstance *GameInstance = GetTypedOuter<UGameInstance>();
  return GameInstance->GetWorld();
}

void UStratisUnrealManager::notifyNetworkChanged() {
  if (transactionBuilder_.IsValid()) {
    transactionBuilder_->setNetwork(adapters::fromFNetwork(network_));
  }
}

// LEGACY

void UStratisUnrealManager::sendCreateContractTransaction(
    const FString &contractCode, const TArray<FString> &parameters, int64 money,
    TFunction<void(const FString &)> callback) {
  this->getCoins([this, contractCode, parameters, money,
                  callback](const TResult<TArray<FUTXO>> &result) {
    const TArray<FUTXO> &utxos = result::getValue(result);

    TArray<TUniquePtr<scparam::MethodParameter>> wrappedParameters;
    wrappedParameters.Reserve(parameters.Num());
    Algo::Transform(parameters, wrappedParameters, scparam::parseFromString);

    TArray<UTXO> mappedUTXOs;
    mappedUTXOs.Reserve(utxos.Num());
    Algo::Transform(utxos, mappedUTXOs, converters::convertUTXO);

    Transaction transaction(
        this->transactionBuilder_->buildCreateContractTransaction(
            contractCode, mappedUTXOs,
            (this->gasPrice * this->gasLimit) + this->defaultFee,
            this->gasPrice, this->gasLimit, (uint64)money,
            MoveTemp(wrappedParameters)));

    this->sendRawTransaction(transaction.transactionHex,
                             transaction.transactionId,
                             [callback](const auto &transactionID) {
                               callback(result::getValue(transactionID));
                             });
  });
}

void UStratisUnrealManager::sendCallContractTransaction(
    const FString &contractAddress, const FString &methodName,
    const TArray<FString> &parameters, uint64 money,
    TFunction<void(const FString &)> callback) {
  this->getCoins([this, contractAddress, methodName, parameters, money,
                  callback](const TResult<TArray<FUTXO>> &result) {
    const TArray<FUTXO> &utxos = result::getValue(result);

    TArray<TUniquePtr<scparam::MethodParameter>> wrappedParameters;
    wrappedParameters.Reserve(parameters.Num());
    Algo::Transform(parameters, wrappedParameters, scparam::parseFromString);

    TArray<UTXO> mappedUTXOs;
    mappedUTXOs.Reserve(utxos.Num());
    Algo::Transform(utxos, mappedUTXOs, converters::convertUTXO);

    Transaction transaction(
        this->transactionBuilder_->buildCallContractTransaction(
            methodName, Address(contractAddress), mappedUTXOs,
            (this->gasPrice * this->gasLimit) + this->defaultFee,
            this->gasPrice, this->gasLimit, money,
            MoveTemp(wrappedParameters)));

    this->sendRawTransaction(transaction.transactionHex,
                             transaction.transactionId,
                             [callback](const auto &transactionID) {
                               callback(result::getValue(transactionID));
                             });
  });
}

void UStratisUnrealManager::makeLocalCall(
    const FLocalCallData &data, TFunction<void(const FString &)> callback) {
  this->requestContextManager_
      .createContext<API::FUnity3dApiUnity3dLocalCallPostDelegate,
                     API::Unity3dApiUnity3dLocalCallPostRequest>(
          request_builders::buildLocalCallRequest(data),
          std::bind(&API::Unity3dApiUnity3dLocalCallPost, unrealApi_.Get(),
                    std::placeholders::_1, std::placeholders::_2),
          [callback](const auto &response) {
            FString returnValue;

            if (response.Content._Return.IsSet()) {
              returnValue = response.Content._Return.GetValue()->AsString();
            }

            callback(returnValue);
          });
}