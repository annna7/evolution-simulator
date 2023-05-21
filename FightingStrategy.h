//
// Created by anna on 5/21/23.
//

#ifndef OOP_FIGHTINGSTRATEGY_H
#define OOP_FIGHTINGSTRATEGY_H

#include "FightingOutcome.h"
#include "Exceptions.h"
#include <memory>
#include <SFML/Graphics/Color.hpp>

class FightingStrategy {
public:
    virtual FightingOutcome fight(const std::shared_ptr<FightingStrategy> &other) = 0;
    virtual std::shared_ptr<FightingStrategy> clone() const = 0; // Clone method
    virtual ~FightingStrategy() = default;
    virtual sf::Color getColor() = 0;
};


#endif //OOP_FIGHTINGSTRATEGY_H
