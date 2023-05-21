#include "Keystone.h"

Keystone::Keystone(int x, int y) : Individual(x, y) {}

sf::Color Keystone::getOwnColor() const {
    return sf::Color::Yellow;
}