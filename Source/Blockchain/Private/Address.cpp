#include "Address.h"

Address::Address(const FString& address) : storage_(address)
{
}

Address::Address(FString&& address) : storage_(MoveTemp(address)) 
{
}

const FString& Address::value() const
{
    return storage_;
}