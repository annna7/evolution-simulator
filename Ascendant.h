//
// Created by anna on 5/14/23.
//

#ifndef OOP_ASCENDANT_H
#define OOP_ASCENDANT_H

#include "Individual.h"
#include "Utils.h"

class Ascendant : public Individual {
    bool hasEaten;

public:
    Ascendant(int x, int y);
    [[nodiscard]] sf::Color getColor() override;
    [[nodiscard]] int getHunger() const override;
    void eat() override;
    [[nodiscard]] int getVision() const override;
    [[nodiscard]] int getSpeed() const override;
    // override copy constructor, assignment operator
    Ascendant(const Ascendant &other);
    Ascendant& operator=(const Ascendant &other);
};


#endif //OOP_ASCENDANT_H
