#include "Keystone.h"

Keystone::Keystone(int x, int y) : Individual(x, y) {}

sf::Color Keystone::getColor() {
    return sf::Color::Yellow;
}