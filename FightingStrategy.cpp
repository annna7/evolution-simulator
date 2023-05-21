//
// Created by anna on 5/21/23.
//

#include "FightingStrategy.h"
#include <memory>

FightingOutcome FightingStrategy::fight(const std::shared_ptr <FightingStrategy> &other) { return DIE_LIVE; }
