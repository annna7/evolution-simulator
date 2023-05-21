#include "Clairvoyant.h"

Clairvoyant::Clairvoyant(int x, int y) : Individual(x, y) {}
int Clairvoyant::getHunger() const { return 2; }
int Clairvoyant::getVision() const { return 5; }
sf::Color Clairvoyant::getOwnColor() const { return sf::Color::Blue; }
