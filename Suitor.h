//
// Created by anna on 5/14/23.
//

#ifndef OOP_SUITOR_H
#define OOP_SUITOR_H

#include "Individual.h"
#include "Utils.h"

template <typename IndividualType>
class Suitor : public Individual {
public:
    Suitor(int x, int y) : Individual(x, y) {}
    [[nodiscard]] int getType() const override { return SUITOR; }
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Green; }
};


#endif //OOP_SUITOR_H
