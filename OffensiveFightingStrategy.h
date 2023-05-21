//
// Created by anna on 5/21/23.
//

#ifndef OOP_OFFENSIVEFIGHTINGSTRATEGY_H
#define OOP_OFFENSIVEFIGHTINGSTRATEGY_H

#include "FightingStrategy.h"
#include "FightingOutcome.h"
#include <memory>

class OffensiveFightingStrategy : public FightingStrategy {
public:
    FightingOutcome fight(const std::shared_ptr<FightingStrategy>& other) override;
};


#endif //OOP_OFFENSIVEFIGHTINGSTRATEGY_H
