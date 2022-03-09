#pragma once

#include "Data.h"
#include "SigningError.h"
#include "Transaction.h"

#include <optional>
#include <string>

struct SigningOutput {
    // Resulting transaction. Note that the amount may be different than the requested amount to account for fees and available funds.
    TW::Bitcoin::Transaction transaction;

    // Signed and encoded transaction bytes.
    TW::Data encoded;

    // Transaction id
    std::string transactionId;

    // Optional error
    std::optional<SigningError> error;
};