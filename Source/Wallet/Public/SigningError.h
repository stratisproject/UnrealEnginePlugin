#pragma once

#include <string>

struct SigningError {
    std::string message;

    SigningError(const std::string& errorMessage) : message(errorMessage) {}
    SigningError(const char* errorMessage) : message(errorMessage) {}

    bool operator==(const SigningError& rhs)
    {
        return this->message == rhs.message;
    }
    bool operator!=(const SigningError& rhs)
    {
        return !(*this == rhs);
    }
};