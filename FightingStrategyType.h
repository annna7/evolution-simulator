#ifndef OOP_FIGHTINGSTRATEGYTYPE_H
#define OOP_FIGHTINGSTRATEGYTYPE_H

#include <string>

enum FightingStrategyType {
    FIGHTING_TYPE_BEGIN,
    DEFENSIVE_TYPE,
    OFFENSIVE_TYPE,
    LOVER_TYPE,
    FIGHTING_TYPE_END
};

std::string fightingStrategyTypeToString(FightingStrategyType type);

#endif //OOP_FIGHTINGSTRATEGYTYPE_H
