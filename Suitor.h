#ifndef OOP_SUITOR_H
#define OOP_SUITOR_H

#include "Individual.h"
#include "Utils.h"

template <typename IndividualType>
class Suitor : public Individual {
public:
    Suitor(int x, int y): Individual(x, y) {}
    [[nodiscard]] sf::Color getColor() override { return {128, 128, 128};}
    [[nodiscard]] int getHunger() const override { return 2; }
};



#endif //OOP_SUITOR_H
