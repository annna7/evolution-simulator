
#include "Ascendant.h"


Ascendant::Ascendant(int x, int y) : Individual(x, y) {
    hasEaten = false;
}

sf::Color Ascendant::getColor() {
    return sf::Color::Magenta;
}

int Ascendant::getHunger() const {
    return 2;
}

void Ascendant::eat() {
    if (!hasEaten) {
        hasEaten = true;
    }
    Individual::eat();
}

int Ascendant::getVision() const {
    if (hasEaten) {
        return 10;
    } else {
        return Individual::getVision();
    }
}

int Ascendant::getSpeed() const {
    if (hasEaten) {
        return 5;
    } else {
        return Individual::getSpeed();
    }
}

Ascendant::Ascendant(const Ascendant &other) : Individual(other) {
    hasEaten = other.hasEaten;
}

Ascendant& Ascendant::operator=(const Ascendant &other) {
    if (this != &other) {
        Individual::operator=(other);
        hasEaten = other.hasEaten;
    }
    return *this;
}