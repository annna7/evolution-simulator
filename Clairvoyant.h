//
// Created by anna on 5/6/23.
//

#ifndef OOP_CLAIRVOYANT_H
#define OOP_CLAIRVOYANT_H

#include "Individual.h"
#include "Utils.h"

class Clairvoyant : public Individual {
public:
    Clairvoyant(int x, int y) : Individual(x, y) {}
    [[nodiscard]] int getHunger() const override { return 3; }
    [[nodiscard]] int getVision() const override { return 5; }
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Blue; }
    [[nodiscard]] int getType() const override { return CLAIRVOYANT; }
};

#endif //OOP_CLAIRVOYANT_H
