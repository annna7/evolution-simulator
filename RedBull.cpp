#include "RedBull.h"

RedBull::RedBull(int x, int y) : Individual(x, y) {}
int RedBull::getSpeed() const { return 5; }
int RedBull::getHunger() const { return 2; }
sf::Color RedBull::getOwnColor() const { return sf::Color::Red; }