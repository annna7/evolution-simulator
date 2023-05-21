//
// Created by anna on 5/7/23.
//

#ifndef OOP_KEYSTONE_H
#define OOP_KEYSTONE_H

#include "Individual.h"
#include "Utils.h"


class Keystone : public Individual {
public:
    Keystone(int x, int y) : Individual(x, y) {}
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Yellow; }
};


#endif //OOP_KEYSTONE_H
