//
// Created by anna on 5/21/23.
//

#include "FightingStrategyType.h"
#include "Exceptions.h"

std::string fightingStrategyTypeToString(FightingStrategyType type) {
    switch (type) {
        case DEFENSIVE_TYPE:
            return "Defensive";
        case OFFENSIVE_TYPE:
            return "Offensive";
        case LOVER_TYPE:
            return "Lover";
        default:
            throw InvalidFightingStrategyType();
    }
}