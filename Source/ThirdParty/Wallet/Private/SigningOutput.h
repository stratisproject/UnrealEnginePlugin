#pragma once

#include "Data.h"
#include "SigningError.h"
#include "Transaction.h"

#include "Misc/Optional.h"
#include <string>

struct SigningOutput {
    // Resulting transaction. Note that the amount may be different than the requested amount to account for fees and available funds.
    TW::Bitcoin::Transaction transaction;

    // Signed and encoded transaction bytes.
    TW::Data encoded;

    // Transaction id
    std::string transactionId;

    // Optional error
    TOptional<SigningError> error;
};