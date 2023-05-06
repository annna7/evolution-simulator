#pragma once

#include <SFML/Graphics.hpp>
#include <ostream>
#include "Cell.h"

class Food : public Cell {
public:
    Food(int x, int y);
    Food();
    Food(const Food &other);
    Food& operator=(const Food &other);
    ~Food();
    friend std::ostream &operator<<(std::ostream &os, const Food &food);
    const sf::Shape *getShape() override;
    sf::Color getColor() override;

private:
    int x, y;
};