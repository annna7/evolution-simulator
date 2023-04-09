#pragma once

#include <SFML/Graphics.hpp>
#include <ostream>

class Food {
public:
    Food(int x, int y);
    Food();
    Food(const Food &other);
    Food& operator=(const Food &other);
    ~Food();
    friend std::ostream &operator<<(std::ostream &os, const Food &food);
    void draw() const;

private:
    int x, y;

    const static int FOOD_SIZE = 5;
};