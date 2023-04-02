#pragma once

#include <SFML/Graphics.hpp>
#include <ostream>

class Food {
public:
    Food(int x, int y);
    Food();
    Food(const Food &other);
    friend std::ostream &operator<<(std::ostream &os, const Food &food);
    friend class Game;

private:
    int x, y;
    int FOOD_SIZE = 5;
    void draw() const;
};