//
// Created by anna on 5/21/23.
//

#include "DefensiveFightingStrategy.h"
#include "OffensiveFightingStrategy.h"
#include <memory>

FightingOutcome DefensiveFightingStrategy::fight(const std::shared_ptr<FightingStrategy>& other) {
    if (std::dynamic_pointer_cast<DefensiveFightingStrategy>(other)) {
        return FightingOutcome::LIVE_LIVE;
    } else {
        return FightingOutcome::DIE_LIVE;
    }
}
