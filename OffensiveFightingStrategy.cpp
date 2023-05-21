//
// Created by anna on 5/21/23.
//

#include "OffensiveFightingStrategy.h"
#include "DefensiveFightingStrategy.h"
#include "Utils.h"

FightingOutcome OffensiveFightingStrategy::fight(const std::shared_ptr<FightingStrategy>& other) {
    if (dynamic_pointer_cast<DefensiveFightingStrategy>(other)) {
        return FightingOutcome::LIVE_DIE;
    } else {
        if (randomIntegerFromInterval(0, 1) == 0) {
            return FightingOutcome::LIVE_LIVE;
        } else {
            return FightingOutcome::DIE_LIVE;
        }
    }
}

sf::Color OffensiveFightingStrategy::getColor() {
    return sf::Color::Black;
}
