#pragma once

#include "Models/FNetwork.h"
#include "StratisNetwork.h"

namespace adapters {
StratisNetwork fromFNetwork(FNetwork network);
}