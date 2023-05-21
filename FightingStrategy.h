//
// Created by anna on 5/21/23.
//

#ifndef OOP_FIGHTINGSTRATEGY_H
#define OOP_FIGHTINGSTRATEGY_H

#include "FightingOutcome.h"
#include "Exceptions.h"
#include <memory>

class FightingStrategy {
public:
    virtual FightingOutcome fight(const std::shared_ptr<FightingStrategy> &other) = 0;
    virtual ~FightingStrategy() = default;
};


#endif //OOP_FIGHTINGSTRATEGY_H
