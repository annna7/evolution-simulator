#pragma once

#include <ostream>
#include "Cell.h"

class Individual : public Cell {
public:
    Individual(int x, int y, int direction, int speed);
    Individual();
    Individual(const Individual &other);

    Individual(int x, int y);

    Individual& operator=(const Individual &other);
    ~Individual();
    friend std::ostream &operator<<(std::ostream &os, const Individual &individual);
    bool operator==(const Individual &rhs) const;
    void move();
    const sf::Shape *getShape() override;
    sf::Color getColor() override;

    int getPosition() const;

private:
    int x, y, speed, direction, health;
    const static int DEFAULT_SPEED = 1;
    const static int RESET_DIRECTION_SEED = 15;
    const static int LIFE_TIME = 100;
    const static int NUMBERS_OF_DIRECTIONS = 8;
};