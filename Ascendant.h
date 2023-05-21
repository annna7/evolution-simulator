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
    Ascendant(int x, int y) : Individual(x, y) {
        hasEaten = false;
    }
    [[nodiscard]] sf::Color getColor() override { return sf::Color::Magenta; }
    [[nodiscard]] int getHunger() const override { return 2; }
    void eat() override {
        if (!hasEaten) {
            hasEaten = true;
        }
        Individual::eat();
    }
    [[nodiscard]] int getVision() const override {
        if (hasEaten) {
            return 10;
        } else {
            return Individual::getVision();
        }
    }
    [[nodiscard]] int getSpeed() const override {
        if (hasEaten) {
            return 5;
        } else {
            return Individual::getSpeed();
        }
    }
    // override copy constructor, assignment operator, swap
    Ascendant(const Ascendant &other) : Individual(other) {
        hasEaten = other.hasEaten;
    }

    Ascendant& operator=(const Ascendant &other) {
        if (this != &other) {
            Individual::operator=(other);
            hasEaten = other.hasEaten;
        }
        return *this;
    }

};


#endif //OOP_ASCENDANT_H
