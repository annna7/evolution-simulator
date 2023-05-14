//
// Created by anna on 5/6/23.
//

#ifndef OOP_REDBULL_H
#define OOP_REDBULL_H

#include "Individual.h"

class RedBull : public Individual {
public:
    RedBull(int x, int y) : Individual(x, y) {}
    [[nodiscard]] int getSpeed() const override  { return 5; }
    [[nodiscard]] int getHunger() const override { return 2; }
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Red; }
    [[nodiscard]] int getType() const override { return RED_BULL; }
};


#endif //OOP_REDBULL_H
