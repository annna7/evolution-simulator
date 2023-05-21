#ifndef OOP_SUITOR_H
#define OOP_SUITOR_H

#include "Individual.h"
#include "Utils.h"

template <typename IndividualType>
class Suitor : public Individual {
public:
    Suitor(int x, int y): Individual(x, y, nullptr) {}
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Magenta; }
    [[nodiscard]] int getHunger() const override { return 2; }
};



#endif //OOP_SUITOR_H
