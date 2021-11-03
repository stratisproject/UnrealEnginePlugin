#include "TransactionBuilderImpl.h"

#include <TransactionBuilderFactory.h>

#include "SmartContracts/SmartContractScriptFactoryProvider.h"

#include <string>
#include <vector>

#include "LibbitcoinConverters.h"
#include "Utils.h"

#include <boost/algorithm/string.hpp>

using namespace libbitcoin::system;

constexpr uint32_t DEFAULT_SEQUENCE = std::numeric_limits<uint32_t>::max();

TransactionBuilderImpl::TransactionBuilderImpl(const std::string &mnemonic,
                                               const StratisNetwork &network)
    : network_(network),
      smartContractScriptFactory_(
          smart_contracts::createSmartContractScriptFactory()) {
  std::vector<std::string> words;
  boost::split(words, mnemonic, boost::is_any_of("\t"));

  long_hash wallet_generation_seed = wallet::decode_mnemonic(words);
  data_chunk seed(std::begin(wallet_generation_seed),
                  std::end(wallet_generation_seed));
  privateKey_ = wallet::hd_private(seed);
}

void TransactionBuilderImpl::setNetwork(const StratisNetwork &network) {
  network_ = network;
}

libbitcoin::system::wallet::payment_address
TransactionBuilderImpl::address() const {
  wallet::ec_public ecPublicKey(privateKey_);
  return ecPublicKey.to_payment_address(network_.base58_pubkey_address_prefix);
}

FString TransactionBuilderImpl::paymentAddress() const {
  return TO_FSTRING(this->address().encoded());
}

Transaction
TransactionBuilderImpl::buildSendTransaction(const FString &destinationAddress,
                                             const TArray<UTXO> &utxos,
                                             uint64 amount, uint64 fee) const {
  wallet::payment_address destinationPaymentAddress(
      converters::makeAddress(destinationAddress));

  uint64 currentBalance = 0;

  chain::input::list inputs(buildInputs(utxos, currentBalance));

  chain::script paybackScript(converters::makeP2PKH(this->address()));

  chain::output::list outputs{
      {currentBalance - amount - fee, paybackScript},
      {amount, converters::makeP2PKH(destinationPaymentAddress)}};

  chain::transaction transaction(1, 0, std::move(inputs), std::move(outputs));

  signTransaction(transaction, paybackScript);

  return utils::transformTransaction(transaction);
}

Transaction TransactionBuilderImpl::buildOpReturnTransaction(
    const TArray<uint8> &data, const TArray<UTXO> &utxos, uint64 fee) const {
  data_chunk dataChunk;
  dataChunk.reserve(data.Num());

  for (uint8 dataByte : data) {
    dataChunk.push_back(dataByte);
  }

  chain::script opReturnScript({machine::operation(machine::opcode::return_),
                                machine::operation(dataChunk, true)});

  chain::script paybackScript(converters::makeP2PKH(this->address()));

  uint64 currentBalance = 0;
  chain::input::list inputs(buildInputs(utxos, currentBalance));

  chain::output::list outputs{{0, opReturnScript},
                              {currentBalance - fee, paybackScript}};

  chain::transaction transaction(1, 0, std::move(inputs), std::move(outputs));

  signTransaction(transaction, paybackScript);

  return utils::transformTransaction(transaction);
}

Transaction TransactionBuilderImpl::buildCreateContractTransaction(
    const FString &contractCode, const TArray<UTXO> &utxos, uint64 fee,
    uint64 gasPrice, uint64 gasLimit, uint64 amount,
    TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>
        &&parameters) const {
  std::vector<uint8_t> scriptBytes =
      smartContractScriptFactory_->makeCreateSmartContractScript(
          {.gasPrice = gasPrice,
           .gasLimit = gasLimit,
           .contractCode = utils::asTArray(utils::hexAsBytes(contractCode)),
           .methodParameters = MoveTemp(parameters)});

  chain::script createContractScript(std::move(scriptBytes), false);

  chain::script paybackScript(converters::makeP2PKH(this->address()));

  uint64 currentBalance = 0;
  chain::input::list inputs(buildInputs(utxos, currentBalance));

  chain::output::list outputs{{currentBalance - fee - amount, paybackScript},
                              {amount, std::move(createContractScript)}};

  chain::transaction transaction(1, 0, std::move(inputs), std::move(outputs));

  signTransaction(transaction, paybackScript);

  return utils::transformTransaction(transaction);
}

Transaction TransactionBuilderImpl::buildCallContractTransaction(
    const FString &methodName, const Address &contractAddress,
    const TArray<UTXO> &utxos, uint64 fee, uint64 gasPrice, uint64 gasLimit,
    uint64 amount,
    TArray<TUniquePtr<smart_contracts::method_parameter::MethodParameter>>
        &&parameters) const {
  std::vector<uint8_t> scriptBytes =
      smartContractScriptFactory_->makeCallSmartContractScript(
          {.gasPrice = gasPrice,
           .gasLimit = gasLimit,
           .contractAddress = contractAddress,
           .methodName = methodName,
           .methodParameters = MoveTemp(parameters)});

  chain::script createContractScript(std::move(scriptBytes), false);

  chain::script paybackScript(converters::makeP2PKH(this->address()));

  uint64 currentBalance = 0;
  chain::input::list inputs(buildInputs(utxos, currentBalance));

  chain::output::list outputs{{currentBalance - fee - amount, paybackScript},
                              {amount, std::move(createContractScript)}};

  chain::transaction transaction(1, 0, std::move(inputs), std::move(outputs));

  signTransaction(transaction, paybackScript);

  return utils::transformTransaction(transaction);
}

chain::input::list
TransactionBuilderImpl::buildInputs(const TArray<UTXO> &utxos,
                                    uint64 &totalBalance) const {
  chain::input::list inputs;
  inputs.reserve(utxos.Num());

  uint64 currentBalance = 0;

  for (auto &utxo : utxos) {
    currentBalance += utxo.satoshis;

    hash_digest hash;
    decode_hash(hash, TO_STD_STRING(utxo.hash));

    chain::input currentInput;

    currentInput.set_sequence(DEFAULT_SEQUENCE);
    currentInput.set_previous_output({std::move(hash), utxo.n});

    inputs.push_back(std::move(currentInput));
  }

  totalBalance += currentBalance;
  return inputs;
}

void TransactionBuilderImpl::signTransaction(
    chain::transaction &transaction, const chain::script &paybackScript) const {
  wallet::ec_public ecPublicKey(privateKey_);
  data_chunk publicKeyData = to_chunk(ecPublicKey.point());

  auto &transaction_inputs = transaction.inputs();
  for (size_t i = 0; i < transaction_inputs.size(); i++) {
    auto &input = transaction_inputs[i];

    endorsement signature;
    chain::script::create_endorsement(signature, privateKey_, paybackScript,
                                      transaction, i,
                                      machine::sighash_algorithm::all);

    machine::operation::list ops{machine::operation(signature),
                                 machine::operation(publicKeyData)};

    input.set_script({std::move(ops)});
  }
}

TSharedPtr<TransactionBuilder>
createTransactionBuilder(const FString &mnemonic,
                         const StratisNetwork &network) {
  return MakeShared<TransactionBuilderImpl>(TO_STD_STRING(mnemonic), network);
}