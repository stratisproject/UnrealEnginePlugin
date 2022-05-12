#include "WalletChecker.h"

#include "HDWallet.h"
#include "HexCoding.h"
#include "Signer.h"

#ifndef TO_STD_STRING
#define TO_STD_STRING(f_string) std::string(TCHAR_TO_UTF8(*f_string))
#endif

#ifndef TO_FSTRING
#define TO_FSTRING(std_string) UTF8_TO_TCHAR(std_string.c_str())
#endif

FString WalletChecker::checkWallet()
{
    TW::HDWallet wallet("legal door leopard fire attract stove similar response photo prize seminar frown",
                        "", false);


    TWCoinType coin = TWCoinType::TWCoinTypeCirrusTest;

    TW::Bitcoin::SigningInput signingInput;

    signingInput.amount = 9999990000;
    signingInput.toAddress = "t8gzBHm8QrTTPzieUosgJBFiPZsr55Pa2r";
    signingInput.changeAddress = "tSZbEtqhDCHhaJs2TrfKtSMYQbSGu7Myn7";
    signingInput.coinType = coin;

    signingInput.privateKeys = {wallet.getKey(coin, TW::derivationPath(coin))};

    TW::Bitcoin::OutPoint outpoint{
        TW::parse_hex("0f310ab28945ae86989a19b1f85da4d951604d4cb430c6244f7b42727e373bbd"),
        1,
        4294967295};

    TW::Bitcoin::Script script{
        TW::parse_hex("76a914135ce694167cc51729277de633842940e6bf067688ac")};

    signingInput.utxos = {
        {outpoint, script, 459599889999},
    };

    auto signedOutput = Signer::sign(signingInput);

    return TO_FSTRING(TW::hex(signedOutput.encoded));

    // return TO_FSTRING(wallet.deriveAddress(TWCoinType::TWCoinTypeCirrusTest));
}