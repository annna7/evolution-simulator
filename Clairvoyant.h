#ifndef OOP_CLAIRVOYANT_H
#define OOP_CLAIRVOYANT_H

#include "Individual.h"
#include "Utils.h"

class Clairvoyant : public Individual {
public:
    Clairvoyant(int x, int y) : Individual(x, y) {}
    [[nodiscard]] int getHunger() const override { return 2; }
    [[nodiscard]] int getVision() const override { return 5; }
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Blue; }
};

#endif //OOP_CLAIRVOYANT_H
